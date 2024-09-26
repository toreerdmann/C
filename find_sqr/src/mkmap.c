
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    // create a file
    //int fd = open("testmap.txt", O_WRONLY | O_CREAT, 0777);
    // or write to stdout
    int fd = 1;
    if (argc != 4) {
        char msg[] = "\
    Usage:\n\n  \
    Arguments:\n   \
    nrows - number of rows\n   \
    ncols - number of cols\n   \
    p - inv prob of obstacle\n\n  \
    Example:\n\n    \
    ./mkmap 3 3 1\n";
        write(1, msg, sizeof(msg)-1);
        return 1;
    }
    int nrows = atoi(argv[1]);
    int ncols = atoi(argv[2]);
    int freq  = atoi(argv[3]);

    //
    // Write header
    //
    int i = 0;
    while (argv[1][i] >= '0' && argv[1][i] <= '9') {
        // write nrows (potentially multi-digit)
        write(fd, &argv[1][i], 1);
        i++;
    }
    write(fd, ".", 1);
    write(fd, "o", 1);
    write(fd, "x", 1);
    write(fd, "\n", 1);

    //
    //Write map
    //
    srand(time(NULL));
    for (int i=0; i<nrows; i++) {
        for (int j=0; j<ncols; j++) {
            int r = rand() % freq;
            if (r == 0)
                write(fd, "o", 1);
            else
                write(fd, ".", 1);
        }
        write(fd, "\n", 1);
    }
    close(fd);

    return 0;
}
