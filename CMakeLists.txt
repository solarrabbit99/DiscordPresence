cmake_minimum_required(VERSION 3.10)

project(DiscordPresence VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
add_subdirectory(include/discord)
file(GLOB LIBRARIES "lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

# add the executable
add_executable(${PROJECT_NAME} src/main.cpp src/presence.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES} discord_libs)