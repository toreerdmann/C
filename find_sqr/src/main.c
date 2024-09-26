
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "util.c"
#include "solve.c"

int main(int argc, char **argv) {

    char header[20] = {0};
    char buf;
    int nrow = 0;
    char free;
    char rect;
    char obs;
    char **rows; 
    int fd;
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
    }
    else if (argc == 1) {
        fd = 0;
    }
    int i = 0;
    while(read(fd, &buf, 1)) {
        header[i] = buf;
        if (buf == '\n')
            break ;
        i++;
    }
    nrow = atoi(header);
    free = '.';
    rect = 'x';
    obs  = 'o';
    if (header[i] != '\n') {
        printf("map error\n");
        return 0;
    }
    //
    // alloc space and read matrix
    //
    rows = malloc(nrow * sizeof(char*));
    for (int i=0; i<nrow; i++) {
        rows[i] = malloc(nrow * sizeof(char));
        for (int j=0; j<nrow; j++)
            read(fd, &rows[i][j], 1);
        read(fd, &buf, 1);
    }
    //
    // get obstacles
    //
    int nobs = 0;
    for (int i=0; i<nrow; i++) 
        for (int j=0; j<nrow; j++)
            if (rows[i][j] == 'o')
                nobs++;
    t_point *obstacles = (t_point *)malloc(nobs * sizeof(t_point));
    if (!obstacles) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    int k = 0;
    for (int i=0; i<nrow; i++) {
        for (int j=0; j<nrow; j++) {
            if (rows[i][j] == 'o') {
                obstacles[k].x = i;
                obstacles[k].y = j;
                k++;
            }
        }
    }
    // find solution
    t_square result = solve(obstacles, nobs, nrow, nrow);
    // print to stdout
    show(rows, nrow, nrow, result);
    return 0;
}
