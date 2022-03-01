#include "gtest/gtest.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "TestSupport.h"
#include "MatrixMultiply.h"

TEST(Test01, testA)
{
    double a[100];
    double b[100];
    double c[100];
    
    generateRandomMatrix(a, 10, 10);
    generateIdentityMatrix(b, 10, 10);
    multiplyMatrices(a, 10, 10, b, 10, c);
    assertEqualMatrices(a, c, 10, 10);
    
}

TEST(Test01, testB)
{
    double a[100];
    double b[100];
    double c[100];
    
    generateRandomMatrix(a, 10, 10);
    generateIdentityMatrix(b, 10, 10);
    multiplyMatrices(b, 10, 10, a, 10, c);
    assertEqualMatrices(a, c, 10, 10);
}

TEST(Test01, testC)
{
    double a[100];
    double b[100];
    double c[100];
    
    /* these arrays are used only for test C */
    uint32_t perturb_rows[5] = {2, 4, 6, 1, 7};
    double perturb_vals[5] = {1.0, -1.0, 2.0, -2.5, 3.0};
    double expected[] = {
        1, -10, 0, 0, 18, 0, -12, 3, 0, 0, 0, -6.5, 0, 0, 10.5, 0, -7,  3, 0, 0,
        0, -10, 0, 0, 18, 0, -12, 3, 0, 0, 0, -10,  0, 1, 18,   0, -12, 3, 0, 0,
        0, -10, 1, 0, 20, 0, -12, 3, 0, 0, 0, -10,  0, 0, 18,   1, -12, 3, 0, 0,
        0, -10, 0, 0, 20, 0, -13, 3, 0, 0, 0, -2.5, 0, 0, 4.5,  0, -3,  1, 0, 0,
        0, -10, 0, 0, 18, 0, -12, 3, 1, 0, 0, -10,  0, 0, 18,   0, -12, 3, 0, 1};
    
    generateIdentityMatrix(a, 10, 10);
    generateIdentityMatrix(b, 10, 10);
    
    perturbMatrix(a, 10, 10, perturb_rows, perturb_vals, 5);
    copyMatrix(a, b, 10, 10);
    perturbMatrix(b, 10, 10, perturb_rows, perturb_vals, 5);
    
    multiplyMatrices(a, 10, 10, b, 10, c);
    
    assertEqualMatrices(c, expected, 10, 10);
    
}

TEST(Test02, testA)
{
    double **a;
    double **b;
    double **c;
    
    a = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(a + i) = (double *)malloc(sizeof(double) * 10);
    }
    b = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(b + i) = (double *)malloc(sizeof(double) * 10);
    }
    generateRandomMatrixPtr(a, 10, 10);
    generateIdentityMatrixPtr(b, 10, 10);
    c = multiplyMatricesPtr(a, 10, 10, b, 10);
    assertEqualMatricesPtr(a, c, 10, 10);
    memoryRelease(a, 10);
    memoryRelease(b, 10);
    memoryRelease(c, 10);
    
}

TEST(Test02, testB)
{
    double **a;
    double **b;
    double **c;
    
    a = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(a + i) = (double *)malloc(sizeof(double) * 10);
    }
    b = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(b + i) = (double *)malloc(sizeof(double) * 10);
    }
    
    generateRandomMatrixPtr(a, 10, 10);
    generateIdentityMatrixPtr(b, 10, 10);
    c = multiplyMatricesPtr(b, 10, 10, a, 10);
    
    assertEqualMatricesPtr(a, c, 10, 10);
    
    memoryRelease(a, 10);
    memoryRelease(b, 10);
    memoryRelease(c, 10);
}

TEST(Test02, testC)
{
    double **a;
    double **b;
    double **c;
    double **expected_ptr;
    
    // these arrays are used only for test C
    uint32_t perturb_rows[5] = {2, 4, 6, 1, 7};
    double perturb_vals[5] = {1.0, -1.0, 2.0, -2.5, 3.0};
    double one[10] = {1, -10, 0, 0, 18, 0, -12, 3, 0, 0};
    double two[10] = {0, -6.5, 0, 0, 10.5, 0, -7, 3, 0, 0};
    double three[10] = {0, -10, 0, 0, 18, 0, -12, 3, 0, 0};
    double four[10] = {0, -10, 0, 1, 18, 0, -12, 3, 0, 0};
    double five[10] = {0, -10, 1, 0, 20, 0, -12, 3, 0, 0};
    double six[10] = {0, -10, 0, 0, 18, 1, -12, 3, 0, 0};
    double seven[10] = {0, -10, 0, 0, 20, 0, -13, 3, 0, 0};
    double eight[10] = {0, -2.5, 0, 0, 4.5, 0, -3, 1, 0, 0};
    double nine[10] = {0, -10, 0, 0, 18, 0, -12, 3, 1, 0};
    double ten[10] = {0, -10, 0, 0, 18, 0, -12, 3, 0, 1};
    
    double *expected[] = {one, two, three, four, five,
        six, seven, eight, nine, ten};
    
    expected_ptr = expected;
    
    a = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(a + i) = (double *)malloc(sizeof(double) * 10);
    }
    b = (double **)malloc(sizeof(double *) * 10);
    for (int i = 0; i < 10; i++) {
        *(b + i) = (double *)malloc(sizeof(double) * 10);
    }
    
    generateIdentityMatrixPtr(a, 10, 10);
    perturbMatrixPtr(a, 10, 10, perturb_rows, perturb_vals, 5);
    
    generateIdentityMatrixPtr(b, 10, 10);
    copyMatrixPtr(a, b, 10, 10);
    perturbMatrixPtr(b, 10, 10, perturb_rows, perturb_vals, 5);
    c = multiplyMatricesPtr(a, 10, 10, b, 10);
    
    assertEqualMatricesPtr(c, expected_ptr, 10, 10);
    memoryRelease(a, 10);
    memoryRelease(b, 10);
    memoryRelease(c, 10);
}

TEST(Test03, testA)
{
    double **result;
    double **input_ptr;
    double **expected_ptr;
    
    double one_a[2] = {1, 2};
    double two_a[2] = {3, 4};
    double *input_a[] = {one_a, two_a};
    input_ptr = input_a;
    
    double one_trans_a[2] = {1, 3};
    double two_trans_a[2] = {2, 4};
    
    double *expected_a[] = {one_trans_a, two_trans_a};
    expected_ptr = expected_a;
    result = transposeMatrix(input_ptr, 2, 2);
    
    assertEqualMatricesPtr(result, expected_ptr, 2, 2);
    memoryRelease(result, 2);
}

TEST(Test03, testB)
{
    double **result;
    double **input_ptr;
    double **expected_ptr;
    
    double one_b[3] = {1, 2, 3};
    double two_b[3] = {4, 5, 6};
    double three_b[3] = {7, 8, 9};
    double *input_b[] = {one_b, two_b, three_b};
    input_ptr = input_b;
    
    double one_trans_b[3] = {1, 4, 7};
    double two_trans_b[3] = {2, 5, 8};
    double three_trans_b[3] = {3, 6, 9};
    
    double *expected_b[] = {one_trans_b, two_trans_b, three_trans_b};
    expected_ptr = expected_b;

    result = transposeMatrix(input_ptr, 3, 3);
    assertEqualMatricesPtr(result, expected_ptr, 3, 3);
    memoryRelease(result, 3);
}

TEST(Test03, testC)
{
    double **result;
    double **input_ptr;
    double **expected_ptr;
    
    double one_c[3] = {1, 2, 3};
    double two_c[3] = {4, 5, 6};
    double *input_c[] = {one_c, two_c};
    input_ptr = input_c;
    
    double one_trans_c[2] = {1, 4};
    double two_trans_c[2] = {2, 5};
    double three_trans_c[2] = {3, 6};
    
    double *expected_c[] = {one_trans_c, two_trans_c, three_trans_c};
    expected_ptr = expected_c;

    result = transposeMatrix(input_ptr, 2, 3);
    assertEqualMatricesPtr(result, expected_ptr, 3, 2);
    memoryRelease(result, 3);
}

TEST(Test04, testA)
{
    double a[20] = {
        0.00, 0.05, -0.04, 0.67,
        -0.26, 0.75, 0.38, 0.43,
        0.00 , -0.48, 0.07, 0.16,
        0.65, 0.28, 0.43, 0.24,
        0.20, 0.00, 0.00 , 1.00};
    double b[8] = {
        0.06, 0.00,
        0.00, 0.34,
        -0.49, 0.71,
        -0.44, 0.00};
    double expected[10] = {
        -0.275200, -0.011400,
        -0.391000, 0.524800,
        -0.104700, -0.113500,
        -0.277300, 0.400500,
        -0.428000, 0.000000};
    double c[10];
    
    multiplyMatrices(a, 5, 4, b, 2, c);
    assertEqualMatrices(c, expected, 5, 2);

}
