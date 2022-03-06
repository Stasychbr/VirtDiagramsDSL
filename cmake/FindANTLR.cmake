if (NOT ANTLR_DIR)
	message( SEND_ERROR "Set ANTLR_DIR variable")
endif()

find_path(ANTLR_INCLUDE_DIR antlr4-runtime.h
		  PATHS ${ANTLR_DIR}/include
		  PATH_SUFFIXES /antlr4-runtime)

find_library(ANTLR_LIBRARY libantlr4-runtime
			 PATHS ${ANTLR_DIR}/lib)

find_program(ANTLR_COMMAND antlr4.bat)

macro(COMPILE_GRAMMAR GrammarName)
	set(OPTIONS WITH_VISITOR)
	set(ONE_VALUE_ARGS DEST_DIR)

	cmake_parse_arguments(COMPILE_ARGS "${OPTIONS}" "${ONE_VALUE_ARGS}" "" ${ARGN} )

	if (COMPILE_ARGS_DEST_DIR)
		set(DEST_DIR ${COMPILE_ARGS_DEST_DIR})
	else()
		set(DEST_DIR ${CMAKE_SOURCE_DIR}/antlr/${GrammarName})
	endif()

	set(${GrammarName}_CXX_OUTPUTS)
	set(ANTLR_COMPILE_FLAGS)

	list(APPEND ${GrammarName}_SOURCES
		${DEST_DIR}/${GrammarName}Lexer.h
		${DEST_DIR}/${GrammarName}Lexer.cpp
		${DEST_DIR}/${GrammarName}Parser.h
		${DEST_DIR}/${GrammarName}Parser.cpp)

	if (COMPILE_ARGS_WITH_VISITOR)
		list(APPEND ${GrammarName}_SOURCES
			${DEST_DIR}/${GrammarName}Visitor.h
			${DEST_DIR}/${GrammarName}Visitor.cpp)
		list(APPEND ANTLR_COMPILE_FLAGS -visitor)
	endif()

	add_custom_command(
		OUTPUT ${${GrammarName}_SOURCES}
		COMMAND ${ANTLR_COMMAND} 
		${GrammarName}.g4
		-o ${DEST_DIR}
		-no-listener
		-Dlanguage=Cpp
		${ANTLR_COMPILE_FLAGS}
		DEPENDS ${GrammarName}.g4
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	
endmacro(COMPILE_GRAMMAR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ANTLR
	REQUIRED_VARS ANTLR_COMMAND ANTLR_LIBRARY ANTLR_INCLUDE_DIR )