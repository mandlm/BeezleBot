#pragma once

#include <string>
#include <set>

struct Settings
{
	std::string telegramToken;
	std::set<std::string> telegramUsers;

	std::string wikiUrl;
	std::string wikiUser;
	std::string wikiPassword;

	Settings(int argc, char **argv);
};
