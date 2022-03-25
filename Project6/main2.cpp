#include <stdio.h>
#include <stdlib.h>
#include "MazeParams.h"
#include "Recursion.h"
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define SHOWDETAILS 1

int maze[MATRIX_SIZE][MATRIX_SIZE];
#define BRANCH 0
#define WALL 1
#define PATH 2
int start_col; // the starting column for the maze;

#define FAILED "!!! FAILED TEST !!!\n"
#define PASSED "TEST PASSED\n"

int mazeMakeCalls = 0;
#define maxMazeMakeCalls 5000

void printMaze(void) {
    unsigned r, c;
    for (r = 0; r < MATRIX_SIZE; r += 1) {
        for (c = 0; c < MATRIX_SIZE; c += 1) {
            switch (maze[r][c]) {
            case BRANCH:
                putchar(' ');
                break;
            case WALL:	
                putchar('#');
                break;
            case PATH: // bread crumb
                putchar('o');
                break;
            default: // error!
                putchar('@');
                break;			
            }
        }
        putchar('\n');
    }
}

void printMaze(int** matrix) {
    unsigned r, c;
    for (r = 0; r < MATRIX_SIZE; r += 1) {
        for (c = 0; c < MATRIX_SIZE; c += 1) {
            switch (matrix[r][c]) {
            case BRANCH:
                putchar(' ');
                break;
            case WALL:	
                putchar('#');
                break;
            case PATH: // bread crumb
                putchar('o');
                break;
            default: // error!
                putchar('@');
                break;			
            }
        }
        putchar('\n');
    }
}

int makePathRecHelper(int, int);
void makeBranchesRecHelper(int, int);
void resetMaze(void);

// path will have the solution
// maze will have the maze (without breadcrumbs)
// start_col will have the starting column
void makeMazeCustom() { 
    // initialize/reset all maze cells to 0
    resetMaze();

    start_col = rand() % MAZE_SIZE;
    start_col = 2 * start_col + 1;

    mazeMakeCalls = 0;
    int res = makePathRecHelper(0, start_col);
    while (res == 0) {
        mazeMakeCalls = 0;
        resetMaze();
        res = makePathRecHelper(0, start_col);
    }

    for (int r = 1; r < MATRIX_SIZE - 1; r++) {
        for (int c = 1; c < MATRIX_SIZE - 1; c++) {
            if (maze[r][c] == PATH) {
                if (rand() % 2 == 0) {
                    makeBranchesRecHelper(r - 1, c);
                    makeBranchesRecHelper(r, c + 1);
                    makeBranchesRecHelper(r + 1, c);
                    makeBranchesRecHelper(r, c - 1);
                }
            }
        }
    }

    // printMaze();
}

void resetMaze(void) {
    for (int r = 0; r < MATRIX_SIZE; r++) {
        for (int c = 0; c < MATRIX_SIZE; c++) {
            maze[r][c] = WALL;
        }
    }
}

int is2Adjacent(int r, int c, int val) {
    int rAdd[4] = {-1, 0, 1, 0};
    int cAdd[4] = {0, 1, 0, -1};

    int res = 0;

    for (int i = 0; i < 4; i++) {
        if(r + rAdd[i] >= 0 && r + rAdd[i] < MATRIX_SIZE &&
            c + cAdd[i] >= 0 && c + cAdd[i] < MATRIX_SIZE &&
            maze[r + rAdd[i]][c + cAdd[i]] == val) {
                res++;
            }
        if (res == 2) return 1;
    }
    return 0;
}

int makePathRecHelper(int r, int c) {
    if (mazeMakeCalls > maxMazeMakeCalls) return 0;
    mazeMakeCalls++;

    // PATH = path
    int adjNum = is2Adjacent(r, c, PATH);
    // printf("Row: %d, Col: %d, adjNum: %d\n", r, c, adjNum);
    if (adjNum) return 0;

    if (r == MATRIX_SIZE - 1) {
        maze[r][c] = PATH;
        return 1;
    }

    int rAdd[4] = {-1, 0, 1, 0};
    int cAdd[4] = {0, 1, 0, -1};
    int used[4] = {0, 0, 0, 0};

    if (r == 0) {
        used[0] = 1;
        used[1] = 1;
        used[3] = 1;
    }

    if (r == 1) {
        used[0] = 1;
    }

    int randDir = rand() % 4;
    int res = 0; 

    while(res == 0) {
        if (used[randDir]) {
            randDir = rand() % 4;
            continue;
        }
        
        if (r + rAdd[randDir] < 0 || r + rAdd[randDir] >= MATRIX_SIZE ||
            c + cAdd[randDir] <= 0 || c + cAdd[randDir] >= MATRIX_SIZE - 1) {
                used[randDir] = 1;
                if (used[0] + used[1] + used[2] + used[3] == 4) return 0;

                randDir = rand() % 4;
                continue;
        }
        
        maze[r][c] = PATH;
        res = makePathRecHelper(r + rAdd[randDir],
            c + cAdd[randDir]);
        if (res == 1) {
            return 1;
        }
        maze[r][c] = WALL;

        used[randDir] = 1;
        if (used[0] + used[1] + used[2] + used[3] == 4) return 0;

        randDir = rand() % 4;
    }

    return 0;
}

int isBP2Adjacent(int r, int c, int val, int val2) {
    int rAdd[4] = {-1, 0, 1, 0};
    int cAdd[4] = {0, 1, 0, -1};

    int res = 0;

    for (int i = 0; i < 4; i++) {
        if(r + rAdd[i] >= 0 && r + rAdd[i] < MATRIX_SIZE &&
            c + cAdd[i] >= 0 && c + cAdd[i] < MATRIX_SIZE &&
            (maze[r + rAdd[i]][c + cAdd[i]] == val || maze[r + rAdd[i]][c + cAdd[i]] == val2)) {
                res++;
            }
        if (res == 2) return 1;
    }
    return 0;
}

void makeBranchesRecHelper(int r, int c) {
    if (r <= 0 || r >= MATRIX_SIZE - 1 || c <= 0 || c >= MATRIX_SIZE - 1) {
        return;
    }

    // 0 = branch, 2 = path
    int adjNum = isBP2Adjacent(r, c, BRANCH, PATH);
    // printf("Row: %d, Col: %d, adjNum: %d\n", r, c, adjNum);
    if (adjNum) return;

    int rAdd[4] = {-1, 0, 1, 0};
    int cAdd[4] = {0, 1, 0, -1};

    int randDir = rand() % 4;

    if (r + rAdd[randDir] <= 0 || r + rAdd[randDir] >= MATRIX_SIZE - 1 ||
        c + cAdd[randDir] <= 0 || c + cAdd[randDir] >= MATRIX_SIZE - 1) {
            return;
    }

    maze[r][c] = BRANCH;
    makeBranchesRecHelper(r + rAdd[randDir], c + cAdd[randDir]);
}

// Helper method for printing an integer array
void printIntArray(int* arr, int len) {
    printf("List: ");

    if (len == 0) {
        printf("{}\n");
        return;
    }

    printf("{");
    for (int i = 0; i < len - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d}\n", arr[len-1]);
}

// Custom Tests
void runMinTest(char* desc, char* funcName, int minFunc(int[], int), int testNum,
    int* arr, int len, int exp, int* score) {

    printf("Test #%d, %s - %s\n", testNum, funcName, desc);
    
    int actual = minFunc(arr, len);
    if (SHOWDETAILS || exp != actual) {
        printIntArray(arr, len);
        printf("Expected Result: %d\n", exp);
        printf("Your Result: %d\n", actual);
        
    }

    if (exp != actual) {
        printf(FAILED);
    }

    else {
        printf(PASSED);
        (*score)++;
    }

    printf("\n");
}

int minTests(void) {
    int score = 0;
    int testNum = 1;

    int (*minFuncs[2]) (int[], int);
    minFuncs[0] = minRec1;
    minFuncs[1] = minRec2;
    char* minFuncsNames[2]; 
    minFuncsNames[0] = "minRec1()";
    minFuncsNames[1] = "minRec2()";

    // minRec1 & minRec2
    for (int m = 0; m < 2; m++) {
        // Test with empty list - will not be given

        // Test with one item in list
        int a1[] = {1};
        runMinTest("one item in list", minFuncsNames[m], minFuncs[m], testNum++, a1, 1, 1, &score);

        // Test with two items in list
        int a2[] = {1, 2}; 
        runMinTest("two items in list", minFuncsNames[m], minFuncs[m], testNum++, a2, 2, 1, &score);

        // Test with two negative items in list
        int a3[] = {-4, -10}; 
        runMinTest("two negative items in list", minFuncsNames[m], minFuncs[m], testNum++, a3, 2, -10, &score);

        // Tests with random integers (both negative and positive)
        for (int i = 0; i < 10; i++) {
            int randLen = rand() % 100 + 1; // random length between 1 - 100
            int a4[randLen];
            int min = 2000;
            for (int j = 0; j < randLen; j++) {
                a4[j] = (rand() % 1001) * (rand() % 2 == 0 ? 1 : -1); // random ints between -1000 and 1000
                if (a4[j] < min) {
                    min = a4[j];
                }
            }
            runMinTest("random list", minFuncsNames[m], minFuncs[m], testNum++, a4, randLen, min, &score);
        }
    }
    
    return score;
}

int inPrecision(double result, double exp) {
    double precision = 0.000000000000001;
    int places = ((int) log(exp)) + 1;
    for (int i = 0; i < places; i++) {
        precision *= 10;
    }

    return (result >= exp && result - exp < precision) ||
        (result <= exp && exp - result < precision);
}

void runSqrtTest(char* desc, int testNum, double num, double exp,
    double low, double high, int* score) {

    double result = sqrtRec(num, low, high);

    int correct = inPrecision(result, exp);

    printf("Test #%d, sqrtRec() - %s\n", testNum, desc);

    if (SHOWDETAILS || !correct) {
        printf("Num to be Sqrt-ed: %f\n", num);
        printf("Expected Result: %.15f\n", exp);
        printf("Your Result: %.15f\n", result);
        
    }

    if (!correct) {
        printf(FAILED);
    }

    else {
        printf(PASSED);
        (*score)++;
    }

    printf("\n");
    return;
}

int sqrtTests(void) {
    // no negative values will be given
    int testNum = 1;
    int score = 0;
    
    // test value 0
    runSqrtTest("num = 0", testNum++, 0, sqrt(0), 0, 0, &score);
    
    // test value 1
    runSqrtTest("num = 1", testNum++, 1, sqrt(1), 0, 1, &score);

    // test 10 random values between 0 and 1
    for (int i = 0; i < 10; i++) {
        double num = (rand() % 10000) / 10000.0;
        runSqrtTest("random double value between 0 and 1", testNum++, num, sqrt(num), 0, 1, &score);
    }

    // test 10 random values between 1 and 100
    for (int i = 0; i < 10; i++) {
        int num = (rand() % 100) + 1;
        runSqrtTest("random int value between 1 and 100", testNum++, 1.0 * num,
            sqrt(num), 0, num, &score);
    }

    // test 10 random values between 1,000 and 10,000
    for (int i = 0; i < 10; i++) {
        int num = (rand() % 9001) + 1000;
        runSqrtTest("random int value between 1,000 and 10,000", testNum++, 1.0 * num,
            sqrt(num), 0, num, &score);
    }

    return score;
}

void runStrCompTests(char* desc, int testNum, char* a, char* b, int exp, int* score) {
    int result = strCompare(a, b); 
    int correct = (result == exp);

    printf("Test #%d, strCompare() - %s\n", testNum, desc);

    if (SHOWDETAILS || !correct) {
        printf("String 1: \"%s\"\nString 2: \"%s\"\n", a, b);
        printf("Expected Result: %d\n", exp);
        printf("Your Result: %d\n", result);
    }

    if (!correct) {
        printf(FAILED);
    }

    else {
        printf(PASSED);
        (*score)++;
    }

    printf("\n");
    return;
}

void runStrComp2Tests(char* desc, int testNum, char* a, char* b, int exp, int* score) {
    int result = strCompare2(a, b);
    int correct = (result == exp);

    printf("Test #%d, strCompare2() - %s\n", testNum, desc);

    if (SHOWDETAILS || !correct) {
        printf("String 1: \"%s\"\nString 2: \"%s\"\n", a, b);
        printf("Expected Result: %d\n", exp);
        printf("Your Result: %d\n", result);
    }

    if (!correct) {
        printf(FAILED);
    }

    else {
        printf(PASSED);
        (*score)++;
    }

    printf("\n");
    return;
}

int strCmpAns(char* a, char* b) {
    int res = strcmp(a, b);

    if (res > 0) {
        return 1;
    }
    else if (res < 0) {
        return -1;
    }

    return res;
}

int isLetter(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int strCmp2Ans(char* a, char* b) {
    int aLen = strlen(a);
    int bLen = strlen(b);

    char *c = (char*) malloc((aLen + 1) * sizeof(char));
    char *d = (char*) malloc((bLen + 1) * sizeof(char));

    int i = 0;

    while (*a) {
        if (isLetter(*a)) {
            c[i] = tolower(*a);
            i++;
        }
        a += 1;
    }
    c[i] = '\0';

    i = 0;
    while (*b) {
        if (isLetter(*b)) {
            d[i] = tolower(*b);
            i++;
        }
        b += 1;
    }

    d[i] = '\0';

    int res = strcmp(c, d);

    free(c);
    free(d);

    if (res > 0) {
        return 1;
    }
    else if (res < 0) {
        return -1;
    }

    return res;
}

int strCompTests(void) {
    int testNum = 1;
    int score = 0;

    // strComp1 (compare all characters)
    char* a; 
    char* b;

    // both strings empty
    a = "";
    b = "";
    runStrCompTests("Both strings len = 0", testNum++, a, b, strCmpAns(a, b), &score);

    // first string empty
    a = "";
    b = "abc";
    runStrCompTests("First string len = 0", testNum++, a, b, strCmpAns(a, b), &score);

    // second string empty
    a = "abc";
    b = "";
    runStrCompTests("Second string len = 0", testNum++, a, b, strCmpAns(a, b), &score);

    // both strings len = 1, same string
    a = "a";
    b = "a";
    runStrCompTests("Both strings len = 1, same string",
        testNum++, a, b, strCmpAns(a, b), &score);
    
    // both strings len = 1, diff string
    a = "a";
    b = "b";
    runStrCompTests("Both strings len = 1, different string",
        testNum++, a, b, strCmpAns(a, b), &score);

    // first string len = 1, second string len != 1
    a = "a";
    b = "abc";
    runStrCompTests("str1 len = 1, str2 len != 1",
        testNum++, a, b, strCmpAns(a, b), &score);

    a = "b";
    b = "abc";
    runStrCompTests("str1 len = 1, str2 len != 1",
        testNum++, a, b, strCmpAns(a, b), &score);

    a = "a";
    b = "dog";
    runStrCompTests("str1 len = 1, str2 len != 1",
        testNum++, a, b, strCmpAns(a, b), &score);
    
    // second string len = 1
    a = "abc";
    b = "a";
    runStrCompTests("str1 len != 1, str2 len = 1",
        testNum++, a, b, strCmpAns(a, b), &score);

    a = "abc";
    b = "b";
    runStrCompTests("str1 len != 1, str2 len = 1",
        testNum++, a, b, strCmpAns(a, b), &score);

    a = "dog";
    b = "a";
    runStrCompTests("str1 len != 1, str2 len = 1",
        testNum++, a, b, strCmpAns(a, b), &score);

    // both strings same (non-0 and non-1)
    a = "sus";
    b = "sus";
    runStrCompTests("Both strings same, len != (0 or 1)",
        testNum++, a, b, strCmpAns(a, b), &score);

    // both strings same length but not same (non-0 and non-1)
    a = "dog";
    b = "sus";
    runStrCompTests("Both strs same length, but not same str",
        testNum++, a, b, strCmpAns(a, b), &score);

    // random strings
    char* charList = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    for (int i = 0; i < 10; i++) {
        int aLen = rand() % 100 + 1;
        int bLen = rand() % 100 + 1;

        a = (char*) malloc((aLen + 1) * sizeof(char));
        b = (char*) malloc((bLen + 1) * sizeof(char));

        for (int i = 0; i < aLen; i++) {
            a[i] = charList[rand() % 52];
        }

        a[aLen] = '\0';

        for (int i = 0; i < bLen; i++) {
            b[i] = charList[rand() % 52];
        }

        b[bLen] = '\0';
        
        runStrCompTests("random strings, 1 <= len <= 100",
            testNum++, a, b, strCmpAns(a, b), &score);
        
        free(a);
        free(b);
    }

    return score;
}

int strComp2Tests(void) {
    int testNum = 1;
    int score = 0;

    // strComp1 (compare all characters)
    char* a; 
    char* b;

    // both strings empty
    a = "";
    b = "";
    runStrComp2Tests("Both strings len = 0", testNum++, a, b, strCmp2Ans(a, b), &score);

    // first string empty
    a = "";
    b = "'-=s";
    runStrComp2Tests("First string len = 0", testNum++, a, b, strCmp2Ans(a, b), &score);


    // second string empty
    a = "=`=.<?\"{}a";
    b = "";
    runStrComp2Tests("Second string len = 0", testNum++, a, b, strCmp2Ans(a, b), &score);

    // both strings len = 1, same string
    a = "a";
    b = "a";
    runStrComp2Tests("Both strings len = 1, same string",
        testNum++, a, b, strCmp2Ans(a, b), &score);
    
    // both strings len = 1, diff string
    a = "=";
    b = "b";
    runStrComp2Tests("Both strings len = 1, different string",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    // both strings with only one alpha char
    a = "#$%^&*(*&^%$#@#2a";
    b = "()_+{\"1?>_&$#@#^b";
    runStrComp2Tests("Both strings with only one alpha char",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    // first string len = 1, second string len != 1
    a = "a";
    b = "abc";
    runStrComp2Tests("str1 len = 1, str2 len != 1",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    a = "b";
    b = "abc";
    runStrComp2Tests("str1 len = 1, str2 len != 1",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    a = "a";
    b = "dog";
    runStrComp2Tests("str1 len = 1, str2 len != 1",
        testNum++, a, b, strCmp2Ans(a, b), &score);
    
    // second string len = 1
    a = "abc";
    b = "a";
    runStrComp2Tests("str1 len != 1, str2 len = 1",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    a = "abc";
    b = "b";
    runStrComp2Tests("str1 len != 1, str2 len = 1",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    a = "dog";
    b = "a";
    runStrComp2Tests("str1 len != 1, str2 len = 1",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    // // both strings same (non-0 and non-1)
    a = "~@##@!!@()*^%$#%&(646897t";
    b = "~@##@!!@()*^%$#%&(646897t";
    runStrComp2Tests("Both strings same, len != (0 or 1)",
        testNum++, a, b, strCmp2Ans(a, b), &score);

    // random strings
    char* charList = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    for (int i = 0; i < 10; i++) {
        int aLen = rand() % 100 + 1;
        int bLen = rand() % 100 + 1;

        a = (char*) malloc((aLen + 1) * sizeof(char));
        b = (char*) malloc((bLen + 1) * sizeof(char));

        for (int i = 0; i < aLen; i++) {
            a[i] = charList[rand() % 52];
        }

        a[aLen] = '\0';

        for (int i = 0; i < bLen; i++) {
            b[i] = charList[rand() % 52];
        }

        b[bLen] = '\0';
        
        runStrComp2Tests("random strings, 1 <= len <= 100",
            testNum++, a, b, strCmp2Ans(a, b), &score);
        
        free(a);
        free(b);
    }

    return score;
}

void runMazeTest(char* desc, int testNum, int* score) {
    printf("Test #%d, solveMazeRec() - %s\n", testNum, desc);

    makeMazeCustom();

    int** ans = (int**) malloc(MATRIX_SIZE * sizeof(int*));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        ans[i] = (int*) malloc(MATRIX_SIZE * sizeof(int));
    }

    for (int r = 0; r < MATRIX_SIZE; r++) {
        for (int c = 0; c < MATRIX_SIZE; c++) {
            ans[r][c] = maze[r][c];
            if(maze[r][c] == PATH) {
                maze[r][c] = BRANCH;
            }
        }
    }

    solveMazeRec(0, start_col);
    int res = 2; // 2 = full credit, 1 = partial, 0 = wrong
    for (int r = 0; r < MATRIX_SIZE; r++) {
        for (int c = 0; c < MATRIX_SIZE; c++) {
            if (ans[r][c] != maze[r][c]) {
                if (ans[r][c] == BRANCH && maze[r][c] == PATH) {
                    res = 1;
                    continue;
                }

                res = 0;
                break;
            }
        }
        if (res == 0) break;
    }

    if (SHOWDETAILS || res == 0) {
        printf("Expected Result:\n");
        printMaze(ans);   
        printf("Your Result:\n");
        printMaze();
    }

    if (res == 0) {
        printf(FAILED);
    }

    else if (res == 1) {
        printf("!!! PARTIAL CREDIT !!!\n");
    }

    else {
        printf(PASSED);
        (*score)++;
    }

    printf("\n");

    for (int i = 0; i < MATRIX_SIZE; i++) {
        free(ans[i]);
    }
    free(ans);

    return;
}

int mazeTests(void) {
    int score = 0;
    int numTest = 1; 

    for (int i = 0; i < 100; i++) {
        runMazeTest("random maze", numTest++, &score);
    }

    return score;
}

void runMartianTest(char* desc, int testNum, int cents, int* score) {
    printf("Test #%d, change(int) - %s %d\n", testNum, desc, cents);

    int pennies = 0;
    int nicks = 0;
    int dodeks = 0;
    int coinsCount = -1;
    
    for (int i = 0; i <= cents / 12; i++) {
        for (int j = 0; j <= (cents - i * 12) / 5; j++) {
            for (int k = 0; k <= (cents - i * 12 - j * 5); k++) {
                if (cents == 12 * i + 5 * j + 1 * k) {
                    if (coinsCount == -1 || i + j + k < coinsCount) {
                        coinsCount = i + j + k;
                        pennies = k;
                        nicks = j;
                        dodeks = i;
                    }
                }
            }
        }
    }
    
    Martian result = change(cents);
    int correct = (result.pennies == pennies && result.nicks == nicks && result.dodeks == dodeks) || 
                    (result.pennies + result.nicks + result.dodeks == pennies + nicks + dodeks);

    if (SHOWDETAILS || !correct) {
        printf("Expected Result: %dd, %dn, %dp\n", dodeks, nicks, pennies);
        printf("Your Result: %dd, %dn, %dp\n", result.dodeks, result.nicks, result.pennies);
    }

    if (!correct) {
        printf(FAILED);
    }

    else {
        printf(PASSED);
        (*score)++;
    }

    printf("\n");
    return;
}

void runMartian2Test(char* desc, int testNum, int cents, int nick_value, int dodek_value, int* score) {
    printf("Test #%d, change(int, int, int) - %s %d\n", testNum, desc, cents);

    int pennies = 0;
    int nicks = 0;
    int dodeks = 0;
    int coinsCount = -1;
    
    for (int i = 0; i <= cents / dodek_value; i++) {
        for (int j = 0; j <= (cents - i * dodek_value) / nick_value; j++) {
            for (int k = 0; k <= (cents - i * dodek_value - j * nick_value); k++) {
                if (cents == dodek_value * i + nick_value * j + 1 * k) {
                    if (coinsCount == -1 || i + j + k < coinsCount) {
                        coinsCount = i + j + k;
                        pennies = k;
                        nicks = j;
                        dodeks = i;
                    }
                }
            }
        }
    }
    
    Martian result = change(cents, nick_value, dodek_value);
    int correct = (result.pennies == pennies && result.nicks == nicks && result.dodeks == dodeks) || 
                    (result.pennies + result.nicks + result.dodeks == pennies + nicks + dodeks);

    if (SHOWDETAILS || !correct) {
        printf("nick_value: %d, dodek_value: %d\n", nick_value, dodek_value);
        printf("Expected Result: %dd, %dn, %dp\n", dodeks, nicks, pennies);
        printf("Your Result: %dd, %dn, %dp\n", result.dodeks, result.nicks, result.pennies);
    }

    if (!correct) {
        printf(FAILED);
    }

    else {
        printf(PASSED);
        (*score)++;
    }

    printf("\n");
    return;
}

int martianTests(void) {
    int score = 0;
    int testNum = 1;

    for (int i = 1; i <= 50; i++) {
        runMartianTest("num cents =", testNum++, i, &score);
    }

    for (int i = 1; i <= 50; i++) {
        runMartian2Test("num cents =", testNum++, i, 5, 12, &score);
    }

    for (int i = 1; i <= 30; i++) {
        int nick_val = rand() % 8 + 2;
        int dodek_val = rand() % 5 + 10;
        runMartian2Test("num cents =", testNum++, i, nick_val, dodek_val, &score);
    }

    for (int i = 1; i <= 30; i++) {
        int nick_val = rand() % 8 + 2;
        int dodek_val = rand() % 5 + 10;
        runMartian2Test("num cents =", testNum++, i, nick_val, dodek_val, &score);
    }

    return score;
}


void printSuccess(void) {
    printf("    /\\____/\\\n");
    printf("   /  ^__^  \\\n");
    printf("  ( ==    == )\n");
    printf("   )        (\n");
    printf("  (          )\n");
    printf(" ( (  )  (  ) )\n");
    printf("(__(__)__(__)__)\n");    
}

int main(void) {
    // set rand() seed
    srand(time(0));

    int numMinTests = 26;
    int minRecScore = minTests();
    
    int numSqrtTests = 32;
    int sqrtScore = sqrtTests();
 
    int numStrTests = 23;
    int strScore = strCompTests();

    int numStr2Tests = 23;
    int str2Score = strComp2Tests();

    int numMazeTests = 100;
    int mazeScore = mazeTests();

    int numMartianTests = 160;
    int martianScore = martianTests();

    printf("\n");

    printf("RESULTS SUMMARY\n");
    printf("minRec1() & minRec2(): %d of %d tests passed\n", minRecScore, numMinTests);
    printf("sqrtRec(): %d of %d tests passed\n", sqrtScore, numSqrtTests);
    printf("strCompare(): %d of %d tests passed\n", strScore, numStrTests);
    printf("strCompare2(): %d of %d tests passed\n", str2Score, numStr2Tests);
    printf("solveMazeRec(): %d of %d tests passed\n", mazeScore, numMazeTests);
    printf("change() (both overloads): %d of %d tests passed\n", martianScore, numMartianTests);

    if (numMinTests == minRecScore &&
        numSqrtTests == sqrtScore &&
        numStrTests == strScore &&
        numStr2Tests == str2Score &&
        numMazeTests == mazeScore &&
        numMartianTests == martianScore) 
        {
            printf("\nPASSED ALL TESTS\n");
            printSuccess();
        }
}
