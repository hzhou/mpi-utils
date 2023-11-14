#include <stdio.h>
#include <stdlib.h>

/* Hmm, can't get it to work. PMI is collective in nature */

int main(int argc, const char **argv)
{
    int rc = 0;
    int PMI_fd = -1;

    const char *p;
    if ((p = getenv("PMI_FD"))) {
        PMI_fd = atoi(p);
    } else {
        /* assume singleton */
        return -1;
    }

    return rc;
}
