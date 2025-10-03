#include "Game.hpp"

void Game::run()
{
	bool exit = false;
	int option = 0;

	Messages::message2();
	while (!exit) {

		option = menuOptions();

		Messages::clearScreen();
		switch (option)
		{
		case 1: // display rules
			Messages::displayRules();
			break;
		case 2: // start game
			Messages::message1();
			logic();
			Messages::postGame(leaderboard);
			break;
		case 3: // add a command
			Messages::addCommandMessage();
			addCommand();
			break;
		case 4: // remove a command
			removeCommand();
			break;
		case 5: // display all commands
			Messages::clearScreen();
			Messages::displayCommandStorage(commandStorage);
			Messages::getContinue();
			Messages::clearScreen();
			break;
		case 6: // show leaderboard
			Messages::clearScreen();
			Messages::displayLeaderboard(leaderboard);
			Messages::getContinue();
			Messages::clearScreen();
			break;
		case 7: // save and exit
			writeLeaderBoard();
			writeCommandStorage();
			exit = true;
		}
	}
	return;
}

void Game::logic() // runs through game logic
{
	shuffleQuestions(); // shuffle questions before begin
	addPlayer(namePrompt(), 0); // have player enter name
	Messages::wait(WAITTINY);
	Messages::clearScreen();
	askQuestions(); // ask questions
	Messages::clearScreen();
	Messages::final(player);
	Messages::wait(WAITLONG);
	updateLeaderBoard(); // update leaderboard following gameplay
	resetList(); // reset command list following gameplay- asked questions get reset to 'false'
}
void Game::askQuestions()
{
	int questionCount = 0;
	int maxQuestions = 4;
	int correctPosition = 0;
	Node<CommandQuestion>* current = commandStorage.getpHead();
	Node <CommandQuestion>* incorrect1 = nullptr;
	Node <CommandQuestion>* incorrect2 = nullptr;
	CommandQuestion* correctQuestion = nullptr;
	do
	{
		correctQuestion = current->getData();
		questionLogic(current, incorrect1, incorrect2);
		if (!correctQuestion->asked)
		{
			cout << "Score: " << player.score << "\n\n";
			cout << "Question " << questionCount + 1 << ":\n";
			correctPosition = (rand() % 3) + 1;
			std::cout << "Command: " << correctQuestion->command << std::endl << "\nSelect an answer:\n\n";
			Messages::displayQuestions(*correctQuestion, *incorrect1->getData(), *incorrect2->getData(), correctPosition);

			if (getOption(3) == correctPosition)
			{
				Messages::clearScreen();
				this->player.score += correctQuestion->points;
				std::cout << "Score: " << player.score << "\nCorrect!" << std::endl;
			}
			else
			{
				Messages::clearScreen();
				std::cout << "Score: " << player.score << "\nIncorrect!" << std::endl;
			}
		}
		current = current->getpNext();
		questionCount++;
		Messages::wait(WAITSHORT);
		Messages::clearScreen();
	} while (current->getpNext() != nullptr && questionCount < maxQuestions);
}



void Game::initLeaderboard()
{
	std::ifstream inputFile(leaderboardFile);
	if (!inputFile.is_open())
	{
		std::cerr << "Encountered error opening " << leaderboardFile << endl;
		return;
	}
	csvParserLeaderboard(inputFile);
	inputFile.close();
}

void Game::initCommands()
{
	std::ifstream inputFile(commandsFile);
	if (!inputFile.is_open())
	{
		std::cerr << "Encountered error opening " << commandsFile << endl;
		return;
	}
	csvParserCommands(inputFile);
}

void Game::csvParserLeaderboard(std::ifstream& inputFile)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);
		std::string name;
		std::string score;
		std::getline(iss, name, ',');
		std::getline(iss, score);
		int intScore = 0;
		intScore = std::stoi(score);
		addPlayer(name, intScore);
		leaderboard.updateLeaderBoard(player);
		player.name = "";
		player.score = 0;
	}
}
void Game::csvParserCommands(std::ifstream& inputFile)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);
		std::string command;
		std::string definition;
		std::string points;
		std::getline(iss, command, ',');
		std::getline(iss, definition, ',');
		std::getline(iss, points, ',');
		int intPoints = 0;
		intPoints = std::stoi(points);
		CommandQuestion newCommand;
		newCommand.command = command;
		newCommand.definition = definition;
		newCommand.points = intPoints;
		commandStorage.insertAtFront(newCommand);
	}
}

void Game::questionLogic(Node<CommandQuestion>*& question0, Node<CommandQuestion>*& question1, Node<CommandQuestion>*& question2)
{
	int totalCommands = commandStorage.sizeOf();
	if (totalCommands < 3)
	{
		std::cerr << "Not enough commands to generate question set.\n";
		question1 = question2 = nullptr;
		return;
	}

	int correctIdx = -1;

	Node <CommandQuestion>* pCurr = commandStorage.getpHead();
	for (int i = 0; pCurr != nullptr; i++, pCurr = pCurr->getpNext())
	{
		if (pCurr == question0)
		{
			correctIdx = i;
			break;
		}
	}
	int idx1, idx2;
	do {
		idx1 = rand() % totalCommands;
	} while (idx1 == correctIdx);

	do {
		idx2 = rand() % totalCommands;
	} while (idx2 == correctIdx || idx2 == idx1);

	question1 = getNodeAt(idx1);
	question2 = getNodeAt(idx2);
}

void Game::addCommand()
{
	std::string command = "";
	std::string definition = "";
	int points = 0;
	getCommandInput(command, definition, points);
	setCommandInput(command, definition, points);
}

void Game::removeCommand()
{
	std::string name = "";
	commandStorage.displayContents();
	std::cout << "Which command would you like to remove?\nEnter the command name: ";
	std::cin >> name;
	commandStorage.removeCommand(name);
}

void Game::setCommandInput(std::string command, std::string definition, int points)
{
	CommandQuestion newCommand;
	newCommand.command = command;
	newCommand.definition = definition;
	newCommand.points = points;
	commandStorage.insertAtFront(newCommand);
	if (commandStorage.getpHead() != nullptr)
	{
		std::cout << "Sucessfully added new command!\n";
	}
	else
	{
		std::cerr << "Failed to add new command!\n";
	}
}

void Game::getCommandInput(std::string& command, std::string& definition, int& points)
{

	std::string input;
	Messages::addCommandMessage1();
	std::getline(std::cin, input);
	std::getline(std::cin, input);
	while (input == "")
	{
		std::cerr << "Error. Please enter a valid command.\n";
		std::getline(std::cin, input);
	}
	command = input;
	Messages::addCommandMessage2();
	std::getline(std::cin, input);
	while (input == "")
	{
		std::cerr << "Error. Please enter a valid command.\n";
		std::getline(std::cin, input);
	}
	definition = input;
	definition = "\"" + definition + "\""; // append quotes
	Messages::addCommandMessage3();
	std::cin >> points;
	while (points < 1)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Error. Please enter valid points.\n";
		std::cin >> points;
	}
}

void Game::shuffleQuestions()
{
	std::vector<CommandQuestion> temp;
	Node<CommandQuestion>* current = commandStorage.getpHead();
	while (current != nullptr)
	{
		temp.push_back(*(current->getData()));
		current = current->getpNext();
	}

	commandStorage.clear();
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(temp.begin(), temp.end(), g);

	for (auto& q : temp) {
		commandStorage.insertAtFront(std::move(q));
	}
}

void Game::resetList()
{
	commandStorage.resetList();
}

void Game::addPlayer(std::string name, int score)
{
	this->player.name = name;
	this->player.score = score;
}

void Game::addCommand(std::string command, std::string definition, int points)
{
	CommandQuestion newCommand;
	newCommand.command = command;
	newCommand.definition = definition;
	newCommand.points = points;
	commandStorage.insertAtFront(newCommand);
}

void Game::writeLeaderBoard()
{
	std::ofstream outputFile(leaderboardFile);
	if (outputFile.is_open())
	{
		leaderboard.writeOut(outputFile);
		outputFile.close();
	}
}
void Game::writeCommandStorage()
{
	std::ofstream outputFile(commandsFile);
	if (outputFile.is_open())
	{
		commandStorage.writeOut(outputFile);
		outputFile.close();
	}
}

void Game::updateLeaderBoard()
{
	leaderboard.updateLeaderBoard(player);
	player.name = "";
	player.score = 0;
}


Node<CommandQuestion>* Game::getNodeAt(int index)
{
	Node<CommandQuestion>* pCurr = commandStorage.getpHead();
	for (int i = 0; i < index; i++)
	{ 
		pCurr = pCurr->getpNext();
	}
	return pCurr;
}

std::string Game::namePrompt()
{
	std::string name = "";
	while (name == "")
	{
		cout << "Please enter your name: ";
		cin >> name;
	}
	return name;
}

int Game::menuOptions()
{
	Messages::message3();
	return getOption(7);
}

int Game::getOption(int max)
{
	int option = 0;
	cin >> option;
	while (option < 1 || option > max)
	{
		cout << "Invalid input!\nPlease enter an option from the displayed list.\n";
		cin >> option;
	}
	return option;
}
