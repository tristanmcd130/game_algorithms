# MCTS
A C++ library implementing [Monte Carlo Tree Search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search).

# How to use
Include mcts.hpp in your .cpp files.

Start by creating a class that inherits from Game. Game is an abstract base class which defines these methods:
- void do_move(string move): Makes the given move.
- vector\<string\> moves() const: Returns all the possible moves the current player can make.
- int players() const: Returns the total number of players.
- int player() const: Returns the current player.
- int winner() const: Returns 0 if nobody has won the game, otherwise the number of the player who won.
- shared_ptr\<Game\> copy() const: Makes a copy of the current game state and returns a shared pointer to it.

Then create an instance of Node with the game state as a parameter. Node::search(int ms) will spend ms milliseconds searching for the best move and return it. If you're planning on using the tree for the next moves too, don't just throw it away and make it do all the calculations over again. Use Node::advance(string move) to get the node representing the move you give it.

Also included with this is an implementation of the game [Clobber](https://en.wikipedia.org/wiki/Clobber), allowing 2 people to play against each other or 1 person to play against PMCGS. When asked for a move, type "best" to have PMCGS make the move for you.
