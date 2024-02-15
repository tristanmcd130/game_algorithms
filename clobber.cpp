#include "clobber.hpp"
#include <algorithm>
#include <iostream>

namespace Clobber
{
	Game::Game(): _player(1)
	{
		for(int y = 0; y < 6; y++)
		{
			for(int x = 0; x < 5; x++)
				_board[y][x] = (x + y) % 2 ? -1 : 1;
		}
	}
	void Game::do_move(const std::string &move)
	{
		std::vector<std::string> legal_moves = moves();
		if(find(legal_moves.begin(), legal_moves.end(), move) == legal_moves.end())
			throw std::invalid_argument(move + " is not a valid move.");
		_board[move.at(2) - 'a'][move.at(3) - '1'] = _player;
		_board[move.at(0) - 'a'][move.at(1) - '1'] = 0;
		//std::cout << "Moved from (" << (move.at(0) - 'a') << ", " << (move.at(1) - '1') << ") to (" << (move.at(2) - 'a') << ", " << (move.at(3) - '1') << ")" << std::endl;
		_player = -_player;
	}
	std::vector<std::string> Game::moves() const
	{
		std::vector<std::string> moves;
		for(int y = 0; y < 6; y++)
		{
			for(int x = 0; x < 5; x++)
			{
				if(_board[y][x] == _player)
				{
					if(y > 0 && _board[y - 1][x] == -_player)
						moves.push_back(std::string(1, y + 'a') + std::to_string(x + 1) + std::string(1, y - 1 + 'a') + std::to_string(x + 1));
					if(y < 5 && _board[y + 1][x] == -_player)
						moves.push_back(std::string(1, y + 'a') + std::to_string(x + 1) + std::string(1, y + 1 + 'a') + std::to_string(x + 1));
					if(x > 0 && _board[y][x - 1] == -_player)
						moves.push_back(std::string(1, y + 'a') + std::to_string(x + 1) + std::string(1, y + 'a') + std::to_string(x));
					if(x < 4 && _board[y][x + 1] == -_player)
						moves.push_back(std::string(1, y + 'a') + std::to_string(x + 1) + std::string(1, y + 'a') + std::to_string(x + 2));
				}
			}
		}
		//for(auto move: moves)
		//	std::cout << move << std::endl;
		return moves;
	}
	int Game::player() const
	{
		return _player;
	}
	int Game::winner() const
	{
		return moves().size() > 0 ? 0 : -_player;
	}
	std::ostream &operator<<(std::ostream &out, const Game &game)
	{
		out << "\x1B[1m  1 2 3 4 5" << std::endl;
		for(int y = 0; y < 6; y++)
		{
			out << "\x1B[1m" << std::string(1, y + 'a') << " \x1B[0m";
			for(int x = 0; x < 5; x++)
			{
				switch(game._board[y][x])
				{
					case 0:
						out << "\x1B[0m.";
						break;
					case 1:
						out << "\x1B[31mO";
						break;
					case -1:
						out << "\x1B[34mO";
						break;
				}
				if(x % 5 != 4)
					out << " ";
			}
			out << "\x1B[0m" << std::endl;
		}
		return out;
	}
}