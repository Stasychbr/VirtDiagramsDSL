cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(VirtDiagramsDSL LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)

set(ANTLR_DIR "C:\\lib\\LIBANTLR4")
find_package(ANTLR REQUIRED)

compile_grammar(MetaGrammar WITH_VISITOR)
message(STATUS "${ANTLR_INCLUDE_DIR}")

include_directories(${ANTLR_INCLUDE_DIR})
add_executable(dsl main.cpp ${MetaGrammar_SOURCES})
target_link_libraries(dsl ${ANTLR_LIBRARY})

