
add_executable( selfplay src/main.cpp)

add_library( mcts SHARED src/mctsselfplay.cpp
                        src/mctsstatenode.cpp
                        src/mctsactionnode.cpp
                        src/mctstree.cpp
                        src/mctsactionbuilder.cpp
                        src/mctsstatebuilder.cpp
                        src/uctguide.cpp
                        src/mctsguide.cpp
                        src/mostvisitedguide.cpp
                        src/gameplaytrainer.cpp)

add_executable( selfplay_unittest test/main.cpp test/actionbuildertest.cpp test/statebuildertest.cpp)

target_link_libraries( selfplay mcts decks engine cards nnet tfwrapper tensorflow)

target_link_libraries( selfplay_unittest cppunit mcts engine cards decks nnet tfwrapper tensorflow)

