
add_library( tfwrapper SHARED
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
                     src/placeholder.cpp
                     src/squareddifference.cpp
                     src/mean.cpp
                     src/biasadd.cpp
                     src/gradients.cpp
                     src/relu.cpp
                     src/sigmoid.cpp
                     src/layer.cpp
                     src/inputlayer.cpp
                     src/denselayer.cpp
                     src/layerinitializer.cpp
                     src/applygradientdescent.cpp
                     src/sgdoptimizer.cpp
                     src/zeroslike.cpp)

add_executable( tf_app src/main.cpp )

target_link_libraries( tf_app tfwrapper tensorflow )

