#include "Sudoku.c"
//NOTE: this file uses nested functions, and not all c compilers support them.
//      So, your code editor may show some errors. Make sure to compile with GCC

int main()
{
    //change these output/input files to solve different puzzles
    FILE* outFilePointer = fopen("./solved_puzzles/expert.txt", "w");
    FILE* inFilePointer = fopen("./original_puzzles/expert.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int r, c;
    int puzzle[9][9];
    DancingLinksStruct dlx;
    while ((read = getline(&line, &len, inFilePointer)) != -1) {
        for (int lineIndex = 0; lineIndex < 81; lineIndex++)
        {
            r = lineIndex / 9;
            c = lineIndex % 9;
            puzzle[r][c] = line[lineIndex] - '0';
        }
        void callback(DancingLinksStruct* dlxp, int x[], int l, int numSolutions)
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
        }
        dlx = initFaster(puzzle);
        algorithmX(&dlx, 1, &callback);
    }
    fclose(outFilePointer);
    fclose(inFilePointer);
    return 0;
}