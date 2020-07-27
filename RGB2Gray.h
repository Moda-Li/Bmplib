#ifndef _RGB2GRAY_H_
#define _RGB2GRAY_H_

void RGB2GrayTypical(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix);
void RGB2GrayInPhotoShop(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix);
void RGB2GrayAverage(unsigned char *GrayImg, int GrayImgSizePix, unsigned char *SrcImage, int SrcImgSizePix);

#endif