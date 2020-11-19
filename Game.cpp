/*****************************************************************************/
/*                                                                           */
/* File: Game.cpp                                                            */
/* Author: Tristan Petty                                                     */
/*                                                                           */
/*****************************************************************************/

#include "Game.h"
#include <iomanip>

/*****************************************************************************/
/*                                                                           */
/* Function: Cell                                                            */ 
/* Input parameters: None                                                    */ 
/* Return value: None                                                        */ 
/* Description: Creates the cells which our board                            */
/* is composed of.                                                           */
/*****************************************************************************/

Game::Cell::Cell ()
{
	owner = NONE;
	cellScore = -1;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Display                                                         */ 
/* Input parameters: Ostream & outs                                          */ 
/* Return value: None                                                        */ 
/* Description: Responsible for how output is displayed, how the board looks */
/*                                                                           */
/*****************************************************************************/

void Game::Cell::Display (ostream & outs)
{
	char symbols []  {'-', 'X', 'O'};
	outs << "|"  << symbols[owner] << "|" ;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Game                                                            */ 
/* Input parameters: None                                                    */ 
/* Return value: None                                                        */ 
/* Description: Keeps count of the score of the Humana and AI                */
/*                                                                           */
/*****************************************************************************/

Game::Game ()
{
	score[0] = 0;
	score[HUMAN] = 0;
	score[COMPUTER] = 0;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Instructions                                                    */ 
/* Input parameters: ostream & outs                                          */ 
/* Return value: None                                                        */ 
/* Description: Explains to user how the game works and how to enter         */
/* commands                                                                  */
/*****************************************************************************/

void Game::Instructions (ostream & outs)
{
  outs << setw(20) << "----Instructions----" << endl;
  outs << "Reversii is a two player game played with black or white pieces." << endl;
  outs << "In order to win the game, you must have more of your pieces";
  outs << " occupying the board when there are no valid moves left." << endl;
    outs << "In order to win you must out flank your opponent to capture their space." << endl;
    outs << "In order to flank, two of your pieces sandwhich any number of their pieces." << endl;
	    outs << "The way the game ends is when there are no valid moves left"
             << "for either player" << endl;
	    outs << "Good Luck and Have Fun." << endl << endl;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Init                                                                  */ 
/* Input parameters: None                                                         */ 
/* Return value: None                                                             */ 
/* Description:                                                              */
/*                                                                           */
/*****************************************************************************/

void Game::Init ()
{
	Cell cell;
	for (int r = 1; r <= ROWS; r++)
		for (int c = 1; c <= COLS; c++)
			board[r][c] = cell;
	board[ROWS/2][COLS/2].owner = COMPUTER;
	board[ROWS/2][COLS/2+1].owner = HUMAN;
	board[ROWS/2+1][COLS/2].owner = HUMAN;
	board[ROWS/2+1][COLS/2+1].owner = COMPUTER;
	score[HUMAN] = 2;
	score[COMPUTER] = 2;
}

/*****************************************************************************/
/*                                                                           */
/* Function: Display                                                         */ 
/* Input parameters: ostream & outs                                          */ 
/* Return value: None                                                        */ 
/* Description: Gives a display of the board so user can play.               */
/*                                                                           */
/*****************************************************************************/

void Game::Display (ostream & outs)
{
  int colScore = 0;
  int rowScore = 1;
	outs << "My Game!" << endl;
	outs << "Scores\tHUMAN: " << score[HUMAN] << ";\tCOMPUTER: " << score[COMPUTER] << endl;
	outs << "  1  2  3  4  5  6  7  8  " << endl;
	for (int r = 1; r <= ROWS; r++)
	{
		for (int c = 1; c <= COLS; c++)
		{
		  if(c == 1)
		    {
		      outs << rowScore;
		  }

			board[r][c].Display(outs);
		}
		rowScore++;
		colScore++;
		outs << endl;
	}

}

/*****************************************************************************/
/*                                                                           */
/* Function: CheckBoard                                                      */ 
/* Input parameters: playerType                                              */ 
/* Return value: Bool                                                        */ 
/* Description: Checks to see all possible moves on the board.               */
/*                                                                           */
/*****************************************************************************/

bool Game::CheckBoard (playerType Who)
{
	bool isValidMove = false;
        for (int i=1; i <= ROWS; i++) //row                                                                                    
        {
                for (int j=1; j <= COLS; j++) //col                                                                            
                {
                        if (ValidMove(Who, i, j))
                                isValidMove = true;
                }
        }
        return isValidMove;
}


/*****************************************************************************/
/*                                                                           */
/* Function: MakeMove                                                        */ 
/* Input parameters: playerType, Row, Col                                    */ 
/* Return value: None                                                        */ 
/* Description: Takes in playerType, row and column and then makes the move  */
/*                                                                           */
/*****************************************************************************/

void Game::MakeMove (playerType Who, int Row, int Col)
{
	playerType other = Who == HUMAN ? COMPUTER : HUMAN;

	 //Move Case:Diagonally Top Left                                                                                                                                   
        int totalCount = 0;
        int count = 0;
        int r = Row-1;
        int c = Col-1;
        while ( r > 0 && c > 0 && board[r][c].owner != NONE && board[r][c].owner != Who)
        {
                count++;
                r--;
                c--;
        }
        if (count > 0 && board[r][c].owner == Who)
	  {
                totalCount += count;
	       for(int i = 0; i <= count; i++){
		board[Row-i][Col-i].owner = Who; 
	       }	
	}

	//Move Case:Diagonally Top Right                                                                                                                                 

	totalCount = 0;
         count = 0;
         r = Row-1;
         c = Col+1;
        while ( r > 0 && c <= COLS && board[r][c].owner != NONE && board[r][c].owner != Who)
        {
                count++;
                r--;
                c++;
	      
        }
        if (count > 0 && board[r][c].owner == Who)
        {
                totalCount += count;
         	for(int i = 0; i <= count; i++){
                        board[Row-i][Col+i].owner = Who;
                }
        }

	//Move Case:Diagonally Bottom Left                                                                                                                               

	totalCount = 0;
         count = 0;
         r = Row+1;
         c = Col-1;
	 while ( c > 0 && r <= ROWS && board[r][c].owner != NONE && board[r][c].owner != Who)
        {
                count++;
                r++;
                c--;
        }
        if (count > 0 && board[r][c].owner == Who)
        {
                totalCount += count;
         	for(int i = 0; i <= count; i++){
                        board[Row+i][Col-i].owner = Who;
                }
        }

	//Move Case:Diagonally Bottom Right                                                                                                                              

	totalCount = 0;
        count = 0;
        r = Row+1;
        c = Col+1;
        while (board[r][c].owner == other)
        {
                count++;
                r++;
                c++;
        }
        if (count > 0 && board[r][c].owner == Who)
        {
                totalCount += count;
         	for(int i = 0; i <= count; i++){
                        board[Row+i][Col+i].owner = Who;
                }
        }

	//Move Case:Directly Up                                                                                                                              
                                                                                  \
	totalCount = 0;
        count = 0;
        r = Row-1;
        c = Col;
        while ( r <= ROWS && board[r][c].owner != NONE && board[r][c].owner != Who)
        {
                count++;
                r--;
        }
        if (count > 0 && board[r][c].owner == Who)
        {
                totalCount += count;
                for(int i = 0; i <= count; i++){
                        board[Row-i][Col].owner = Who;
                }
        }

	 //Move Case:Directly Right                                                                                                                                        
                                                                                  \
	totalCount = 0;
	count = 0;
	r = Row;
        c = Col+1;
        while (c <= COLS && board[r][c].owner != NONE && board[r][c].owner != Who)
        {
                count++;
                c++;
	}       
        if (count > 0 && board[r][c].owner == Who)
        {
                totalCount += count;
                for(int i = 0; i <= count; i++){
                        board[Row][Col+i].owner = Who;
                }
        }

	 //Move Case:Directly Left                                                                                                                                       

	totalCount = 0;
	count = 0;
	r = Row;
        c = Col-1;
        while ( c <= COLS && board[r][c].owner != NONE && board[r][c].owner != Who)
        {
                count++;
		r--;
	}       
        if (count > 0 && board[r][c].owner == Who)
        {
                totalCount += count;
		board[Row][Col].owner = Who;
                for(int i = 0; i <= count; i++){
                        board[Row][Col-i].owner = Who;
                }
        }

	 //Move Case:Directly Down                                                                                                                                       
                                                                                  \
	totalCount = 0;
	count = 0;
	r = Row+1;
        c = Col;
        while ( r <= ROWS && board[r][c].owner != NONE && board[r][c].owner != Who)
        {
                count++;
                r++;
	}       
        if (count > 0 && board[r][c].owner == Who)
        {
                totalCount += count;
                for(int i = 0; i <= count; i++){
                        board[Row+i][Col].owner = Who;
                }
        }
	cout << totalCount;
	int hScore = 0;
	int cScore = 0;
	for (int r = 1; r <= ROWS; r++)
        {
                for (int c = 1; c <= COLS; c++)
                {
		  if(board[r][c].owner == HUMAN){
		    hScore++;
		  }
		  if(board[r][c].owner == COMPUTER){
		    cScore++;
		  }
		}
	}
	  score[0] = 0;
	  score[HUMAN] = hScore;
	  score[COMPUTER] = cScore;

	  board[Row][Col].owner = Who;
}
     

/*****************************************************************************/
/*                                                                           */
/* Function:                                                                 */ 
/* Input parameters:                                                         */ 
/* Return value:                                                             */ 
/* Description:                                                              */
/*                                                                           */
/*****************************************************************************/

bool Game::ValidMove (playerType Who, int Row, int Col)
{

  	if(Row < 1|| Row >= ROWS+1 || Col < 1 || Col >= COLS+1 )//move to top of validMove. 
    	{
	    	cout << "Out of bounds" << endl;
    		return false;
    	}

	if (board[Row][Col].owner != NONE)
                return false;

	// Sets other to be the other player (that is not Who).
	playerType other = Who == HUMAN ? COMPUTER : HUMAN;
        
	//Move Case:Diagonally Top Left                                                                                                        
        int totalCount = 0;
        int count = 0;
        int r = Row-1;
        int c = Col-1;
        while (board[r][c].owner == other)
        {
                count++;
                r--;
                c--;
        }
        if (count > 0 && board[r][c].owner == Who)
                totalCount += count;
	//Move Case:Directly Left                                                                                                                    
        count = 0;
        r = Row;
        c = Col-1;
        while (board[r][c].owner == other)
        {
                count++;
                c--;
        }
        if (count > 0 && board[r][c].owner == Who)
                totalCount += count;
	//Move Case: Diagonally Down Left                                                                                                                            
	count = 0;
        r = Row+1;
        c = Col-1;
        while (board[r][c].owner == other)
        {
                count++;
                r++;
                c--;
        }
        if (count > 0 && board[r][c].owner == Who)
                totalCount += count;

	//Move Case: Move Directly Down                                                                                                                            
	count = 0;
        r = Row+1;
        c = Col;
        while (board[r][c].owner == other)
        {
                count++;
                r++;
        }
        if (count > 0 && board[r][c].owner == Who)
                totalCount += count;
	//Move Case: Directly Up                                                                                                                            
	count = 0;
        r = Row-1;
        c = Col;
        while (board[r][c].owner == other)
        {
                count++;
                r--;
        }
        if (count > 0 && board[r][c].owner == Who)
                totalCount += count;
	//Move Case: Directly Right                                                                                                                          
	count = 0;
        r = Row;
        c = Col+1;
        while (board[r][c].owner == other)
        {
                count++;
                c++;
        }
        if (count > 0 && board[r][c].owner == Who)
                totalCount += count;
	//Move Case: Diagonally Up Right                                                                                                                           
	count = 0;
        r = Row-1;
        c = Col+1;
        while (board[r][c].owner == other)
        {
                count++;
                r++;
                c--;
        }
        if (count > 0 && board[r][c].owner == Who)
                totalCount += count;
	//Move Case: Diagonally Down Right                                                                                                                            
	count = 0;
        r = Row+1;
        c = Col+1;
        while (board[r][c].owner == other)
        {
                count++;
                r++;
                c++;
        }
        if (count > 0 && board[r][c].owner == Who)
	{
		totalCount += count;
	}


	if(totalCount > 0)
	{
		return true;
	}
	return false;
}

/*****************************************************************************/
/*                                                                           */
/* Function:                                                                 */ 
/* Input parameters:                                                         */ 
/* Return value:                                                             */ 
/* Description:  Prompt user for location of move                            */
/*                                                                           */
/*****************************************************************************/

bool Game::ChooseMove (playerType Who, int & Row, int & Col, istream & In, ostream & Out)
{  
  cout << "Enter Row number: " << endl;
  cin >> Row;
  cout << "Enter Column Number: " << endl;
  cin >> Col;

  //Case for when user enters invalid input
  
  while( !ValidMove( Who, Row, Col) )
  {
    cout << "You have entered an invalid move please, re-enter" << endl;
    cout << "Enter Row number: " << endl;
    cin >> Row;
    cout << "Enter Column Number: " << endl;
    cin >> Col;
  }
  return true;
}

/*****************************************************************************/
/*                                                                           */
/* Function: ChooseMove                                                      */ 
/* Input parameters: playerType , Row, Column                                */ 
/* Return value:                                                             */ 
/* Description: AI determines desired location of move                       */
/*                                                                           */
/*****************************************************************************/

bool Game::ChooseMove (playerType Who, int & Row, int & Col)
{
	// Go through every cell on the board.
	// Call IsValid for every cell
	// Return true for the first cell that IsValid returns true for
 	for (int r = 1; r <= ROWS; r++)
	{
		for (int c = 1; c <= COLS; c++)
		{
	  		if(ValidMove(Who, r, c))
			{
		  		Row = r;
		  		Col = c;
	    			return true;
	  		}
	  
		}
	}
	return false;
}
  
/*****************************************************************************/
/*                                                                           */
/* Function:Done                                                             */ 
/* Input parameters:None                                                     */ 
/* Return value:Bool                                                         */ 
/* Description: Determines whether or not a game is finished by checking if  */
/* both parties have any available moves                                     */
/*****************************************************************************/

bool Game::Done ()
{
	if(CheckBoard(HUMAN))
	{
		cout << "Human has moves available" << endl;
		return false;
	}
	if(CheckBoard(COMPUTER))
	{
		cout << "Computer has moves available" << endl;
		return false;
	}

	cout << "No moves available" << endl;
	return true;



/*
  bool noValidMoves = false;
	if(CheckBoard(HUMAN) == false && CheckBoard(COMPUTER) == false)
	  {
	    //If both cases are true then we finally have no more moves.
	    noValidMoves = true;
	}
	return noValidMoves;
*/}

/*****************************************************************************/
/*                                                                           */
/* Function: Winner                                                          */ 
/* Input parameters: Ostream & Outs                                          */ 
/* Return value: playerType                                                  */ 
/* Description: Returns the type of winner of the match and writes           */
/* a congratulatory message.                                                 */
/*****************************************************************************/

playerType Game::Winner (ostream & outs)
{
	playerType winner = NONE;
	if(score[HUMAN] > score[COMPUTER])
	{
	  //Human Win
		cout << "Congratulations, you have won." << endl;
		winner = HUMAN;
	}
	else if (score[HUMAN] == score[COMPUTER])
	{
	  //Tie
	  cout << "Human Score" << score[HUMAN] << "Computer Score"  << score[COMPUTER] << endl;
	  cout << "You have tied." << endl;
		winner = NONE;
	}
	else
	{
	  //Computer Win
		cout << "Computer has won the match" << endl;
		winner = COMPUTER;
	}
	return winner;

}
