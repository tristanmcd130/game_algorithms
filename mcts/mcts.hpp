#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <map>
#include <functional>
#include <random>

namespace MCTS
{
	struct Game
	{
		virtual void do_move(const std::string &) = 0;
		virtual std::vector<std::string> moves() const = 0;
		virtual int players() const = 0;
		virtual int player() const = 0;
		virtual int winner() const = 0;
		virtual std::shared_ptr<Game> copy() const = 0;
	};
	class Node
	{
		public:
			Node();
			Node(const std::shared_ptr<Game> &, const std::optional<std::reference_wrapper<Node>> & = std::nullopt);
			std::string search(int = 1000);
			Node &advance(const std::string &);
			friend std::ostream &operator<<(std::ostream &, const Node &);
		private:
			std::shared_ptr<Game> _state;
			std::optional<std::reference_wrapper<Node>> _parent;
			std::map<std::string, Node> _children;
			int _wins, _simulations;
			std::mt19937 _gen;
			bool fully_expanded() const;
			double uct() const;
			Node &select();
			Node &expand();
			int simulate();
			void backpropagate(int);
			std::string to_string(int = 0) const;
	};
}