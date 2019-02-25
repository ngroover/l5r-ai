
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )
link_directories( "${CMAKE_CURRENT_SOURCE_DIR}/lib" )

add_executable( nnet_app src/main.cpp
                     src/gamegraph.cpp
                     src/gamesession.cpp)

target_link_libraries( nnet_app )

