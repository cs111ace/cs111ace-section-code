#include <iostream>
#include <unordered_map>
#include <map>
#include "library.cpp"

int main()
{
	// hashamp that I initialized
	std::unordered_map<int, std::string> map{{1, "Fabio"}};

	// iterating through map
	for (auto elem : map)
	{
		std::cout << elem.first << std::endl;
	}

	task(2);
	return 0;
}
