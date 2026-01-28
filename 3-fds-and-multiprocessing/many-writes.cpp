#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

#define OPEN_BEFORE_FORK 0

void write_to_file_many_times(int fd, const char *label)
{
    for (int i = 0; i < 1000; i++)
    {
        char msg[100];
        printf(msg, "%s: line %d\n", label, i);

        write(fd, msg, sizeof(msg));
    }
}

int main()
{
#ifdef OPEN_BEFORE_FORK
    int fd = open("out/race_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
#endif
    auto pid = fork();

    if (pid == 0)
    {
#if !OPEN_BEFORE_FORK
        int fd = open("out/race_output.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        printf("Opened in child, fd=%d\n", fd);
#endif
        write_to_file_many_times(fd, "CHILD");
        close(fd);
    }
    else
    {
#if !OPEN_BEFORE_FORK
        int fd = open("out/race_output.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        printf("Opened in parent, fd=%d\n", fd);
#endif
        // Parent
        write_to_file_many_times(fd, "PARENT");
        waitpid(pid, nullptr, 0);
        close(fd);
    }

    return 0;
}