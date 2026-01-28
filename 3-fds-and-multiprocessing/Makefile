CXX = g++
CXXFLAGS = -std=c++17

all: many-writes.cpp fork.cpp
	$(CXX) $(CXXFLAGS) -o many-writes many-writes.cpp
	$(CXX) $(CXXFLAGS) -o fork fork.cpp

clean:
	rm -f many-writes fork