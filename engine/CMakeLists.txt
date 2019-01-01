
add_library( engine SHARED src/engine.cpp
                        src/agent.cpp
                        src/gamestate.cpp
                        src/humanagent.cpp
                        src/cpuagent.cpp
                        src/choice.cpp
                        src/decision.cpp
                        src/phasemanager.cpp
                        src/carddatamanager.cpp
                        src/dynastycardmanager.cpp
                        src/conflictcardmanager.cpp
                        src/provincecardmanager.cpp
                        src/tokenmanager.cpp
                        src/agentmanager.cpp
                        src/turnmanager.cpp
                        src/conflictmanager.cpp)

add_executable( simulator sim/main.cpp )

add_executable( unittest test/main.cpp test/pregametest.cpp )

target_link_libraries( simulator decks engine cards )

target_link_libraries( unittest cppunit decks engine cards)
