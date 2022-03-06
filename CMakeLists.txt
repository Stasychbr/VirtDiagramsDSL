cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(VirtDiagramsDSL LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(ANTLR_DIR "C:\\lib\\LIBANTLR4")
find_package(ANTLR REQUIRED)

compile_grammar(MetaGrammar WITH_VISITOR)

file(GLOB_RECURSE PROJECT_SOURCES *.cpp *.h)

include_directories(${ANTLR_INCLUDE_DIR})

qt_add_executable(vdl ${PROJECT_SOURCES} ${MetaGrammar_SOURCES})
target_link_libraries(vdl PRIVATE Qt6::Widgets ${ANTLR_LIBRARY})
target_compile_definitions(vdl PUBLIC -DQT_NO_KEYWORDS)
