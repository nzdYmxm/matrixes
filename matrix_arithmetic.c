#include<stdlib.h>
#include<stdio.h>

#ifndef bool
#define true 1
#define false 0
#define bool int
#endif

#define OPER_ADD 1
#define OPER_MUL 2
#define OPER_TRANSPOSE 3

int get_operation();

bool get_matrix_data(int *width, int *height);
bool init_matrix(int ***matrix, int width, int height);

bool input_matrix(int **matrix, int width, int height);
void print_matrix(int **matrix, int width, int height);

bool has_scan_error(int result, char tmp);
bool get_all_data(int *operation,
    int ***matr_1, int *width_1, int *height_1,
    int ***matr_2, int *width_2, int *height_2);

void do_operation(int operation, int **mat_1, int w_1, int h_1, int **mat_2, int w_2, int h_2);

int** sum_matrices(int **mat_1, int w, int h, int **mat_2);
int** transpose_matrix(int **mat_1, int w, int h);
int** mul_matrices(int **mat_1, int w_1, int h_1, int **mat_2, int h_2);

int main() {
    int operation;

    int **mat_1, w_1, h_1;
    int **mat_2, w_2, h_2;

    bool error = get_all_data(&operation, &mat_1, &w_1, &h_1, &mat_2, &w_2, &h_2);

    if (error) {
        printf("n/a");
    } else {
        do_operation(operation, mat_1, w_1, h_1, mat_2, w_2, h_2);
        free(mat_1);
        free(mat_2);
    }
    return 0;
}

void do_operation(int operation, int **mat_1, int w_1, int h_1, int **mat_2, int w_2, int h_2) {
    if (operation == OPER_ADD) {
        if (w_1 == w_2 && h_1 == h_2) {
            int** sum = sum_matrices(mat_1, w_1, h_1, mat_2);
            print_matrix(sum, w_1, h_1);
            free(sum);
        } else {
            printf("n/a");
        }
    } else if (operation == OPER_MUL) {
        if (w_1 == h_2) {
            int** mul = mul_matrices(mat_1, w_1, h_1, mat_2, w_2);
            print_matrix(mul, w_2, h_1);
            free(mul);
        } else {
            printf("n/a");
        }
    } else if (operation == OPER_TRANSPOSE) {
        int **transp = transpose_matrix(mat_1, w_1, h_1);
        print_matrix(transp, h_1, w_1);
        free(transp);
    }
}


int** mul_matrices(int **mat_1, int w_1, int h_1, int **mat_2, int w_2) {
    int **mul;
    init_matrix(&mul, w_2, h_1);

    for (int i = 0; i < h_1; i++) {
        for (int j = 0; j < w_2; j++) {
            int prod_sum = 0;

            for (int k = 0; k < w_1; k++)
                prod_sum += mat_1[i][k] * mat_2[k][j];

            mul[i][j] = prod_sum;
        }
    }

    return mul;
}

int** sum_matrices(int **mat_1, int w, int h, int **mat_2) {
    int **sum;
    init_matrix(&sum, w, h);

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            sum[i][j] = mat_1[i][j] + mat_2[i][j];

    return sum;
}

int ** transpose_matrix(int **mat, int w, int h) {
    int **res;
    init_matrix(&res, h, w);

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            res[j][i] = mat[i][j];
        }

    return res;
}


// Scans stdin for matrix size and content
bool get_matrix(int ***mat, int *w, int *h) {
    bool is_allocated = false;

    bool error = get_matrix_data(w, h);

    if (!error)  {
        error = init_matrix(mat, *w, *h);

        if (!error) {
            is_allocated = true;
            error = input_matrix(*mat, *w, *h);
        }
    }

    if (is_allocated && error)
        free(*mat);

    return error;
}

// Scans stdin for operation (1/2/3)
int get_operation() {
    int result;

    char tmp;
    int scan_result = scanf("%d%c", &result, &tmp);

    if (has_scan_error(scan_result, tmp))
        result = 0;

    if (result < 1 || result > 3)
        result = 0;

    return result;
}

// Tries to scan stdin for all data required
bool get_all_data(int *operation,
    int ***matr_1, int *width_1, int *height_1,
    int ***matr_2, int *width_2, int *height_2) {
    bool error = false;

    *operation = get_operation();

    if (*operation == 0) {
        error = true;
    } else {
        error = get_matrix(matr_1, width_1, height_1);

        if (!error) {
            if (*operation != OPER_TRANSPOSE)
                error = get_matrix(matr_2, width_2, height_2);
            else
                error = init_matrix(matr_2, 1, 1);
        }
    }

    return error;
}



// Scans stdin for matrix content
bool input_matrix(int **matrix, int width, int height) {
    bool error = false;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char tmp;
            int scan_result = scanf("%d%c", &(matrix[i][j]), &tmp);

            if (has_scan_error(scan_result, tmp))
                error = true;
        }

        if (error)
            break;
    }

    return error;
}

// Prints matrix via stdout
void print_matrix(int **matrix, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                printf("%d", matrix[i][j]);
            else
                printf(" %d", matrix[i][j]);
        }

        if (i < (height - 1))
            printf("\n");
    }
}

// Allocates matrix with given size
bool init_matrix(int ***matrix, int width, int height) {
    bool error = false;

    (*matrix) = (int**) malloc(width * height * sizeof(int) + height * sizeof(int*));
    int *ptr = (int*) ((*matrix) + height);

    if ((*matrix) == 0) {
        error = true;
    } else {
        for (int i = 0; i < height; i++)
            (*matrix)[i] = ptr + width * i;
    }

    return error;
}

bool has_scan_error(int result, char tmp) {
    return result != 2 || !(tmp == ' ' || tmp == '\n');
}

// Scans stdio for width and height
bool get_matrix_data(int *width, int *height) {
    bool error = false;

    char tmp;
    int scan_result = scanf("%d%c", height, &tmp);

    if (has_scan_error(scan_result, tmp) || (*height) <= 0) {
        error = true;
    } else {
        scan_result = scanf("%d%c", width, &tmp);

        if (has_scan_error(scan_result, tmp) || (*width) <= 0) {
            error = true;
        } else {
            error = false;
        }
    }

    return error;
}
