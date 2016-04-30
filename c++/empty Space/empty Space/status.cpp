#include "status.h"

void addStatus(std::string display, std::vector<std::string>* status)
{
	//If the size is larger than 5, remove the top element
	if (status->size() >= 8) status->erase(status->begin());
	status->push_back(display);
}

void clearStatus(std::vector<std::string>* status)
{
	status->clear();
}