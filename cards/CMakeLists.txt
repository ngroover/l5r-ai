include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library( cards SHARED src/cards.cpp 
                     src/card.cpp 
                     src/cardgenerator.cpp)
                     #src/carddata.cpp
                     #src/carddatagenerator.cpp)

add_executable( cards_test test/main.cpp src/carddata.cpp src/carddatagenerator.cpp test/carddatageneratortest.cpp )

target_link_libraries( cards_test glog cppunit )

