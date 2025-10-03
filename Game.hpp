#pragma once
#include "Data.hpp"
#include "List.hpp"
#include "Messages.hpp"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>

#define leaderboardFile "leaderboard.csv"
#define commandsFile "commands.csv"


using std::cout;
using std::cin;



class Game
{
public:
	Game()
	{
		srand(time(0));
		initLeaderboard();
		initCommands();
	}
	~Game()
	{
	}
	void run(); // run main loop
	void logic(); // game logic
	void askQuestions(); // ask questions
	void questionLogic(Node<CommandQuestion>*& question0, Node<CommandQuestion>*& question1, Node<CommandQuestion>*& question2); // selects questions
	void initLeaderboard(); // reads in and initialize leaderboard list
	void initCommands(); // reads in and initialize command list
	void csvParserLeaderboard(std::ifstream& inputFile); // parser for csv file - leaderboard
	void csvParserCommands(std::ifstream& inputFile); // parser for csv file- commands
	void addCommand(); // add a command
	void removeCommand(); // remove a command
	void setCommandInput(std::string command, std::string definition, int points); // set a command
	void getCommandInput(std::string& command, std::string& definition, int& points); // input for setting command
	void shuffleQuestions(); // shuffle questions in list
	void resetList(); // reset questions list- commands asked set back to "false"
	void addPlayer(std::string name, int score); // add player 
	void addCommand(std::string command, std::string definition, int points); // add command
	void writeLeaderBoard(); // write to outfile leaderboard.csv
	void writeCommandStorage(); // write to outfile commands.csv
	void updateLeaderBoard(); // updates leaderboard- add new player
	Node<CommandQuestion>* getNodeAt(int index); // helper function for question logic
	std::string namePrompt(); // prompt for name
	int menuOptions(); // read menu options, returns user choice
	int getOption(int max); // gets option input, returns within 1-max bounds
private:
	PlayerCard player;
	List<CommandQuestion> commandStorage;
	List<PlayerCard> leaderboard;
};
