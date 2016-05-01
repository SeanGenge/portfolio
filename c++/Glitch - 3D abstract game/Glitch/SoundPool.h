#pragma once

#include "MemoryPool.h"
#include "SoundManager.h"

/*
	This pool deals with sound objects. Makes it easier to play multiple sounds of the same type efficiently
*/

class SoundPool : public MemoryPool<Sound>
{
private:
	SoundManager* m_sManager;
	char* m_filename;
	int m_numItems;

	void initialize()
	{
		for (unsigned int i = 0; i < m_numItems; i++)
		{
			m_pool.push_back(std::make_pair(m_sManager->GetNewSound(m_filename), false));
		}
	}

public:
	SoundPool(int numItems, SoundManager* sm, char* filename)
	{
		m_sManager = sm;
		m_filename = filename;

		if (numItems < 1)
			m_numItems = 1;
		else
			m_numItems = numItems;

		initialize();
	}
};