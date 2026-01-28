#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

void spawn_child()
{
  auto pid = fork();
  if (pid == 0)
  {
    std::cout << "I am the child process" << std::endl;
  }
  else
  {
    std::cout << "I am the parent process" << std::endl;
  }
}

void spawn_and_wait_for_child()
{
  auto pid = fork();
  std::cout << "Hi from the "
            << (pid == 0 ? "child" : "parent")
            << " pid: "
            << pid
            << std::endl;

  int status;
  if (pid == 0)
    waitpid(-1, &status, 0);
}

int main()
{
  spawn_and_wait_for_child();
  return 0;
}
