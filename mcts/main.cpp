#include "mcts.hpp"
#include "clobber.hpp"

int main(int argc, char *argv[])
{
	int players;
	std::cout << "How many players? (1 or 2): " << std::flush;
	std::cin >> players;
	while(players != 1 && players != 2)
	{
		std::cout << "Please input a correct amount of players." << std::endl << "How many players? (1 or 2): " << std::flush;
		std::cin >> players;
	}
	//std::cout << std::endl;
	auto game = std::make_shared<Clobber::Game>();
	while(!game->winner())
	{
		std::cout << *game << (game->player() == 1 ? "Red" : "Blue") << " player's move: " << std::flush;
		try
		{
			std::string move;
			MCTS::Node tree(game);
			if(players == 1 && game->player() == 2)
			{
				move = tree.search();
				std::cout << move << std::endl;
				game->do_move(move);
				//std::cout << std::endl;
			}
			else
			{
				std::cin >> move;
				game->do_move(move == "best" ? tree.search() : move);
			}
			//std::cout << std::endl;
		}
		catch(const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << *game << (game->winner() == 1 ? "Red" : "Blue") << " player wins!" << std::endl;
	return 0;
}