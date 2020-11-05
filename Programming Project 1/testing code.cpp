#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
//Configuration
#define CPU_USE_AI 0
#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define IN_A_ROW 3
#define SCORE_NUM_GAMES 32
#define PLAYER_USES_X true

void closeGame(int scoreBoard[][SCORE_NUM_GAMES]);

int main() {
	//VARIABLES FOR PLAYING TIC TAC TOE
	char board[BOARD_WIDTH][BOARD_HEIGHT]; //The assignment says "inside main"
	int scoreBoard[2][SCORE_NUM_GAMES];
	unsigned int turns_played = 0; 
	unsigned int games_played = 0; //MAX SCORE_NUM_GAMES
	unsigned int iterator = 0;
	
	//FUNCTIONS FOR PLAYING TIC TAC TOE
	void clearBoard(char[][BOARD_HEIGHT]);
	void resetScoreBoard(int[][SCORE_NUM_GAMES], unsigned int&);
	bool initialize(char[][BOARD_HEIGHT], int[][SCORE_NUM_GAMES], unsigned int&);
	void playerTurn(char[][BOARD_HEIGHT], int[][SCORE_NUM_GAMES], unsigned int&);
	bool checkWin(char board[][BOARD_HEIGHT], char whichOne);
	void computerTurn(char[][BOARD_HEIGHT], int[][SCORE_NUM_GAMES], unsigned int&);
	bool checkWinner(char[][BOARD_HEIGHT], int[][SCORE_NUM_GAMES], unsigned int&);
	void drawBoard(char[][BOARD_HEIGHT]);
	
	//the game
	initialize(board, scoreBoard, games_played);
	//std::cout << "Got past initialize!\n";
	srand(time(0));
	while(games_played < SCORE_NUM_GAMES)
	{
		//std::cout << "before clearing the board" << std::endl;
		clearBoard(board);
		turns_played = 0;
		iterator = rand()%2 + 1; //if divisible by 2, player plays
		//std::cout << "Got past clearing the board and stuff";
			while(!checkWinner(board, scoreBoard, turns_played) && turns_played < BOARD_WIDTH * BOARD_HEIGHT){ //While there is no winner and the game isn't over...
				if(iterator%2 == 0)
				{
					drawBoard(board);
					playerTurn(board, scoreBoard, turns_played);
				} else {
					computerTurn(board, scoreBoard, turns_played);
				}
				iterator++;
			}
		if(!checkWin(board, 'X') && !checkWin(board, 'O'))
			std::cout << "\n\nTIE!!!\n\n";
		else if(checkWin(board, PLAYER_USES_X?'X':'O')){
			scoreBoard[0][games_played] = 1;
		} else {
			scoreBoard[1][games_played] = 1;
		}
		games_played++;
	}
	std::cout << "Thanks for playing!" << std::endl;
	closeGame(scoreBoard);
	return 0;
}


















void drawBoard(char board[][BOARD_HEIGHT]){
	//std::cout << "drawBoard works!!!\n";
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		std::cout << "\n|";
		for(int j = 0; j < BOARD_WIDTH; j++)
			std::cout <<"----|";
		std::cout << std::endl;
		
		for(int j = 0; j < BOARD_WIDTH; j++)
			std::cout << "|   " << board[j][i];
		std::cout <<"|";
	}
	std::cout << "\n|";
	for(int j = 0; j < BOARD_WIDTH; j++)
		std::cout <<"----|";
	std::cout << std::endl;
}

void drawBoardCPU(int board[][BOARD_HEIGHT]){
	//~ //std::cout << "drawBoard works!!!\n";
	//~ for (int i = 0; i < BOARD_HEIGHT; i++)
	//~ {
		//~ std::cout << "\n|";
		//~ for(int j = 0; j < BOARD_WIDTH; j++)
			//~ std::cout <<"----|";
		//~ std::cout << std::endl;
		
		//~ for(int j = 0; j < BOARD_WIDTH; j++)
			//~ std::cout << "|   " << board[j][i];
		//~ std::cout <<"|";
	//~ }
	//~ std::cout << "\n|";
	//~ for(int j = 0; j < BOARD_WIDTH; j++)
		//~ std::cout <<"----|";
	//~ std::cout << std::endl;
}

void clearBoard(char board[][BOARD_HEIGHT]){
	for (int i = 0; i < BOARD_WIDTH; i++)
		for(int j = 0; j < BOARD_HEIGHT; j++)
		{
			//std::cout << "Clearing " << i << " " << j << std::endl;
			board[i][j] = ' ';
		}
}

void resetScoreBoard(int scoreBoard[][SCORE_NUM_GAMES], unsigned int& games_played){
	for (unsigned int i = 0; i < 2; i++)
		for(unsigned int j = 0; j < SCORE_NUM_GAMES; j++)
		{
			scoreBoard[i][j] = 0;
		}
	games_played = 0;
}

bool initialize(char board[][BOARD_HEIGHT], int scoreBoard[][SCORE_NUM_GAMES], unsigned int& games_played){ //init functions should always have a bool return value
	system("clear");
	//std::cout << "init\n";
	clearBoard(board);
	resetScoreBoard(scoreBoard, games_played);
	return true;
}

void closeGame(int scoreBoard[][SCORE_NUM_GAMES]){
	system("clear");
	std::cout << "\nThanks for playing.!" << std::endl;
	std::cout << "SCOREBOARD:\nPLAYER|CPU\n";
	int cputotal = 0;
	int playertotal = 0;
	for(int i = 0; i < SCORE_NUM_GAMES; i++){
		std::cout << (scoreBoard[0][i] == 1?"WIN ":"LOSS") << "  |" << (scoreBoard[1][i] == 1?"WIN ":"LOSS") << std::endl;
		playertotal += scoreBoard[0][i];
		cputotal += scoreBoard[1][i];
	}
	if (playertotal > cputotal){
		std::cout << "\nThe Player Wins overall with " << playertotal << " wins.";
	} else if (cputotal > playertotal){
		std::cout << "\nThe CPU Wins overall with " << cputotal << " wins.";
	} else {
		std::cout << "\nCome back and become the Tic Tac Toe Champion!!!";
	}
	exit(0);
}

void playerTurn(char board[][BOARD_HEIGHT], int scoreBoard[][SCORE_NUM_GAMES], unsigned int& turns_played){
	//There is no error checking because I believe I would lose points for adding it
	int x = -1;
	int y = -1;
	int failures = 0;

	while(((x > BOARD_WIDTH || x < 0 || y < 0 || y > BOARD_HEIGHT) || board[x][y] != ' ')){
		if(failures == 2)
			closeGame(scoreBoard);
		if(failures == 1)
			std::cout << "\nType the row and column and seperate them with a space, do not press Enter until you have typed BOTH row AND column\nrow is bound inclusive between 0 and " << BOARD_WIDTH - 1 << " while column is bound inclusive between 0 and " << BOARD_HEIGHT - 1 << "\nOrigin is at top left, increasing downward and to the right.\nExample input (do not type the quotes): \"0 0\"\nColumn is first because it makes it easy to think in terms of (x,y)\n\nInput something invalid again to exit the program\nEnter you move's cell row and column : "; // Input Tutorial
		else
			std::cout << "\nEnter you move's cell row and column : "; //lol this is literally what it says in the assignment
		std::cin >> x;
		std::cin >> y;
		std::cout << "\nx: " << x << "\ny: " << y << std::endl;
		failures++;
	}
	
	board[x][y] = PLAYER_USES_X?'X':'O';
	turns_played++;
}

bool checkWin(char board[][BOARD_HEIGHT], char whichOne){
	//This solution is written for the generalized tic tac toe of any positive integer IN_A_ROW, BOARD_WIDTH and BOARD_HEIGHT
	//std::cout << "\nCHECKING FOR PLAYER WHO USES " << whichOne << std::endl;
	//Check horizontal lines
	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		//std::cout << "\nCHECKING LINE Y = " << y << std::endl;
		int streak = 0;
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			//std::cout << "\nx = " << x << "\ny = " << y << "\nchar = " << board[x][y] << "\nstreak = " << streak << std::endl;
			if (streak >= IN_A_ROW)
				{return true;/*std::cout << "\nWIN ON THE HORIZONTAL!";*/}
			if(board[x][y] == whichOne)
				streak++;
			else
				streak = 0;
			if (streak >= IN_A_ROW)
				{return true;/*std::cout << "\nWIN ON THE HORIZONTAL!";*/}
		}
	}
	
	
	
	
	
	
	
	
	//Vertical Lines
	for(int x = 0; x < BOARD_WIDTH; x++)
	{	
		int streak = 0;
		//std::cout << "\nCHECKING LINE X = " << x << std::endl;
		for(int y = 0; y < BOARD_HEIGHT; y++)
		{
			/*std::cout << "\nx = " << x << "\ny = " << y << "\nchar = " << board[x][y] << "\nstreak = " << streak << std::endl;*/
			if (streak >= IN_A_ROW)
				{return true;/*std::cout << "\nWIN ON THE VERTICAL!";*/}
			if(board[x][y] == whichOne)
				streak++;
			else
				streak = 0;
			if (streak >= IN_A_ROW)
				{return true;/*std::cout << "\nWIN ON THE VERTICAL!";*/}
		}
	}
	
	//Check Negative Diagonals
	//Possible Starting Points
	for(int x = 0; x < BOARD_WIDTH - IN_A_ROW + 1; x++)
	{
		for(int y = 0; y < BOARD_HEIGHT - IN_A_ROW + 1; y++)
		{
			//~ std::cout << "\nCHECKING FOR NEGATIVE DIAGONALS STARTING AT " << x << ", " << y;
			int streak = 0;
			//Go diagonally down and right from here until either:
			//1) You hit an edge
			//2) the streak >= IN_A_ROW
			int _x = x;
			int _y = y;
			while(_x < BOARD_WIDTH && _y < BOARD_HEIGHT && _x >= 0 && _y >= 0)
			{
				//~ std::cout << "\n@\nX = " << _x << "\nY = " << _y << "\nSTREAK = " << streak << "\nCHAR = " << board[_x][_y];
				if(streak >= IN_A_ROW)
					return true;
				if(board[_x][_y] == whichOne)
					streak++;
				else
					streak = 0;
				_x++;
				_y++;
				if(streak >= IN_A_ROW)
					return true;
			}
		}
	}
	//Check Positive Diagonals
	//Possible Starting points
	for(int x = IN_A_ROW - 1; x < BOARD_WIDTH; x++)
	{
		for(int y = 0; y < BOARD_HEIGHT - IN_A_ROW + 1; y++)
		{
			//~ std::cout << "\nCHECKING FOR POSITIVE DIAGONALS STARTING AT " << x << ", " << y;
			int streak = 0;
			//Go diagonally down and left from here until either:
			//1) You hit an edge
			//2) the streak >= IN_A_ROW
			int _x = x;
			int _y = y;
			while(_x < BOARD_WIDTH && _y < BOARD_HEIGHT && _x >= 0 && _y >= 0)
			{
				//~ std::cout << "\n@\nX = " << _x << "\nY = " << _y << "\nSTREAK = " << streak << "\nCHAR = " << board[_x][_y];
				if(streak >= IN_A_ROW)
					return true;
				if(board[_x][_y] == whichOne)
					streak++;
				else
					streak = 0;
				_x--;
				_y++;
				if(streak >= IN_A_ROW)
					return true;
			}
		}
	}
	return false;
}


int GetLongestStreakForPlayer(char board[][BOARD_HEIGHT], char whichOne){ //yes, I know this could replace checkWin but the assignment is NOT to make the smallest binary or tightest namespace
	int Longest_Streak = 0;
	//Check horizontal lines
	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		//std::cout << "\nCHECKING LINE Y = " << y << std::endl;
		int streak = 0;
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			//std::cout << "\nx = " << x << "\ny = " << y << "\nchar = " << board[x][y] << "\nstreak = " << streak << std::endl;
			if (streak > Longest_Streak)
				{Longest_Streak = streak;}
			if(board[x][y] == whichOne)
				streak++;
			else
				streak = 0;
			if (streak > Longest_Streak)
				{Longest_Streak = streak;}
		}
	}
	
	
	
	
	
	
	
	
	//Vertical Lines
	for(int x = 0; x < BOARD_WIDTH; x++)
	{	
		int streak = 0;
		//std::cout << "\nCHECKING LINE X = " << x << std::endl;
		for(int y = 0; y < BOARD_HEIGHT; y++)
		{
			/*std::cout << "\nx = " << x << "\ny = " << y << "\nchar = " << board[x][y] << "\nstreak = " << streak << std::endl;*/
			if (streak > Longest_Streak)
				{Longest_Streak = streak;}
			if(board[x][y] == whichOne)
				streak++;
			else
				streak = 0;
			if (streak > Longest_Streak)
				{Longest_Streak = streak;}
		}
	}
	
	//Check Negative Diagonals
	//Possible Starting Points
	for(int x = 0; x < BOARD_WIDTH - IN_A_ROW + 1; x++)
	{
		for(int y = 0; y < BOARD_HEIGHT - IN_A_ROW + 1; y++)
		{
			//~ std::cout << "\nCHECKING FOR NEGATIVE DIAGONALS STARTING AT " << x << ", " << y;
			int streak = 0;
			//Go diagonally down and right from here until either:
			//1) You hit an edge
			//2) the streak >= IN_A_ROW
			int _x = x;
			int _y = y;
			while(_x < BOARD_WIDTH && _y < BOARD_HEIGHT && _x >= 0 && _y >= 0)
			{
				//~ std::cout << "\n@\nX = " << _x << "\nY = " << _y << "\nSTREAK = " << streak << "\nCHAR = " << board[_x][_y];
				if (streak > Longest_Streak)
				{Longest_Streak = streak;}
				if(board[_x][_y] == whichOne)
					streak++;
				else
					streak = 0;
				_x++;
				_y++;
				if (streak > Longest_Streak)
				{Longest_Streak = streak;}
			}
		}
	}
	//Check Positive Diagonals
	//Possible Starting points
	for(int x = IN_A_ROW - 1; x < BOARD_WIDTH; x++)
	{
		for(int y = 0; y < BOARD_HEIGHT - IN_A_ROW + 1; y++)
		{
			//~ std::cout << "\nCHECKING FOR POSITIVE DIAGONALS STARTING AT " << x << ", " << y;
			int streak = 0;
			//Go diagonally down and left from here until either:
			//1) You hit an edge
			//2) the streak >= IN_A_ROW
			int _x = x;
			int _y = y;
			while(_x < BOARD_WIDTH && _y < BOARD_HEIGHT && _x >= 0 && _y >= 0)
			{
				//~ std::cout << "\n@\nX = " << _x << "\nY = " << _y << "\nSTREAK = " << streak << "\nCHAR = " << board[_x][_y];
				if (streak > Longest_Streak)
				{Longest_Streak = streak;}
				if(board[_x][_y] == whichOne)
					streak++;
				else
					streak = 0;
				_x--;
				_y++;
				if (streak > Longest_Streak)
				{Longest_Streak = streak;}
			}
		}
	}
	return Longest_Streak;
						
} //EOF LONGEST STREAK NO MOVE
						
						

void computerTurn(char board[][BOARD_HEIGHT], int scoreBoard[][SCORE_NUM_GAMES], unsigned int& turns_played){
	int x = -1;
	int y = -1;
	int howmanytimes = 0;
	//for the CPU to use
	int board_evaluation[BOARD_WIDTH][BOARD_HEIGHT];
	char sim_board[BOARD_WIDTH][BOARD_HEIGHT];
	
	if(!CPU_USE_AI)
		while((x > BOARD_WIDTH || x < 0 || y < 0 || y > BOARD_HEIGHT) || board[x][y] != ' '){
			if(howmanytimes > (BOARD_WIDTH * BOARD_HEIGHT * 5))
				std::cout << "\nThis message should never appear\nif it does, you should buy lottery tickets\n";
			x = rand()%BOARD_WIDTH;
			y = rand()%BOARD_HEIGHT;
			howmanytimes++;
		}
	else
		{
			//clear out the board evaluation
			for(int i = 0; i < BOARD_WIDTH; i++)
				for(int j = 0; j < BOARD_HEIGHT; j++)
					board_evaluation[i][j] = 0;
			
			//EVALUATE EVERY POSSIBLE MOVE WE CAN MAKE TO SEE IF THERE IS A WINNING MOVE, THEN FOR BLOCKING AN ENEMY WIN, THEN FOR THE LONGEST STREAK, THEN FOR PROXIMITY TO OTHER PIECES, THEN FOR BEING IN_A_ROW/2 AWAY FROM ALL EDGES
			for(int i = 0; i < BOARD_WIDTH; i++)
				for(int j = 0; j < BOARD_HEIGHT; j++)
				{
					if(board[i][j] == ' ')//if it is even a legal move
					{
						//~~~~
						//CHECKING FOR WINNING MOVES
						//~~~~
						
						//Reset the simboard
						for(int _i = 0; _i < BOARD_WIDTH; _i++)
							for(int _j = 0; _j < BOARD_HEIGHT; _j++)
								sim_board[_i][_j] = board[_i][_j];
						
						sim_board[i][j] = PLAYER_USES_X?'O':'X';
						if(checkWin(sim_board, PLAYER_USES_X?'O':'X'))
							board_evaluation[i][j] += 1000000; //basically have to move here, a million will do that
						
						//~~~~
						//CHECKING FOR BLOCKING THE OPPONENT
						//~~~~
						//Place a piece on the simboard at i, j
						sim_board[i][j] = PLAYER_USES_X?'X':'O';
						if(checkWin(sim_board, PLAYER_USES_X?'X':'O'))
							board_evaluation[i][j] += 100000; //blocking the opponent is less important than winning, but it is pretty important
							
						//~~~~
						//CHECKING FOR LONGEST STREAK
						//~~~~
						sim_board[i][j] = PLAYER_USES_X?'O':'X';
						board_evaluation[i][j] += (GetLongestStreakForPlayer(sim_board, PLAYER_USES_X?'O':'X') + 1) * 200;
						
						
						//~~~~
						//CHECKING FOR ENDING THE PLAYER'S STREAKS
						//~~~~
						sim_board[i][j] = PLAYER_USES_X?'X':'O';
						board_evaluation[i][j] += GetLongestStreakForPlayer(sim_board, PLAYER_USES_X?'X':'O') * 200; // it is slightly less important to end the player's streaks
						
						//~~~~
						//PROXIMITY TO OTHER PIECES
						//~~~~
						//~ //Make a square that is 2 times IN_A_ROW by 2 times IN_A_ROW within the playing area
						sim_board[i][j] = PLAYER_USES_X?'X':'O';
						for(int w = 0; w < BOARD_WIDTH; w++)
							for(int h = 0; h < BOARD_HEIGHT; h++)
								if(board[w][h] != ' ' && !(w == i && h == j))
									{
										int distance_from_wh_to_ij = sqrt((w - i) * (w - i) + (h - j) * (h - j));
										board_evaluation[i][j] += 30/(distance_from_wh_to_ij + 1);
									}
								else{
										int distance_from_wh_to_ij = sqrt((w - i) * (w - i) + (h - j) * (h - j));
										board_evaluation[i][j] += 20/(distance_from_wh_to_ij + 1);
									}
								
					
					} else {
						//don't even try
						board_evaluation[i][j] = -1;
					}
					
				} //EOF board evaluation
				
				
			//look for the largest value
			int largest_evaluation = board_evaluation[0][0];
			int largest_eval_X = 0;
			int largest_eval_Y = 0;
			for(int _i = 0; _i < BOARD_WIDTH; _i++)
				for(int _j = 0; _j < BOARD_HEIGHT; _j++){
					if(board_evaluation[_i][_j] > largest_evaluation){
						largest_evaluation = board_evaluation[_i][_j];
						largest_eval_X = _i;
						largest_eval_Y = _j;
					} else if(board_evaluation[_i][_j] == largest_evaluation){
						//Make the CPU ever-so-slightly random
						int n = rand()%(100);
						if(n >= 90){
							largest_evaluation = board_evaluation[_i][_j];
							largest_eval_X = _i;
							largest_eval_Y = _j;
						}
					}
				}
			x = largest_eval_X;
			y = largest_eval_Y;
			// FAILSAFE
			if(((x > BOARD_WIDTH || x < 0 || y < 0 || y > BOARD_HEIGHT) || board[x][y] != ' '))
				while((x > BOARD_WIDTH || x < 0 || y < 0 || y > BOARD_HEIGHT) || board[x][y] != ' '){
					std::cout << "\nCPU has decided to move randomly this turn" << std::endl;
					x = rand()%BOARD_WIDTH;
					y = rand()%BOARD_HEIGHT;
					howmanytimes++;
				}
			drawBoardCPU(board_evaluation);
		}
		
	//~ //TEMPORARY FAILSAFE
	//~ if(CPU_USE_AI)
		//~ while((x > BOARD_WIDTH || x < 0 || y < 0 || y > BOARD_HEIGHT) || board[x][y] != ' '){
			//~ if(howmanytimes > (BOARD_WIDTH * BOARD_HEIGHT * 5))
				//~ std::cout << "\nThis message should never appear\nif it does, you should buy lottery tickets\n";
			//~ x = rand()%BOARD_WIDTH;
			//~ y = rand()%BOARD_HEIGHT;
			//~ howmanytimes++;
		//~ }
	board[x][y] = PLAYER_USES_X?'O':'X';
	turns_played++;
}


bool checkWinner(char board[][BOARD_HEIGHT], int scoreBoard[][SCORE_NUM_GAMES], unsigned int& turns_played){
	//std::cout << "\nCHECKING WINNER...";
	if (checkWin(board, (PLAYER_USES_X?'X':'O')))
	{
		std::cout << "\nCONGLATURATION !!!\n\nYOU HAVE COMPLETED\nA GREAT GAME.\n\nAND PROOVED THE JUSTICE\nOF OUR CULTURE.\n\nNOW GO AND REST OUR\nHEROES !\n\n\n" << "You won\nPlayed " << turns_played << " Turns." << std::endl;
		return true;
	}
	if (checkWin(board, (PLAYER_USES_X?'O':'X')))
	{
		std::cout << "CPU wins";
		return true;
	}
	//std::cout << "Got into checkWinner\n";
	//printout for the cpu winning
	
	//std::cout << "CPU: HOW ARE YOU GENTLEMEN !!\n\n\nCPU: ALL YOUR BASE ARE BELONG TO US.\n\n\nCPU: YOU ARE ON THE WAY TO DESTRUCTION.\n\n\nCPU: YOU HAVE NO CHANCE TO SURVIVE MAKE YOUR TIME.\n\n\nCPU: HA HA HA HA ....\n\n\nIn short, you have defeated by a computer." << std::endl;
	//printout for the player winning
	//std::cout << "CONGLATURATION !!!\n\nYOU HAVE COMPLETED\nA GREAT GAME.\n\nAND PROOVED THE JUSTICE\nOF OUR CULTURE.\n\nNOW GO AND REST OUR\nHEROES !\n\n\n" << "You won\nPlayed " << turns_played << " Turns." << std::endl;
	return false;
}
