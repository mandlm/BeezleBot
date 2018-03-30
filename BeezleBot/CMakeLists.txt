cmake_minimum_required(VERSION 3.5)

project(BeezleBot LANGUAGES CXX)

find_package(Boost 1.60.0 COMPONENTS program_options REQUIRED)

add_executable(${PROJECT_NAME} 
	BeezleBot.cpp
	settings.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE 
		Boost::program_options
		tgbot
		DokuWiki
)

target_compile_features(${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)

