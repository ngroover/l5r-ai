
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )
link_directories( "${CMAKE_CURRENT_SOURCE_DIR}/lib" )

add_library( nnet SHARED src/gamegraph.cpp
                        src/gamesession.cpp
                        src/gamestateencoder.cpp
                        src/gamestatebuilder.cpp
                        src/policybuilder.cpp
                        src/policyencoder.cpp)

add_executable( nnet_app src/main.cpp)

add_executable( nnet_unittest test/main.cpp
                        test/gamestatebuildertest.cpp
                        test/policybuildertest.cpp
                        test/policyencodertest.cpp)

target_link_libraries( nnet_app tfwrapper tensorflow decks engine cards nnet)

target_link_libraries( nnet_unittest cppunit engine cards decks nnet tfwrapper tensorflow)
