#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace Clobber
{
	class Game
	{
		public:
			Game();
			void do_move(const std::string &);
			std::vector<std::string> moves() const;
			int player() const;
			int winner() const;
			friend std::ostream &operator<<(std::ostream &, const Game &);
		private:
			int _board[6][5];
			int _player;
	};
}