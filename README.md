# Defender

The implementation of the Defender arcade game utilised an object-oriented programming approach using C++17, the SFML 2.6.0 framework for object display, and Doctest 2.4.11 framework for automated unit testing

The objective of the game in the current state is to destroy all the enemy landers. These enemies spawn randomly near the ship and shoot missiles towards the ship. However, the missiles can be evaded by swiftly moving out of the general direction of the missiles or by destroying the landers before they shoot. If the player happens to get hit by a lander’s missile or collide with a lander, pod or swarmer, the player loses one of their three lives. Make sure to retaliate by returning fire using the ship’s lasers and be wary of the ship’s fuel levels, as it decreases as the player moves the ship. Fuel levels can be replenished by moving through a fuel canisters. The game is won by destroying all 20 landers. Conversely, the game can be lost either if the player loses all three lives, if the player runs out of fuel, or if all five humanoids are killed or kidnapped.

Detailed documentation discussing the implementation of the game, and a game executable can be found under releases.  
