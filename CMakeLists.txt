cmake_minimum_required(VERSION "3.7.1")
project("BruteFEngine")

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC
		    "include/*.h"
			"src/*.cpp"
)

add_executable(EngineTest ${SRC})

#install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
