
add_library( engine SHARED src/engine.cpp
                        src/agent.cpp
                        src/gamestate.cpp
                        src/humanagent.cpp
                        src/cpuagent.cpp
                        src/choice.cpp
                        src/decision.cpp
                        src/pregameengine.cpp
                        src/engineshared.cpp
                        src/dynastyengine.cpp
                        src/drawengine.cpp)

add_executable( simulator test/main.cpp )

target_link_libraries( simulator decks engine cards )
