# pmcgs
A C++ library implementing [Pure Monte Carlo Game Search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search#Pure_Monte_Carlo_game_search).

# How to use
Include pmcgs.hpp in your .cpp files.

The first parameter to the pmcgs function is a shared pointer to a class inheriting from Game. Game is an abstract base class which defines these methods:
- void do_move(string move): Makes the given move.
- vector\<string\> moves() const: Returns all the possible moves the current player can make.
- int player() const: Returns the current player.
- int winner() const: Returns 0 if nobody has won the game, otherwise the number of the player who won.
- shared_ptr<Game> copy() const: Makes a copy of the current game state and returns a shared pointer to it.

Also included with this is an implementation of the game [Clobber](https://en.wikipedia.org/wiki/Clobber), allowing 2 people to play against each other or 1 person to play against PMCGS. When asked for a move, type "best" to have PMCGS make the move for you.
