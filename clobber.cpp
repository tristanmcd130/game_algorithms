#include "pmcgs.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef enum {EMPTY, RED, BLUE = -1} Piece;

class Clobber
{
	Piece _board[30];
	Piece _player;
	int position_to_index(string position)
	{
		if(position.size() != 2 || position.at(0) < 'A' || position.at(0) > 'F' || position.at(1) < '1' || position.at(1) > '5')
			throw invalid_argument(position + " is not a valid board position.");
		return (position.at(0) - 'A') * 5 + position.at(1) - '1';
	}
	string index_to_position(int index)
	{
		string from(1, index / 5 + 'A');
		string to(1, index % 5 + '1');
		return from + to;
	}
	public:
		Clobber()
		{
			for(int i = 0; i < 30; i++)
				_board[i] = i % 2 ? BLUE : RED;
			_player = RED;
		}
		Piece player()
		{
			return _player;
		}
		Clobber do_move(string move_string)
		{
			Clobber new_game = *this;
			vector<string> moves = possible_moves();
			if(find(moves.begin(), moves.end(), move_string) == moves.end())
				throw invalid_argument(move_string + " is not a valid move.");
			string from = move_string.substr(0, 2);
			string to = move_string.substr(2, 2);
			new_game._board[position_to_index(to)] = _player;
			new_game._board[position_to_index(from)] = EMPTY;
			new_game._player = (Piece)(-_player);
			return new_game;
		}
		vector<string> possible_moves()
		{
			vector<string> moves;
			for(int y = 0; y < 6; y++)
			{
				for(int x = 0; x < 5; x++)
				{
					if(_board[y * 5 + x] == _player)
					{
						if(y > 0 && _board[(y - 1) * 5 + x] == -_player)
							moves.push_back(index_to_position(y * 5 + x) + index_to_position((y - 1) * 5 + x));
						if(y < 5 && _board[(y + 1) * 5 + x] == -_player)
							moves.push_back(index_to_position(y * 5 + x) + index_to_position((y + 1) * 5 + x));
						if(x > 0 && _board[y * 5 + (x - 1)] == -_player)
							moves.push_back(index_to_position(y * 5 + x) + index_to_position(y * 5 + (x - 1)));
						if(x < 4 && _board[y * 5 + (x + 1)] == -_player)
							moves.push_back(index_to_position(y * 5 + x) + index_to_position(y * 5 + (x + 1)));
					}
				}
			}
			return moves;
		}
		Piece winner()
		{
			return possible_moves().size() ? EMPTY : (Piece)(-_player);
		}
		friend ostream &operator<<(ostream &out, const Clobber &game)
		{
			out << "\x1B[1m  1 2 3 4 5" << endl;
			for(int y = 0; y < 6; y++)
			{
				out << "\x1B[1m" << (char)(y + 'A') << " \x1B[0m";
				for(int x = 0; x < 5; x++)
				{
					switch(game._board[y * 5 + x])
					{
						case EMPTY:
							out << "\x1B[0m.";
							break;
						case RED:
							out << "\x1B[31mO";
							break;
						case BLUE:
							out << "\x1B[34mO";
							break;
					}
					if(x % 5 != 4)
						out << " ";
				}
				out << "\x1B[0m" << endl;
			}
			return out;
		}
		bool operator<(const Clobber &rhs) const
		{
			for(int i = 0; i < 30; i++)
			{
				if(_board[i] != rhs._board[i])
					return _board[i] < rhs._board[i];
			}
			return false;
		}
};

int main()
{
	int players;
	cout << "How many players? (1 or 2): ";
	cin >> players;
	while(players != 1 && players != 2)
	{
		cout << "Please input a correct amount of players." << endl << "How many players? (1 or 2): ";
		cin >> players;
	}
	cout << endl;
	Clobber game;
	while(!game.winner())
	{
		cout << game << endl << (game.player() == RED ? "Red" : "Blue") << " player's move: ";
		try
		{
			if(players == 1 && game.player() == BLUE)
			{
				game = pmcgs(game, 1000);
				cout << endl;
			}
			else
			{
				string move;
				cin >> move;
				game = move == "best" ? pmcgs(game, 1000) : game.do_move(move);
			}
			cout << endl;
		}
		catch(const exception &e)
		{
			cout << e.what() << endl << endl;
		}
	}
	cout << game << endl << (game.winner() == RED ? "Red" : "Blue") << " player wins!" << endl;
	return 0;
}