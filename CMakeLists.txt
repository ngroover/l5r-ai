cmake_minimum_required(VERSION 2.8.11)
project(l5r-ai)

include_directories("engine/include")
include_directories("decks/include")
include_directories("cards/include")
include_directories("mcts/include")

add_subdirectory(engine)
add_subdirectory(decks)
add_subdirectory(cards)
#add_subdirectory(mcts)
add_subdirectory(tf)
