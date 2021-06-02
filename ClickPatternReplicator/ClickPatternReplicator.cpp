#include <iostream>
#include <vector>
#include "RecordPattern.h"
int main(int argl, char *argv[])
{
	std::string cmd;
	std::vector<struct Click>pattern;
	std::cin >> cmd;
	struct Click* clicks;
	while (cmd != "exit")
	{
		if (cmd == "record")
		{
			RecordPattern(&clicks);
			for (size_t i = 0; clicks[i].button != 0; i++)
				pattern.push_back(clicks[i]);
		}
		std::cin >> cmd;
	}
	return 0;
}