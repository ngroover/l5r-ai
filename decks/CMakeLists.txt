
add_library( decks SHARED src/decklist.cpp src/decklistmanager.cpp )

add_executable( deck_test test/main.cpp test/decklistmanagertest.cpp )

target_link_libraries( deck_test glog gtest pthread decks )
