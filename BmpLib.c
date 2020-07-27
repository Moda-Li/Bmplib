/*********************************************
 * brief introduction：dealwith bmp file
 * authon：lihaoyu
 * creat by 2019/6
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BmpLib.h"
#include "RGB2Gray.h"

/*********************************************
 * 功能：打开bmp文件
 * 参数：
 *      path：文件路径+文件名
 * 返回值：
 *      NULL：打开失败
 *      Bmp_t *：文件句柄
**********************************************/
Bmp_t *BmpFileOpen(char *path)
{
    FILE *fp = fopen(path, "r");
    if(fp == NULL)
    {
        printf("open %s failed...\r\n", path);
        return NULL;
    }

    Bmp_t *bmp = (Bmp_t *)malloc(sizeof(Bmp_t));
    if(bmp == NULL)
    {
        printf("bmp malloc error...\r\n");
        fclose(fp);
        return NULL;
    }
    memset(bmp, 0x00, sizeof(Bmp_t));

    strcpy(bmp->pathname, path);

    int ret = 0;

    ret = fread(bmp, sizeof(BmpHeader_t), 1, fp);
    if(ret < 0)
    {
        printf("fread Bmp_t error...\r\n");
        free(bmp);
        fclose(fp);
        return NULL;
    }

    if(bmp->header.fileinfo.type[0] != 'B' || bmp->header.fileinfo.type[1] != 'M')
    {
        printf("%s is not bmp file, can not open...\r\n", path);
        free(bmp);
        fclose(fp);
        return NULL;
    }

    bmp->pixwszie = bmp->header.bitmap.width;
    bmp->pixhsize = bmp->header.bitmap.height;
    bmp->pixsize = bmp->header.bitmap.width * bmp->header.bitmap.height;
    bmp->imgsize = bmp->header.bitmap.sizeimage;

    bmp->imgsrc = (unsigned char *)malloc(bmp->imgsize);
    if(bmp->imgsrc == NULL)
    {
        printf("malloc bmp->imgsrc error...\r\n");
        free(bmp);
        fclose(fp);
        return NULL;
    }


    ret = fread(bmp->imgsrc, bmp->imgsize, 1, fp);
    if(ret < 0)
    {
        printf("fread imgsrc error...\r\n");
        free(bmp);
        free(bmp->imgsrc);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return bmp;
}

/*********************************************
 * 功能：释放bmp文件
 * 参数：
 *      bmp：bmp文件句柄
**********************************************/
int BmpFileClose(Bmp_t *bmp)
{
    if(bmp == NULL)
        return -1;
    
    if(bmp->imgsrc != NULL)
        free(bmp->imgsrc);

    free(bmp);
    return 0;
}

/*********************************************
 * 功能：创建bmp文件
 * 参数：
 *      imgsrc：RGB数据
 *      width：bmp宽
 *      height：bmp高
 *      bitdepth：位深度(8, 16, 24, 32)
 * 返回值：
 *      NULL：创建失败
 *      Bmp_t *：bmp句柄
**********************************************/
Bmp_t *BmpFileCreat(unsigned char *imgsrc, int width, int height, int bitdepth)
{
    Bmp_t *bmp = (Bmp_t *)malloc(sizeof(Bmp_t));
    if(bmp == NULL)
    {
        printf("bmp malloc error...\r\n");
        return NULL;
    }
    memset(bmp, 0x00, sizeof(Bmp_t));

/*************** Bmp_t start ***************/
    /* FileInof_t start */
    bmp->header.fileinfo.type[0] = 'B';
    bmp->header.fileinfo.type[1] = 'M';
    bmp->header.fileinfo.size = (width*height*bitdepth/8) + 54;
    bmp->header.fileinfo.reserved1 = 0;
    bmp->header.fileinfo.reserved2 = 0;
    bmp->header.fileinfo.offset = 54;
    /* FileInof_t end */

    /* BitMapInfo_t start */
    bmp->header.bitmap.size = 40;
    bmp->header.bitmap.width = width;
    bmp->header.bitmap.height = height;
    bmp->header.bitmap.planes = 1;
    bmp->header.bitmap.count = bitdepth;
    bmp->header.bitmap.compression = 0;
    bmp->header.bitmap.sizeimage = (width*height*bitdepth/8);
    bmp->header.bitmap.xmeter = width*3;
    bmp->header.bitmap.ymeter = height*3;
    bmp->header.bitmap.cused = 0;
    bmp->header.bitmap.cimportant = 0;
    /* BitMapInfo_t end */

    bmp->pixwszie = width;           //bmp图片宽(单位：像素)
    bmp->pixhsize = height;           //bmp图片高(单位：像素)
    bmp->pixsize = width*height;            //bmp图片分辨率(单位：像素)
    bmp->imgsize = (width*height*bitdepth/8); //bmp图片占内存大小(不包含文件头)(单位：字节)
    memset(bmp->pathname, 0, 64);
    bmp->imgsrc = (unsigned char *)malloc(width*height*bitdepth/8);
    if(bmp->imgsrc == NULL)
    {
        printf("bmp->imgsrc malloc error...\r\n");
        free(bmp);
        return NULL;
    }
    memcpy(bmp->imgsrc, imgsrc, width*height*bitdepth/8);
/*************** Bmp_t end ***************/
    return bmp;
}

/*********************************************
 * 功能：保存bmp文件
 * 参数：
 *      path：保存路径 + 文件名
 *      bmp：bmp句柄
 * 返回值：
 *       -1：保存失败
 *      > 0：保存成功
**********************************************/
int BmpFileSave(char *path, Bmp_t *bmp)
{
    FILE *fp = fopen(path, "w");
    if(fp == NULL)
    {
        printf("open %s failed...\r\n", path);
        return -1;
    }

    int ret = 0;

    ret = fwrite(&bmp->header, sizeof(BmpHeader_t), 1, fp);
    if(ret < 0)
    {
        printf("fwrite bmp->header error...\r\n");
        fclose(fp);
        return -1;
    }
    ret = fwrite(bmp->imgsrc, bmp->imgsize, 1, fp);
    if(ret < 0)
    {
        printf("fwrite bmp->imgsrc error...\r\n");
        fclose(fp);
        return -1;
    }
    fflush(fp);

    return fclose(fp);
}

/*********************************************
 * 功能：保存Bitmap数据
 * 参数：
 *      path：保存路径 + 文件名
 *      bmp：bmp句柄
 *      bmapformat：bitmap保存方式
 * 返回值：
 *       -1：保存失败
 *      > 0：保存成功
**********************************************/
int BmpFileSaveBitMap(char *path, Bmp_t *bmp, BmpBitMapFormat_t bmapformat)
{
    int ret = 0;

    FILE *fp = fopen(path, "w");
    if(fp == NULL)
    {
        printf("open %s failed...\r\n", path);
        return -1;
    }

    switch (bmapformat)
    {
    case BMP_BITMAP_FORMAT_RGB_FRONT:
    {
        unsigned char *tmpbuf = (unsigned char *)malloc(bmp->imgsize);
        if(tmpbuf == NULL)
        {
            printf("BmpFileSaveBitMap: malloc error, malloc size: %d\r\n", bmp->imgsize);
            fclose(fp);
            return -1;
        }
        for(int i = 0, j = bmp->imgsize - 1; i < bmp->imgsize; i++, j--)
            tmpbuf[i] = bmp->imgsrc[j];
        ret = fwrite(tmpbuf, bmp->imgsize, 1, fp);
        if(ret < 0)
        {
            printf("fwrite bmp->imgsrc error...\r\n");
            fclose(fp);
            free(tmpbuf);
            return -1;
        }
        free(tmpbuf);
        break;
    }
    case BMP_BITMAP_FORMAT_RGB_BACK:
    {
        unsigned char *tmpbuf = (unsigned char *)malloc(bmp->imgsize);
        if(tmpbuf == NULL)
        {
            printf("BmpFileSaveBitMap: malloc error, malloc size: %d\r\n", bmp->imgsize);
            fclose(fp);
            return -1;
        }

        for(int i = 0; i < bmp->imgsize; i += 3)
        {
            tmpbuf[i    ] = bmp->imgsrc[i + 2];
            tmpbuf[i + 1] = bmp->imgsrc[i + 1];
            tmpbuf[i + 2] = bmp->imgsrc[i    ];
        }

        ret = fwrite(tmpbuf, bmp->imgsize, 1, fp);
        if(ret < 0)
        {
            printf("fwrite bmp->imgsrc error...\r\n");
            fclose(fp);
            free(tmpbuf);
            return -1;
        }
        free(tmpbuf);
        break;
    }
    case BMP_BITMAP_FORMAT_BGR_FRONT:
    {
        unsigned char *tmpbuf = (unsigned char *)malloc(bmp->imgsize);
        if(tmpbuf == NULL)
        {
            printf("BmpFileSaveBitMap: malloc error, malloc size: %d\r\n", bmp->imgsize);
            fclose(fp);
            return -1;
        }

        for(int i = 0, j = bmp->imgsize - 1; i < bmp->imgsize; i += 3, j-= 3)
        {
            tmpbuf[i    ] = bmp->imgsrc[j - 2];
            tmpbuf[i + 1] = bmp->imgsrc[j - 1];
            tmpbuf[i + 2] = bmp->imgsrc[j    ];
        }

        ret = fwrite(tmpbuf, bmp->imgsize, 1, fp);
        if(ret < 0)
        {
            printf("fwrite bmp->imgsrc error...\r\n");
            fclose(fp);
            free(tmpbuf);
            return -1;
        }
        free(tmpbuf);
        break;
    }
    case BMP_BITMAP_FORMAT_BGR_BACK:
    {
        ret = fwrite(bmp->imgsrc, bmp->imgsize, 1, fp);
        if(ret < 0)
        {
            printf("fwrite bmp->imgsrc error...\r\n");
            fclose(fp);
            return -1;
        }
        break;
    }
        
    default:
        break;
    }

    
    fflush(fp);
    return fclose(fp);
}

/*********************************************
 * 功能：输出bmp文件信息
 * 参数：
 *      bmp：bmp句柄
**********************************************/
void BmpFileInfoShow(Bmp_t *bmp)
{
    printf("\r\n----- BmpFileInfoShow ----->\r\n");
    printf("    file path: %s\r\n", bmp->pathname);

    printf("(1) ---> FileInof_t\r\n");
    printf("    bmp->header.fileinfo.type: %c%c\r\n", bmp->header.fileinfo.type[0], bmp->header.fileinfo.type[1]);
    printf("    bmp->header.fileinfo.size: %d\r\n", bmp->header.fileinfo.size);
    printf("    bmp->header.fileinfo.reserved1: %d\r\n", bmp->header.fileinfo.reserved1);
    printf("    bmp->header.fileinfo.reserved2: %d\r\n", bmp->header.fileinfo.reserved2);
    printf("    bmp->header.fileinfo.offset: %d\r\n", bmp->header.fileinfo.offset);

    printf("(2) ---> BitMapInfo_t\r\n");
    printf("    bmp->header.bitmap.size: %d\r\n", bmp->header.bitmap.size);
    printf("    bmp->header.bitmap.width: %d\r\n", bmp->header.bitmap.width);
    printf("    bmp->header.bitmap.height: %d\r\n", bmp->header.bitmap.height);
    printf("    bmp->header.bitmap.planes: %d\r\n", bmp->header.bitmap.planes);
    printf("    bmp->header.bitmap.count: %d\r\n", bmp->header.bitmap.count);
    printf("    bmp->header.bitmap.compression: %d\r\n", bmp->header.bitmap.compression);
    printf("    bmp->header.bitmap.sizeimage: %d\r\n", bmp->header.bitmap.sizeimage);
    printf("    bmp->header.bitmap.xmeter: %d\r\n", bmp->header.bitmap.xmeter);
    printf("    bmp->header.bitmap.ymeter: %d\r\n", bmp->header.bitmap.ymeter);
    printf("    bmp->header.bitmap.cused: %d\r\n", bmp->header.bitmap.cused);
    printf("    bmp->header.bitmap.cimportant: %d\r\n", bmp->header.bitmap.cimportant);

    printf("(3) ---> Bmp_t\r\n");
    printf("    bmp->header { BmpHeader_t }\r\n");
    printf("    bmp->pixwszie: %d\r\n", bmp->pixwszie);
    printf("    bmp->pixhsize: %d\r\n", bmp->pixhsize);
    printf("    bmp->pixsize: %d\r\n", bmp->pixsize);
    printf("    bmp->imgsize: %d\r\n", bmp->imgsize);
    printf("----- BmpFileInfoShow end -----\r\n\r\n");
}


/*********************************************
 * 功能：RGB转灰度图
 * 参数：
 *      calmeth：转换方法
 *      rgb：bmp句柄
 * 返回值：
 *      NULL：转换失败
 *      Bmp_t *：灰度图bmp句柄
**********************************************/
Bmp_t *BmpRgbToGray(CalculationMethod_t calmeth, Bmp_t *rgb)
{
    if(rgb == NULL)
    {
        printf("rgb is null...\r\n");
        return NULL;
    }

    if(rgb->imgsrc == NULL)
    {
        printf("rgb->imgsrc is null...\r\n");
        return NULL;
    }

    Bmp_t *gray = (Bmp_t *)malloc(sizeof(Bmp_t));
    if(gray == NULL)
    {
        printf("gray malloc error...\r\n");
        return NULL;
    }
    memset(gray, 0x00, sizeof(Bmp_t));

    memcpy(gray, rgb, sizeof(Bmp_t));
    gray->imgsrc = NULL;

    gray->imgsrc = (unsigned char *)malloc(rgb->imgsize);
    if(gray->imgsrc == NULL)
    {
        printf("malloc gray->imgsrc error...\r\n");
        free(gray);
        return NULL;
    }

    switch (calmeth)
    {
    case CALCU_METHOD_TYPICAL:
        RGB2GrayTypical(gray->imgsrc, gray->pixsize, rgb->imgsrc, rgb->pixsize);
        break;
    case CALCU_METHOD_PHOTOSHOW:
        RGB2GrayInPhotoShop(gray->imgsrc, gray->pixsize, rgb->imgsrc, rgb->pixsize);
        break;
    case CALCU_METHOD_AVERAGE:
        RGB2GrayAverage(gray->imgsrc, gray->pixsize, rgb->imgsrc, rgb->pixsize);
        break;
    
    default:
        printf("CalculationMethod_t error...\r\n");
        free(gray);
        free(gray->imgsrc);
        return NULL;
    }    

    return gray;
}

/*********************************************
 * 功能：bmp灰度图二值化
 * 参数：
 *      threshold：转换阈值(0 ~ 255)
 *      rgb：bmp句柄
 * 返回值：
 *      NULL：转换失败
 *      Bmp_t *：二值图bmp句柄
**********************************************/
Bmp_t *BmpGrayToBinary(unsigned char threshold, Bmp_t *gray)
{
    if(gray == NULL)
    {
        printf("gray is null...\r\n");
        return NULL;
    }

    if(gray->imgsrc == NULL)
    {
        printf("gray->imgsrc is null...\r\n");
        return NULL;
    }

    Bmp_t *binary = (Bmp_t *)malloc(sizeof(Bmp_t));
    if(binary == NULL)
    {
        printf("binary malloc error...\r\n");
        return NULL;
    }
    memset(binary, 0x00, sizeof(Bmp_t));

    memcpy(binary, gray, sizeof(Bmp_t));
    binary->imgsrc = NULL;

    binary->imgsrc = (unsigned char *)malloc(gray->imgsize);
    if(binary->imgsrc == NULL)
    {
        printf("malloc binary->imgsrc error...\r\n");
        free(binary);
        return NULL;
    }

    for (int i = 0; i < gray->pixsize; i++)
    {		
        if(gray->imgsrc[3 * i] > threshold)	
            binary->imgsrc[3 * i + 0] = binary->imgsrc[3 * i + 1] = binary->imgsrc[3 * i + 2] = 255;
        else
            binary->imgsrc[3 * i + 0] = binary->imgsrc[3 * i + 1] = binary->imgsrc[3 * i + 2] = 0;
    }

    return binary;
}