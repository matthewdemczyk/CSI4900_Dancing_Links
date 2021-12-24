#include "Sudoku.c"
#include <time.h>

int numClues(int puzzle[9][9])
{
    int numClues = 0;
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            if (puzzle[r][c] != 0) {numClues++;};
        };
    };
    return numClues;
}

int main()
{
    /*
    int puzzle[9][9] = { //17 clue puzzle with 1 solution, retrieved from https://www.free-sudoku.com/sudoku.php?dchoix=evil
        {0, 1, 3, 0, 0, 0, 8, 0, 0},
        {0, 0, 0, 0, 5, 7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {6, 5, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 0, 3, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 7, 0, 0, 6, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 0, 3, 0, 1},
        {0, 0, 0, 0, 0, 0, 4, 0, 0},
    };
    */
    /*
    int puzzle[9][9] = { //16 clue puzzle with many solutions
        {6, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 6, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 0},
        {0, 0, 5, 0, 2, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 6, 0, 0, 0, 1, 0},
        {1, 0, 0, 5, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 7, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3},
    };
    */
    /*
    int puzzle[9][9] = { //blank puzzle
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    */
   /*
    int puzzle[9][9] = { //Puzzle from biliang's mutidoku tests, in the class SudokuGameTest.java, in function testAlgorithmXStatus4()
        {3,0,1,0,0,0,0,0,2},
        {0,0,0,0,0,0,0,7,0},
        {0,0,0,0,6,0,3,0,0},
        {0,3,0,5,0,7,0,0,1},
        {0,1,0,0,0,0,0,2,0},
        {0,0,0,0,1,3,0,0,0},
        {1,0,0,0,0,0,0,3,0},
        {0,0,6,0,2,0,0,0,0},
        {0,2,0,0,0,0,1,0,8},
    };
    */
    int puzzle[9][9] = { //17 clue puzzle with 1 solution, retrieved from https://www.free-sudoku.com/sudoku.php?dchoix=evil
        {6, 0, 0, 0, 0, 0, 0, 5, 0},
        {0, 0, 0, 0, 3, 0, 6, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 0},
        {0, 0, 5, 0, 2, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 6, 0, 0, 0, 1, 0},
        {1, 0, 0, 5, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 7, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3},
    };
    printf("Solving %d clue puzzle:\n", numClues(puzzle));
    printSudoku(puzzle);

    // Start intializing the puzzle
    clock_t beginInit = clock();
    DancingLinksStruct dlx = initFaster(puzzle);
    clock_t endInit = clock();

    // Start solving the puzzle
    clock_t beginX = clock();
    int threshold = 100000;
    int numSolutionsFound = algorithmX(&dlx, threshold, &nothing);
    clock_t endX = clock();

    // Printout of results
    long cpuCyclesTotalSpentInit = (endInit - beginInit);
    long cpuCyclesTotalSpentX = (endX - beginX);
    double timeSpentInit = ((double) cpuCyclesTotalSpentInit) / CLOCKS_PER_SEC;
    double timeSpentX = ((double) cpuCyclesTotalSpentX) / CLOCKS_PER_SEC;
    if (numSolutionsFound == threshold)
    {
        printf("The number of solutions was equal to or greather than the threshhold, which was %d.\n", threshold);
    } else {
        printf("The puzzle had fewer solutions than the threshhold, which was %d. The total number of solutions was %d.\n", threshold, numSolutionsFound);
    };
    printf("Initialization took: %f seconds to execute (%ld CPU cycles)\n", timeSpentInit, cpuCyclesTotalSpentInit);
    printf("Algorithm X    took: %f seconds to execute (%ld CPU cycles)\n", timeSpentX, cpuCyclesTotalSpentX);
    printf("Overall Time   took: %f seconds to execute (%ld CPU cycles)\n", timeSpentX+timeSpentInit, cpuCyclesTotalSpentX+cpuCyclesTotalSpentInit);
    return 0;
}