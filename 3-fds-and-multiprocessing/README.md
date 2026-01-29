# File descriptors and Multiprocessing

## How to run programs
To build and run the code in this directory, run the following commands in your terminal:

```bash
# Compile all C/C++ files using the provided Makefile
make

# To run the "fork" example:
./fork

# To run the "many-writes" example:
./many-writes
```

If you want to clean up the compiled files and output, run:
```bash
make clean
```

## Background
### Preprocessor directives
Preprocessor directives are special instructions handled by the C/C++ preprocessor before the actual compilation of code begins. They begin with a `#` symbol, such as `#define` and `#ifdef`.

In the `many-writes.cc` example, you'll notice `#define OPEN_BEFORE_FORK 0` at the top of the file. This line defines a named constant (`OPEN_BEFORE_FORK`) that can be used to conditionally compile or exclude sections of code.

## What you should do
1. run the `many-writes` program with the `OPEN_BEFORE_FORK` preprocessor macro set to `0` and then with `1`.
Is there a difference? You should look into the `out/race_output.txt` file that gets generated.
> 💡 **Hint:** In the `out/race_output.txt` file, try searching for the lines `PARENT: line 999` and `CHILD: line 999`. See where they appear and what lines are printed before and after them.

2. Is there something that is just **wrong** about the output that you are seeing in `out/race_output.txt`, if so 
why might that be?