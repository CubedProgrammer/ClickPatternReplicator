#include <iostream>
#include <vector>
#include "RecordPattern.h"
#include "SaveLoad.h"
int main(int argl, char *argv[])
{
	std::string cmd;
	std::vector<struct Click>pattern;
	std::cin >> cmd;
	struct Click* clicks;
	std::string tmp;
	while (cmd != "exit")
	{
		if (cmd == "record")
		{
			std::cin >> tmp;
			RecordPattern(&clicks);
			for (size_t i = 0; clicks[i].button != 0; i++)
				pattern.push_back(clicks[i]);
			SaveClickPattern(clicks, tmp.c_str());
		}
		std::cin >> cmd;
	}
	return 0;
}