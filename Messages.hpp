#pragma once
#include <iostream>
#include <cstdlib> // for system()
#include <thread> // for sleep
#include <chrono> // for seconds
//#include "list.hpp"
#include <ctime> 

#define WAITTINY 200
#define WAITHALF 500
#define WAITSHORT 700
#define WAITLONG 2000
using std::cout;
using std::cin;

struct Messages
{

	static void clearScreen() // found this code online - cross compatibility clearing console
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
	}

	static void wait(int time) // wait - to make interface pretty
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}

	static void displayCommandStorage(const List<CommandQuestion>& storage) // display contents of commands list
	{
		storage.displayContents();
	}

	static void displayLeaderboard(const List<PlayerCard>& storage) // display contents of leaderboard list
	{
		cout << "Leaderboard:\n";
		storage.displayContents();
	}

	static void displayRules() // display rules
	{
		cout << "RULES:\nThe user will be presented with 20 MCQs on linux commands and their scores will be tracked for maintaining leaderboard.\n";
		getContinue();
		clearScreen();
	}

	static void getContinue() // pauses until user inputs enter
	{
		cout << "Press enter to continue...\n";
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		cin.get();
	}

	static void message1() // starting game display
	{
		clearScreen();
		cout << "Starting game";
		wait(WAITTINY);
		cout << ".";
		wait(WAITTINY);
		cout << ".";
		wait(WAITTINY);
		cout << ".";
		wait(WAITTINY);
		cout << "\n";
		getContinue();
		clearScreen();
	}

	static void message2() // display welcome message
	{
		cout << "Welcome to Linux Trivia!\nA multiple choice question game aimed to test you on Linux command knowledge.\n";
		cout << "Press enter to continue...\n";
		cin.get();
		clearScreen();
	}

	static void message3()
	{
		cout << "Linux Trivia\n~~Main Menu~~\n1. View Rules\n2. Play New Game\n3. Add a Command\n";
		cout << "4. Remove a Command\n5. Display All Commands\n6. Show Leaderboard\n7. Save and Exit\n";
	}
	static void addCommandMessage()
	{
		std::cout << "Add a new command.\n";
	}
	static void addCommandMessage1()
	{
		std::cout << "Enter the command: ";
	}
	static void addCommandMessage2()
	{
		std::cout << "Enter the definition: ";
	}
	static void addCommandMessage3()
	{
		std::cout << "Enter number of points: ";
	}
	static void displayQuestions(CommandQuestion correctQuestion, CommandQuestion incorrectQuestion1, CommandQuestion incorrectQuestion2, int randomNumber)
	{
		switch (randomNumber)
		{
		case 1:
			displayQuestion(correctQuestion);
			displayQuestion(incorrectQuestion1);
			displayQuestion(incorrectQuestion2);
			break;
		case 2:
			displayQuestion(incorrectQuestion1);
			displayQuestion(correctQuestion);
			displayQuestion(incorrectQuestion2);
			break;
		case 3:
			displayQuestion(incorrectQuestion1);
			displayQuestion(incorrectQuestion2);
			displayQuestion(correctQuestion);
			break;
		}
	}
	static void displayQuestion(CommandQuestion question)
	{
		cout << question.definition << endl;
	}
	static void final(const PlayerCard& player)
	{
		std::cout << "Final score: " << player.score << std::endl;
	}
	static void displayTop3(List<PlayerCard>& leaderboard)
	{
		cout << "Top 3 leaderboard:\n";
		leaderboard.displayTop3();
	}
	static void postGame(List<PlayerCard>& leaderboard)
	{
		Messages::clearScreen();
		Messages::displayTop3(leaderboard);
		Messages::getContinue();
		Messages::clearScreen();
	}
};