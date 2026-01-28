#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define OPEN_BEFORE_FORK 0

void write_to_file_many_times(int fd, std::string label)
{
    for (int i = 0; i < 1000; i++)
    {
        std::string msg = label + ": line " + std::to_string(i) + "\n";

        write(fd, msg.c_str(), msg.length());
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
        std::cout << "Opened in child, fd=" << fd << std::endl;
#endif
        write_to_file_many_times(fd, "CHILD");
        close(fd);
    }
    else
    {
#if !OPEN_BEFORE_FORK
        int fd = open("out/race_output.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        std::cout << "Opened in parent, fd=" << fd << std::endl;
#endif
        // Parent
        write_to_file_many_times(fd, "PARENT");
        waitpid(pid, nullptr, 0);
        close(fd);
    }

    return 0;
}