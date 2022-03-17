#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <chrono>
#include "Set.h"

unsigned time();
int const number_of_tests = 1000;
int const maximum_set_size = 100;

void randomSet(Set* s);
void visualTests(void);
void equalityTests(void);
void specialCaseTests(void);
void relationalTests(void);
void algebraicTests(void);
void testTime(void);

int main (void) {
    visualTests();
    equalityTests();
    specialCaseTests();
    relationalTests();
    algebraicTests();
    testTime();
    printf("The tests are over\n");
}

void randomSet(Set* s) {
    Set t;
    int n = rand() % maximum_set_size + 1;
    int i;

    createEmptySet(&t);
    for (i = 0; i < n; i += 1) {
        insertSet(&t, rand() % maximum_set_size);
    }
    assignSet(s, &t);
    destroySet(&t);
}

void showOutput(const char* str, Set* set) {
    printf("%s", str);
    displaySet(set);
    printf("\n");
}

void visualTests() {
    Set s;
    Set t;
    int i;
    createEmptySet(&s);
    showOutput("The set constructed with the default constructor: ", &s);

    for (i = 0; i < 10; i += 1) {
        insertSet(&s, i);
    }
    showOutput("The set should be {0, ..., 9}:  ", &s);

    // test Insert() and Contains() with '<<'
    for (i = 0; i < 10; i += 1) {
        insertSet(&s, i);
    }
    showOutput("The set should be {0, ..., 9}:  ", &s);

    createCopySet(&t, &s);
    showOutput("The copy of s constructed with the copy constructor = ", &t);

    randomSet(&t);
    showOutput("The random set generated equals = ", &t);

    printf("The visual tests are over\n");
    destroySet(&s);
    destroySet(&t);
}

void equalityTests(void) {
    int i;
    for (i = 0; i < number_of_tests; i += 1) {
        Set s;
        Set t;

        createEmptySet(&s);
        randomSet(&s);
        createCopySet(&t, &s);
        assert(isEqualToSet(&t, &s));
        assert(isEqualToSet(&s, &t));
        insertSet(&t, maximum_set_size);
        assert(! isEqualToSet(&s, &t));
        assert(! isEqualToSet(&t, &s));
        randomSet(&t);
        assert(! isEqualToSet(&t, &s));
        destroySet(&s);
        destroySet(&t);
    }       // This test could fail with small probability
    printf("The equality tests have been passed\n");
}

typedef void (*setFun)(Set*, const Set*);
void checkCase(setFun fun, Set* s1, Set* s2, Set* expect) {
    Set res;
    createCopySet(&res, s1);
    (*fun)(&res, s2);
    assert(isEqualToSet(&res, expect));
    destroySet(&res);
}

void specialCaseTests(void) {
    Set empty;
    Set universal;
    int i;
    Set s;
    Set r;

    createEmptySet(&empty);
    createEmptySet(&universal);
    createEmptySet(&r);
    for (i = 0; i < maximum_set_size; i += 1) {
        insertSet(&universal, i);
    }
    checkCase(&subtractFromSet, &universal, &universal, &empty);
    checkCase(&unionInSet, &universal, &universal, &universal);
    checkCase(&intersectFromSet, &universal, &universal, &universal);
    checkCase(&intersectFromSet, &universal, &empty, &empty);
    checkCase(&intersectFromSet, &empty, &universal, &empty);
    checkCase(&unionInSet, &universal, &empty, &universal);
    checkCase(&unionInSet, &empty, &universal, &universal);
    checkCase(&unionInSet, &empty, &empty, &empty);
    checkCase(&subtractFromSet, &empty, &empty, &empty);
    checkCase(&intersectFromSet, &empty, &empty, &empty);

    createEmptySet(&s);
    assert(isEmptySet(&s));
    for (i = 0; i < 10; i += 1) {
        insertSet(&s, i);
    }
    assert(s.len == 10);
    for (i = 0; i < 10; i += 1) {
        assert(isMemberSet(&s, i));
    }
    for (i = 0; i < 10; i += 1) {
        removeSet(&s, i);
        removeSet(&s, i);
        assert(s.len == 9 - i);
    }
    assert(isEmptySet(&s));
    for (i = 0; i < number_of_tests; i += 1) {
        randomSet(&s);
        assert(isSubsetOf(&empty, &s));
        assert(!isSubsetOf(&s, &empty));
        assert(isSubsetOf(&s, &universal));
        assert(!isSubsetOf(&universal, &s));

        checkCase(&intersectFromSet, &empty, &s, &empty);
        checkCase(&intersectFromSet, &s, &empty, &empty);
        checkCase(&intersectFromSet, &universal, &s, &s);
        checkCase(&intersectFromSet, &s, &universal, &s);

        checkCase(&unionInSet, &universal, &s, &universal);
        checkCase(&unionInSet, &s, &universal, &universal);

        checkCase(&subtractFromSet, &s, &empty, &s);

        assignSet(&r, &universal);
        subtractFromSet(&r, &s); // r = u - s;
        checkCase(&subtractFromSet, &universal, &r, &s); // (u - (u - s) == s)
        checkCase(&unionInSet, &s, &r, &universal); // s + (u - s) == u
        checkCase(&unionInSet, &r, &s, &universal); // (u - s) + s == u
    }
    printf("The special case tests have been passed\n");
    destroySet(&empty);
    destroySet(&universal);
    destroySet(&s);
    destroySet(&r);
}

void relationalTests() {
    Set s;
    Set t;
    int i;

    createEmptySet(&s);
    createEmptySet(&t);
    for (i = 0; i < number_of_tests; i += 1) {
        randomSet(&s);
        assignSet(&t, &s);
        assert(isSubsetOf(&s, &t));
        assert(isSubsetOf(&t, &s));
        assert(isEqualToSet(&s, &t));
        assert(isEqualToSet(&t, &s));
        insertSet(&s, rand() % maximum_set_size + maximum_set_size);
        assert(isSubsetOf(&t, &s));
        assert(! isSubsetOf(&s, &t));
    }
    printf("The relational tests have been passed\n");
    destroySet(&s);
    destroySet(&t);
}

void algebraicTests(void) {
    Set empty;
    Set universal;
    int i;
    Set s;
    Set t;
    Set u;
    Set v;
    Set w;

    createEmptySet(&empty);
    createEmptySet(&universal);
    for (i = 0; i < maximum_set_size; i += 1) {
        insertSet(&universal, i);
    }

    createEmptySet(&s);
    createEmptySet(&t);
    createEmptySet(&u);
    createEmptySet(&v);
    createEmptySet(&w);

    for (i = 0; i < number_of_tests; i += 1) {
        randomSet(&u);
        randomSet(&v);
        randomSet(&w);

        /* u + v == v + u */
        assignSet(&s, &u);
        unionInSet(&s, &v);
        assignSet(&t, &v);
        unionInSet(&t, &u);
        assert(isEqualToSet(&s, &t));

        /* u + (v + w) == (u + v) + w */
        assignSet(&t, &v);
        unionInSet(&t, &w);
        assignSet(&s, &u);
        unionInSet(&s, &t);
        assignSet(&t, &u);
        unionInSet(&t, &v);
        unionInSet(&t, &w);
        assert(isEqualToSet(&s, &t));

        /* u * v == v * u */
        assignSet(&s, &u);
        intersectFromSet(&s, &v);
        assignSet(&t, &v);
        intersectFromSet(&t, &u);
        assert(isEqualToSet(&s, &t));

        /* u * (v * w) == (u * v) * w */
        assignSet(&t, &v);
        intersectFromSet(&t, &w);
        assignSet(&s, &u);
        intersectFromSet(&s, &t);
        assignSet(&t, &u);
        intersectFromSet(&t, &v);
        intersectFromSet(&t, &w);
        assert(isEqualToSet(&s, &t));

        /* u - v == u - (u * v) */
        assignSet(&s, &u);
        intersectFromSet(&s, &v);
        assignSet(&t, &u);
        subtractFromSet(&t, &s);
        assignSet(&s, &u);
        subtractFromSet(&s, &v);
        assert(isEqualToSet(&s, &t));

        /* additional tests, not implemented
           assert(w * (u - v) == w * u - w * v);
           assert(u * (v + w) == (u * v) + (u * w));
           assert(universal - (u * v) == (universal - u) + (universal - v));
           assert(universal - (u + v) == (universal - u) * (universal - v));
        */
    }
    printf("The algebraic tests have been passed\n");
    destroySet(&empty);
    destroySet(&universal);
    destroySet(&s);
    destroySet(&t);
    destroySet(&u);
    destroySet(&v);
    destroySet(&w);
}

/*
 * create two sets with n random elements
 * the sets should have 50% of the elements in common
 */
void createRandomSetN(int n, Set* a, Set* b) {
    int x;
    int last_size = 0;
    createEmptySet(a);
    while (a->len < n) {
        if (a->len != last_size) {
            last_size = a->len;
            if (last_size % 1000 == 0) {
                printf("%d..", last_size);
                fflush(stdout);
            }
        }
        x = 2 * (5 * n - (rand() % (10 * n)));
        if (isMemberSet(a, x)) { continue; } // try another number
        /* a will have only even elements */
        insertSet(a, x);
        if ((rand() % 2) == 0) {
            insertSet(b, x);
        } else {
            insertSet(b, x + 1); // an odd value, can't be in a
        }
    }
    assert(a->len == b->len);
}

typedef void (*Function)(void);

double timeFunction(Function f) {
    int reps = 128;
    uint64_t time = 0;
    volatile int k;
    while (time < 6000) {
        if (reps > 1000000000) { return 0.0; } // overflow?
        auto start = std::chrono::high_resolution_clock::now();
        for (k = 0; k < reps; k += 1) {
            f();
        }
        auto end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        reps *= 2;
    }

    return ((double) time) / reps;
}

volatile int bogus_value; // used to ensure compiler does not optimize away our func calls

Set* setA;
Set* setB;
Set* setAPrime; // almost exactly the same as A

int is_mem_x;
void isMemberTimeFun(void) {
    if (isMemberSet(setA, is_mem_x)) {
        is_mem_x ^= 1;
        is_mem_x <<= 1;
    } else {
        is_mem_x >>= 1;
        is_mem_x ^= 2;
    }
}

void isEqualTimeFun(void) {
    bogus_value = isEqualToSet(setA, setAPrime);
}

void isSubsetTimeFun(void) {
    bogus_value = isSubsetOf(setA, setAPrime);
}

void unionTimeFun(void) {
    Set t;
    createCopySet(&t, setA);
    unionInSet(&t, setB);
    destroySet(&t);
}

void intersectTimeFun(void) {
    Set t;
    createCopySet(&t, setA);
    intersectFromSet(&t, setB);
    destroySet(&t);
}

void subtractTimeFun(void) {
    Set t;
    createCopySet(&t, setA);
    subtractFromSet(&t, setB);
    destroySet(&t);
}

bool checkLinear(double times[], int sizes[], int first, int last) {
    double time_ratio = times[last] / times[first];
    double size_ratio = sizes[last] / sizes[first];

    if (time_ratio < size_ratio * 1.25) {
        return true;
    } else {
        return false;
    }
}

bool checkSubLinear(double times[], int sizes[], int first, int last) {
    double time_ratio = times[last] / times[first];
    double size_ratio = sizes[last] / sizes[first];

    if (time_ratio < size_ratio * 0.5) {
        return true;
    } else {
        return false;
    }
}

enum Tests {
    IS_MEMBER = 0,
    INSERT = 1,
    REMOVE = 2,
    IS_EQUAL_TO = 3,
    IS_SUBSET_OF = 4,
    UNION_IN = 5,
    INTERSECT_FROM = 6,
    SUBTRACT_FROM = 7,

    NUM_TESTS /* MUST BE LAST */
};

typedef enum Scales {
    SUB_LINEAR,
    LINEAR,
    SUPER_LINEAR
} Scales;
/* NOTE: the order of these strings MUST MATCH EXACTLY the order of the Scales enum */
const char* scaling_strings[] = {
    "sub linear (YAHOO!)",
    "linear",
    "super linear, yuck."
};

int sizes[] = { 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600 };
//const unsigned num_times = sizeof(sizes) / sizeof(int);
#define num_times (sizeof(sizes) / sizeof(int))
Set setsA[num_times];
Set setsAPrime[num_times];
Set setsB[num_times];
double times[num_times];

Scales determineScaling(Function fun) {
    bool linear;
    bool sublinear;

    unsigned trial = 0;
    for (; trial < num_times; trial += 1) {
        if (trial > 0 && ((times[trial - 1] * sizes[trial])     > 10)) { break; }
        setA = &setsA[trial];
        setB = &setsB[trial];
        setAPrime = &setsAPrime[trial];
        times[trial] = timeFunction(fun);
        printf("time taken for size %d was %g\n",
            sizes[trial], times[trial]);
    }

    if (trial < 3) {
        printf("I'm sorry, your program is way too inefficient.\n");
        printf("you'll need to find a way-faster computer to test it on\n");
        return SUPER_LINEAR;
    }
    linear = checkLinear(times, sizes, 0, trial - 1)
        || checkLinear(times, sizes, 1, trial - 1);
    sublinear = checkSubLinear(times, sizes, 0, trial - 1)
        || checkSubLinear(times, sizes, 1, trial - 1);

    if (sublinear) { return SUB_LINEAR; }
    else if (linear) { return LINEAR; }
    else { return SUPER_LINEAR; }
}

void testTime(void) {
    Scales behavior[NUM_TESTS];

    for (uint32_t k = 0; k < num_times; k += 1) {
        printf("creating a random set with %d elements...", sizes[k]);
        fflush(stdout);
        createRandomSetN(sizes[k], &setsA[k], &setsB[k]);
        int x = 10 * sizes[k];
        createCopySet(&setsAPrime[k], &setsA[k]);
        insertSet(&setsA[k], x);
        insertSet(&setsAPrime[k], x + 1);
        insertSet(&setsB[k], x);
        printf("done\n");
    }

    printf("checking scaling of isMember\n");
    behavior[IS_MEMBER] = determineScaling(&isMemberTimeFun);
    printf("isMember's scaling appears to be: %s\n", scaling_strings[behavior[IS_MEMBER]]);

    printf("checking scaling of isEqualTo\n");
    behavior[IS_EQUAL_TO] = determineScaling(&isEqualTimeFun);
    printf("isEqualTo's scaling appears to be: %s\n", scaling_strings[behavior[IS_EQUAL_TO]]);

    printf("checking scaling of isSubsetOf\n");
    behavior[IS_SUBSET_OF] = determineScaling(&isSubsetTimeFun);
    printf("isSubsetOf's scaling appears to be: %s\n", scaling_strings[behavior[IS_SUBSET_OF]]);

    printf("checking scaling of unionIn\n");
    behavior[UNION_IN] = determineScaling(&unionTimeFun);
    printf("unionIn's scaling appears to be: %s\n", scaling_strings[behavior[UNION_IN]]);

    printf("checking scaling of intersectFrom\n");
    behavior[INTERSECT_FROM] = determineScaling(&intersectTimeFun);
    printf("intersectFrom's scaling appears to be: %s\n", scaling_strings[behavior[INTERSECT_FROM]]);

    printf("checking scaling of subtractFrom\n");
    behavior[SUBTRACT_FROM] = determineScaling(&subtractTimeFun);
    printf("subtractFrom's scaling appears to be: %s\n", scaling_strings[behavior[SUBTRACT_FROM]]);

    printf("Performance Summary:\n");
    printf("isMemberSet\t\t%s\n", scaling_strings[behavior[IS_MEMBER]]);
    printf("isEqualToSet\t\t%s\n", scaling_strings[behavior[IS_EQUAL_TO]]);
    printf("isSubsetOf\t\t%s\n", scaling_strings[behavior[IS_SUBSET_OF]]);
    printf("unionInSet\t\t%s\n", scaling_strings[behavior[UNION_IN]]);
    printf("intersectFromSet\t%s\n", scaling_strings[behavior[INTERSECT_FROM]]);
    printf("subtractFromSet\t\t%s\n", scaling_strings[behavior[SUBTRACT_FROM]]);
    for (uint32_t i = 0; i < num_times; i++) {
        destroySet(&setsA[i]);
        destroySet(&setsAPrime[i]);
        destroySet(&setsB[i]);
    }
}
