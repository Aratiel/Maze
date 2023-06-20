# note: use "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ ." to generate debug version for coverage
# Copyright <lwolmer> 2022
#############################################################
#                                                           #
#                          MISC                             #
#                                                           #
#############################################################
#dvi
FIND_PROGRAM( MAKEINFO makeinfo )

IF(NOT MAKEINFO)
	MESSAGE(FATAL_ERROR "texinfo not found! Aborting...")
ENDIF() # NOT MAKEINFO

add_custom_target(dvi ALL
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/documentation
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.png ${CMAKE_BINARY_DIR}/documentation
    COMMAND makeinfo --no-split --html -o ${CMAKE_BINARY_DIR}/documentation/documentation.html ${CMAKE_CURRENT_SOURCE_DIR}/src/raw_document.texi
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

set_property(
    TARGET dvi
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/documentation
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/documentation DESTINATION ${CMAKE_BINARY_DIR}/bin)
