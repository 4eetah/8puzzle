#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <forward_list>

class Board
{
private:
	int dim;    	// dimensional
	int** blocks;	// array for board

	void boardToList(int ri, int ci, int rn, int cn, std::forward_list<Board*>  & l);
	bool exist(int i, int j);
	void exch(int** ar, int ri, int ci, int rn, int cn);
	
public:
	static int** arAlloc(int dim);

	Board()
	{
		dim = 0;
		blocks = NULL;
	}
	Board(int dim);
	Board(const Board* b);
	Board(int** blocks, int dim);
    	~Board();
// dimension of board
	int dimension();     
// hamming priority function, return number of blocks out of place

	int hamming();       

/* manhatten priority function
   sum of Manhattan distances between blocks and goal */
	int manhatten();     

// is this board the goal board?
	bool isGoal();       

/* a board obtained by exchanging two adjacent blocks 
   in the same row */
	Board twin();     

// does this board equal b?
	bool equals(const Board* b);  

// all neighboring boards
	std::forward_list<Board*> neighbors();  
	
// string representation of the board
    	std::string toString();
	
	int** getBlocks();
};
#endif
