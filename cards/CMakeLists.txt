include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library( cards SHARED src/cardgenerator.cpp
                     src/carddata.cpp
                     src/carddatagenerator.cpp)

target_link_libraries( cards glog )

add_executable( cards_test test/main.cpp src/carddata.cpp src/carddatagenerator.cpp test/carddatageneratortest.cpp )

target_link_libraries( cards_test glog gtest pthread )

