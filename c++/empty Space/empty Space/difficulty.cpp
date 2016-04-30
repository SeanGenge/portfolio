#include "difficulty.h"

void setupDifficulty(Difficulty d, int* nMon, int* nArtefact)
{
	switch (d)
	{
	case beginner:
		*nMon = 15;
		*nArtefact = 10;
		break;
	case average:
		*nMon = 25;
		*nArtefact = 15;
		break;
	case impossible:
		*nMon = 35;
		*nArtefact = 25;
		break;
	}
}

std::string getDifficulty(Difficulty d)
{
	switch (d)
	{
	case beginner: return "beginner";
	case average: return "average";
	case impossible: return "impossible";
	}
}

Difficulty mapIntToDifficulty(int v)
{
	switch (v)
	{
	case 0: return beginner;
	case 1: return average;
	case 2: return impossible;
	}
}