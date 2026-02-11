/*
 * ppong.cpp -- Process Pong Launcher
 * -----------------------------------
 * Original author: Trip Master, with modifications by Fabio Ibanez.
 *
 * Your task: launch two player processes and connect them with pipes so they
 * can rally back and forth. The provided `player` executable communicates
 * entirely through stdin (reads opponent's shot) and stdout (writes own shot).
 *
 * Architecture (2 pipes, 2 children):
 *
 *   Player 1 stdout ──[pipe1]──> Player 2 stdin
 *   Player 2 stdout ──[pipe2]──> Player 1 stdin
 */

#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

int main()
{
    // TODO: Create two pipes: p1_to_p2 and p2_to_p1.

    // TODO: Fork Player 1.
    //   - Use dup2 to connect p1_to_p2's write end to STDOUT_FILENO.
    //   - Use dup2 to connect p2_to_p1's read end to STDIN_FILENO.
    //   - Close ALL four original pipe FDs (both pipes, both ends).
    //   - Call execvp to run "./player" with arguments "1" and "0.8".

    // TODO: Fork Player 2.
    //   - Use dup2 to connect p1_to_p2's read end to STDIN_FILENO.
    //   - Use dup2 to connect p2_to_p1's write end to STDOUT_FILENO.
    //   - Close ALL four original pipe FDs (both pipes, both ends).
    //   - Call execvp to run "./player" with arguments "2" and "0.8".

    // TODO: Close all pipe FDs in the parent (the parent doesn't use them).

    // TODO: Wait for both children to finish.

    return 0;
}
