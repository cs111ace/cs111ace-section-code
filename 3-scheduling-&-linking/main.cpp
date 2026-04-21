#include <iostream>
#include <unordered_map>
#include <map>

int main()
{

	std::unordered_map<int, std::string> map{};
	for (auto elem : map)
	{
		std::cout << elem << std::endl;
	}
	return 0;
}
