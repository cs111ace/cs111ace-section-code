#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

void spawn_child()
{
  auto pid = fork();
  if (pid == 0)
  {
    printf("I am the child process\n");
  }
  else
  {
    printf("I am the parent process\n");
  }
}

void spawn_and_wait_for_child()
{
  auto pid = fork();
  printf("Hi from the %s pid: %d\n", (pid == 0 ? "child" : "parent"), pid);

  int status;
  if (pid == 0)
    waitpid(-1, &status, 0);
}

int main()
{
  spawn_and_wait_for_child();
  return 0;
}
