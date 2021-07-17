#include "windows.h"
#include <iostream>
#include <string>
#include <vector>
#include "RecordPattern.h"
#include "SaveLoad.h"
int main(int argl, char *argv[])
{
	std::string cmd;
	std::cin >> cmd;
	struct Click* clicks = nullptr;
	std::string tmp;
	int delay;
	INPUT mi[2];
	mi[0].type = INPUT_MOUSE;
	mi[1].type = INPUT_MOUSE;
	auto& [press, release] = mi;
	press.mi.time = release.mi.time = 0;
	press.mi.mouseData = release.mi.mouseData = 0;
	press.mi.dx = press.mi.dy = release.mi.dx = release.mi.dy = 0;
	while (cmd != "exit")
	{
		if (cmd == "help")
		{
			std::cout << "record *filename* to record and save to a file\n";
			std::cout << "load *filename* to load a recorded pattern\n";
			std::cout << "play *delay* to play the loaded pattern after some time." << std::endl;
		}
		else if (cmd == "record")
		{
			std::cin >> tmp;
			RecordPattern(&clicks);
			std::cout << "Recorded pattern." << std::endl;
			SaveClickPattern(clicks, tmp.c_str());
			std::cout << "Saved pattern." << std::endl;
		}
		else if (cmd == "load")
		{
			std::cin >> tmp;
			LoadClickPattern(&clicks, tmp.c_str());
			std::cout << "Loaded pattern." << std::endl;
		}
		else if (cmd == "play")
		{
			std::cin >> tmp;
			delay = std::stoi(tmp);
			Sleep(delay * 1000);
			for (size_t i = 0; clicks[i].button != 0; i++)
			{
				SetCursorPos(clicks[i].x, clicks[i].y);
				switch (clicks[i].button)
				{
					case LBUTTON:
						press.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
						release.mi.dwFlags = MOUSEEVENTF_LEFTUP;
						break;
					case MBUTTON:
						press.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
						release.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
						break;
					case RBUTTON:
						press.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
						release.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
						break;
				}
				SendInput(2, mi, sizeof(mi[0]));
				Sleep(100);
			}
		}
		std::cin >> cmd;
	}
	return 0;
}