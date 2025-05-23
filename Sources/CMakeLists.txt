cmake_minimum_required(VERSION 3.10)

project(com.elgato.cpu VERSION 1.4.2)

if (APPLE)
  set(
    STREAMDECK_PLUGIN_DIR
    "$ENV{HOME}/Library/ApplicationSupport/com.elgato.StreamDeck/Plugins"
  )
  find_library(APPKIT_LIBRARY AppKit)
  set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()
set(
  CMAKE_INSTALL_PREFIX
  "${STREAMDECK_PLUGIN_DIR}/${CMAKE_PROJECT_NAME}"
  CACHE STRING "See cmake documentation"
)

set(CMAKE_CXX_STANDARD 23)
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
set(
  EXTRA_LIBS
  StreamDeckSDK
)
if (APPLE)
  list(APPEND SOURCES macOS/CpuUsageHelper.mm)
  list(APPEND EXTRA_LIBS ${APPKIT_LIBRARY})
elseif (WIN32)
  list(APPEND SOURCES Windows/CpuUsageHelper.cpp)
endif()
add_executable(
  cpu
  ${SOURCES}
)
target_link_libraries(cpu ${EXTRA_LIBS})
