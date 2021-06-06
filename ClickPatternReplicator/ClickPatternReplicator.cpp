#include <iostream>
#include <string>
#include <vector>
#include "RecordPattern.h"
#include "SaveLoad.h"
int main(int argl, char *argv[])
{
	std::string cmd;
	std::vector<struct Click>pattern;
	std::cin >> cmd;
	struct Click* clicks = nullptr;
	std::string tmp;
	int delay;
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
		else if (cmd == "load")
		{
			std::cin >> tmp;
			LoadClickPattern(&clicks, tmp.c_str());
			for (size_t i = 0; clicks[i].button != 0; i++)
				pattern.push_back(clicks[i]);
		}
		else if (cmd == "play")
		{
			std::cin >> tmp;
			delay = std::stoi(tmp);
			for (size_t i = 0; clicks[i].button != 0; i++);
		}
		std::cin >> cmd;
	}
	return 0;
}