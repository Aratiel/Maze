# note: use "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ ." to generate debug version for coverage
# Copyright <lwolmer> 2022
#############################################################
#                                                           #
#                   GLOBAL CMAKE SETUP                      #
#                                                           #
#############################################################
option(ENABLE_CODE_ANALYSIS "Run code cppcheck" ON)
cmake_minimum_required(VERSION 3.5)
# Path to cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")
# disable extentions for pure C++
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()
enable_testing()
enable_language(CXX)
if(ENABLE_CODE_ANALYSIS)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if (CMAKE_CXX_CPPCHECK)
        list(
            APPEND CMAKE_CXX_CPPCHECK 
                "--enable=warning"
                "--inconclusive"
                "--force" 
                "--inline-suppr"
                "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
        )
    endif()
endif(ENABLE_CODE_ANALYSIS)

#############################################################
#                                                           #
#                     Dependencies                          #
#                                                           #
#############################################################
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/doc)
    add_subdirectory(doc)
endif()
IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/maze)
    add_subdirectory(maze)
ENDIF()
#############################################################
#                                                           #
#                      EXECUTABLE                           #
#                                                           #
#############################################################
set(PROJECT_NAME "A1_Maze")

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT REQUIRED NAMES Qt6 Qt5 COMPONENTS Widgets)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_CXX_FLAGS "-Werror -Wall -fexceptions -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo ${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB PROJECT_SOURCES
    "*.h"  "*.cc" "*.ui" "*.qrc" "models/*.h"  "models/*.cc"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    GL_SILENCE_DEPRECATION
  )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE maze_generate)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER ${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/maze

)

set_property(
    TARGET ${PROJECT_NAME}
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)


#############################################################
#                                                           #
#                     GTEST COMPILE                         #
#                                                           #
#############################################################
message("-- Added GTest target from source")
if (NOT TARGET gtest_main)
    unset(CMAKE_CXX_FLAGS)
    unset(CMAKE_CXX_FLAGS_DEBUG)
    set(_flag_sync_required TRUE)
    add_subdirectory(googletest EXCLUDE_FROM_ALL)
endif ()
include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)
set(GTEST_FOUND TRUE)

#############################################################
#                                                           #
#                         TESTING                           #
#                                                           #
#############################################################
if (GTEST_FOUND)
    IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
        add_subdirectory(tests)
    endif()
endif()

#############################################################
#                                                              #
#                    additional checks                      #
#                                                           #
#############################################################
find_program(CLANG_FORMAT NAMES clang-format)
if (CLANG_FORMAT)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.clang-format)
        MESSAGE(WARNING ".clang-format file should be placed in src folder, continuing without it, test result may be incorect.")
    else()
        file(GLOB_RECURSE STYLE_CHECK_FILES *.cc *.h *.tpp *.inc)
        list(FILTER STYLE_CHECK_FILES EXCLUDE REGEX "/googletest/")
        add_custom_target(stylecheck
        COMMAND ${CLANG_FORMAT} -n ${STYLE_CHECK_FILES}
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

        add_custom_target(stylechange
        COMMAND ${CLANG_FORMAT} -i ${STYLE_CHECK_FILES}
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    endif()
    
endif()

#############################################################
#                                                           #
#                          MISC                             #
#                                                           #
#############################################################
#tests
# add_custom_target(tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose
#                   DEPENDS unit_tests unit_tests_matrix)

#tests
add_custom_target(tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose
                  DEPENDS unit_tests)

#install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin BUNDLE DESTINATION ${CMAKE_BINARY_DIR}/bin)

#unistall
add_custom_target(uninstall
COMMAND rm -rf ${CMAKE_BINARY_DIR}/bin)

set_property(
    TARGET uninstall
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/install_manifest.txt
)

#dist
add_custom_target(dist
COMMAND make install && cd bin && tar -cjf ${CMAKE_BINARY_DIR}/dist.tar.gz . -C ${CMAKE_BINARY_DIR}/bin . WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

set_property(
    TARGET dist
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/dist.tar.gz
)


