CXX = g++
CXXFLAGS = -std=c++17

all: $(wildcard *.c*)
	mkdir -p out
	$(foreach file, $(wildcard *.c*), $(CXX) $(CXXFLAGS) -o $(basename $(file)) $(file);)

clean:
	rm -rf out
	rm -f $(wildcard *.exe)