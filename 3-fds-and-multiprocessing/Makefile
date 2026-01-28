CXX = g++
CXXFLAGS = -std=c++17

all: $(wildcard *.cpp)
	mkdir -p out
	$(foreach file, $(wildcard *.cpp), $(CXX) $(CXXFLAGS) -o $(basename $(file)) $(file);)

clean:
	rm -rf out
	rm -f $(wildcard *.exe)