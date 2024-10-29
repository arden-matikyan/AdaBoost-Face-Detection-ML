INCLUDE_DIRECTORIES(
                ${PROJECT_SOURCE_DIR}/src/actors
                ${PROJECT_SOURCE_DIR}/src/graph)

LINK_DIRECTORIES(
                $ENV{WELTERGEN}
)

ADD_EXECUTABLE(driver.exe
        driver.cpp)

TARGET_LINK_LIBRARIES(
        driver.exe
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
INSTALL(TARGETS driver.exe DESTINATION .)
INSTALL(TARGETS driver.exe DESTINATION $ENV{UXTMP})

