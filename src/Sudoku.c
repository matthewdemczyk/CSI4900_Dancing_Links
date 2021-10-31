#include "ExactCover.c"


/*
    Initializes a Sudoku puzzle as an exact cover problem into a dancing links datastructure (DancingLinksStruct)
    using the initDancingLinks function from ExactCover.c
*/
DancingLinksStruct initFromSudoku(int puzzle[9][9])
{
    // First, construct an array of all of the headers of a completely empty board
    char constraintPrefixes[4] = {'p', 'r', 'c', 'b'};
    char headers[324][3];
    int headerIndex = 0;
    for (int constraintIndex = 0; constraintIndex < 4; constraintIndex++)
    {
        for (int a = 0; a < 9; a++)
        {
            for (int b = 0; b < 9; b++)
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
    OptionStruct options[729];
    int x;
    int optionIndex = 0;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            for (int k = 1; k < 10; k++){
                x = (3*(i/3)) + (j/3);
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
    DancingLinksStruct dlx = initDancingLinks(324, headers, 729, options);

    // Now, for each item in the existing sudoku: cover each constraint
    int k;
    for (int i = 0; i < 9; i ++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (puzzle[i][j] != 0)
            {
                k = puzzle[i][j] - 1;
                x = (3*(i/3)) + (j/3);
                // Need to get the index of each of the constraints, that is what the calculations inside the function calls are
                cover(&dlx, (i*9) + j + 1);
                cover(&dlx, (i*9) + k + 81 + 1);
                cover(&dlx, (j*9) + k + 162 + 1);
                cover(&dlx, (x*9) + k + 243 + 1);
            }
        };
    };
    return dlx;
}

/*
    Useful function to print a sudoku board to the console. Prints 0's as "-"
*/
void printSudoku(int puzzle[9][9])
{
    for(int row = 0; row<9; row++)
    {
        for(int col = 0; col<9; col++)
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

/*
    A function that can be passed to algorithmX to run when it finds a solution.
    Prints the solution as a sudoku board, but it doesn't print the given clues (only the solution clues)
*/
void printSudokuSolution(DancingLinksStruct* dlxp, int *x, int l, int numSolutions)
{
    int puzzle[9][9] = {
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
    printf("Solution #%d:\n", numSolutions);
    printSudoku(puzzle);
}

/*
    A function that can be passed to algorithmX to run when it finds a solution.
    Prints the first 5 solutions as a sudoku board, and ignores the rest.
*/
void printFirst5Solutions(DancingLinksStruct* dlxp, int *x, int l, int numSolutions)
{
    if (numSolutions > 6)
    {
        return;
    } else if (numSolutions == 6)
    {
        printf("First 5 solutions have been printed, all of the next solutions will not be printed.\n");
    } else
    {
        printSudokuSolution(dlxp, x, l, numSolutions);
    };
}