cmake_minimum_required(VERSION 3.10)

project(com.elgato.cpu VERSION 1.2)

if (APPLE)
  set(
    STREAMDECK_PLUGIN_DIR
    "$ENV{HOME}/Library/ApplicationSupport/com.elgato.StreamDeck/Plugins"
  )
endif()
set(
  CMAKE_INSTALL_PREFIX
  "${STREAMDECK_PLUGIN_DIR}/${CMAKE_PROJECT_NAME}"
  CACHE STRING "See cmake documentation"
)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED true)
if (MSVC)
  add_definitions("/Zc:__cplusplus" -DUNICODE=1)
endif()
include_directories("${CMAKE_SOURCE_DIR}")

include("StreamDeckSDK.cmake")

set(
  SOURCES
  MyStreamDeckPlugin.cpp
  main.cpp
)
if (APPLE)
  list(APPEND SOURCES macOS/CpuUsageHelper.cpp)
elseif (WIN32)
  list(APPEND SOURCES Windows/CpuUsageHelper.cpp)
endif()
add_executable(
  cpu
  ${SOURCES}
)
target_link_libraries(cpu StreamDeckSDK)
