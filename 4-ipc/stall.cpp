#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>
#include <iostream>


static const char *kPipeMessage = "Hello, this message is coming through a pipe.";

void vanilla_fork() {
    int fds[2];

    pid_t pidOrZero = fork();
    // pipe(fds);
    if (pidOrZero == 0) {
        // CHILD
        pipe(fds);
        printf("Child: fds[0] = %d, fds[1] = %d\n", fds[0], fds[1]);
        exit(0); // what happens if you get rid of this?
    }
    // PARENT
    pipe(fds);
    printf("Parent: fds[0] = %d, fds[1] = %d\n", fds[0], fds[1]);
    waitpid(pidOrZero, NULL, 0);
}

// Lecture code from CS111 at Stanford University lecture 11, slide 33 Winter 2026
void pipe_example()
{

    int fds[2];
    pipe(fds);
    size_t bytesSent = strlen(kPipeMessage) + 1;
    pid_t pidOrZero = fork();
    if (pidOrZero == 0)
    { // In the child, we only read from the pipe
        close(fds[1]);
        char buffer[bytesSent];
        int bytesRead = read(fds[0], buffer, sizeof(buffer));
        printf("Child read %d bytes from pipe.\n", bytesRead);
        bytesRead = read(fds[0], buffer, sizeof(buffer));
        close(fds[0]);
        printf("Message from parent: %s\n", buffer);
        exit(0);
    }
    // In the parent, we only write to the pipe (assume everything is written)
    close(fds[0]);
    write(fds[1], kPipeMessage, bytesSent); // program will still terminate
    close(fds[1]);
    waitpid(pidOrZero, NULL, 0);
}


// Lecture code from CS111 at Stanford University lecture 11, slide 33 Winter 2026
void parent_doesnt_close()
{
    int fds[2];
    pipe(fds);
    size_t bytesSent = strlen(kPipeMessage) + 1;
    pid_t pidOrZero = fork();
    if (pidOrZero == 0)
    { // In the child, we only read from the pipe
        close(fds[1]);
        char buffer[bytesSent];
        int bytesRead = read(fds[0], buffer, sizeof(buffer));
        printf("Child read %d bytes from pipe.\n", bytesRead);
        bytesRead = read(fds[0], buffer, sizeof(buffer));
        close(fds[0]);
        printf("Message from parent: %s\n", buffer);
        exit(0);
    }
    // In the parent, we only write to the pipe (assume everything is written)
    close(fds[0]);
    write(fds[1], kPipeMessage, bytesSent); // program will still terminate
    // close(fds[1]);
    waitpid(pidOrZero, NULL, 0);
}

void pipe_waitpid_example()
{
    int fds[2];
    pipe(fds);
    size_t bytesSent = strlen(kPipeMessage) + 1;
    pid_t pidOrZero = fork();
    if (pidOrZero == 0)
    { // In the child, we only read from the pipe
        close(fds[1]);
        char buffer[bytesSent];
        printf("Child is waiting for message from parent...\n");
        int bytesRead = read(fds[0], buffer, sizeof(buffer));
        printf("Child read %d bytes from pipe.\n", bytesRead);
        bytesRead = read(fds[0], buffer, sizeof(buffer));
        close(fds[0]);
        printf("Message from parent: %s\n", buffer);
        exit(0);
    }
    // In the parent, we only write to the pipe (assume everything is written)
    close(fds[0]);
    // This will cause a deadlock! The parent waits for the child to finish,
    // but the child is waiting for the parent to write to the pipe.
    waitpid(pidOrZero, NULL, 0);
    printf("Parent is writing to pipe...\n");
    write(fds[1], kPipeMessage, bytesSent);
    close(fds[1]);
}

// TODO: why is this stalling?
void reader_hangs_open_fd()
{
    int fds[2];
    pipe(fds);
    size_t bytesSent = strlen(kPipeMessage) + 1;
    pid_t pidOrZero = fork();

    if (pidOrZero == 0)
    {
        char buffer[bytesSent];
        read(fds[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        printf("Child is trying to read again (expecting EOF)...\n");

        int bytesRead = read(fds[0], buffer, sizeof(buffer));

        printf("This line will never print. Read returned %d\n", bytesRead);
        exit(0);
    }
    close(fds[0]);
    write(fds[1], kPipeMessage, bytesSent);
    close(fds[1]); // Parent closes their write end
    waitpid(pidOrZero, NULL, 0);
}

int main(int argc, char *argv[])
{
    int selection;
    while (true)
    {
        std::cout << "\n--- Function Harness ---" << std::endl;
        std::cout << "1. Run vanilla_fork example" << std::endl;
        std::cout << "2. Run pipe example" << std::endl;
        std::cout << "3. Run parent_doesnt_close example" << std::endl;
        std::cout << "4. Run pipe_waitpid_example" << std::endl;
        std::cout << "5. reader_hangs_open_fd" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> selection;

        switch (selection)
        {
        case 1:
            vanilla_fork();
            break;
        case 2:
            pipe_example();
            break;
        case 3:
            parent_doesnt_close();
            break;
        case 4:
            pipe_waitpid_example();
            break;
        case 5:
            reader_hangs_open_fd();
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