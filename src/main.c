#include "Sudoku.c"
#include <time.h>

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
    int puzzle[9][9] = { //16 clue puzzle, same as the final puzzle (currently uncommented) with the 5 in row 1 removed
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
    // Nested function in main that can refer to the current puzzle without having to be passed it as a parameter
    // This should be passed to algorithmX to run when a solution is found
    */
    /*
    void printSudokuSolutionWithGivens(DancingLinksStruct* dlxp, int *x, int l, int numSolutions)
    {
        int optionNum, rowNum, colNum, val, r;
        for (int i = 0; i < l; i++)
        {
            r = x[i];
            while(dlxp->LEN_TOP[r] > 0)
            {
                r++;
            };
            optionNum = (dlxp->LEN_TOP[r] * -1) -1;
            rowNum = optionNum/81;
            colNum = ((optionNum/9)%9);
            val = (optionNum%9)+1;
            puzzle[rowNum][colNum] = val; //puzzle is defined outside of function
        };
        printf("Solution #%d:\n", numSolutions);
        printSudoku(puzzle);
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
    printf("Solving:\n");
    printSudoku(puzzle);

    // Start solving the puzzle
    clock_t begin = clock();
    DancingLinksStruct dlx = initFromSudoku(puzzle);
    //memdump(&dlx);
    int threshold = 2;
    int numSolutionsFound = algorithmX(&dlx, threshold, &printSudokuSolution);

    clock_t end = clock();

    // Printout of results
    long cpuCyclesTotalSpent = (end - begin);
    double timeSpent = ((double) cpuCyclesTotalSpent) / CLOCKS_PER_SEC;
    if (numSolutionsFound == threshold)
    {
        printf("The number of solutions was equal to or greather than the threshhold, which was %d.\n", threshold);
    } else {
        printf("The puzzle had fewer solutions than the threshhold, which was %d. The total number of solutions was %d.\n", threshold, numSolutionsFound);
    };
    printf("Task took: %f seconds to execute (%ld CPU cycles)\n", timeSpent, cpuCyclesTotalSpent);
    return 0;
}