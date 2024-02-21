#pragma once
#include "pmcgs.hpp"
#include <iostream>

namespace Clobber
{
	class Game: public PMCGS::Game
	{
		public:
			Game();
			void do_move(const std::string &) override;
			std::vector<std::string> moves() const override;
			int player() const override;
			int winner() const override;
			std::shared_ptr<PMCGS::Game> copy() const override;
			friend std::ostream &operator<<(std::ostream &, const Game &);
		private:
			int _board[6][5];
			int _player;
	};
}