/**
 * @file fork.cc
 *
 * @brief This program demonstrates the use of fork.
 *
 * @author Fabio Ibanez
 * Contact: fabioi@stanford.edu
 *
 */

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/** Spawn a child process.
 *
 * Spawns a child process and prints a message from the child or parent process.
 *
 * @return void
 */
void spawn_child()
{
  auto pidOrZero = fork();
  if (pidOrZero == 0)
  {
    printf("I am the child process\n");
  }
  else
  {
    printf("I am the parent process\n");
  }
}

/** Spawn a child process and wait for it to finish.
 *
 * Spawns a child process and waits for it to finish before printing a message from the parent process.
 *
 * @return void
 */
void spawn_and_wait_for_child()
{
  auto pidOrZero = fork();
  printf("Hi from the %s pid: %d\n", (pidOrZero == 0 ? "child" : "parent"), pidOrZero);

  int status;
  if (pidOrZero == 0)
    waitpid(-1, &status, 0);
}

int main()
{
  spawn_and_wait_for_child();
  return 0;
}
