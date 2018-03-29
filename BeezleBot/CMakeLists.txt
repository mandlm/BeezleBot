cmake_minimum_required(VERSION 3.5)

project(BeezleBot LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
	BeezleBot.cpp
)

target_compile_features(${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)

