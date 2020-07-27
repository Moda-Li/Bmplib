#ifndef _RGB2GRAY_H_
#define _RGB2GRAY_H_

/**
 * 功能：RGB图像转灰度图
 * 参数：
 *      GrayImg：灰度图数据缓存区
 *      GrayImgSizePix：灰度图数据缓存区大小(单位：像素)
 *      SrcImage：RGB图源数据
 *      SrcImgSizePix：RGB图源数据大小(单位：像素)
 * 原理：使用通用算法计算
*/
extern void RGB2GrayTypical(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix);

/**
 * 功能：RGB图像转灰度图
 * 参数：
 *      GrayImg：灰度图数据缓存区
 *      GrayImgSizePix：灰度图数据缓存区大小(单位：像素)
 *      SrcImage：RGB图源数据
 *      SrcImgSizePix：RGB图源数据大小(单位：像素)
 * 原理：使用PhotoShop原理计算
*/
extern void RGB2GrayInPhotoShop(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix);

/**
 * 功能：RGB图像转灰度图
 * 参数：
 *      GrayImg：灰度图数据缓存区
 *      GrayImgSizePix：灰度图数据缓存区大小(单位：像素)
 *      SrcImage：RGB图源数据
 *      SrcImgSizePix：RGB图源数据大小(单位：像素)
 * 原理：使用均值计算
*/
extern void RGB2GrayAverage(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix);

#endif