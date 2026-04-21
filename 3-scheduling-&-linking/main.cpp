#include <iostream>
#include <unordered_map>
#include <map>
#include "library.cpp"
#include <thread>

int main()
{
	// hashamp that I initialized
	std::unordered_map<int, std::string> map{{1, "Fabio"}};

	// iterating through map
	for (auto elem : map)
	{
		std::cout << elem.first << std::endl;
	}

	std::thread t1(task, 1);
	std::thread t2(task, 2);
	return 0;
}
