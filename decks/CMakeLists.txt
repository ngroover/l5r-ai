
add_library( decks SHARED src/decklist.cpp src/decklistmanager.cpp src/decklistvalidator.cpp )

add_executable( deck_test test/main.cpp test/decklistmanagertest.cpp test/decklistvalidatortest.cpp )

target_link_libraries( deck_test glog gtest pthread decks cards )
