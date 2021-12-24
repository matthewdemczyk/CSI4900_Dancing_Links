#include "Sudoku.c"
#include <stdlib.h>
#include <math.h>
/*
    A general framework for heuristic search

    Generic optimization problem (minimization) for finding the minimum number of clues such that a Sudoku grid has exactly 1 solution
    -----------------------------------------------------------------------------------------------------------------------------------

    Set X                         : all combinations of the clues in the puzzle such that the number of clues is between 17 and 81

    Objective function p: X -> Z  : the "cost" function. in our case, it is the number of clues in the puzzle.

    feasability function          : find the number of solutions to a puzzle. if it has over 1 solution, it is not feasibile.

    neighbourhood definition      : a neighbourhood of a puzzle A is the set of all puzzles which have 1 clue removed from puzzle A, and A itself
*/



// returns the number of clues that puzzle has
int cost(int puzzle[9][9])
{
    int numClues = 0;
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            if (puzzle[r][c] != 0)
            {
                numClues++;
            }
        }
    }
    return numClues;
}

// returns true if the puzzle has a unique solution
int isFeasible(int puzzle[9][9])
{
    DancingLinksStruct dlx = initFaster(puzzle);
    int numSolutions = algorithmX(&dlx, 2, &nothing);
    return (numSolutions == 1);
}

// copies the inPuzzle to outPuzzle
void copyPuzzle(int inPuzzle[9][9], int outPuzzle[9][9])
{
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            outPuzzle[r][c] = inPuzzle[r][c];
        }
    }
}

//  struct used in hillclimb
typedef struct Clue {
    int row;
    int col;
} Clue;

// outPuzzles parameter is a buffer that the solution will be witten to
void hillclimb(int puzzle[9][9], int outPuzzle[9][9])
{
    // Make a copy of the puzzle to solve (since puzzle is just a pointer)
    int currentBestPuzzle[9][9];
    copyPuzzle(puzzle, currentBestPuzzle);
    int numClues = 81;

    // Populate neighbourhood array
    Clue neighbourArray[81];
    int index = 0;
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            neighbourArray[index].row = r;
            neighbourArray[index].col = c;
            index++;
        }
    }

    // Attempt to remove each neighbour
    int removedClue, swapIndex;
    Clue swap;
    for (int i = 0; i < 81; i++)
    {
        // Randomly choose a number between i ... 80 (inclusively)
        swapIndex = i + rand() / (RAND_MAX / (80 - i + 1) + 1);

        // Swap i and the random index chosen above
        swap = neighbourArray[swapIndex];
        neighbourArray[swapIndex] = neighbourArray[i];
        neighbourArray[i] = swap;

        // Store the clue that is about to be removed, then remove it
        removedClue = currentBestPuzzle[neighbourArray[i].row][neighbourArray[i].col];
        currentBestPuzzle[neighbourArray[i].row][neighbourArray[i].col] = 0;

        // Decrement the number of clues (since we just removed one)
        numClues--;

        // Check if the new puzzle is feasible
        if (!isFeasible(currentBestPuzzle))
        {
            // If the puzzle is not feasible with the clue removed, put it back
            currentBestPuzzle[neighbourArray[i].row][neighbourArray[i].col] = removedClue;
            // Increment the number of clues (since we just added one)
            numClues++;
        }
        if (numClues == 17)
        { // Since we know that no puzzle can have < 17 clues, exit early
            break;
        }
    }
    // "Return" the best solution
    copyPuzzle(currentBestPuzzle, outPuzzle);
}

// outPuzzles parameter is a buffer that the solution will be witten to
void simulated_annealing(int puzzle[9][9], int outPuzzle[9][9], float t, float alpha, int cMax)
{
    int currentPuzzle[9][9]; // This is the puzzle as we are adding/removing during the annealing
    int currentPuzzleCost = 81;
    copyPuzzle(puzzle, currentPuzzle);

    int bestPuzzle[9][9]; // This is the best puzzle we have found so far
    int bestPuzzleCost = 81;

    int row, col, r;
    for (int c = 0; c < cMax; c++)
    {
        // Choose a random clue in the puzzle
        row = rand() / (RAND_MAX / (9) + 1);
        col = rand() / (RAND_MAX / (9) + 1);

        // Check if the clue has been removed or not yet
        if (currentPuzzle[row][col] != 0)
        { // Case when the clue has not been removed yet
            // First remove the clue
            currentPuzzle[row][col] = 0;
            // Check if the puzzle is feasible with the clue removed
            if (!isFeasible(currentPuzzle))
            {
                // If it wasn't feasible, put the clue back
                currentPuzzle[row][col] = puzzle[row][col];
            } else {
                // If it was feasible, check if we reached a new best solution
                currentPuzzleCost--; // decrement cost because we removed a clue
                // If we are at a new best solution, save it
                if (currentPuzzleCost < bestPuzzleCost)
                {
                    copyPuzzle(currentPuzzle, bestPuzzle);
                    bestPuzzleCost = currentPuzzleCost;
                    if (currentPuzzleCost == 17)
                    {
                        // If we are at a 17 clue puzzle we know this is the best possible solution, so return early
                        copyPuzzle(bestPuzzle, outPuzzle);
                        return;
                    }
                }
            }
        } else
        { // Case when the clue has been removed
            // Decide if we want to put it back randomly, based on cooling schedule
            r = (float)rand()/(float)RAND_MAX;
            if (r < 1/(expf(1.0/t))) //probability for this to become half
            { //This means we decided to put the clue back
                currentPuzzle[row][col] = puzzle[row][col];
                currentPuzzleCost++; //increment cost becase we added back a clue
            }
        }
        // Advance the cooling schedule
        t = alpha * t;
    }
    // "Return" the solution
    copyPuzzle(bestPuzzle, outPuzzle);
}