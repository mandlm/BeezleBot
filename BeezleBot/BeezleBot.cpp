#include "settings.h"
#include "tgbot/bot.h"

#include <iostream>
#include <sstream>

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

		tgbot::LongPollBot bot(settings.token);
		bot.callback([] (const tgbot::types::Message message, const tgbot::methods::Api &api)
		{
			if (message.text != nullptr && message.from != nullptr)
			{
				std::ostringstream logMessage;
				logMessage << message.from->firstName;

				if (message.from->username != nullptr)
				{	
					logMessage << " (" << *message.from->username << ")";
				}
				
				logMessage << ": " << *message.text;
				api.getLogger().info(logMessage.str());
			}
		});
		bot.start();
	}
	catch (std::runtime_error &e)
	{
		return EXIT_FAILURE;
	}

	std::cout << "BeezleBot running" << std::endl;

	return EXIT_SUCCESS;
}

