
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )
message("${CMAKE_CURRENT_SOURCE_DIR}/include")
link_directories( "${CMAKE_CURRENT_SOURCE_DIR}/lib" )
message("${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_executable( tf_app src/main.cpp
                     src/tfgraph.cpp
                     src/tfsession.cpp
                     src/doubletensor.cpp
                     src/tfoperation.cpp
                     src/constop.cpp
                     src/addop.cpp
                     src/matmulop.cpp
                     src/floattensor.cpp
                     src/tensor.cpp
                     src/truncatednormalop.cpp
                     src/int32tensor.cpp
                     src/variable.cpp
                     src/assignop.cpp
                     src/booltensor.cpp
                     src/placeholder.cpp)

target_link_libraries( tf_app tensorflow )

