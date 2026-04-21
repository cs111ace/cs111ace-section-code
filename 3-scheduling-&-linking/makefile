CXX = "g++"
LINKER = "ld"
SOURCES := $(wildcard *.cpp)
OBJS := $(wildcard *.o)

all: compile link execute

compile:
	# the -c flag means that we *only* compile
	# in practice you let the compiler simply link
	$(CXX) $(SOURCES) -c

link:
	$(LINKER) \
	/usr/lib/x86_64-linux-gnu/crt1.o \
	/usr/lib/x86_64-linux-gnu/crti.o \
	main.o \
	/usr/lib/x86_64-linux-gnu/crtn.o \
	-L$$(dirname $$(gcc --print-file-name=libstdc++.so)) -lstdc++ -lgcc_s \
	-lc \
	-dynamic-linker /lib64/ld-linux-x86-64.so.2 \

execute:
	./a.out

clean:
	rm -rf *.out *.o