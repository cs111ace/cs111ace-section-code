/*
 * ppong.cpp -- Process Pong Launcher
 * -----------------------------------
 * Solution author: Fabio Ibanez.
 *
 * Your task: launch two player processes and connect them with pipes so they
 * can rally back and forth. The provided `player` executable communicates
 * entirely through stdin (reads opponent's shot) and stdout (writes own shot).
 *
 * Architecture (2 pipes, 2 children):
 *
 *   Player 1 stdout ──[pipe1]──> Player 2 stdin
 *   Player 2 stdout ──[pipe2]──> Player 1 stdin
 *
 * Steps:
 *   1. Create two pipes (p1_to_p2 and p2_to_p1).
 *   2. Fork Player 1:
 *        - dup2 so its STDOUT writes into p1_to_p2
 *        - dup2 so its STDIN  reads  from p2_to_p1
 *        - Close all original pipe FDs
 *        - execvp("./player", ...) with args: "1" and "0.8"
 *   3. Fork Player 2:
 *        - dup2 so its STDIN  reads  from p1_to_p2
 *        - dup2 so its STDOUT writes into p2_to_p1
 *        - Close all original pipe FDs
 *        - execvp("./player", ...) with args: "2" and "0.8"
 *   4. In the parent: close all pipe FDs, then wait for both children.
 */

#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

int main()
{
    // TODO: Create two pipes: p1_to_p2 and p2_to_p1.
    int p1_to_p2[2];
    pipe(p1_to_p2);
    int p2_to_p1[2];
    pipe(p2_to_p1);

    // TODO: Fork Player 1.
    //   - Use dup2 to connect p1_to_p2's write end to STDOUT_FILENO.
    //   - Use dup2 to connect p2_to_p1's read end to STDIN_FILENO.
    //   - Close ALL four original pipe FDs (both pipes, both ends).
    //   - Call execvp to run "./player" with arguments "1" and "0.8".
    int p1_pid = fork();
    if (p1_pid == 0)
    {
        // you are in p1
        dup2(p1_to_p2[1], STDOUT_FILENO);
        dup2(p2_to_p1[0], STDIN_FILENO);

        close(p1_to_p2[0]);
        close(p1_to_p2[1]);
        close(p2_to_p1[0]);
        close(p2_to_p1[1]);
        char *argv[] = {(char *)"./player", (char *)"1", (char *)"0.8", NULL};
        execvp(argv[0], argv);
    }

    // TODO: Fork Player 2.
    //   - Use dup2 to connect p1_to_p2's read end to STDIN_FILENO.
    //   - Use dup2 to connect p2_to_p1's write end to STDOUT_FILENO.
    //   - Close ALL four original pipe FDs (both pipes, both ends).
    //   - Call execvp to run "./player" with arguments "2" and "0.8".
    int p2_pid = fork();
    if (p2_pid == 0)
    {
        dup2(p1_to_p2[0], STDIN_FILENO);
        dup2(p2_to_p1[1], STDOUT_FILENO);

        close(p1_to_p2[0]);
        close(p1_to_p2[1]);
        close(p2_to_p1[0]);
        close(p2_to_p1[1]);

        char *argv[] = {(char *)"./player", (char *)"2", (char *)"0.8", NULL};
        execvp(argv[0], argv);
    }

    // TODO: Close all pipe FDs in the parent (the parent doesn't use them).
    close(p1_to_p2[0]);
    close(p1_to_p2[1]);
    close(p2_to_p1[0]);
    close(p2_to_p1[1]);

    // TODO: Wait for both children to finish.
    while (waitpid(-1, NULL, 0) != -1)
    {
        /* loop */
    }

    return 0;
}
