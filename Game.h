 
#pragma once
#include <iostream>

using namespace std;

const int ROWS = 8;
const int COLS = 8;

/*****************************************************************************/
/*                                                                           */
/* Type: playerType                                                          */ 
/* Description: This enumerated type defines the different players in the    */
/* game. NONE is used to identify a cell that has not been claimed and a     */
/* tied game.                                                                */
/*                                                                           */
/*****************************************************************************/

#ifndef PLAYER_TYPE
#define PLAYER_TYPE
enum playerType {NONE, HUMAN, COMPUTER};
#endif

/*****************************************************************************/
/*                                                                           */
/* Class:                                                                    */ 
/* Description:                                                              */
/*                                                                           */
/*****************************************************************************/

class Game
{
	private:
		struct Cell
		{
			Cell ();
			void Display (ostream & outs);
			playerType owner;
			int cellScore;
		};
		Cell board [ROWS+2][COLS+2];
		int score[3];
		bool ValidMove (playerType Who, int Row, int Col);
		bool CheckBoard (playerType Who);
	public:
		Game ();
		void Instructions (ostream & outs);
		void Init ();
		void Display (ostream & outs);
		void MakeMove (playerType Who, int Row, int Col);
		bool ChooseMove (playerType Who, int & Row, int & Col, istream & In, ostream & Out);
		bool ChooseMove (playerType Who, int & Row, int & Col);
		bool Done ();
		playerType Winner (ostream & outs);
};
