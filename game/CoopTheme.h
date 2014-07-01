/*
 * CoopTheme.h
 *
 *  Created on: Jan 19, 2014
 *      Author: marcuzzo
 */

#ifndef COOPTHEME_H_
#define COOPTHEME_H_

#include "pairstheme.h"

class CoopTheme: protected PairsTheme
{
public:
	CoopTheme(const QString& path, const QString &level, const int &cards, int const &maxMoves);
	virtual ~CoopTheme();
	QString m_level(){return m_level;}
	int maxMoves(){return m_maxMoves;}
	int cards(){return m_cards;}

private:
	Qstring m_level;
	int m_cards;
	int m_maxMoves;

};

#endif /* COOPTHEME_H_ */
