/* Best-first search.
A solution to the problem that illustrates a general artificial intelligence
methodology known as the A* search algorithm.
We define a search node of the game to be a board, 
the number of moves made to reach the board, and the previous search node. 
First, insert the initial search node (the initial board, 0 moves, and a null previous search node)
into a priority queue. Then, delete from the priority queue the search node with the minimum priority,
and insert onto the priority queue all neighboring search nodes
(those that can be reached in one move from the dequeued search node).
Repeat this procedure until the search node dequeued corresponds to a goal board.
The success of this approach hinges on the choice of priority function for a search node */

#include "Solver.h"
#include <queue>

bool Solver::ByManhatten(Node* o1, Node* o2)
{
	int prior1 = o1->board->manhatten() + o1->moves;
	int prior2 = o2->board->manhatten() + o2->moves;
	return prior1 > prior2;
}
bool Solver::ByHammington(Node* o1, Node* o2)
{
	int prior1 = o1->board->hamming() + o1->moves;
	int prior2 = o2->board->hamming() + o2->moves;
	return prior1 > prior2;
}

Solver::Solver(Board* initial)
{
	if (initial == NULL)
		return;

	Node* first = new Node(initial, NULL, 0);

	Board init_twin = initial->twin();
	Node* first_twin = new Node(&init_twin, NULL, 0);
	
	Node* minPq1;
	Node* minPq2;

	std::priority_queue<Node*, std::vector<Node*>, bool (*)(Node*, Node*)> pq(ByManhatten);
	std::priority_queue<Node*, std::vector<Node*>, bool (*)(Node*, Node*)> pq_twin(ByManhatten);

    if ((minPq1 = first)->board->isGoal())
	{
		result = minPq1;
		solvable = true;
		return;
	}

    if ((minPq2 = first_twin)->board->isGoal())
	{
		result = minPq2;
		solvable = false;
		return;
	}

	for (Board* b : minPq1->board->neighbors())
        pq.push(new Node(b, minPq1, minPq1->moves + 1));

    for (Board* b : minPq2->board->neighbors())
        pq_twin.push(new Node(b, minPq2, minPq2->moves + 1));

/*Because search nodes corresponding to the same board are enqueued on the priority queue many times,
when considering the neighbors of a search node,
don't enqueue a neighbor if its board is the same as the board of the previous search node*/

    while (!(minPq1 = pq.top())->board->isGoal() &&
            !(minPq2 = pq_twin.top())->board->isGoal())
    {
        pq.pop();
        pq_twin.pop();

        for (Board* b : minPq1->board->neighbors())
            if(!b->equals(minPq1->prev->board))
            {
                pq.push(new Node(b, minPq1, minPq1->moves+1));
            }

        for (Board* b : minPq2->board->neighbors())
            if(!b->equals(minPq2->prev->board))
            {
                pq_twin.push(new Node(b, minPq2, minPq2->moves+1));
            }
    }

    result = minPq1->board->isGoal() ? minPq1 : minPq2;
    solvable = (result == minPq1);
}

// Not all initial boards can lead to the goal board
bool Solver::isSolvable()
{
	return solvable;
}

int Solver::moves()
{
	if(!solvable) return -1;
	return result->moves;
}

std::forward_list<Board*> Solver::solution()
{
	std::forward_list<Board*> l;
	Node* ans = result;
	l.push_front(ans->board);
	while (ans->prev != NULL)
	{
		ans = ans->prev;
		l.push_front(ans->board);
	}
	return l;
}
