# Inter-Process Communication

This directory contains C++ programs demonstrating concepts of inter-process communication using pipes.

## How to Build

To compile the programs, you can use the provided `Makefile`. Open your terminal and run:

```bash
make
```

This will compile `stall.cpp` and `reroute.cpp` into executables named `stall` and `reroute` in the current directory.

To clean up the compiled files, you can run:

```bash
make clean
```
## How to Run

Once compiled, you can run the programs directly from your terminal:

- To run the `stall` program, which demonstrates various pipe behaviors and potential deadlocks:
  ```bash
  ./stall
  ```
  You will be presented with a menu to choose which function to run.

- To run the `reroute` program, which demonstrates file descriptor redirection:
  ```bash
  ./reroute
  ```

## Activity: Find, Fix, and Describe the Bug

Your task is to identify and fix a bug in the `stall` program that causes it to hang indefinitely.

### 1. Find the Bug

First, run the `stall` program and select **option 4** (`reader_hangs_open_fd`).

```bash
./stall
```

You will notice that the program prints the first message from the child but then hangs, never printing the final line or exiting. Your goal is to figure out why.

Read through the code for the `reader_hangs_open_fd` function in `stall.cpp`. Ask yourself the following questions to guide your investigation:

- The child process successfully reads the message from the parent once. Why does it get stuck on the *second* `read` call?
- What is the expected behavior of `read` on a pipe when there is no more data to be read? When does it return 0 (signaling End-Of-File, or EOF)?
- For a `read` call on a pipe to return 0, what must be true about all file descriptors pointing to the **write-end** of that pipe?

### 2. Fix the Bug

Once you believe you have found the issue, modify the code in `stall.cpp` to fix it. A comment in the code already hints at the solution. After applying the fix, re-compile the program using `make` and run option 4 again. If the program now prints both messages and exits cleanly, you have fixed it!

### 3. Describe the Bug

In your own words, answer the following:

- **What was the bug?** Why did the child process hang on the second `read` call instead of detecting the end-of-file?
- **Why did the fix work?** Explain how your change allowed the child process to correctly identify that the parent had closed its end of the pipe and no more data was coming.
