#include "commandhandler.h"

#include <sstream>

using tgbot::methods::Api;
using tgbot::types::Message;

CommandHandler::CommandHandler(const Settings &settings)
	: m_settings(settings), m_wiki(settings.wikiUrl + "/lib/exe/xmlrpc.php",
								settings.wikiUser, settings.wikiPassword)
{
}

void CommandHandler::handle(
	const tgbot::types::Message &message, const tgbot::methods::Api &api)
{
	if (message.text == nullptr || message.from == nullptr
		|| message.from->username == nullptr)
	{
		return;
	}

	if (m_settings.telegramUsers.find(*message.from->username)
		== m_settings.telegramUsers.end())
	{
		api.sendMessage(std::to_string(message.chat.id), "Unknown user!");

		return;
	}

	std::ostringstream logMessage;
	logMessage << message.from->firstName << " (" << *message.from->username
			   << ")"
			   << ":\\\\ " << *message.text;
	api.getLogger().info(logMessage.str());

	std::ostringstream wikiMessage;
	wikiMessage << "\n" << logMessage.str() << "\n";
	try
	{
		m_wiki.appendToPage("beezletest", wikiMessage.str());

		std::ostringstream pageUrl;
		pageUrl << m_settings.wikiUrl << "/doku.php?id="
				<< "beezletest";
		api.sendMessage(std::to_string(message.chat.id),
			"Stored to wiki at " + pageUrl.str());
	}
	catch (std::runtime_error &e)
	{
		std::ostringstream reply;
		reply << "Error writing to wiki: " << e.what();
		api.getLogger().error(reply.str());
		api.sendMessage(std::to_string(message.chat.id), reply.str());
	}
}
