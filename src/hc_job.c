#include "opt.c"
#include <time.h>

int main()
{
    // Seed the RNG and write the seed to the output file.
    time_t seed = time(NULL);
    srand (seed);
    FILE* outFilePointer = fopen("./outpuzzles.txt", "a");
    fprintf(outFilePointer, "Seed: %ld\n", seed);

    int numHillClimbsPerPuzzle = 500;
    fprintf(outFilePointer, "Hillclimbs per puzzle: %d\n", numHillClimbsPerPuzzle);
    fclose(outFilePointer);

    // Varibles used when reading the input file
    FILE* inFilePointer = fopen("./inpuzzles.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    // Variables used when running the hillclimb
    int puzzle[9][9];
    int resultPuzzle[9][9];
    int bestPuzzle[9][9];
    int r, c, resultPuzzleCost, maxPuzzleCost, totalCost, bestPuzzleCost;

    while ((read = getline(&line, &len, inFilePointer)) != -1) {
        maxPuzzleCost = 0;
        totalCost = 0;
        bestPuzzleCost = 81;
        for (int lineIndex = 0; lineIndex < 81; lineIndex++)
        {
            r = lineIndex / 9;
            c = lineIndex % 9;
            puzzle[r][c] = line[lineIndex] - '0';
        }
        // Do the actual hillclimb here
        for(int x = 0; x < numHillClimbsPerPuzzle; x++)
        {
            hillclimb(puzzle, resultPuzzle);
            resultPuzzleCost = cost(resultPuzzle);
            if (resultPuzzleCost<bestPuzzleCost)
            {
                bestPuzzleCost = resultPuzzleCost;
                copyPuzzle(resultPuzzle, bestPuzzle);
            }
            // Used for average cost
            totalCost = totalCost + resultPuzzleCost;
            // Keep track of max cost
            if (resultPuzzleCost>maxPuzzleCost)
            {
                maxPuzzleCost = resultPuzzleCost;
            }
        }
        // Save the best solution here
        FILE* outFilePointer = fopen("./outpuzzles.txt", "a");
        // write to sol file
        for (int r = 0; r < 9; r++)
        {
            for (int c = 0; c < 9; c++)
            {
            fprintf(outFilePointer, "%d", bestPuzzle[r][c]);
            };
        };
        fprintf(outFilePointer, ",%d,%d", totalCost, maxPuzzleCost);
        fprintf(outFilePointer, "\n");
        fclose(outFilePointer);
    }
    fclose(inFilePointer);
    return 0;
}