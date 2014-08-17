#include <iostream>
#include <fstream>
#include "Board.h"
#include "Solver.h"
#include "Draw.h"

using namespace std;

int main(int argc, char** argv)
{
    ifstream fin;

    if (argc == 2)
    {
        fin.open(argv[1]);
        if (!fin.is_open())
            cerr << "Could not open " << argv[1] << endl;
    }
    else
    {
        cerr << "Usage: " << argv[0] << " [board's filename]\n";
        exit(EXIT_FAILURE);
    }

    int N;
    fin >> N;
    int** blocks = Board::arAlloc(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fin >> blocks[i][j];

    Board* initial = new Board(blocks, N);
    Solver* solver = new Solver(initial);

    if (!solver->isSolvable())
        cout << "No solution possible\n";
    else
    {
        cout << "Minimum number of moves = " << solver->moves() << endl;
        if (N == 4)
        {
            Draw theDraw;
            theDraw.OnExecute(solver->solution());
        }
        else
        {
            for (Board* b : solver->solution())
                cout << b->toString() << endl;
        }
    }
    return 0;
}
