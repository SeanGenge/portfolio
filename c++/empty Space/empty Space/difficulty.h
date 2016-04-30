#pragma once
#include <string>

//All the difficulties
enum Difficulty
{
	beginner = 0,
	average = 1,
	impossible = 2
};

void setupDifficulty(Difficulty d, int* nMon, int* nArtefact);
//Returns the difficulty as a string
std::string getDifficulty(Difficulty d);
//Changes an int to difficulty
Difficulty mapIntToDifficulty(int v);
