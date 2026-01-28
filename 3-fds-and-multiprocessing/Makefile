CXX = g++
CXXFLAGS = -std=c++17

all: $(wildcard *.cpp)
	$(foreach file, $(wildcard *.cpp), $(CXX) $(CXXFLAGS) -o $(basename $(file)) $(file);)

clean:
	rm -f $(wildcard *.exe)