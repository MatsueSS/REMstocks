cmake_minimum_required(VERSION 3.10)

project(REMstocks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(/usr/lib)

#file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(SOURCES
    src/BotTelegram.cpp
    src/Interface.cpp
    src/JsonWorker.cpp
    src/PostgresDB.cpp
    src/PyLoader.cpp
    src/TelegramSender.cpp
    src/TelegramUser.cpp
    tests/test_PostgresDB.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(CURL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})

find_package(PostgreSQL REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PostgreSQL_LIBRARIES})