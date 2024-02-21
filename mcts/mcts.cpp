#include "mcts.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>

namespace MCTS
{
	Node::Node(): _state(nullptr), _parent(std::nullopt), _wins(0), _simulations(0), _gen(std::random_device{}()) {}
	Node::Node(const std::shared_ptr<Game> &state, const std::optional<std::reference_wrapper<Node>> &parent): _state(state), _parent(parent), _wins(0), _simulations(0), _gen(std::random_device{}()) {}
	std::string Node::search(int ms)
	{
		auto start = std::chrono::high_resolution_clock::now();
		while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() < ms)
		{
			auto &child = select().expand();
			child.backpropagate(child.simulate());
		}
		return std::max_element(_children.begin(), _children.end(), [](auto &x, auto &y) {return x.second._simulations < y.second._simulations;})->first;
	}
	Node &Node::advance(const std::string &move)
	{
		_parent = std::nullopt;
		return _children.at(move);
	}
	bool Node::fully_expanded() const {return _children.size() == _state->moves().size();}
	double Node::uct() const {return (double)_wins / _simulations + sqrt(2 * log(_parent->get()._simulations) / _simulations);}
	Node &Node::select()
	{
		if(!fully_expanded() || _state->moves().size() == 0)
		{
			//std::cout << "SELECT: " << this << ": not fully expanded, selecting self" << std::endl;
			return *this;
		}
		std::reference_wrapper<Node> leaf = _children.begin()->second;
		double best_uct = 0;
		for(auto &[move, node]: _children)
		{
			//std::cout << "SELECT: " << this << ": " << move << " (" << node._wins << "/" << node._simulations << "): UCT = " << node.uct() << std::endl;
			if(node.uct() > best_uct)
			{
				best_uct = node.uct();
				leaf = node;
			}
		}
		//std::cout << "SELECT: " << this << ": selecting child " << &leaf << std::endl;
		return leaf.get().select();
	}
	Node &Node::expand()
	{
		if(fully_expanded() || _state->winner())
		{
			//std::cout << "EXPAND: " << this << ": fully expanded or terminal state, selecting self" << std::endl;
			return *this;
		}
		std::vector<std::string> unexpanded_moves;
		for(auto move: _state->moves())
		{
			if(_children.count(move) == 0)
				unexpanded_moves.push_back(move);
		}
		std::uniform_int_distribution<> distrib(0, unexpanded_moves.size() - 1);
		std::string move = unexpanded_moves.at(distrib(_gen));
		//std::cout << "EXPAND: " << this << ": creating new state after move " << move << std::endl;
		std::shared_ptr<Game> state = _state->copy();
		state->do_move(move);
		_children[move] = Node(state, *this);
		return _children.at(move);
	}
	int Node::simulate()
	{
		std::shared_ptr<Game> simulated_state = _state->copy();
		while(!simulated_state->winner())
		{
			std::uniform_int_distribution<> distrib(0, simulated_state->moves().size() - 1);
			simulated_state->do_move(simulated_state->moves().at(distrib(_gen)));
		}
		//std::cout << "SIMULATE: " << this << ": our player is " << _state->player() << ", " << simulated_state->winner() << " won" << std::endl;
		return simulated_state->winner();
	}
	void Node::backpropagate(int winner)
	{
		int our_winner = (_state->player() - 2) % _state->players();
		if(our_winner < 0)
			our_winner += _state->players(); // for some reason x % y where x < 0 is x and not y - x
		our_winner++;
		//std::cout << "BACKPROPAGATE: " << this << ": did our guy, " << our_winner << ", win? " << winner << " won" << std::endl;
		if(winner == our_winner)
		{
			_wins++;
			//std::cout << "BACKPROPAGATE: " << this << ": we won, increasing wins to " << _wins << std::endl;
		}
		_simulations++;
		//std::cout << "BACKPROPAGATE: " << this << ": increasing simulations to " << _simulations << std::endl;
		if(_parent)
		{
			//std::cout << "BACKPROPAGATE: " << this << ": backpropagating parent" << std::endl;
			_parent->get().backpropagate(winner);
		}
	}
	std::string Node::to_string(int tabs) const
	{
		std::string string = std::to_string(_wins) + "/" + std::to_string(_simulations) + "\n";
		for(auto &[move, node]: _children)
			string += std::string(tabs + 1, '\t') + move + ": " + node.to_string(tabs + 1);
		return string;
	}
	std::ostream &operator<<(std::ostream &out, const Node &node) {return out << node.to_string();}
}