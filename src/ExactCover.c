#include <stdio.h>


#define MAX_HEADERS 325 //equals max number of items + 1 for dummy node
#define MAX_NODES 3971
#define MAX_NAME_LENGTH 3


typedef struct DancingLinksStruct {
    // When initialized, it is assumed that numHeaders <= MAX_HEADERS
    int numHeaders;
    char NAME[MAX_HEADERS][MAX_NAME_LENGTH];
    int LLINK[MAX_HEADERS];
    int RLINK[MAX_HEADERS];

    // When initialized, it is assumed that numNodes <= MAX_NODES
    int numNodes;
    int DLINK[MAX_NODES];
    int ULINK[MAX_NODES];
    int LEN_TOP[MAX_NODES];
} DancingLinksStruct;


typedef struct OptionStruct {
    int numElements;
    char names[MAX_HEADERS][MAX_NAME_LENGTH];
} OptionStruct;

/*
    The function that initializes the DancingLinksStruct from:
        an array of headers (items)
        an array of options
    This function is the pseudo code from Knuth's "The Art of Computer Programming, Volume 4, Fascicle 5"
    in the solution to Exercise 8 in chapter 7.2.2.1, page 224
*/
DancingLinksStruct initDancingLinks
    (
        int numHeaders, // The number of elements in the universal set of the exact cover problem. Assumed to be <= MAX_HEADERS-1 (-1 for dummy node)
        char headers[][MAX_NAME_LENGTH], // Names for each item (this is equivalent to the universal set which we are covering)
        int numOptions, // The total number of options in the exact cover problem (aka # of subsets). Assumed to be <= MAX_OPTIONS
        OptionStruct options[] // Array of tuples that first contain the number of elemnts (numElements) then an array of what those elements are
    )

{
    // DancingLinksStruct is initialized empty and is filled in throughout the funtion, then returned
    DancingLinksStruct dlx;
    dlx.numHeaders = numHeaders + 1; // (need + 1 for dummy node)
    // Set dummy node name
    if (MAX_NAME_LENGTH == 3){
        dlx.NAME[0][0] = 'd';
        dlx.NAME[0][1] = 'u';
        dlx.NAME[0][2] = 'm';
    };
    // I1 (read the first option)
    // This first for loop loops from 1 .. numHeaders+1 because index 0 will be the dummy node
    for (int i = 1; i < numHeaders + 1; i++)
    {
        for(int j = 0; j<MAX_NAME_LENGTH; j++)
        {
            dlx.NAME[i][j] = headers[i-1][j];
        }
        dlx.LLINK[i] = i - 1;
        dlx.RLINK[i-1] = i;
        dlx.LEN_TOP[i] = 0;
        dlx.DLINK[i] = i;
        dlx.ULINK[i] = i;
    };
    // I2 (finish the horizontal list)
    // handle final header serperately as it wraps around to dummy node
    // dlxp->LLINK[numHeaders] = numHeaders -1; (done in above for loop already)
    dlx.RLINK[numHeaders] = 0;

    //create dummy node
    dlx.LLINK[0] = numHeaders;
    // dlxp->RLINK[0] = 1; (done in above for loop already)
    dlx.LEN_TOP[0] = -1;
    dlx.DLINK[0] = -1;
    dlx.ULINK[0] = -1;

    // I3 (prepare for options)
    int M = 0; // The LEN_TOP value of spacer nodes (it's the option number but negative)
    int p = numHeaders + 1; // The current index we are at

    // I4 (read an option)
    int foundIndex, indexWeAreChecking, q, k;
    for (int optionIndex = 0; optionIndex < numOptions; optionIndex++)
        {
            k = options[optionIndex].numElements;
            for (int j = 1; j < k + 1; j++)
            {
                // First find the header index that corresponds to the current item
                foundIndex = 0;
                indexWeAreChecking = 0;
                // This while loop assumes that the option is made correctly and each item actually appears in the headers array
                while (foundIndex == 0)
                {
                    indexWeAreChecking++;
                    //Compare the 2 strings by iterating over each character in them
                    foundIndex = indexWeAreChecking; //Set this temporarily, and if the strings don't match, reset it
                    for (int strIndex = 0; strIndex < MAX_NAME_LENGTH; strIndex++)
                    {
                        if (dlx.NAME[indexWeAreChecking][strIndex] != options[optionIndex].names[j - 1][strIndex])
                        {
                            foundIndex = 0;
                        }
                    };
                };
                // At this point the foundIndex is "ij" in the book
                dlx.LEN_TOP[foundIndex]++;
                q = dlx.ULINK[foundIndex];
                dlx.ULINK[p + j] = q;
                dlx.DLINK[q] = p + j;
                dlx.DLINK[p+j] = foundIndex;
                dlx.ULINK[foundIndex] = p + j;
                dlx.LEN_TOP[p + j] = foundIndex;
            };
            // I5 (finish an option)
            M--;
            dlx.DLINK[p] = p + k;
            p = p + k + 1;
            dlx.LEN_TOP[p] = M;
            dlx.ULINK[p] = p - k;
        };
    dlx.DLINK[p] = -1;
    dlx.numNodes = p + 1;
    return dlx;
}

/*
    Internal function of Algorithm X. This hides an option p.
*/
void hide(DancingLinksStruct* dlxp, int p)
{
    int q, x, u, d;
    q = p+1;
    while(q != p)
    {
        x = dlxp->LEN_TOP[q];
        u = dlxp->ULINK[q];
        d = dlxp->DLINK[q];
        if (x <= 0)
        {
            q = u;
        } else {
            dlxp->DLINK[u] = d;
            dlxp->ULINK[d] = u;
            dlxp->LEN_TOP[x]--;
            q++;
        };
    };
};

/*
    Internal function of Algorithm X. This covers an item i.
*/
void cover(DancingLinksStruct* dlxp, int i)
{
    int p, l, r;
    p = dlxp->DLINK[i];
    while (p != i)
    {
        hide(dlxp, p);
        p = dlxp->DLINK[p];
    };
    l = dlxp->LLINK[i];
    r = dlxp->RLINK[i];
    dlxp->RLINK[l] = r;
    dlxp->LLINK[r] = l;
};

/*
    Internal function of Algorithm X. This unhides an option p.
*/
void unhide(DancingLinksStruct* dlxp, int p)
{
    int q, x, u, d;
    q = p - 1;
    while (q != p)
    {
        x = dlxp->LEN_TOP[q];
        u = dlxp->ULINK[q];
        d = dlxp->DLINK[q];
        if (x <= 0)
        {
            q = d;
        } else {
            dlxp->DLINK[u] = q;
            dlxp->ULINK[d] = q;
            dlxp->LEN_TOP[x]++;
            q--;
        };
    };
};

/*
    Internal function of Algorithm X. This uncovers an item i.
*/
void uncover(DancingLinksStruct* dlxp, int i)
{
    int p, l, r;
    l = dlxp->LLINK[i];
    r = dlxp->RLINK[i];
    dlxp->RLINK[l] = i;
    dlxp->LLINK[r] = i;
    p = dlxp->ULINK[i];
    while (p != i)
    {
        unhide(dlxp, p);
        p = dlxp->ULINK[p];
    };
};

/*
    AlgorithmX as written by Knuth. Returns the number of solutions found, but may be terminated early
    if the number of solutions reaches the threshold parameter.
*/
int algorithmX
(
    DancingLinksStruct* dlxp, // A pointer to the DancingLinksStruct that this function will exectute on. Should be initialized outside the function
    int threshold, // The max number of solutions to find
    void (*solutionCallback)(DancingLinksStruct*, int[], int, int) // A function that is ran each time a solution is found, and is passed
                                                              // the solution (in array x) in addtion the the length of the solution (l)
                                                              // and a pointer to the DancingLinksStruct (dlxp)
)
{
    //X1: Initialize
        int x[MAX_HEADERS-1]; // Array of chosen solutions
        int l = 0;
        int i, p, j, f, theta;
        int numSolutionsFound = 0;

    X2: // Enter level l
        if (dlxp->RLINK[0] == 0) // Hence all items have been covered
        {
            //visit solution that is specified by x0,x1, ... xl-1
            numSolutionsFound++;
            solutionCallback(dlxp, x, l, numSolutionsFound);
            if (numSolutionsFound == threshold) {return numSolutionsFound;};
            goto X8;
        };

    //X3: // Choose i
        // This is done though the MRV heuristic in Exercise 9
        theta = 10;
        f = dlxp->RLINK[0];
        while (f != 0)
        {
            if (dlxp->LEN_TOP[f] < theta)
            {
                theta = dlxp->LEN_TOP[f];
                i = f;
            };
            f = dlxp->RLINK[f];
        };

    //X4: // Cover i
        cover(dlxp, i);
        x[l] = dlxp->DLINK[i];

    X5: // Try x[l]
        if (x[l] == i)
        {
            goto X7; // We've tried all options for i
        } else {
            p = x[l] + 1;
            while (p != x[l])
            {
                j = dlxp->LEN_TOP[p];
                if (j <= 0)
                {
                    p = dlxp->ULINK[p];
                } else {
                    cover(dlxp, j); // This covers the items != i in the option that contains x[l]
                    p++;
                }
            };
            l++;
            goto X2;
        };

    X6: // Try again
        p = x[l] - 1;
        while (p != x[l])
        {
            j = dlxp->LEN_TOP[p];
            if (j <= 0)
            {
                p = dlxp->DLINK[p];
            } else {
                // This uncovers the items != i in the option that contains x[l], using the reverse order in X5
                uncover(dlxp, j);
                p--;
            };
        };
        i = dlxp->LEN_TOP[x[l]];
        x[l] = dlxp->DLINK[x[l]];
        goto X5;

    X7: // Backtrack
        uncover(dlxp, i);

    X8: // Leave level l
        if (l == 0)
        {
            return numSolutionsFound;
        } else {
            l--;
            goto X6;
        };
};


/*
    A function that can be passed to algorithmX to run when it finds a solution.
    This prints the options in the solution that was found (0-indexed).
*/
void printOptionNumbers0Indexed(DancingLinksStruct* dlxp, int x[], int l, int numSolutions)
{
    (void)numSolutions; //to supress comiler warnings for unused variable
    printf("Solution #%d found using options: ", numSolutions);
    int r, optionNum;
    for (int i = 0; i < l; i++)
    {
        r = x[i];
        while(dlxp->LEN_TOP[r] > 0)
        {
            r++;
        };
        optionNum = (dlxp->LEN_TOP[r] * -1) - 1;
        printf("%d ", optionNum);
    };
    printf("\n");
}


/*
    A function that can be passed to algorithmX to run when it finds a solution.
    This does nothing at all. This is useful when only calculating the amount of solutiouns
*/
void nothing(DancingLinksStruct* dlxp, int x[], int l, int numSolutions) {}


/*
    Helper function that writes each of the 6 arrays stored in a DancingLinksStruct to files in folder ./memdump/
*/
void memdump (DancingLinksStruct* dlxp)
{
    FILE *ulinkfprt = fopen("./memdump/ULINK.txt", "w");
    for (int i = 0; i < dlxp->numNodes; i++)
    {
        fprintf(ulinkfprt, "%d\n", dlxp->ULINK[i]);
    }
    fclose(ulinkfprt);

    FILE *dlinkfprt = fopen("./memdump/DLINK.txt", "w");
    for (int i = 0; i < dlxp->numNodes; i++)
    {
        fprintf(dlinkfprt, "%d\n", dlxp->DLINK[i]);
    }
    fclose(dlinkfprt);

    FILE *lentopfprt = fopen("./memdump/LEN_TOP.txt", "w");
    for (int i = 0; i < dlxp->numNodes; i++)
    {
        fprintf(lentopfprt, "%d\n", dlxp->LEN_TOP[i]);
    }
    fclose(lentopfprt);

    FILE *rlinkfprt = fopen("./memdump/RLINK.txt", "w");
    for (int i = 0; i < dlxp->numHeaders; i++)
    {
        fprintf(rlinkfprt, "%d\n", dlxp->RLINK[i]);
    }
    fclose(rlinkfprt);

    FILE *llinkfprt = fopen("./memdump/LLINK.txt", "w");
    for (int i = 0; i < dlxp->numHeaders; i++)
    {
        fprintf(llinkfprt, "%d\n", dlxp->LLINK[i]);
    }
    fclose(llinkfprt);

    FILE *namefprt = fopen("./memdump/NAME.txt", "w");
    char charBuff[MAX_NAME_LENGTH];
    for (int i = 0; i < dlxp->numHeaders; i++)
    {
        for (int j = 0; j < MAX_NAME_LENGTH; j++)
        {
            charBuff[j] = dlxp->NAME[i][j];
        }
        fprintf(namefprt, "%s\n", charBuff);
    }
    fclose(namefprt);
}