cmake_minimum_required(VERSION 3.25)

set(SHARED_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Networking/include")
set(SHARED_SOURCE_DIR "${PROJECT_SOURCE_DIR}/Networking/src")


SET(SOURCES
        "${SHARED_SOURCE_DIR}/NetworkClient.cpp"
        "${SHARED_SOURCE_DIR}/NetworkQueue.cpp"
        "${SHARED_SOURCE_DIR}/NetworkServer.cpp")

SET(INCLUDES
        "${SHARED_INCLUDE_DIR}/NetworkClient.h"
        "${SHARED_INCLUDE_DIR}/NetworkConnection.h"
        "${SHARED_INCLUDE_DIR}/NetworkMessage.h"
        "${SHARED_INCLUDE_DIR}/NetworkQueue.h"
        "${SHARED_INCLUDE_DIR}/NetworkServer.h")

add_library(network_lib ${SOURCES} ${INCLUDES})