# l5r-ai
A neural network based Legend of the 5 Rings LCG AI written in C++

This AI is inspired by AlphaGo Zero.  It combines Monte Carlo tree search with deep neural network reinforcement learning.  It uses only self play to improve itself.

## Initial thoughts
The state/action space for L5R is very large especially considering the entire card pool.  Also hidden information/randomness is still a challenge to take into consideration.

As a simple initial proof of concept the initial version will play with the following limitations.
* no hidden information (hand exposed, and no deck shuffling)
* turn based bidding starting with first player
* lion and crane starter decks only

## Motivations
* I am an L5R player myself looking to better my own gameplay and deckbuilding
* I have an interest in programming and machine learning

## Long term Goals
Once the initial engine is complete and can successfully learn to play with these limitations I would like to start to experiment and evolve it with more features.
* Hidden information
* Supporting different clan matchups
* Deckbuilding and deck strength evalutation
* Increase to support card pool and evolve with the meta
* Add a GUI to the engine for easy human play
