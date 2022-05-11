#include <cstdlib>
#include <iostream>
#include <iomanip>

#define N 4
#define M 5

int A[N][M] = { { 1, 2, 3, 4, 5 }, { 6, 7, 8, 9, 10 }, { 11, 12, 13, 14, 15 }, { 16, 17, 18, 19, 20 } };

void fillArray(int ***arr)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            (*arr)[i][j] = A[i][j];
        }
    }
}

void printArray(int ***arr)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << std::setw(5) << (*arr)[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main()
{
    //int *p = (int *)malloc(N * M * sizeof(int));
    //int **pp = (int **)malloc(N * sizeof(int *));

    int **pp = new int *[N];
    int *p = new int[N * M];

    for (int i = 0; i < N; ++i) {
        pp[i] = p + (i * M);
        // pp[i] = &p[i * M];
        // int j = i * M;
        // int *t = &p[j];
        // pp[i] = t;
    }

    fillArray(&pp);
    printArray(&pp);

    //free(pp);
    //free(p);

    delete[] p;
    delete[] pp;

    return 0;
}
