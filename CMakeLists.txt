cmake_minimum_required(VERSION 2.8.11)
project(l5r-ai)


include_directories("engine/include")
include_directories("decks/include")
include_directories("cards/include")

add_subdirectory(engine)
add_subdirectory(decks)
add_subdirectory(cards)
