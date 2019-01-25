
add_executable( selfplay src/main.cpp
                         src/mctsselfplay.cpp
                         src/mctsstatenode.cpp
                         src/mctsactionnode.cpp
                         src/mctstree.cpp)

target_link_libraries( selfplay decks engine cards )

#target_link_libraries( unittest cppunit decks engine cards boost_serialization)
