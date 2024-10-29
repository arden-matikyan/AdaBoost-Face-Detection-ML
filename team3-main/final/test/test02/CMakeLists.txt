INCLUDE_DIRECTORIES(
                ${PROJECT_SOURCE_DIR}/src/actors
                ${PROJECT_SOURCE_DIR}/src/graph)
             

LINK_DIRECTORIES(
                $ENV{WELTERGEN}
)

ADD_EXECUTABLE(driver2.exe
        driver2.cpp)

TARGET_LINK_LIBRARIES(
        driver2.exe
                classifier
                welt_c_edges
                welt_c_runtime
                welt_cpp_actors_basic
                welt_cpp_actor
                welt_cpp_actors_image
                welt_cpp_runtime
                welt_cpp_utils
                welt_cpp_graph
        )
INSTALL(TARGETS driver2.exe DESTINATION .)
INSTALL(TARGETS driver2.exe DESTINATION ${PROJECT_SOURCE_DIR}/test/test022)

