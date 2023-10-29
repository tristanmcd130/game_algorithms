# pmcgs
A C++ library implementing [Pure Monte Carlo Game Search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search#Pure_Monte_Carlo_game_search).

# How to use
Simply include pmcgs.hpp in your .cpp files.

The class used as the template parameter to the pmcgs function needs a few methods implemented:
- int player(): Returns the current player.
- T do_move(auto move): Makes the given move and returns the new game state. Should not modify the invoking object.
- auto possible_moves(): Returns all the possible moves the current player can make.
- int winner(): Returns 0 if nobody has won the game, otherwise the number of the player who won.
- bool operator<(T rhs): Needed so it can be used as a key to a map.

Also included with this is an implementation of the game [Clobber](https://en.wikipedia.org/wiki/Clobber), allowing 2 people to play against each other or 1 person to play against PMCGS. When asked for a move, type "best" to have PMCGS make the move for you.
