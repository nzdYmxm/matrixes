#include<stdlib.h>
#include<stdio.h>

#ifndef bool
#define true 1
#define false 0
#define bool int
#endif

#define MAX_STATIC_WIDTH 100
#define MAX_STATIC_HEIGHT 100

#define MEM_STATIC 1
#define MEM_ONE_ARRAY 2
#define MEM_ARRAYS_PTRS 3
#define MEM_TWO_ARRAYS 4

bool get_matrix_data(int *mem_type, int *width, int *height);
bool init_matrix(int ***matrix, int width, int height, int mem_type, int **static_buffer);

bool input_matrix(int **matrix, int width, int height);
void print_matrix(int **matrix, int width, int height);

void free_matrix(int **matrix, int height, int mem_type);
bool has_scan_error(int result, char tmp);

void init_static_pointers(int **pointers, int *buffer);

int main() {
    int static_buffer[MAX_STATIC_WIDTH * MAX_STATIC_HEIGHT];
    int *static_pointers[MAX_STATIC_HEIGHT];
    init_static_pointers(static_pointers, static_buffer);

    int **matrix;

    bool is_allocated = false;
    int memory_type, width, height;


    bool error = get_matrix_data(&memory_type, &width, &height);

    if (error) {
        printf("n/a");
    } else {
        error = init_matrix(&matrix, width, height, memory_type, (int**) static_pointers);

        if (error) {
            printf("n/a");
        } else {
            is_allocated = memory_type != MEM_STATIC ? true : false;
            error = input_matrix(matrix, width, height);

            if (error) {
                printf("n/a");
            } else {
                print_matrix(matrix, width, height);
            }
        }
    }

    if (is_allocated)
        free_matrix(matrix, height, memory_type);

    return 0;
}

void init_static_pointers(int **pointers, int *buffer) {
    for (int i = 0; i < MAX_STATIC_HEIGHT; i++)
        pointers[i] = buffer + i * MAX_STATIC_WIDTH;
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

bool static_matrix(int ***matrix, int width, int height, int **static_buffer) {
    bool error = false;

    if (width >= MAX_STATIC_WIDTH || height >= MAX_STATIC_HEIGHT) {
        error = true;
    } else {
        (*matrix) = static_buffer;
    }

    return error;
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

bool init_matrix(int ***matrix, int width, int height, int mem_type, int **static_buffer) {
    bool error = false;

    if (mem_type == MEM_STATIC) {
        error = static_matrix(matrix, width, height, static_buffer);
    } else if (mem_type == MEM_ONE_ARRAY) {
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

    if (has_scan_error(scan_result, tmp) || (*mem_type) < 1 || (*mem_type) > 4) {
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
