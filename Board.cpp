#include "Board.h"
#include <sstream>

Board* goal = NULL;
	
int** Board::arAlloc(int dim)
{
	int** ar = new int*[dim];
	for (int i = 0; i < dim; i++)
		ar[i] = new int[dim];
    	return ar;
}
	
int** Board::getBlocks()
{
	return blocks;
}

/* Filling board with dimensional dim;
   Right bottom tile is empty tile to shift through board 
   and solve puzzle */  

Board::Board(int dim)
{
	this->dim = dim;
	blocks = arAlloc(dim);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			blocks[i][j] = i * dim + j + 1;
	blocks[dim-1][dim-1] = 0;
}

Board::Board(const Board* b)
{
	this->dim = b->dim;
	this->blocks = arAlloc(dim); 
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			this->blocks[i][j] = b->blocks[i][j];
}

Board::Board(int** blocks, int dim) 
{
	this->dim = dim;
	this->blocks = arAlloc(dim);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			this->blocks[i][j] = blocks[i][j];
}

Board::~Board()
{
	for (int i = 0; i < dim; i++)
            delete [] blocks[i];
	delete [] blocks;
}

int Board::dimension()
{
	return dim;
}

// The number of blocks in wrong position 
int Board::hamming()
{
	int wrong = 0;
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			if (blocks[i][j] != 0 && blocks[i][j] != i * dim + j + 1)
				wrong++;
	return wrong;
}
/* The sum of the Manhattan distances (sum of the vertical and horizontal distance) 
   from the blocks to their goal positions */
int Board::manhatten()
{
	int distance = 0;
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			if (blocks[i][j] != 0)
			{
				int row = (blocks[i][j] - 1) / dim;
				int col = (blocks[i][j] - 1) % dim;
				if(i != row || j != col)
				{
					row = (i > row) ? (i - row) : (row - i);
					col = (j > col) ? (j - col) : (col - j);
					distance += row + col;
				}
			}
	return distance;
}

bool Board::isGoal()
{
	if (goal == NULL || goal->dim != this->dim)
	    goal =  new Board(dim);
	return this->equals(goal);
}

Board Board::twin()
{
	Board t(this);
	if (t.blocks[0][0] != 0 && t.blocks[0][1] != 0)
		exch(t.blocks, 0, 0, 0, 1);
	else exch(t.blocks, 1, 0, 1, 1);
	return t;
}

bool Board::equals(const Board* that)
{
	if (that == this) return true;
	if (that == NULL) return false;
	if (this->dim != that->dim) return false;

	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			if (this->blocks[i][j] == that->blocks[i][j])
				;
			else return false;
	return true;
}

std::forward_list<Board*> Board::neighbors()
{
	std::forward_list<Board*> l;
	int i, j = 0;
	bool flag = false;
	for (i = 0; i < dim; i++)
	{
		for (j = 0; j < dim; j++)
			if (blocks[i][j] == 0) { flag = true; break; }
		if (flag) break;
	}
	if(exist(i+1, j)) boardToList(i, j, i+1, j, l);
	if(exist(i-1, j)) boardToList(i, j, i-1, j, l);
	if(exist(i, j+1)) boardToList(i, j, i, j+1, l);
	if(exist(i, j-1)) boardToList(i, j, i, j-1, l);

	return l;
}

void Board::boardToList(int ri, int ci, int rn, int cn, std::forward_list<Board*> & l)
{
	Board*b = new Board(this);
        exch(b->blocks, ri, ci, rn, cn);
	l.push_front(b);
}

bool Board::exist(int i, int j)	
{
	return (i >= 0) && (j >= 0) && (i < dim) && (j < dim);
}

void Board::exch(int** ar, int ri, int ci, int rn, int cn)
{
	ar[ri][ci] = ar[ri][ci] ^ ar[rn][cn];
	ar[rn][cn] = ar[ri][ci] ^ ar[rn][cn];
	ar[ri][ci] = ar[ri][ci] ^ ar[rn][cn];
}

std::string Board::toString()
{
	std::string s;
	std::stringstream ss;
       	s.append(std::to_string(dim) + "\n");
	for (int i =0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{	
			ss.width(4);
			ss << blocks[i][j];
		}
		ss << "\n";	
	}
	s.append(ss.str());
	return s;
}
