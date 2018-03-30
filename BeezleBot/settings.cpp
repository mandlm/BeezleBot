#include "settings.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

Settings::Settings(int argc, char **argv)
{
	namespace po = boost::program_options;

	po::options_description commandlineOptions("Allowed options");
	commandlineOptions.add_options()
		("help,h", "show this help message")
		("config-file,f", po::value<std::string>(), "read options from config file")
		("token,t", po::value<std::string>(&token)->required(), "Telegram bot token")
		("users,u", po::value<std::vector<std::string>>(&users)->multitoken()->required(), "allowed Telegram users")
	;

	po::variables_map configuredOptions;
	po::store(po::command_line_parser(argc, argv).options(commandlineOptions).run(), 
			configuredOptions);

	if (configuredOptions.find("help") != configuredOptions.cend())
	{
		std::cout << commandlineOptions << std::endl;
		throw std::runtime_error("invalid options");
	}

	if (configuredOptions.find("config-file") != configuredOptions.cend())
	{
		std::ifstream configFile(configuredOptions["config-file"].as<std::string>());

		po::options_description fileOptions;
		fileOptions.add_options()
			("token", po::value<std::string>(&token))
			("users", po::value<std::vector<std::string>>(&users)->multitoken())
		;

		try
		{
			po::store(po::parse_config_file(configFile, fileOptions), configuredOptions);
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
	}
	catch (po::required_option &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		std::cout << commandlineOptions << std::endl;
		throw std::runtime_error("invalid options");
	}
}
