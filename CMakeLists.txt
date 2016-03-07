#First Try
cmake_minimum_required(VERSION 2.6)
project (ParkIt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(SFML 2 COMPONENTS graphics system window REQUIRED)
find_package(SFGUI 0.2.3 REQUIRED)

include_directories(include)

SET(bridge_SRCS 	
	src/main.cpp
	src/GameMap.cpp
	src/Display.cpp
	src/MovingObject.cpp
	include/GameMap.h
	include/Display.h
	include/MovingObject.h
)

add_executable(ParkIt ${bridge_SRCS})


if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(ParkIt ${SFML_LIBRARIES})
endif()

if(SFGUI_FOUND)
	include_directories(${SFGUI_INCLUDE_DIR})
	target_link_libraries(ParkIt ${SFGUI_LIBRARY})
endif()





