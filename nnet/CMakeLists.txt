
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )
link_directories( "${CMAKE_CURRENT_SOURCE_DIR}/lib" )

# TODO: make a library
add_executable( nnet_app src/main.cpp
                     src/gamegraph.cpp
                     src/gamesession.cpp
                     src/gamestateencoder.cpp
                     src/charactercardslot.cpp)

add_executable( nnet_unittest test/main.cpp test/characterslottest.cpp src/charactercardslot.cpp )

target_link_libraries( nnet_app tfwrapper tensorflow decks engine cards)

target_link_libraries( nnet_unittest cppunit )
