CXX = g++
CXXFLAGS = -std=c++17

all: $(wildcard *.c*)
	$(foreach file, $(wildcard *.c*), $(CXX) $(CXXFLAGS) -o $(basename $(file)) $(file);)

clean:
	rm -f $(wildcard *.exe)