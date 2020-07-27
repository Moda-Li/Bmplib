#ifndef _BMPLIB_H_
#define _BMPLIB_H_

#include <stdio.h>

/**
 * bmp文件信息
*/
#pragma pack(1)
typedef struct
{
    char            type[2];      //文件类型
    unsigned int    size;         //文件大小
    unsigned short  reserved1;    //保留, 必须为零
    unsigned short  reserved2;    //保留, 必须为零
    unsigned int    offset;       //从头到位图数据的偏移
}FileInof_t;
#pragma pack()

/**
 * 位图信息
*/
#pragma pack(1)
typedef struct
{
    unsigned int size;         //本结构体所占用字节数,即40个字节	
    int width;                  //位图的宽度，以像素为单位，像素数量是4字节对齐的	
    int height;                 // 位图的高度，以像素为单位	
    unsigned short planes;      // 目标设备的级别，必须为1	
    unsigned short count;       // 每个像素所需的位数，必须是1(双色, 4(16色), 8(256色)或24(真彩色) 之一	
    unsigned int compression;   // 位图压缩类型，必须是 0(不压缩), 1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型) 之一	
    unsigned int sizeimage;     // 位图的大小，以字节为单位	
    unsigned int xmeter;        // 位图水平分辨率，每米像素数	
    unsigned int ymeter;        // 位图垂直分辨率，每米像素数	
    unsigned int cused;         // 位图实际使用的颜色表中的颜色数	
    unsigned int cimportant;    // 位图显示过程中重要的颜色数
}BitMapInfo_t;
#pragma pack()

/**
 * bmp文件头
*/
typedef struct
{
    FileInof_t      fileinfo;
    BitMapInfo_t    bitmap;
}BmpHeader_t;

/**
 * bmp文件
*/
typedef struct 
{
    BmpHeader_t header;
    int pixwszie;           //bmp图片宽(单位：像素)
    int pixhsize;           //bmp图片高(单位：像素)
    int pixsize;            //bmp图片分辨率(单位：像素)
    int imgsize;            //bmp图片占内存大小(不包含文件头)(单位：字节)
    char pathname[64];      //文件名
    unsigned char *imgsrc;
}Bmp_t;

/**
 * 操作模式
*/
typedef enum
{
    BMPMDLI_TO_GRAY = 0,
    BMPMDLI_TO_BINARY = 1,
}BmpMdliMode_t;

/**
 * 灰度计算方式
*/
typedef enum
{
    CALCU_METHOD_TYPICAL = 0,
    CALCU_METHOD_PHOTOSHOW = 1,
    CALCU_METHOD_AVERAGE = 2,
}CalculationMethod_t;

/**
 * BMP位图数据输出格式
*/
typedef enum
{
    BMP_BITMAP_FORMAT_RGB_FRONT = 0,    /* RGB数据, 顺序排列 */
    BMP_BITMAP_FORMAT_RGB_BACK = 1,     /* RGB数据, 反序排列 */
    BMP_BITMAP_FORMAT_BGR_FRONT = 2,    /* BGR数据, 顺序排列 */
    BMP_BITMAP_FORMAT_BGR_BACK = 3,     /* BGR数据, 反序排列 */
}BmpBitMapFormat_t;

/*********************************************
 * 功能：打开bmp文件
 * 参数：
 *      path：文件路径+文件名
 * 返回值：
 *      NULL：打开失败
 *      Bmp_t *：文件句柄
**********************************************/
extern Bmp_t *BmpFileOpen(char *path);    //打开bmp文件

/*********************************************
 * 功能：释放bmp文件
 * 参数：
 *      bmp：bmp文件句柄
**********************************************/
extern int BmpFileClose(Bmp_t *bmp);      //关闭bmp文件

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
extern Bmp_t *BmpFileCreat(unsigned char *imgsrc, int width, int height, int bitdepth);

/*********************************************
 * 功能：保存bmp文件
 * 参数：
 *      path：保存路径 + 文件名
 *      bmp：bmp句柄
 * 返回值：
 *       -1：保存失败
 *      > 0：保存成功
**********************************************/
extern int BmpFileSave(char *path, Bmp_t *bmp);

/*********************************************
 * 功能：保存Bitmap数据
 * 参数：
 *      path：保存路径 + 文件名
 *      bmp：bmp句柄
 * 返回值：
 *       -1：保存失败
 *      > 0：保存成功
**********************************************/
int BmpFileSaveBitMap(char *path, Bmp_t *bmp, BmpBitMapFormat_t bmapformat);

/*********************************************
 * 功能：输出bmp文件信息
 * 参数：
 *      bmp：bmp句柄
**********************************************/
extern void BmpFileInfoShow(Bmp_t *bmp);

/*********************************************
 * 功能：RGB转灰度图
 * 参数：
 *      calmeth：转换方法
 *      rgb：bmp句柄
 * 返回值：
 *      NULL：转换失败
 *      Bmp_t *：灰度图bmp句柄
**********************************************/
extern Bmp_t *BmpRgbToGray(CalculationMethod_t calmeth, Bmp_t *rgb);   //bmp转gray

/*********************************************
 * 功能：bmp灰度图二值化
 * 参数：
 *      threshold：转换阈值(0 ~ 255)
 *      rgb：bmp句柄
 * 返回值：
 *      NULL：转换失败
 *      Bmp_t *：二值图bmp句柄
**********************************************/
extern Bmp_t *BmpGrayToBinary(unsigned char  threshold, Bmp_t *gray);


#endif