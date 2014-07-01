/*
 * CoopTheme.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: marcuzzo
 */

#include "CoopTheme.h"

CoopTheme::CoopTheme(const QString& path, const QString &level, const int &cards, int const &maxMoves)
	: PairsTheme(path)
{
	m_level = level;
	m_cards = cards;
	m_maxMoves = maxMoves;
}

CoopTheme::~CoopTheme()
{
	// TODO Auto-generated destructor stub
}

