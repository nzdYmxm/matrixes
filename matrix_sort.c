#include<stdlib.h>
#include<stdio.h>

#ifndef bool
#define true 1
#define false 0
#define bool int
#endif

#define MEM_ONE_ARRAY 1
#define MEM_ARRAYS_PTRS 2
#define MEM_TWO_ARRAYS 3

bool get_matrix_data(int *mem_type, int *width, int *height);
bool init_matrix(int ***matrix, int width, int height, int mem_type);

bool input_matrix(int **matrix, int width, int height);
void print_matrix(int **matrix, int width, int height);

void free_matrix(int **matrix, int height, int mem_type);
bool has_scan_error(int result, char tmp);

void sort_matrix_rows(int **matrix, int height, int width);

int main() {
    int **matrix;

    bool is_allocated = false;
    int memory_type, width, height;


    bool error = get_matrix_data(&memory_type, &width, &height);

    if (error) {
        printf("n/a");
    } else {
        error = init_matrix(&matrix, width, height, memory_type);

        if (error) {
            printf("n/a");
        } else {
            is_allocated = true;
            error = input_matrix(matrix, width, height);

            if (error) {
                printf("n/a");
            } else {
                sort_matrix_rows(matrix, width, height);
                print_matrix(matrix, width, height);
            }
        }
    }

    if (is_allocated)
        free_matrix(matrix, height, memory_type);

    return 0;
}

int sum_row(int *row, int width) {
    int sum = 0;

    for (int i = 0; i < width; i++)
        sum += row[i];

    return sum;
}

void sort_matrix_rows(int **matrix, int height, int width) {
    for (int row = 0; row < height; row++) {
        int min_sum_row = row;
        int min_sum = sum_row(matrix[min_sum_row], width);

        for (int check = row + 1; check < height; check++) {
            int check_sum = sum_row(matrix[check], width);
            if (check_sum < min_sum) {
                min_sum_row = check;
                min_sum = check_sum;
            }
        }

        int *tmp = matrix[row];
        matrix[row] = matrix[min_sum_row];
        matrix[min_sum_row] = tmp;
    }
}

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

void free_matrix(int **matrix, int height, int mem_type) {
    if (mem_type == MEM_ONE_ARRAY) {
        free(matrix);
    } else if (mem_type == MEM_ARRAYS_PTRS) {
        for (int i = 0; i < height; i++)
            free(matrix[i]);

        free(matrix);
    } else if (mem_type == MEM_TWO_ARRAYS) {
        free(matrix[0]);
        free(matrix);
    }
}

bool one_array_matrix(int ***matrix, int width, int height) {
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

bool arrays_ptrs_matrix(int ***matrix, int width, int height) {
    bool error = false;

    (*matrix) = (int**) malloc(height * sizeof(int*));

    if ((*matrix) == 0) {
        error = true;
    } else {
        for (int i = 0; i < height; i++) {
            (*matrix)[i] = (int*) malloc(width * sizeof(int));

            if ((*matrix)[i] == 0) {
                error = true;
                break;
            }
        }
    }

    return error;
}

bool two_arrays_matrix(int ***matrix, int width, int height) {
    bool error = false;
    (*matrix) = (int**) malloc(height * sizeof(int*));
    int *values_array = (int*) malloc(width * height * sizeof(int));

    if ((*matrix) == 0 || values_array == 0) {
        error = true;
    } else {
        for (int i = 0; i < height; i++)
            (*matrix)[i] = values_array + width * i;
    }
    return error;
}

bool init_matrix(int ***matrix, int width, int height, int mem_type) {
    bool error = false;

    if (mem_type == MEM_ONE_ARRAY) {
        error = one_array_matrix(matrix, width, height);
    } else if (mem_type == MEM_ARRAYS_PTRS) {
        error = arrays_ptrs_matrix(matrix, width, height);
    } else if (mem_type == MEM_TWO_ARRAYS) {
        error = two_arrays_matrix(matrix, width, height);
    } else {
        error = true;
    }

    return error;
}

bool has_scan_error(int result, char tmp) {
    return result != 2 || !(tmp == ' ' || tmp == '\n');
}

bool get_matrix_data(int *mem_type, int *width, int *height) {
    bool error = false;

    char tmp;
    int scan_result = scanf("%d%c", mem_type, &tmp);

    if (has_scan_error(scan_result, tmp) || (*mem_type) < 1 || (*mem_type) > 3) {
        error = true;
    } else {
        scan_result = scanf("%d%c", height, &tmp);

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
    }

    return error;
}
