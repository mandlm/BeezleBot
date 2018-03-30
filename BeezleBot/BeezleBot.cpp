#include "settings.h"

#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		Settings settings(argc, argv);

		std::cout << "token: " << settings.token << std::endl;
		std::cout << "users: " << std::flush;
		for (const auto &user : settings.users)
		{
			std::cout << user << " ";
		}
		std::cout << std::endl;
	}
	catch (std::runtime_error &e)
	{
		return EXIT_FAILURE;
	}

	std::cout << "BeezleBot running" << std::endl;

	return EXIT_SUCCESS;
}

