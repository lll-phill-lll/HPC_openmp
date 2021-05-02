#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void zero_init_matrix(double ** matrix, size_t N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(double ** matrix, size_t N)
{

    for (int i = 0; i != N; ++i)
    {
        for (int j = 0; j != N; ++j)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
 printf("-------------\n");
}

void rand_init_matrix(double ** matrix, size_t N)
{
    srand(time(0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = i+j; // rand() / RAND_MAX;
        }
    }
}

double ** malloc_matrix(size_t N)
{
    double ** matrix = (double **)malloc(N * sizeof(double *));

    for (int i = 0; i < N; ++i)
    {
        matrix[i] = (double *)malloc(N * sizeof(double));
    }

    return matrix;
}

void free_matrix(double ** matrix, size_t N)
{
    for (int i = 0; i < N; ++i)
    {
        free(matrix[i]);
    }

    free(matrix);
}

int main()
{
    const size_t N = 3; // size of an array

    clock_t start, end;

    double ** A, ** B, ** C; // matrices

    printf("Starting:\n");

    A = malloc_matrix(N);
    B = malloc_matrix(N);
    C = malloc_matrix(N);

    rand_init_matrix(A, N);
    rand_init_matrix(B, N);
    zero_init_matrix(C, N);

    start = clock();

//
//  matrix multiplication algorithm
//
//
   int i,j,k;
   #pragma omp parallel for private(i,j,k) shared(A,B,C)

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end = clock();

    printf("Time elapsed (ijn): %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);


    print_matrix(A, N);
    print_matrix(B, N);
    print_matrix(C, N);

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
