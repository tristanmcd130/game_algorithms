#include "pmcgs.hpp"
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
	Clobber::Game game;
	while(!game.winner())
	{
		std::cout << game << (game.player() == 1 ? "Red" : "Blue") << " player's move: " << std::flush;
		try
		{
			std::string move;
			if(players == 1 && game.player() == -1)
			{
				move = PMCGS::pmcgs(game, 1000);
				std::cout << move << std::endl;
				game.do_move(move);
				//std::cout << std::endl;
			}
			else
			{
				std::cin >> move;
				game.do_move(move == "best" ? PMCGS::pmcgs(game, 1000) : move);
			}
			//std::cout << std::endl;
		}
		catch(const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << game << (game.winner() == 1 ? "Red" : "Blue") << " player wins!" << std::endl;
	return 0;
}