/*
Program: PA1: Linux Commands Matching Games
Author: Troy Muehlbauer
Date: 9/18/2025
Description: This program runs 20 questions in which the user must answer correctly for points.

Remarks: This program was definitely somewhat of a challenge. Between not having coded for a few months
and some of the templating process (which I ran into a couple issues with), this assignment took me a fair
bit of time to put together. Future assignments I would like to improve modularity, clarity of my code,
and improve program logic.

An advantage for using a linked list for this problem would be the modularity of nodes, which allow for solid memory management
and expandability capability. A disadvantage I would say would be the ease of use of using something like an array in which
things like randomizing and selection of data can be done very easily.
*/

#include "Game.hpp"

int main()
{

	Game game;
	game.run();

	return 0;
}