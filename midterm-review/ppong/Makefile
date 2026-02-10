CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: player ppong ppong_soln

player: player.cpp
	$(CXX) $(CXXFLAGS) -o player player.cpp

ppong: ppong.cpp
	$(CXX) $(CXXFLAGS) -o ppong ppong.cpp

ppong_soln: ppong_soln.cpp
	$(CXX) $(CXXFLAGS) -o ppong_soln ppong_soln.cpp

clean:
	rm -f player ppong ppong_soln
