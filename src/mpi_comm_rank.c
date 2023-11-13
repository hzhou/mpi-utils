#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    int rc = 0;
    int PMI_rank = -1;

    const char *p;
    if ((p = getenv("PMI_RANK"))) {
        PMI_rank = atoi(p);
    } else if ((p = getenv("OMPI_COMM_WORLD_RANK"))) {
        PMI_rank = atoi(p);
    } else {
        /* assume singleton */
        PMI_rank = 0;
    }

    printf("%d\n", PMI_rank);

    return rc;
}
