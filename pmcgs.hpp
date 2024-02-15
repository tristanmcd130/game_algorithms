#pragma once
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <iostream>

namespace PMCGS
{
	template<typename T>
	std::string pmcgs(const T &game, int ms = 1000)
	{
		std::map<std::string, int> wins;
		for(auto move: game.moves())
			wins[move] = 0;
		std::mt19937 generator(std::random_device{}());
		auto start = std::chrono::high_resolution_clock::now();
		while(std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count() < ms)
		{
			for(auto &[key, value]: wins)
			{
				T new_game = game;
				new_game.do_move(key);
				while(!new_game.winner())
				{
					auto moves = new_game.moves();
					std::uniform_int_distribution<int> distribution(0, moves.size() - 1);
					new_game.do_move(moves.at(distribution(generator)));
				}
				if(new_game.winner() == game.player())
					value++;
			}
		}
		auto best_move = wins.begin()->first;
		for(auto &[key, value]: wins)
		{
			if(value > wins[best_move])
				best_move = key;
		}
		return best_move;
	}
}