cmake_minimum_required(VERSION 3.10.2)
project(WebMin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

add_executable(WebMin main.cpp SocketFD.cpp SocketFD.h util.h Mime.cpp Mime.h Data.h ErrorPage.cpp ErrorPage.h Server.cpp Server.h Data.cpp util.cpp)