#pragma once
#include <iostream>
#include <string>


struct CommandQuestion
{
	bool asked = false;
	std::string command = "";
	std::string definition = "";
	int points = 0;
};

inline std::ostream& operator<< (std::ostream& lhs, CommandQuestion& rhs)
{
	lhs << "Command: " << rhs.command << " Definition: " << rhs.definition << " Points: " << rhs.points;
	return lhs;
}

struct PlayerCard
{
	std::string name = "";
	int score = 0;
};
inline std::ostream& operator<< (std::ostream& lhs, PlayerCard& rhs)
{
	lhs << "Name: " << rhs.name << " Score: " << rhs.score;
	return lhs;
}