cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

set(TARGET_NAME slogger)

add_subdirectory(SocketLog/socketlog)
include_directories(SocketLog/socketlog)

add_library(${TARGET_NAME} SHARED ${SOCKET_LOG_LIB_SRC} SLogger.cpp)

target_link_libraries(${TARGET_NAME} socketlog)

# for android
IF(CMAKE_SYSTEM_NAME MATCHES "Android")
    target_link_libraries(${TARGET_NAME} log)

    if (DEFINED LIB_OUTPUT_PATH)
        set(outpath ${LIB_OUTPUT_PATH}/${TARGET_NAME}/${ANDROID_ABI}/${CMAKE_BUILD_TYPE})
        set_target_properties(${TARGET_NAME} PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${outpath}"
                LIBRARY_OUTPUT_DIRECTORY "${outpath}")
    endif()
ENDIF()

# example
add_executable(test SLogger_test.cpp)
target_link_libraries(test slogger)
