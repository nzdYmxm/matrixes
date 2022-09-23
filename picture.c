#include<stdio.h>

#define N 15
#define M 13

void transform(int buf[N][M], int **matr, int n);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int **picture, int n, int m);

int  main() {
    int picture_data[N][M];
    int *picture[N];

    transform(picture_data, picture, N);
    reset_picture(picture, N, M);
    make_picture(picture, N, M);
    print_picture(picture, N, M);

    return 0;
}

void print_picture(int **picture, int n, int m) {
    for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
        if (x == 0)
            printf("%d", picture[y][x]);
        else
            printf(" %d", picture[y][x]);
    }
    if (y < (n - 1))
        printf("\n");
    }
}

void make_window_frame(int **picture, int w, int h, int *frame_w, int *frame_h) {
    int mid_w = w / 2;
    int mid_h = h / 2;

    for (int j = 0; j < w; j++) {
        picture[0][j] = frame_w[j];
        picture[mid_h][j] = frame_w[j];
        picture[h - 1][j] = frame_w[j];
    }
    for (int i = 0; i < h; i++) {
        picture[i][0] = frame_h[i];
        picture[i][mid_w] = frame_h[i];
        picture[i][w - 1] = frame_h[i];
    }
}

void make_tree_trunk(int **picture, int x, int y, int *tree_trunk, int trunk_length) {
    for (int j = 0; j < trunk_length; j++) {
        picture[y][j + x] = tree_trunk[j];
        picture[y - 1 - j][x + 1] = tree_trunk[j];
        picture[y - 1 - j][x + 2] = tree_trunk[j];
    }
}

void make_tree_foliage(int **picture, int x, int y, int *foliage, int foliage_length) {
    for (int j = 0; j < foliage_length; j++) {
        picture[y + 1][x + j] = foliage[j];
        picture[y + 2][x + j] = foliage[j];
        picture[y + j][x + 1] = foliage[j];
        picture[y + j][x + 2] = foliage[j];
    }
}

void make_sun(int **picture, int x, int y, int sun[6][5]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            picture[i + y][j + x] = sun[i][j];
        }
    }
}

void make_picture(int **picture, int n, int m) {
    int frame_w[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int frame_h[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int tree_trunk[] = { 7, 7, 7, 7 };
    int tree_foliage[] = { 3, 3, 3, 3 };
    int sun_data[6][5] = { { 0, 6, 6, 6, 6 },
                           { 0, 0, 6, 6, 6 },
                           { 0, 0, 6, 6, 6 },
                           { 0, 6, 0, 0, 6 },
                           { 0, 0, 0, 0, 0 },
                           { 0, 0, 0, 0, 0 } };

    reset_picture(picture, n, m);

    make_tree_trunk(picture, 2, 10, tree_trunk, 4);
    make_tree_foliage(picture, 2, 2, tree_foliage, 4);
    make_sun(picture, 7, 1, sun_data);

    int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);
    int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);
    // Window frame
    make_window_frame(picture, length_frame_w, length_frame_h, frame_w, frame_h);
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int buf[N][M], int **matr, int n) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf[i];
    }
}
