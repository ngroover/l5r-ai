
add_library( engine SHARED src/engine.cpp
                        src/agent.cpp
                        src/humanagent.cpp
                        src/cpuagent.cpp
                        src/state/gamestate.cpp
                        src/state/player.cpp
                        src/state/cardarea.cpp
                        src/state/character.cpp
                        src/state/conflict.cpp
                        src/state/ring.cpp
                        src/state/tokens.cpp
                        src/choice.cpp
                        src/decision.cpp
                        src/phasemanager.cpp
                        src/carddatamanager.cpp
                        src/dynastycardmanager.cpp
                        src/conflictcardmanager.cpp
                        src/provincecardmanager.cpp
                        src/tokenmanager.cpp
                        src/turnmanager.cpp
                        src/gamestateintfc.cpp
                        src/cardareamanager.cpp
                        src/mulliganmanager.cpp
                        src/conflictphasemanager.cpp
                        src/conflictresolutionmanager.cpp
                        src/charactermanipulator.cpp
                        src/ringmanager.cpp
                        src/imperialfavormanager.cpp
                        src/endgame.cpp)

add_executable( simulator sim/main.cpp )

add_executable( unittest test/main.cpp test/pregametest.cpp )
                           #test/gamestatetest.cpp
                           #test/dynastytest.cpp
                           ##test/biddingtest.cpp
                           #test/choicesimulation.cpp
                           #test/conflicttest.cpp
                           #test/regrouptest.cpp
                           #test/deckreshuffle.cpp)

target_link_libraries( simulator decks engine cards )

target_link_libraries( unittest gtest pthread decks engine cards )
