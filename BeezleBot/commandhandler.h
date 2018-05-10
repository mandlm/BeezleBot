#pragma once

#include "settings.h"
#include "dokuwiki.h"
#include "tgbot/bot.h"

class CommandHandler
{
private:
	Settings m_settings;
	DokuWiki m_wiki;

public:
	CommandHandler(const Settings &settings);

	void handle(const tgbot::types::Message &message, const tgbot::methods::Api &api);
};
