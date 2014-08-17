#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"
#include <forward_list>

class Solver
{
private:
	bool solvable;
	class Node
	{
	public:
		Board* board;
		Node* prev;
		int moves;
		Node()
		{
			board = NULL;
			prev = NULL;
			moves = 0;
		}
		Node(Board* board, Node* prev, int moves)
		{
			this->board = board;
			this->prev = prev;
			this->moves = moves;
		}
	};
	Node* result;

	static bool ByManhatten(Node*, Node*);
	static bool ByHammington(Node*, Node*);

public:
// Find a solution to the initial board (using the A* algorithm)
	Solver(Board* initial);

// Is the initial board solvable?
	bool isSolvable(); 

// min number of moves to solve initial board; -1 if no solution
	int moves();

// sequence of boards in a shortest solution;
	std::forward_list<Board*> solution();
};
#endif
