#include "Entity.h"

int Entity::_numEntity = 0;

Entity::Entity()
{
	m_entId = _numEntity;
	_numEntity++;
}

Entity::~Entity()
{
	_numEntity--;
}