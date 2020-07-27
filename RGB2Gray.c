#include <stdio.h>
#include <math.h>

/**
 * 功能：RGB图像转灰度图
 * 参数：
 *      GrayImg：灰度图数据缓存区
 *      GrayImgSizePix：灰度图数据缓存区大小(单位：像素)
 *      SrcImage：RGB图源数据
 *      SrcImgSizePix：RGB图源数据大小(单位：像素)
 * 原理：使用通用算法计算
*/
void RGB2GrayTypical(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix)
{
    if(GrayImg == NULL || GrayImgSizePix < SrcImgSizePix || SrcImage == NULL || SrcImgSizePix <= 0)
        return;

    int GrayValue = 0;
    for (int i = 0; i < SrcImgSizePix; i++)
    {		
        unsigned char b = (unsigned char)SrcImage[3 * i + 0];		
        unsigned char g = (unsigned char)SrcImage[3 * i + 1];		
        unsigned char r = (unsigned char)SrcImage[3 * i + 2];		
        GrayValue = r * 0.299 + g * 0.587 + b * 0.114;	
        GrayImg[3 * i + 0] = GrayImg[3 * i + 1] = GrayImg[3 * i + 2] = GrayValue;
    }
}

/**
 * 功能：RGB图像转灰度图
 * 参数：
 *      GrayImg：灰度图数据缓存区
 *      GrayImgSizePix：灰度图数据缓存区大小(单位：像素)
 *      SrcImage：RGB图源数据
 *      SrcImgSizePix：RGB图源数据大小(单位：像素)
 * 原理：使用PhotoShop原理计算
*/
void RGB2GrayInPhotoShop(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix)
{	
    if(GrayImg == NULL || GrayImgSizePix < SrcImgSizePix || SrcImage == NULL || SrcImgSizePix <= 0)
        return;

    for (int i = 0; i < SrcImgSizePix; i++)	
    {		
        unsigned char b = SrcImage[3 * i + 0];		
        unsigned char g = SrcImage[3 * i + 1];		
        unsigned char r = SrcImage[3 * i + 2];		
        GrayImg[3 * i + 0] = GrayImg[3 * i + 1] = GrayImg[3 * i + 2] = pow((pow(r, 2.2) * 0.2973 + pow(g, 2.2) * 0.6274 + pow(b, 2.2) * 0.0753), 1/2.2);	
    }
}

/**
 * 功能：RGB图像转灰度图
 * 参数：
 *      GrayImg：灰度图数据缓存区
 *      GrayImgSizePix：灰度图数据缓存区大小(单位：像素)
 *      SrcImage：RGB图源数据
 *      SrcImgSizePix：RGB图源数据大小(单位：像素)
 * 原理：使用均值计算
*/
void RGB2GrayAverage(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix)
{	
    if(GrayImg == NULL || GrayImgSizePix < SrcImgSizePix || SrcImage == NULL || SrcImgSizePix <= 0)
        return;

    for (int i = 0; i < SrcImgSizePix; i++)	
    {		
        unsigned char b = SrcImage[3 * i + 0];		
        unsigned char g = SrcImage[3 * i + 1];		
        unsigned char r = SrcImage[3 * i + 2];		
        GrayImg[3 * i + 0] = GrayImg[3 * i + 1] = GrayImg[3 * i + 2] = (b + g + r) / 3;	
    }
}

