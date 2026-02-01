/**
 * @file many-writes.cc
 *
 * @brief This program demonstrates the use of file descriptors and multiprocessing.
 * It creates a file and writes to it from both a parent and child process.
 *
 * @author Fabio Ibanez
 * Contact: fabioi@stanford.edu
 *
 */

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> // for waitpid
#include <cstdio>

#define OPEN_BEFORE_FORK 1

/** Write to a file many times.
 *
 * Writes the string `label` to the file `fd` 1000 times.
 *
 * @param fd file descriptor
 * @param label string to write to the file
 */
void write_to_file_many_times(int fd, const char *label)
{
    for (int i = 0; i < 1000; i++)
    {
        char msg[100];
        int len = snprintf(msg, sizeof(msg), "%s: line %d\n", label, i);

        write(fd, msg, len);
    }
}

/** Main function.
 *
 * Creates a file and writes to it from both a parent and child process.
 *
 * @return 0 on success
 */
int main()
{
#if OPEN_BEFORE_FORK
    int fd = open("out/race_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("Opened in parent, fd=%d\n", fd);
#endif
    auto pidOrZero = fork();

    if (pidOrZero == 0)
    {
#if !OPEN_BEFORE_FORK
        int fd = open("out/race_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        printf("Opened in child, fd=%d\n", fd);
#endif
        write_to_file_many_times(fd, "CHILD");
        close(fd);
    }
    else
    {
#if !OPEN_BEFORE_FORK
        int fd = open("out/race_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        printf("Opened in parent, fd=%d\n", fd);
#endif
        // Parent
        write_to_file_many_times(fd, "PARENT");
        waitpid(pidOrZero, nullptr, 0);
        close(fd);
    }

    return 0;
}