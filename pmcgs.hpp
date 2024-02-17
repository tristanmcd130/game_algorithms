#pragma once
#include <string>
#include <vector>
#include <memory>

namespace PMCGS
{
	struct Game
	{
		virtual void do_move(const std::string &) = 0;
		virtual std::vector<std::string> moves() const = 0;
		virtual int player() const = 0;
		virtual int winner() const = 0;
		virtual std::shared_ptr<Game> copy() const = 0;
	};
	std::string pmcgs(const std::shared_ptr<Game> &, int = 1000);
}