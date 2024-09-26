
t_square solve(t_point *obs, int nobs, int nx, int ny) {
    int i;
    int j;
    int sz = 0;
    int iopt;
    int jopt;
    t_point topL = {.x = 0, .y = 0};
    t_point botR = {.x = 0, .y = 0};
    t_square sq = {.topL = topL, .botR = botR};
    i = 0;
    while (i < nx-sz+1) {
        j = 0;
        while (j < ny-sz+1) {
            sq.topL.x = i;
            sq.topL.y = j;
            sq.botR.x = i+sz+1;
            sq.botR.y = j+sz+1;
            while (i+sz+1 < nx && j+sz+1 < ny && is_empty(obs, nobs, &sq)) {
                // remember solution
                iopt = i;
                jopt = j;
                // increase size
                sz++;
                // adjust square
                sq.topL.x = i;
                sq.topL.y = j;
                sq.botR.x = i+sz+1;
                sq.botR.y = j+sz+1;
            }
            j++;
        }
        i++;
    }
    sq.topL.x = iopt;
    sq.topL.y = jopt;
    sq.botR.x = iopt+sz;
    sq.botR.y = jopt+sz;
    return sq;
}
