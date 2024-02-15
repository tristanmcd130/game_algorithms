# pmcgs
A C++ library implementing [Pure Monte Carlo Game Search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search#Pure_Monte_Carlo_game_search).

# How to use
Simply include pmcgs.hpp in your .cpp files.

The class used as the template parameter to the pmcgs function needs a few methods implemented:
- void do_move(string move): Makes the given move.
- vector<string> moves() const: Returns all the possible moves the current player can make.
- int player() const: Returns the current player.
- int winner() const: Returns 0 if nobody has won the game, otherwise the number of the player who won.

Also included with this is an implementation of the game [Clobber](https://en.wikipedia.org/wiki/Clobber), allowing 2 people to play against each other or 1 person to play against PMCGS. When asked for a move, type "best" to have PMCGS make the move for you.
