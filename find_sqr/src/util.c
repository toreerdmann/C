
typedef struct Point {
    int x;
    int y;
} t_point;

typedef struct Square {
    t_point topL;
    t_point botR;
} t_square;

int is_in(t_point *p, t_square *sq) {
    return (p->x >= sq->topL.x && p->x <= sq->botR.x && p->y >= sq->topL.y && p->y <= sq->botR.y);
}

int is_empty(t_point *obs, int nobs, t_square *sq) {
    int k = 0;
    while(k < nobs) {
        if (is_in(&obs[k], sq))
            return 0;
        k++;
    }
    return 1;
}

void show(char **rows, int nx, int ny, t_square sq) {
    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            t_point p = {.x = i, .y = j};
            if (is_in(&p, &sq))
                if (rows[i][j] == 'o')
                    printf("X");
                else
                    printf("x");
            else 
                printf("%c", rows[i][j]);
        }
        printf("\n");
    }
}
