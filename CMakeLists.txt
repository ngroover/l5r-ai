cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

project(l5r-ai)

include_directories("engine/include")
include_directories("decks/include")
include_directories("cards/include")
include_directories("mcts/include")
include_directories("tf/include")
include_directories("nnet/include")

link_directories( "tf/lib" )

add_subdirectory(engine)
add_subdirectory(decks)
add_subdirectory(cards)
#add_subdirectory(mcts)
add_subdirectory(tf)
#add_subdirectory(nnet)
