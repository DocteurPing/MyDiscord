cmake_minimum_required(VERSION 3.25)

set(SHARED_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Networking/include")
set(SHARED_SOURCE_DIR "${PROJECT_SOURCE_DIR}/Networking/src")

SET(INCLUDES
        "${SHARED_INCLUDE_DIR}/NetworkClient.hpp"
        "${SHARED_INCLUDE_DIR}/NetworkConnection.hpp"
        "${SHARED_INCLUDE_DIR}/NetworkMessage.hpp"
        "${SHARED_INCLUDE_DIR}/NetworkQueue.hpp"
        "${SHARED_INCLUDE_DIR}/NetworkServer.hpp")

add_library(network_lib ${INCLUDES})
set_target_properties(network_lib PROPERTIES LINKER_LANGUAGE CXX)
