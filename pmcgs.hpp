#pragma once
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>

namespace PMCGS
{
	std::map<std::string, int> wins;
	std::mutex mutex;
	template<typename T>
	void playout(const T &game, const std::string &move)
	{
		std::mt19937 generator(std::random_device{}());
		T new_game = game;
		new_game.do_move(move);
		while(!new_game.winner())
		{
			auto moves = new_game.moves();
			std::uniform_int_distribution<int> distribution(0, moves.size() - 1);
			new_game.do_move(moves.at(distribution(generator)));
		}
		std::lock_guard<std::mutex> lock(mutex);
		wins[move] += new_game.winner() == game.player();
	}
	template<typename T>
	std::string pmcgs(const T &game, int ms = 1000)
	{
		wins.clear();
		int simulations = 0;
		auto start = std::chrono::high_resolution_clock::now();
		while(std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count() < ms)
		{
			std::vector<std::thread> threads;
			for(auto &move: game.moves())
				threads.push_back(std::thread(playout<T>, game, move));
			for(auto &thread: threads)
				thread.join();
			simulations++;
		}
		auto best_move = wins.begin()->first;
		for(auto &[key, value]: wins)
		{
			//std::cout << key << ": " << value << "/" << simulations << std::endl;
			if(value > wins[best_move])
				best_move = key;
		}
		return best_move;
	}
}