#include <iostream>
#include <unordered_map>
#include <map>

int main()
{

	std::unordered_map<int, std::string> map{{1, "Fabio"}};
	for (auto elem : map)
	{
		std::cout << elem.first << std::endl;
	}
	return 0;
}
