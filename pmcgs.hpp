#include <map>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;

template<typename T>
T pmcgs(T state, int ms)
{
	map<T, int> wins;
	int simulations = 0;
	for(auto move : state.possible_moves())
		wins[state.do_move(move)] = 0;
	mt19937 generator(std::random_device{}());
	auto start = chrono::high_resolution_clock::now();
	while(chrono::duration<double, std::milli>(chrono::high_resolution_clock::now() - start).count() < ms)
	{
		for(auto &[key, value] : wins)
		{
			T new_state = key;
			while(!new_state.winner())
			{
				auto moves = new_state.possible_moves();
				uniform_int_distribution<int> distribution(0, moves.size() - 1);
				new_state = new_state.do_move(moves.at(distribution(generator)));
			}
			if(new_state.winner() == state.player())
				value++;
		}
		simulations++;
	}
	T best_state = wins.begin()->first;
	for(auto &[key, value] : wins)
	{
		if(value > wins[best_state])
			best_state = key;
	}
	return best_state;
}
