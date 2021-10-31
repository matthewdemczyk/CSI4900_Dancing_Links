#include "ExactCover.c"
#include <stdlib.h>

/*
    Key function for the qsort function from stdlib.h
*/
int qsortkeyfunction (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}


/*
    Callback function called when algorithmX finds a solution during unit test 1.
*/
void unitTest1Callback(DancingLinksStruct* dlxp, int x[], int l, int numSolutions)
{
    printf("***Start solution %d callback\n", numSolutions);
    //Static expected outcome for this test.
    int expectedSolution[3] = {1, 4, 5};
    int expectedSolutionLength = 3;
    int observedSolution[MAX_HEADERS];
    //Get the option numbers for each item
    int r;
    for (int i = 0; i < l; i++)
    {
        r = x[i];
        while(dlxp->LEN_TOP[r] > 0)
        {
            r++;
        };
        observedSolution[i] = (dlxp->LEN_TOP[r] * - 1);
    };
    //Sort the observed solution because it might not be in the same order we defined expectedSolution
    //Now, ensure that the observed results are the same as the expected result
    qsort(observedSolution, l, sizeof(int), qsortkeyfunction);
    int passedTest = 0; //0 means test was passed, 1 means failed
    if (expectedSolutionLength == l)
    {
        printf("expected length matches (%d)\n", expectedSolutionLength);
    } else {
        passedTest = 1;
        printf("expected length DOES NOT MATCH! expected length was (%d), but solution was (%d)\n", expectedSolutionLength, l);
    }
    for (int i = 0; i < expectedSolutionLength; i++)
    {
        if (expectedSolution[i] != observedSolution[i])
        {
            passedTest = 1;
        }
        printf("at index %d | expected: %d | observed %d\n", i, expectedSolution[i], observedSolution[i]);
    }
    if (passedTest == 0)
    {
        printf("Unit test 1 (for solution # %d) PASSED\n", numSolutions);
    } else {
        printf("Unit test 1 (for solution # %d) FAILED\n", numSolutions);
    }
};


/*
    Runs unit test 1.
*/
void unitTest1()
{
    printf("---------- START UNIT TEST 1 ----------\n");
    // Page 64 example in Knuth's book
    char headers[7][MAX_NAME_LENGTH] = {"a  ", "b  ", "c  ", "d  ", "e  ", "f  ", "g  "};
    OptionStruct options[6] = {
        {2, {"c  ", "e  "}},
        {3, {"a  ", "d  ", "g  "}},
        {3, {"b  ", "c  ", "f  "}},
        {3, {"a  ", "d  ", "f  "}},
        {2, {"b  ", "g  "}},
        {3, {"d  ", "e  ", "g  "}},
    };
    int threshold = 10;
    DancingLinksStruct dlx = initDancingLinks(7, headers, 6, options);
    memdump(&dlx);
    int numSolutions = algorithmX(&dlx, threshold, &unitTest1Callback);
    if (numSolutions == 1)
    {
        printf("Observed # of solutions matches? YES expected: 1 observed: %d (threshold was %d)\n", numSolutions, threshold);
    } else {
        printf("Observed # of solutions matches? NO expected: 1 observed: %d (threshold was %d)\n", numSolutions, threshold);
    }
    printf("----------  END  UNIT TEST 1 ----------\n");
};


/*
    Callback function called when algorithmX finds a solution during unit test 2.
*/
void unitTest2Callback(DancingLinksStruct* dlxp, int x[], int l, int numSolutions)
{
    printf("***Start solution %d callback\n", numSolutions);
    //Static expected outcome for this test.
    int expectedSolution[2];
    int expectedSolutionLength;
    if (numSolutions == 1)
    {
        expectedSolution[0] = 1;
        expectedSolution[1] = 3;
        expectedSolutionLength = 2;
    } else if (numSolutions == 2){ //numExpectedSolutions == 2
        expectedSolution[0] = 2;
        expectedSolution[1] = 4;
        expectedSolutionLength = 2;
    }
    int observedSolution[MAX_HEADERS];
    //Get the option numbers for each item
    int r;
    for (int i = 0; i < l; i++)
    {
        r = x[i];
        while(dlxp->LEN_TOP[r] > 0)
        {
            r++;
        };
        observedSolution[i] = (dlxp->LEN_TOP[r] * - 1);
    };
    //Sort the observed solution because it might not be in the same order we defined expectedSolution
    //Now, ensure that the observed results are the same as the expected result
    qsort(observedSolution, l, sizeof(int), qsortkeyfunction);
    int passedTest = 0; //0 means test was passed, 1 means failed
    if (expectedSolutionLength == l)
    {
        printf("expected length matches (%d)\n", expectedSolutionLength);
    } else {
        passedTest = 1;
        printf("expected length DOES NOT MATCH! expected length was (%d), but solution was (%d)\n", expectedSolutionLength, l);
    }
    for (int i = 0; i < expectedSolutionLength; i++)
    {
        if (expectedSolution[i] != observedSolution[i])
        {
            passedTest = 1;
        }
        printf("at index %d | expected: %d | observed %d\n", i, expectedSolution[i], observedSolution[i]);
    }
    if (passedTest == 0)
    {
        printf("Unit test 2 (for solution # %d) PASSED\n", numSolutions);
    } else {
        printf("Unit test 2 (for solution # %d) FAILED\n", numSolutions);
    }
};


/*
    Runs unit test 2.
*/
void unitTest2()
{
    printf("---------- START UNIT TEST 2 ----------\n");
    char headers[5][MAX_NAME_LENGTH] = {"a  ", "b  ", "c  ", "d  ", "e  "};
    OptionStruct options[5] = {
        {2, {"a  ", "b  "}},
        {2, {"a  ", "c  "}},
        {3, {"c  ", "d  ", "e  "}},
        {3, {"b  ", "d  ", "e  "}},
        {3, {"a  ", "b  ", "c  "}},
    };
    int threshold = 10;
    DancingLinksStruct dlx = initDancingLinks(5, headers, 5, options);
    int numSolutions = algorithmX(&dlx, threshold, &unitTest2Callback);
    if (numSolutions == 2)
    {
        printf("Observed # of solutions matches? YES expected: 1 observed: %d (threshold was %d)\n", numSolutions, threshold);
    } else {
        printf("Observed # of solutions matches? NO expected: 1 observed: %d (threshold was %d)\n", numSolutions, threshold);
    }
    printf("----------  END  UNIT TEST 1 ----------\n");
};


/*
    Runs unit test 3.
*/
void unitTest3()
{
    printf("---------- START UNIT TEST 3 ----------\n");
    char headers[6][MAX_NAME_LENGTH] = {"a  ", "b  ", "c  ", "d  ", "e  ", "f  "};
    OptionStruct options[5] = {
        {2, {"a  ", "b  "}},
        {2, {"a  ", "c  "}},
        {3, {"c  ", "d  ", "e  "}},
        {3, {"b  ", "d  ", "e  "}},
        {3, {"a  ", "b  ", "c  "}},
    };
    int threshold = 10;
    DancingLinksStruct dlx = initDancingLinks(6, headers, 5, options);
    int numSolutions = algorithmX(&dlx, threshold, &nothing);
    if (numSolutions == 0)
    {
        printf("Observed # of solutions matches? YES expected: 0 observed: %d (threshold was %d)\n", numSolutions, threshold);
    } else {
        printf("Observed # of solutions matches? NO expected: 0 observed: %d (threshold was %d)\n", numSolutions, threshold);
    }
    printf("----------  END  UNIT TEST 3 ----------\n");
};


int main()
{
    unitTest1();
    unitTest2();
    unitTest3();
};