CXX = "g++"
LINKER = "ld"
SOURCES := $(wildcard *.cpp)
OBJS := $(wildcard *.o)

all: compile link execute

# the -c flag means that we *only* compile
# in practice you let the compiler simply link
compile:
	$(CXX) $(SOURCES) -c

link:
	@echo "==> Linking with crt1/crti/main.o/crtn + libstdc++, libgcc_s, libc"
	@echo "    Dynamic linker: /lib64/ld-linux-x86-64.so.2"
	@$(LINKER) \
	  /usr/lib/x86_64-linux-gnu/crt1.o \
	  /usr/lib/x86_64-linux-gnu/crti.o \
	  main.o \
	  /usr/lib/x86_64-linux-gnu/crtn.o \
	  -L$$(dirname $$(gcc --print-file-name=libstdc++.so)) -lstdc++ -lgcc_s \
	  -lc \
	  -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
	  -o out
	@echo "==> Link complete. Run with ./out"

execute:
	./a.out

clean:
	rm -rf *.out *.o