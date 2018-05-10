#include "settings.h"
#include "commandhandler.h"
#include "tgbot/bot.h"
#include "dokuwiki.h"

#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
	try
	{
		Settings settings(argc, argv);

		CommandHandler commandHandler(settings);

		tgbot::LongPollBot bot(settings.telegramToken);

		bot.callback(tgbot::utils::whenStarts,
			[](const tgbot::types::Message message,
				const tgbot::methods::Api &api,
				const std::vector<std::string> args) {
				api.sendMessage(std::to_string(message.chat.id), "pong");
			},
			"/ping");

		bot.callback(tgbot::utils::whenStarts,
			[](const tgbot::types::Message message,
				const tgbot::methods::Api &api,
				const std::vector<std::string> args) {
				api.sendMessage(std::to_string(message.chat.id),
					"Bot commands:\n"
					"/ping \tsend life-sign\n"
					"/help \tshow this message");
			},
			"/help");

		bot.callback([&commandHandler](const tgbot::types::Message message,
						 const tgbot::methods::Api &api) {
			commandHandler.handle(message, api);
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
