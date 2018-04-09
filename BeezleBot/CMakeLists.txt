cmake_minimum_required(VERSION 3.6)

project(BeezleBot LANGUAGES CXX)

find_package(Boost 1.55.0 COMPONENTS program_options REQUIRED)

add_executable(${PROJECT_NAME} 
	BeezleBot.cpp
	settings.cpp
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE 
		Boost::program_options
		xxtelebot
		DokuWiki
)

