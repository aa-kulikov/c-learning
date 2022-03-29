#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define ROW 25
#define STOLB 80

int countNeighbors(int** board, int x, int y);
void evol(int **grid, int ** srid);
void graphic(int ** grid);
void input(int ** grid);
void copy(int ** grid, int ** sgrid);

int main() {
    int even = 0; 
    int start = 1;
    int ** f_evol = malloc(ROW * sizeof(int*));
    for (int i = 0; i < ROW; i++) {
        f_evol[i] = calloc(STOLB, sizeof(int));
    }
    int ** s_evol = malloc(ROW * sizeof(int*));
    for (int i = 0; i < ROW; i++) {
        s_evol[i] = calloc(STOLB, sizeof(int));
    }
    input(f_evol);
    copy(f_evol, s_evol);
    printf("\x1b[2J");
    while (start == 1) {
        printf("\x1b[H");
        graphic(f_evol);
        switch (even) {
            case 0:
                evol(s_evol, f_evol);
                even++;
                break;
            case 1:
                evol(f_evol, s_evol);
                even--;
                break;
        }
        usleep(300000);
    }
    for (int i = 0; i < ROW; i++) {
        free(f_evol[i]);
    }
    free(f_evol);
    for (int i = 0; i < ROW; i++) {
        free(s_evol[i]);
    }
    free(s_evol);
}

int countNeighbors(int** board, int x, int y) {
	int sum = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			int row = (x + i + ROW) % ROW;
			int col = (y + j + STOLB) % STOLB;

			sum += board[row][col];
		}
	}

	sum -= board[x][y];

	return sum;
}


void graphic(int ** grid){
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < STOLB; j++) {
            if (grid[i][j] == 1) {
                printf("X");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}


void input(int ** grid){
    int a;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < STOLB; j++) {
            scanf("%d", &a);
            grid[i][j] = a;
        }
    }
}

void copy(int ** grid, int ** sgrid){
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < STOLB; j++) {
            (sgrid[i][j]) = (grid[i][j]); 
        }
    }
}

void evol(int **grid, int ** srid) {
    int count = 0;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < STOLB; j++) {
            count = countNeighbors(grid, i, j);
            if (count == 3) {
                srid[i][j] = 1;
            } else if ((count > 3) || (count < 2)) {
                srid[i][j] = 0;
            } else {
                srid[i][j] = grid[i][j];
            }
        }
    }
}

