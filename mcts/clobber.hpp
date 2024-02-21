#pragma once
#include "mcts.hpp"
#include <iostream>

namespace Clobber
{
	class Game: public MCTS::Game
	{
		public:
			Game();
			//~Game();
			void do_move(const std::string &) override;
			std::vector<std::string> moves() const override;
			int players() const override;
			int player() const override;
			int winner() const override;
			std::shared_ptr<MCTS::Game> copy() const override;
			friend std::ostream &operator<<(std::ostream &, const Game &);
		private:
			int _board[6][5];
			int _player;
	};
}