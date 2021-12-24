//NOTE: depending on your editor you may see many errors highlighted.
//      This is because this code uses nested functions and not all
//      c compilers support them. Make sure to use GCC
#include "Sudoku.c"
#include <time.h>

/*
    Puzzles retrieved from:
    https://web.archive.org/web/20200726052010/https://staffhome.ecm.uwa.edu.au/~00013890/sudokumin.php

    ^^ (that is a link to the gordon royle puzzle archived)
*/

int unitTest1() //solve all archived gordon royle 17-clue puzzles, and ensure that each one only has 1 solution
{
    FILE* inFilePointer = fopen("./sudoku17.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* outFilePointer = fopen("./sudoku17_solutions.txt", "w");

    DancingLinksStruct dlx;
    int puzzle[9][9];
    int puzzleNo = 0;

    int solutionNo = 0;
    /*
        Created callback as nested function.
        This is so that I can define a file pointer
        outside of the callback function and have
        it "passed" to the callback via scoping.
        Also takes the puzzle variable from
        unitTest1() 's scope aswell.
    */
    void unitTest1Callback(DancingLinksStruct* dlxp, int x[], int l, int numSolutions)
    {
        solutionNo++;
        if (numSolutions > 1) {printf("Error! Puzzle %d was found to have multiuple solutions!\n", puzzleNo);}
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
            puzzle[rowNum][colNum] = val;
        };
        //write to sol file
        for (int r = 0; r < 9; r++)
        {
            for (int c = 0; c < 9; c++)
            {
            fprintf(outFilePointer, "%d", puzzle[r][c]);
            };
        };
        fprintf(outFilePointer, "\n");
        //printSudoku(puzzle);
    };
    int r, c, numFromPuzzle;
    //while (((read = getline(&line, &len, inFilePointer)) != -1) && puzzleNo < 10) {
    while ((read = getline(&line, &len, inFilePointer)) != -1) {
        puzzleNo++;
        //printf("%d: %s", puzzleNo, line);
        for (int lineIndex = 0; lineIndex < 81; lineIndex++)
        {
            r = lineIndex / 9;
            c = lineIndex % 9;
            puzzle[r][c] = line[lineIndex] - '0';
        }
        //printf("+++Puzzle:++++++++++\n");
        //printSudoku(puzzle);
        //printf("+++Soltuion:++++++++\n");
        dlx = initFaster(puzzle);
        //dlx = initFromSudoku(puzzle);
        numFromPuzzle = algorithmX(&dlx, 2, &unitTest1Callback);
        //numFromPuzzle = algorithmX(&dlx, 1, &nothing);
        if (numFromPuzzle > 1)
        {
            printf("Warning: puzzle number %d had over 1 solution\n", puzzleNo);
        }
    }
    fclose(inFilePointer);
    fclose(outFilePointer);
    printf("%d solutions found total\n", solutionNo);
    return puzzleNo;
}

void unitTest2()
{
    int puzzle[9][9] = { //17 testing, added in second 1 in row 1, col 2
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 0, 0},
        {0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 6, 0},
        {0, 0, 7, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    printf("Attempting to solve: (9-clues, no solutions, constraints ARE violated in clues)\n");
    printSudoku(puzzle);
    DancingLinksStruct dlx = initFaster(puzzle);
    int numSolutions = algorithmX(&dlx, 2, &printSudokuSolution);
    printf("Number of solutions found in unit test 2 was: %d . Expected: 0.\n", numSolutions);
}

void unitTest3()
{
    int puzzle[9][9] = { //18 givens but it is not solvable
        {6, 8, 0, 0, 0, 0, 0, 5, 0},
        {0, 0, 0, 0, 3, 0, 6, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 0},
        {0, 0, 5, 0, 2, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 6, 0, 0, 0, 1, 0},
        {1, 0, 0, 5, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 7, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3},
    };
    printf("Attempting to solve: (18-clues, no solutions, constraints NOT violated in clues)\n");
    printSudoku(puzzle);
    DancingLinksStruct dlx = initFaster(puzzle);
    int numSolutions = algorithmX(&dlx, 2, &printSudokuSolution);
    printf("Number of solutions found in unit test 3 was: %d . Expected: 0.\n", numSolutions);
}

void unitTest4()
{
    int puzzle[9][9] = { //16 givens, should be many solutions
        {0, 0, 0, 0, 0, 0, 0, 5, 0},
        {0, 0, 0, 0, 3, 0, 6, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 0},
        {0, 0, 5, 0, 2, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 6, 0, 0, 0, 1, 0},
        {1, 0, 0, 5, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 7, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3},
    };
    printf("Attempting to solve: (16-clues, many solutions)\n");
    printSudoku(puzzle);
    DancingLinksStruct dlx = initFaster(puzzle);
    int numSolutions = algorithmX(&dlx, 0, &nothing);
    printf("Number of solutions found in unit test 4 was: %d . Expected: Lots!.\n", numSolutions);
}

/*
    Useful function to print a 4x4 sudoku board to the console. Prints 0's as "-"
*/
void print4x4Sudoku(int puzzle[4][4])
{
    for(int row = 0; row<4; row++)
    {
        for(int col = 0; col<4; col++)
        {
            if (puzzle[row][col] == 0){
                printf("- ");
            } else {
                printf("%d ", puzzle[row][col]);
            };
        };
        printf("\n");
    };
}




void unitTest5()
{
    //int puzzle[4][4] = {
    //    {1,2,3,4},
    //    {3,4,1,2},
    //    {2,0,4,0},
    //    {4,0,2,0}
    //};
    int puzzle[4][4] = {
        {1,2,0,0},
        {3,4,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    /*
        A function that can be passed to algorithmX to run when it finds a solution.
        Prints the solution as a 4x4 sudoku board, including the initial clues from puzzle defined in outter function
    */
    void print4x4SudokuSolution(DancingLinksStruct* dlxp, int *x, int l, int numSolutions)
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
            rowNum = optionNum/16;
            colNum = ((optionNum/4)%4);
            val = (optionNum%4)+1;
            puzzle[rowNum][colNum] = val;
        };
        printf("Solution #%d:\n", numSolutions);
        print4x4Sudoku(puzzle);
    }
    printf("Unit test 5 is solving:\n");
    print4x4Sudoku(puzzle);
    // First, construct an array of all of the headers of a completely empty board
    char constraintPrefixes[4] = {'p', 'r', 'c', 'b'};
    char headers[64][3];
    int headerIndex = 0;
    for (int constraintIndex = 0; constraintIndex < 4; constraintIndex++)
    {
        for (int a = 0; a < 4; a++)
        {
            for (int b = 0; b < 4; b++)
            {
                headers[headerIndex][0] = constraintPrefixes[constraintIndex];
                headers[headerIndex][1] = a + '0'; // convers the int to char (ie. 9 -> '9')
                if (constraintIndex == 0)
                {
                    headers[headerIndex][2] = b + '0';
                } else {
                    headers[headerIndex][2] = (b+1) + '0';
                };
                headerIndex++;
            };
        };
    };
    // Second, construct an array of OptionStructs of all the options of a completely empty board
    OptionStruct options[64];
    int x;
    int optionIndex = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 1; k < 5; k++){
                x = (2*(i/2)) + (j/2);
                options[optionIndex].numElements = 4;
                options[optionIndex].names[0][0] = 'p';
                options[optionIndex].names[0][1] = i + '0';
                options[optionIndex].names[0][2] = j + '0';

                options[optionIndex].names[1][0] = 'r';
                options[optionIndex].names[1][1] = i + '0';
                options[optionIndex].names[1][2] = k + '0';

                options[optionIndex].names[2][0] = 'c';
                options[optionIndex].names[2][1] = j + '0';
                options[optionIndex].names[2][2] = k + '0';

                options[optionIndex].names[3][0] = 'b';
                options[optionIndex].names[3][1] = x + '0';
                options[optionIndex].names[3][2] = k + '0';
                optionIndex ++;
            };
        };
    };
    // Initialize the dancing links structure from an empty board using the values we computer above
    DancingLinksStruct dlx = initDancingLinks(64, headers, 64, options);

    // Now, for each item in the existing sudoku: cover each constraint
    int k;
    for (int i = 0; i < 4; i ++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (puzzle[i][j] != 0)
            {
                k = puzzle[i][j] - 1;
                x = (2*(i/2)) + (j/2);
                // Need to get the index of each of the constraints, that is what the calculations inside the function calls are
                cover(&dlx, (i*4) + j + 1);
                cover(&dlx, (i*4) + k + 16 + 1);
                cover(&dlx, (j*4) + k + 32 + 1);
                cover(&dlx, (x*4) + k + 48 + 1);
            }
        };
    };
    int numSolutions = algorithmX(&dlx, 0, &print4x4SudokuSolution);
    printf("Unit test 5 had %d total solutions. Expected: 12\n", numSolutions);

}
//unit test 3 - puzzle that is valid, but not solvable
//unit test 4 - ensure many solutions can be found (17 clue - remove a clue)
//unit test 5 - smaller grid size, ensure that the # of solutions is the same as expected

/*
    TODO:
        collect different puzzles of different difficulty
        collect stats for different puzzle difficulty
        email https://www.free-sudoku.com/sudoku.php?dchoix=evil
        simulated anealling to removed clues
*/
int main()
{
    printf("---------- START UNIT TEST 1 ----------\n");
    clock_t begin = clock();
    int numPuzzles = unitTest1();
    clock_t end = clock();
    long clockCyclesTotalSpent = (end - begin);
    printf("Solved %d 17 clue Sudokus in %f seconds (%ld clock cycles)\n", numPuzzles, ((double) clockCyclesTotalSpent) / CLOCKS_PER_SEC, clockCyclesTotalSpent);
    printf("Solutions written to file: sudoku17_solutions.txt\n");
    printf("----------  END  UNIT TEST 1 ----------\n");
    printf("---------- START UNIT TEST 2 ----------\n");
    unitTest2();
    printf("----------  END  UNIT TEST 2 ----------\n");
    printf("---------- START UNIT TEST 3 ----------\n");
    unitTest3();
    printf("----------  END  UNIT TEST 3 ----------\n");
    printf("---------- START UNIT TEST 4 ----------\n");
    unitTest4();
    printf("----------  END  UNIT TEST 4 ----------\n");
    printf("---------- START UNIT TEST 5 ----------\n");
    unitTest5();
    printf("----------  END  UNIT TEST 5 ----------\n");
    return 0;
}