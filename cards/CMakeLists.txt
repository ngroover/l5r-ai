include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library( cards SHARED src/cards.cpp src/card.cpp src/cardgenerator.cpp src/carddata.cpp)

