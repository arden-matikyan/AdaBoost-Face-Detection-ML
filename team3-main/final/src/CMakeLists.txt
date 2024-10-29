SET(source_list
  actors/classifier.cpp

  actors/file_sink.cpp
  actors/txt_img_read.cpp

  util2/cascadeClassifier.cpp 
  util2/featureUtil.cpp
  util2/strongClassifier.cpp
  util2/weakClassifier.cpp
  
  
  graph/graph.cpp)


INCLUDE_DIRECTORIES(
		actors
		graph
        $ENV{UXWELTERC}/src/gems/actors/basic
        $ENV{UXWELTERC}/src/gems/actors/common
        $ENV{UXWELTERC}/src/gems/edges
        $ENV{UXWELTERC}/src/tools/runtime
        $ENV{UXWELTERC}/src/tools/graph

        $ENV{UXWELTER}/lang/cpp/src/gems/actors/common
        $ENV{UXWELTER}/lang/cpp/src/gems/actors/basic
        $ENV{UXWELTER}/lang/cpp/src/tools/graph
        $ENV{UXWELTER}/lang/cpp/src/tools/runtime
        $ENV{UXWELTER}/lang/cpp/src/apps/basic

)



ADD_LIBRARY(classifier ${source_list})
INSTALL(TARGETS classifier DESTINATION .)
INSTALL(TARGETS classifier DESTINATION $ENV{UXTMP})
