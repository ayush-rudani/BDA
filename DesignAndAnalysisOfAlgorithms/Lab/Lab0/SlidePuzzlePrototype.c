/*
 * Main.c
 *
 *  Created on: 16-Jun-2018
 *      Author: JigarPandya
 *     Purpose: Slide Puzzle Game Development
 *              - logic building
 *              - Buffered input vs Unbuffered input
 *              - Top Down approach for distributing work amongst developers team
 *              - Array and functions.
 *              - Scancodes of keys
 *              - Symbolic Constants
 *              - Documentation
 *              - Random number generator
 *
 *              Limitation: Nonsolvable problems' inversion logic is not attempted for MAZESIZE other than 3.
 *              Rule to check if a 3x3 puzzle is solvable or not.
 *      	        It is not possible to solve an example of 3x3 if number of inversions is odd in the input state.
 *              Inversions mean any two numbers starting left to right top to bottom, not in ascending order of data.
 *				Linux platform only.
 *				Use of random generator is not optimized.
 *
 *              Tips for playing: See botoom of this source file. Or press H while running.
 */

#define MAZESIZE 3
#define STAR 0
#define SC_ENTER1 10
#define SC_UP_ARROW 65
#define SC_DOWN_ARROW 66
#define SC_RIGHT_ARROW 67
#define SC_LEFT_ARROW 68
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/* Populates maze array elements with random data values. 1..MAZESIZE*MAZESIZE -1.
 * In the last cell places STAR to indicate empty.
 */
void initializeMaze(int maze[][MAZESIZE]);

/*
 * Supporting function to initializeMaze; Pre-populates all cell with STAR.
 * This helps identifying empty shells while placing data 1..MAZESIZE*MAZESIZE -1 at random empty locations.
 */
void initilizeAllStar(int maze[][MAZESIZE]);

/* Not all 3X3 maze are solvable.
 * Rule to check if a 3x3 puzzle is solvable or not.
 * It is not possible to solve an example of 3x3 if number of inversions is odd in the input state.
 * Inversions mean any two numbers starting left to right top to bottom, not in ascending order of data.
 * input: prepopulated maze with STAR and 1..MAZESIZE*MAZESIZE -1.
 * output: Returns calculated invesion count.
 */
int calculateInversions(int maze[][MAZESIZE]);


/* Supporting function
 * input: 2D array row index i and column row index j as input with mazesize.
 * output: Pass by refernce, result is sotred into memory pointed by pointer pnumber.
 * Here,number like 1, 2, ... MAZESIZE*MAZESIZE . While array index i, j from 0.
 */
void indexToNumber(int *pnumber,int mazesize, int i, int j);

/*
 * Display 2-D Maze on the screen in matrix form.
 */
void displayMaze(int maze[MAZESIZE][MAZESIZE]);

/* Read a key input from keyboard.
 * Process the scancode and return as below:
 * 'H' ascii for key pressed 'H', Arrow keys scan code as defined UP-65, DOWN-66, Right-67, LEFT-68. Others 0;
 */
int inputKeyArrowOrOther(void);

/* Supporting function
 * Provide a number 1.. MAZESIZE*MAZESIZE -1 and it returns its corresponding i,j index location as if in the destination maze.
 * i.e. input number 1 provide (0,0) (i,j), ..., 6 provide (1,2) (i,j). etc.
 */
void numberToIndex(int number,int mazesize, int *i, int *j);

/*
 * Whenever any arrow key is pressed, program logic to move the empty/STAR cell accordingly. But few movements are not valid.
 * i.e. empty/STAR cell is the last most at 9 location then it can't move BOTTOM and RIGHT.
 * Output: Return value. 1 - valid movement. 0 - invalid movement.
 */
int isValidMovement(int maze[][MAZESIZE],int star_location,int key_pressed);

/* Make the actual move requested, if valid.
 * input: prepopulated maze, the current active key, and the location number 1..MAZESIZE*MAZESIZE where the STAR is stored currently.
 * Output: Swap the STAR with the respective number as per the arrow direction. Update the star locatoin in the caller's memory accordingly.
 *         Also, record total number of movements till now. And return the current total number of movements including the recent.
 */
int performMovement(int maze[][MAZESIZE],int key_pressed,int *pstar_location);

/* Display Congratulations message to winner when maze slide achieves the goal.
 * Also, display total number of movements user has performed to reach the objective.
 * input: total_movements is provided to this function as input-read.
 * Assumptions: The key_pressed achieves a valid movement. This check has been completed prior calling performMovement.
 */
void displayWinner(int total_movements);

/* After each performMovement, the resulting maze need to be matched as goal maze.
 * input: prepopulated maze may be also after a move
 * output: Return 1 if objective achieved. 0 if not.
 */
int validateResult(int maze[][MAZESIZE]);

/* It's a feature so that user need not press enter key after every arrows press.
 * This can be achieved by unbuffered I/O mechanism. The library getchar is buffered I/O mechanism.
 */
int unbufferedGetchar(void);

/*
 * Show tips as string message on the screen.
 */
void showTips();

int main()
{

//  Unsolvable Problem as INV count is 19 odd.
//	int maze[MAZESIZE][MAZESIZE]={{5, 	4, 	8},
//			{3, 	7, 	2},
//			{6, 	1, 	STAR}};
//Working example without auto initalizeMaze call.
//int maze[MAZESIZE][MAZESIZE]={{1, 8, 2},
//            {STAR, 4, 3},  // Value STAR defined is used for empty space. It is set 0 to count inversions correctly.
//            {7, 6, 5}};
//int maze[MAZESIZE][MAZESIZE]={{1, 2, 3},
//            {7, 8, 4},  // Value STAR defined is used for empty space. It is set 0 to count inversions correctly. Inversion count 6
//            {5, 6, STAR}};
//int maze[MAZESIZE][MAZESIZE]={{7, 5, 2},
//            {4, 6, 1},  // Value STAR defined is used for empty space. It is set 0 to count inversions correctly.Inversion count 16
//            {8, 3, STAR}};


	int maze[MAZESIZE][MAZESIZE];
	int key_pressed;
	int star_location;
	//Initialize maze with random numbers [1 TO CUBESIZE*CUBSESIZE-1] and last with *
	printf("\n ******* Slide Puzzle 3x3 - An example of Jigsaw! \n");
	printf("\n Auto Generation of solvable puzzle is in progress...");
	while(1)
	{
		initializeMaze(maze);
		int invcount=calculateInversions(maze);
		if((invcount%2)==0)
		{
			printf("\n Inversion count %d", invcount);
			printf("\n Generated Input has valid(even) number of inversions and it is a solvable puzzle. %d",invcount);
			break;
		}
	}

	//initializeMaze current implementation, places * at the last place only hence we may fix hard number but still below is generic logic to locate star.
	int i,j;
	for(i=0;i<MAZESIZE;i++)
	{
		for(j=0;j<MAZESIZE;j++)
		{
			if(maze[i][j]==STAR)
			{
				indexToNumber(&star_location,MAZESIZE, i,j);
				//printf("\n Star Location %d",star_location);
				break;
			}
		}
	}
	//Play the game till win or exit requested.
	printf("\n Play the game till you win or request exit via pressing any other key than arrows or H. \n Anytime press H for Tips.\n");
	while(1)
	{
		//Display maze
		displayMaze(maze);

		//Read movement request key. Return 0 for other. Code for arrows.
		key_pressed=inputKeyArrowOrOther();

		if(key_pressed=='H')
			showTips();
		else if(key_pressed)//its any arrow
		{

			//Validate the movement for boundary
			if(isValidMovement(maze, star_location, key_pressed)==0)
			{
				printf("\n Invalid movement");
				continue;
			}
		}
		else
		{
			printf("\n Do you want to quit? (Y/y for yes. Any other for No.)");
			int tempch=unbufferedGetchar();//Discard extra enter key in case of any other key then enter itself. Or that will be the key in the response y/n.
			if(tempch=='y')
				break;
			if(tempch!=SC_ENTER1)
			{
				key_pressed=getchar();
				if(key_pressed=='y' || key_pressed=='Y')
					break;
			}
			else
			{
				printf("\n Key pressed is other than any of the arrows.");
				continue;
			}
		}

		//Perform the movement provided the movement is valid.
		int total_movements;
		total_movements=performMovement(maze,key_pressed,&star_location);
		printf("\n Movement's Count %d",total_movements);

		//Validate for winning
		if(validateResult(maze))
		{
			//Display maze
			displayMaze(maze);

			//Display winner message and the total moves
			displayWinner(total_movements);
			break;
		}
		//getchar();
	}

	printf("\n Thank you for attempting Slide Puzzle - Jigsaw. Bye.\n");
	return (0);

}
