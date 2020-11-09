#include<stdio.h>
#include<stdlib.h>
#ifndef __BMP_H
#define __BMP_H
//这是用于读取BMP图像的基本操作。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20201029于中国科学技术大学） 
//BMP文件头 
struct BmpHeader{
	unsigned short type;
	//文件类型，通常BM
	unsigned long size;
	//整个文件大小
	unsigned long reserved;
	//保留位，为0
	unsigned long offbits;
	//图片色块区前的位数，单色位40，16色位118，256色位1078，16位、24位、32位色位54 
};
//BMP信息 
struct BmpInfo{
	unsigned long infosize;
	//该结构体大小，一般为40 
	unsigned long width;	
	//图片横向像素个数 
	unsigned long height;
	//图片竖向像素个数 
	unsigned short plane;
	//图像面数，为1 
	unsigned short pictype;
	//图片类型，单色位1，16色位4，256色位8，16位色位16，24位色位24、32位色位32 
	unsigned long compress;
	//压缩方式，0无压缩，1RLE8，2RLE4，3根据掩码决定
	unsigned long picsize;
	//色块区域字节数，必须是4的倍数 
	unsigned long xppx;
	//横向分辨率，像素/米 
	unsigned long yppx;
	//纵向分辨率，像素/米 
	unsigned long clrused;
	//被用的颜色数目，0表示全部 
	unsigned long clrimp;
	//重要颜色数目，0表示同等重要 
};
//BMP调色板数组单元 
typedef int BmpColor;
//函数内容 
int FileReadBmp(FILE *fp,BmpHeader &bh,BmpInfo &bi,BmpColor *&bc){
	//读取bmp，返回调色板字节数 
	fread(&bh.type,sizeof(short),1,fp);
	fread(&bh.size,sizeof(long),1,fp);
	fread(&bh.reserved,sizeof(long),1,fp);
	fread(&bh.offbits,sizeof(long),1,fp);
	fread(&bi.infosize,sizeof(long),1,fp);
	fread(&bi.width,sizeof(long),1,fp);
	fread(&bi.height,sizeof(long),1,fp);
	fread(&bi.plane,sizeof(short),1,fp);
	fread(&bi.pictype,sizeof(short),1,fp);
	fread(&bi.compress,sizeof(long),1,fp);
	fread(&bi.picsize,sizeof(long),1,fp);
	fread(&bi.xppx,sizeof(long),1,fp);
	fread(&bi.yppx,sizeof(long),1,fp);
	fread(&bi.clrused,sizeof(long),1,fp);
	fread(&bi.clrimp,sizeof(long),1,fp);
	if(bi.pictype==16||bi.pictype==24||bi.pictype==32){
		bc=NULL;
		return(0);
	}
	else if(bi.pictype==1){
		bc=(BmpColor *)calloc(sizeof(BmpColor),2);
		fread(bc,sizeof(BmpColor),2,fp);
		return(8);
	}
	else if(bi.pictype==4){
		bc=(BmpColor *)calloc(sizeof(BmpColor),16);
		fread(bc,sizeof(BmpColor),16,fp);
		return(64);
	}
	else if(bi.pictype==8){
		bc=(BmpColor *)calloc(sizeof(BmpColor),256);
		fread(bc,sizeof(BmpColor),256,fp);
		return(1024);
	}
}
void FileWriteBmp(FILE *fp,BmpHeader bh,BmpInfo bi,BmpColor *bc,int n){
	//写入新的bmp文件 
	fwrite(&bh.type,sizeof(short),1,fp);
	fwrite(&bh.size,sizeof(long),1,fp);
	fwrite(&bh.reserved,sizeof(long),1,fp);
	fwrite(&bh.offbits,sizeof(long),1,fp);
	fwrite(&bi.infosize,sizeof(long),1,fp);
	fwrite(&bi.width,sizeof(long),1,fp);
	fwrite(&bi.height,sizeof(long),1,fp);
	fwrite(&bi.plane,sizeof(short),1,fp);
	fwrite(&bi.pictype,sizeof(short),1,fp);
	fwrite(&bi.compress,sizeof(long),1,fp);
	fwrite(&bi.picsize,sizeof(long),1,fp);
	fwrite(&bi.xppx,sizeof(long),1,fp);
	fwrite(&bi.yppx,sizeof(long),1,fp);
	fwrite(&bi.clrused,sizeof(long),1,fp);
	fwrite(&bi.clrimp,sizeof(long),1,fp);
	fwrite(bc,sizeof(BmpColor),n/4,fp);
}
void PrintBmpInfo(BmpHeader bh,BmpInfo bi,BmpColor *bc,int n){
	//打印bmp信息 
	printf("信息如下：\n");
	printf("文件大小：%d Bytes\n",bh.size);
	printf("水平长度：%d pix\n",bi.width);
	printf("垂直长度：%d pix\n",bi.height);
	printf("图片颜色类型：2^%d\n",bi.pictype);
	printf("压缩类型：%d （0无压缩，1RLE8，2RLE4，3根据掩码决定）\n",bi.compress);
	printf("图片色块区大小：%d 个四字节\n",bi.picsize/4);
	printf("水平分辨率：%d ppm （0是未定义）\n",bi.xppx);
	printf("垂直分辨率：%d ppm （0是未定义）\n",bi.yppx);
	printf("使用颜色数：%d （0是全部）\n",bi.clrused);
	printf("重要颜色数：%d （0是全部）\n",bi.clrimp);
	printf("特殊调色板颜色数：%d\n",n/4);
}
#endif
