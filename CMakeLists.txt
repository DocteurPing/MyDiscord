cmake_minimum_required(VERSION 3.25)

project(MyServer)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/Server/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Server/include")

SET(SOURCES
        "${SOURCE_DIR}/VoiceServer.cpp"
        "${SOURCE_DIR}/main.cpp")

SET(INCLUDES
        "${INCLUDE_DIR}/VoiceServer.h")

include_directories(Networking)
link_directories(Networking)
add_subdirectory(Networking)
add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} network_lib)