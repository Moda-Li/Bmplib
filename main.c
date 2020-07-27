#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "BmpLib.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("please input the bmp file path...\r\n");
        return -1;
    }
    
    /* open a bmp file */
    printf("open bmp file %s\r\n", argv[1]);
    Bmp_t *bmp = BmpFileOpen(argv[1]);
    if(bmp == NULL)
    {
        printf("open bmp file %s failed\r\n", argv[1]);
        return -1;
    }
    printf("open %s success...\r\n\r\n", argv[1]);

    /* show bmp file info */
    BmpFileInfoShow(bmp);

    BmpFileClose(bmp);

    return 0;
}