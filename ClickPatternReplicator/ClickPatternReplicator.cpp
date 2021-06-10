#include "windows.h"
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
	INPUT mi[2];
	mi[0].type = INPUT_MOUSE;
	mi[1].type = INPUT_MOUSE;
	auto& [press, release] = mi;
	press.mi.time = release.mi.time = 0;
	press.mi.mouseData = release.mi.mouseData = 0;
	press.mi.dx = press.mi.dy = release.mi.dx = release.mi.dy = 0;
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
				default:
					break;
				}
				SendInput(2, mi, sizeof(mi[0]));
			}
		}
		std::cin >> cmd;
	}
	return 0;
}