
#include <iostream>
#include "Game.h"

using namespace std;
/*****************************************************************************/
/*                                                                           */
/* Description:Defines the rules for the game.                               */
/*                                                                           */
/*****************************************************************************/

int main ()
{
	Game game;
	game.Instructions (cout);
	game.Init();
	game.Display (cout);
	string playerNames [] = {"NONE", "HUMAN", "COMPUTER"};
	playerType player = HUMAN;
	while (!game.Done())
	{
		cout << "Hi" << endl;
		int row, col;
		bool moveAvailable = false;
		if (player == HUMAN) // Human Player
			moveAvailable = game.ChooseMove(player, row, col, cin, cout);
		else
			moveAvailable = game.ChooseMove(player, row, col);
		if (moveAvailable)
		{
			game.MakeMove(player, row, col);
			game.Display(cout);
		}
		else
			cout << "No move available for " << playerNames[player] << " Player.\n";
		if (player == HUMAN)
			player = COMPUTER;
		else
			player = HUMAN;
	}
	cout << "GameOver! ";
	int winner = game.Winner(cout);
	return 0;
}
