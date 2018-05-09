#include "settings.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

Settings::Settings(int argc, char **argv)
{
	namespace po = boost::program_options;

	std::vector<std::string> telegramUserList;

	po::options_description commandlineOptions("Allowed options");
	commandlineOptions.add_options()("help,h", "show this help message")(
		"config-file,f", po::value<std::string>(),
		"read options from config file")("telegram-token",
		po::value(&telegramToken)->required(),
		"Telegram bot token")("telegram-users",
		po::value(&telegramUserList)->multitoken()->required(),
		"allowed Telegram users")("wiki-url", po::value(&wikiUrl)->required(),
		"DokuWiki xml-rpc url")("wiki-username",
		po::value(&wikiUser)->required(),
		"DokuWiki xml-rpc username")("wiki-password",
		po::value(&wikiPassword)->required(), "DokuWiki xml-rpc password");

	po::variables_map configuredOptions;
	po::store(
		po::command_line_parser(argc, argv).options(commandlineOptions).run(),
		configuredOptions);

	if (configuredOptions.find("help") != configuredOptions.cend())
	{
		std::cout << commandlineOptions << std::endl;
		throw std::runtime_error("invalid options");
	}

	if (configuredOptions.find("config-file") != configuredOptions.cend())
	{
		std::ifstream configFile(
			configuredOptions["config-file"].as<std::string>());

		po::options_description fileOptions;
		fileOptions.add_options()("Telegram.token", po::value(&telegramToken))(
			"Telegram.users", po::value(&telegramUserList)->multitoken())(
			"DokuWiki.url", po::value(&wikiUrl)->required())(
			"DokuWiki.username", po::value(&wikiUser)->required())(
			"DokuWiki.password", po::value(&wikiPassword)->required());

		try
		{
			po::store(po::parse_config_file(configFile, fileOptions),
				configuredOptions);

			configuredOptions.insert(
				{"telegram-token", configuredOptions["Telegram.token"]});
			configuredOptions.insert(
				{"telegram-users", configuredOptions["Telegram.users"]});
			configuredOptions.insert(
				{"wiki-url", configuredOptions["DokuWiki.url"]});
			configuredOptions.insert(
				{"wiki-username", configuredOptions["DokuWiki.username"]});
			configuredOptions.insert(
				{"wiki-password", configuredOptions["DokuWiki.password"]});
		}
		catch (po::unknown_option &e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			throw std::runtime_error("invalid options");
		}
	}

	try
	{
		po::notify(configuredOptions);

		telegramUsers.insert(telegramUserList.begin(), telegramUserList.end());
	}
	catch (po::required_option &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << commandlineOptions << std::endl;
		throw std::runtime_error("invalid options");
	}
}
