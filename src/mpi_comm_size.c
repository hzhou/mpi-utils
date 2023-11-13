#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    int rc = 0;
    int PMI_size = 0;

    const char *p;
    if ((p = getenv("PMI_SIZE"))) {
        PMI_size = atoi(p);
    } else  if ((p = getenv("OMPI_COMM_WORLD_SIZE"))) {
        PMI_size = atoi(p);
    } else {
        /* assume singleton */
        PMI_size = 1;
    }

    printf("%d\n", PMI_size);

    return rc;
}
