
cmake_minimum_required(VERSION 2.8)
project(classifier)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/src/actors
        $ENV{UXWELTER}/lang/cpp/src/gems/actors/common
        $ENV{UXWELTER}/lang/cpp/src/gems/actors/basic
        $ENV{UXWELTER}/lang/cpp/src/tools/graph
        $ENV{UXWELTER}/lang/c/src/tools/runtime
        $ENV{UXWELTER}/lang/c/src/gems/actors/common
        $ENV{UXWELTER}/lang/c/src/gems/edges
        )

add_subdirectory(src)

IF(EXISTS ${PROJECT_SOURCE_DIR}/demo)
    ADD_SUBDIRECTORY(demo)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/demo)

IF(EXISTS ${PROJECT_SOURCE_DIR}/test)
    ADD_SUBDIRECTORY(test)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test)

IF(EXISTS ${PROJECT_SOURCE_DIR}/test/test01)
    ADD_SUBDIRECTORY(test/test01)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test/test01)


IF(EXISTS ${PROJECT_SOURCE_DIR}/test/test02)
    ADD_SUBDIRECTORY(test/test02)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test/test02)

IF(EXISTS ${PROJECT_SOURCE_DIR}/test/test03)
    ADD_SUBDIRECTORY(test/test03)
ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test/test03)


INSTALL(TARGETS classifier DESTINATION $ENV{UXTMP})






