cmake_minimum_required(VERSION 3.25)

project(MyDiscord)

set(CMAKE_CXX_STANDARD 20)

set(SERVER_SOURCE_DIR "${PROJECT_SOURCE_DIR}/Server/src")
set(SERVER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Server/include")

set(CLIENT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/Client/src")
set(CLIENT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Client/include")

set(SHARED_DIR "${PROJECT_SOURCE_DIR}/Shared")

SET(SERVER_SOURCES
        "${SERVER_SOURCE_DIR}/VoiceServer.cpp"
        "${SERVER_SOURCE_DIR}/main.cpp")

SET(SERVER_INCLUDES
        "${SERVER_INCLUDE_DIR}/VoiceServer.hpp")

SET(CLIENT_SOURCES
        "${CLIENT_SOURCE_DIR}/VoiceClient.cpp"
        "${CLIENT_SOURCE_DIR}/main.cpp")

SET(CLIENT_INCLUDES
        "${CLIENT_INCLUDE_DIR}/VoiceClient.hpp")

SET(SHARED_INCLUDES
        "${SHARED_DIR}/Messages.hpp")

include_directories(Networking)
link_directories(Networking)
add_subdirectory(Networking)
add_executable(MyServer ${SERVER_SOURCES} ${SERVER_INCLUDES} ${SHARED_INCLUDES})
add_executable(MyClient ${CLIENT_SOURCES} ${CLIENT_INCLUDES} ${SHARED_INCLUDES})
target_link_libraries(MyServer network_lib)
target_link_libraries(MyClient network_lib)