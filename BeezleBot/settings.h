#pragma once

#include <string>
#include <vector>

struct Settings
{
	std::string token;
	std::vector<std::string> users;

	Settings(int argc, char **argv);	
};

