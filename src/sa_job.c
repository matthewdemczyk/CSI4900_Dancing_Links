#include "opt.c"
#include <time.h>

int main()
{
    float t = 1.44;
    float alpha = 0.9999;
    int cMax = 500000;
    // Seed the RNG and write the seed to the output file.
    time_t seed = time(NULL);
    srand (seed);
    FILE* outFilePointer = fopen("./outpuzzles_sa.txt", "a");
    fprintf(outFilePointer, "Seed: %ld\n", seed);

    fprintf(outFilePointer, "Cooling schedule used: t = %f, alpha = %f, cMax = %d\n", t, alpha, cMax);
    fclose(outFilePointer);

    // Varibles used when reading the input file
    FILE* inFilePointer = fopen("./inpuzzles.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    // Variables used when running the simulated annealing
    int puzzle[9][9];
    int resultPuzzle[9][9];
    int r, c;

    while ((read = getline(&line, &len, inFilePointer)) != -1) {
        for (int lineIndex = 0; lineIndex < 81; lineIndex++)
        {
            r = lineIndex / 9;
            c = lineIndex % 9;
            puzzle[r][c] = line[lineIndex] - '0';
        }
        // Do the actual simulated annealing here
        simulated_annealing(puzzle, resultPuzzle, t, alpha, cMax);
        // Save the solution
        FILE* outFilePointer = fopen("./outpuzzles_sa.txt", "a");
        // write to sol file
        for (int r = 0; r < 9; r++)
        {
            for (int c = 0; c < 9; c++)
            {
            fprintf(outFilePointer, "%d", resultPuzzle[r][c]);
            };
        };
        fprintf(outFilePointer, "\n");
        fclose(outFilePointer);
    }
    fclose(inFilePointer);
}