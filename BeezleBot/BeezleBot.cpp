#include "settings.h"
#include "tgbot/bot.h"
#include "dokuwiki.h"

#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
	try
	{
		Settings settings(argc, argv);

		DokuWiki wiki(settings.wikiUrl + "/lib/exe/xmlrpc.php", 
				settings.wikiUser, settings.wikiPassword);

		tgbot::LongPollBot bot(settings.telegramToken);
		bot.callback([&wiki, &settings](const tgbot::types::Message message,
		                                const tgbot::methods::Api &api) 
		{
			if (message.text != nullptr && message.from != nullptr
			    && message.from->username != nullptr)
			{
				if (settings.telegramUsers.find(*message.from->username)
				    == settings.telegramUsers.end())
				{
					api.sendMessage(std::to_string(message.chat.id), "Unknown user!");
				}
				else
				{
					std::ostringstream logMessage;
					logMessage << message.from->firstName << " (" << *message.from->username << ")"
					           << ":\\\\ " << *message.text;
					api.getLogger().info(logMessage.str());

					std::ostringstream wikiMessage;
					wikiMessage << "\n" << logMessage.str() << "\n";
					try
					{
						wiki.appendToPage("beezletest", wikiMessage.str());
					}
					catch (std::runtime_error &e)
					{
						std::ostringstream reply;
						reply << "Error writing to wiki: " << e.what();
						api.getLogger().error(reply.str());
						api.sendMessage(std::to_string(message.chat.id), reply.str());
					}

					std::ostringstream pageUrl;
					pageUrl << settings.wikiUrl << "/doku.php?id=" << "beezletest";
					api.sendMessage(std::to_string(message.chat.id), 
							"Stored to wiki at " + pageUrl.str());
				}
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
