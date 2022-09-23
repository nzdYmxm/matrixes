#include<stdio.h>
#include<stdlib.h>

#define MAX_LENGTH 10

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

bool input(int **data, int *length);
void insertion_sort(int *data, int length);
void output(int *data, int length);

int main() {
    int *data;
    int length;

    bool error = input(&data, &length);

    if (error) {
        printf("n/a");
    } else {
        insertion_sort(data, length);
        output(data, length);

        free(data);
    }

    return 0;
}

bool has_scan_err(int result, char tmp) {
    return result != 2 || !(tmp == ' ' || tmp == '\n');
}

bool input(int **data, int *length) {
    bool error = false;
    char tmp;
    int scan_result = scanf("%d%c", length, &tmp);

    if (has_scan_err(scan_result, tmp) || (*length) <= 0 || (*length) > MAX_LENGTH) {
        error = true;
    } else {
        (*data) = (int*) malloc( (*length) * sizeof(int) );

        if (data == 0) {
            error = true;
        } else {
            for (int i = 0; i < *length; i++) {
                scan_result = scanf("%d%c", &(*data)[i], &tmp);

                if (has_scan_err(scan_result, tmp)) {
                    error = true;
                    break;
                }
            }
        }
    }

    return error;
}

void insertion_sort(int *data, int length) {
    for (int i = 0; i < length; i++) {
        int min_element = i;

        for (int j = i; j < length; j++)
            if (data[j] < data[min_element])
                min_element = j;

        int tmp = data[i];
        data[i] = data[min_element];
        data[min_element] = tmp;
    }
}

void output(int *data, int length) {
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            printf("%d", data[i]);
        } else {
            printf(" %d", data[i]);
        }
    }
}
