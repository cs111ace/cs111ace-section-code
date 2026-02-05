#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>
#include <iostream>


static const char *kPipeMessage = "Hello, this is being written to the write end of a pipe\n";

// NOTE: no printf called in this function, yet we still print out to the terminal
void dup2_example()
{
    int fds[2];
    pipe(fds);
    size_t bytesSent = strlen(kPipeMessage) + 1;
    dup2(STDOUT_FILENO, fds[1]); // should make it such that writing to pipe writes to STDOUT
    pid_t pidOrZero = fork();
    if (pidOrZero == 0)
    {
        // in the child
        write(fds[1], kPipeMessage, bytesSent);
        // close the write end since we're doing writing
        close(fds[1]);
        close(fds[0]);
    }
    // In the parent, we only write to the pipe (assume everything is written)
    close(fds[0]);
    write(fds[1], kPipeMessage, bytesSent); // program will still terminate
    close(fds[1]);
    waitpid(pidOrZero, NULL, 0);
}

int main(int argc, char *argv[])
{
    int selection;
    while (true)
    {
        std::cout << "\n--- Function Harness ---" << std::endl;
        std::cout << "1. Run pipe example" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> selection;

        switch (selection)
        {
        case 1:
            dup2_example();
            break;
        case 0:
            return 0;
        default:
            std::cout << "Invalid selection. Please try again." << std::endl;
            break;
        }
    }
    return 0;
}