#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printBoard(int **board, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (board[i][j] == 1)
            {
                printf("Q ");
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int isSafeBacktracking(int **board, int n, int row, int col)
{
    int i, j;

    for (i = 0; i < col; i++)
    {
        if (board[row][i])
            return 0;
    }

    i = row;
    j = col;
    while (i >= 0 && j >= 0)
    {
        if (board[i][j])
            return 0;
        i--;
        j--;
    }

    i = row;
    j = col;
    while (i < n && j >= 0)
    {
        if (board[i][j])
            return 0;
        i++;
        j--;
    }
    return 1;
}

int isValidPosition(int **board, int n)
{
    int i, j, k, l;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (board[i][j] == 1)
            {
                k = 0;
                while (k < n)
                {
                    if (k != j && board[i][k] == 1)
                        return 0;
                    k++;
                }
                k = 0;
                while (k < n)
                {
                    if (k != i && board[k][j] == 1)
                        return 0;
                    k++;
                }
                k = 0;
                while (k < n)
                {
                    l = 0;
                    while (l < n)
                    {
                        if (k != i && l != j && board[k][l] == 1)
                        {
                            if (k - l == i - j || k + l == i + j)
                                return 0;
                        }
                        l++;
                    }
                    k++;
                }
            }
        }
    }
    return 1;
}

void get2DCoordinates(int index, int *row, int *col, int n)
{
    *row = index / n;
    *col = index % n;
}

int solveNQueensBacktrackingUtil(int **board, int n, int col, int *total_solutions)
{
    int i;

    if (col >= n)
    {
        (*total_solutions)++;
        printf("Solution %d:\n", *total_solutions);
        printBoard(board, n);
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        if (isSafeBacktracking(board, n, i, col))
        {
            board[i][col] = 1;
            solveNQueensBacktrackingUtil(board, n, col + 1, total_solutions);
            board[i][col] = 0;
        }
    }
    return 0;
}

void solveNQueensBacktracking(int n, int *total_solutions, double *execution_time)
{
    clock_t start = clock();
    int **board = (int **)malloc(n * sizeof(int *));
    int i;
    *total_solutions = 0;

    for (i = 0; i < n; i++)
    {
        board[i] = (int *)calloc(n, sizeof(int));
    }
    solveNQueensBacktrackingUtil(board, n, 0, total_solutions);

    clock_t end = clock();
    *execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++)
    {
        free(board[i]);
    }
    free(board);

    printf("BACKTRACKING\n");
    printf("Total solutions: %d\n", *total_solutions);
    printf("Execution time: %f seconds\n\n", *execution_time);
}

int next_permutation(int *array, int n)
{
    int i = n - 2;
    int k, l;

    while (i >= 0 && array[i] >= array[i + 1])
    {
        i--;
    }

    if (i < 0)
        return 0;

    int j = n - 1;
    while (array[j] <= array[i])
    {
        j--;
    }

    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;

    k = i + 1;
    l = n - 1;
    while (k < l)
    {
        int temp = array[k];
        array[k] = array[l];
        array[l] = temp;
        k++;
        l--;
    }
    return 1;
}

void solveNQueensOptimized1(int n, int *total_solutions, double *execution_time)
{
    clock_t start = clock();
    int *columns = (int *)malloc(n * sizeof(int));
    int i, j;
    *total_solutions = 0;
    int finished = 0;

    for (i = 0; i < n; i++)
    {
        columns[i] = 0;
    }

    while (!finished)
    {
        int is_valid = 1;
        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (columns[i] == columns[j] || abs(columns[i] - columns[j]) == abs(i - j))
                {
                    is_valid = 0;
                    break;
                }
            }
            if (!is_valid)
                break;
        }

        if (is_valid)
        {
            (*total_solutions)++;
            printf("Solution %d:\n", *total_solutions);

            int **board = (int **)malloc(n * sizeof(int *));
            for (i = 0; i < n; i++)
            {
                board[i] = (int *)calloc(n, sizeof(int));
                board[i][columns[i]] = 1;
            }
            printBoard(board, n);

            for (i = 0; i < n; i++)
            {
                free(board[i]);
            }
            free(board);
        }

        int row = n - 1;
        while (row >= 0 && columns[row] == n - 1)
        {
            columns[row] = 0;
            row--;
        }

        if (row < 0)
        {
            finished = 1;
        }
        else
        {
            columns[row]++;
        }
    }

    clock_t end = clock();
    *execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("OPTIMIZED 1\n");
    printf("Total solutions: %d\n", *total_solutions);
    printf("Execution time: %f seconds\n\n", *execution_time);

    free(columns);
}

void solveNQueensOptimized2(int n, int *total_solutions, double *execution_time)
{
    clock_t start = clock();

    int *columns = (int *)malloc(n * sizeof(int));
    int i, j;
    *total_solutions = 0;

    for (i = 0; i < n; i++)
    {
        columns[i] = i;
    }

    do
    {
        int is_valid = 1;
        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (abs(columns[i] - columns[j]) == abs(i - j))
                {
                    is_valid = 0;
                    break;
                }
            }
            if (!is_valid)
                break;
        }

        if (is_valid)
        {
            (*total_solutions)++;
            printf("Solution %d:\n", *total_solutions);

            int **board = (int **)malloc(n * sizeof(int *));
            for (i = 0; i < n; i++)
            {
                board[i] = (int *)calloc(n, sizeof(int));
                board[i][columns[i]] = 1;
            }
            printBoard(board, n);

            for (i = 0; i < n; i++)
            {
                free(board[i]);
            }
            free(board);
        }
    } while (next_permutation(columns, n));

    clock_t end = clock();
    *execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("OPTIMIZED 2\n");
    printf("Total solutions: %d\n", *total_solutions);
    printf("Execution time: %f seconds\n\n", *execution_time);

    free(columns);
}

void solveNQueensBruteForce(int n, int *total_solutions, double *execution_time)
{
    clock_t start = clock();

    int **board = (int **)malloc(n * sizeof(int *));
    int i, j;

    for (i = 0; i < n; i++)
    {
        board[i] = (int *)calloc(n, sizeof(int));
    }

    int *queens = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        queens[i] = i;
    }

    *total_solutions = 0;
    int finished = 0;
    int total_cells = n * n;

    while (!finished)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                board[i][j] = 0;
            }
        }

        for (i = 0; i < n; i++)
        {
            int row, col;
            get2DCoordinates(queens[i], &row, &col, n);
            board[row][col] = 1;
        }

        if (isValidPosition(board, n))
        {
            (*total_solutions)++;
            printf("Solution %d:\n", *total_solutions);
            printBoard(board, n);
        }

        i = n - 1;
        while (i >= 0 && queens[i] == total_cells - n + i)
        {
            i--;
        }

        if (i < 0)
        {
            finished = 1;
        }
        else
        {
            queens[i]++;
            for (j = i + 1; j < n; j++)
            {
                queens[j] = queens[j - 1] + 1;
            }
        }
    }

    clock_t end = clock();
    *execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++)
    {
        free(board[i]);
    }

    printf("BRUTE FORCE\n");
    printf("Total solutions: %d\n", *total_solutions);
    printf("Execution time: %f seconds\n\n", *execution_time);

    free(board);
    free(queens);
}

void runAllMethods(int n)
{
    int total_solutions_optimized1;
    double execution_time_optimized1;

    int total_solutions_optimized2;
    double execution_time_optimized2;

    int total_solutions_brute_force;
    double execution_time_brute_force;

    int total_solutions_backtracking;
    double execution_time_backtracking;

    solveNQueensOptimized1(n, &total_solutions_optimized1, &execution_time_optimized1);
    solveNQueensOptimized2(n, &total_solutions_optimized2, &execution_time_optimized2);
    solveNQueensBruteForce(n, &total_solutions_brute_force, &execution_time_brute_force);
    solveNQueensBacktracking(n, &total_solutions_backtracking, &execution_time_backtracking);

    printf("Brute Force:\n");
    printf("Total solutions: %d\n", total_solutions_brute_force);
    printf("Execution time: %f seconds\n\n", execution_time_brute_force);
    printf("--------------------\n");

    printf("Optimized 1:\n");
    printf("Total solutions: %d\n", total_solutions_optimized1);
    printf("Execution time: %f seconds\n\n", execution_time_optimized1);
    printf("--------------------\n");

    printf("Optimized 2:\n");
    printf("Total solutions: %d\n", total_solutions_optimized2);
    printf("Execution time: %f seconds\n\n", execution_time_optimized2);
    printf("--------------------\n");

    printf("Backtracking:\n");
    printf("Total solutions: %d\n", total_solutions_backtracking);
    printf("Execution time: %f seconds\n\n", execution_time_backtracking);
    printf("--------------------\n");
}

int main()
{
    int n;
    int total_solutions;
    double execution_time;
    int exit_program = 0;

    printf("Enter board size for N-Queens problem: ");
    scanf("%d", &n);

    while (exit_program != 1)
    {
        printf("1-Brute Force\n2-Backtracking\n3-Optimized 1\n4-Optimized 2\n5-All Methods\n0-Exit\n");
        int choice;
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            solveNQueensBruteForce(n, &total_solutions, &execution_time);
            break;
        case 2:
            solveNQueensBacktracking(n, &total_solutions, &execution_time);
            break;
        case 3:
            solveNQueensOptimized1(n, &total_solutions, &execution_time);
            break;
        case 4:
            solveNQueensOptimized2(n, &total_solutions, &execution_time);
            break;
        case 5:
            runAllMethods(n);
            break;
        case 0:
            printf("Exiting.\n");
            exit_program = 1;
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
    return 0;
}
