#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"BMP.h"
#ifndef __VIGENERE_H
#define __VIGENERE_H
//这是用于Vigenere加密BMP图像的基本操作。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191017于中国科学技术大学） 
//函数内容 
void keygen(FILE *fp,int n){
	//生成长度为n字节的密钥 
	int flag;
	char ran;
	fwrite(&n,sizeof(int),1,fp);
	srand((unsigned int)time(0));
	for(flag=0;flag<n;flag++){
		ran=(char)rand();
		fwrite(&ran,sizeof(char),1,fp);
	}
}
void VigenereEncode(FILE *fin,FILE *fkey,FILE *fout){
	//用Vigenere算法加密，n调色板字节数，pics色块字节数，keyl密钥字节数，in读入数据，skey存放密钥，out写出数据 
	int n,pics,keyl,flag;
	char in,*skey,out;
	BmpHeader bh;
	BmpInfo bi;
	BmpColor *bc;
	bc=NULL;
	n=FileReadBmp(fin,bh,bi,bc);
	FileWriteBmp(fout,bh,bi,bc,n);
	PrintBmpInfo(bh,bi,bc,n);
	fseek(fin,n+14+40,SEEK_SET);
	fseek(fout,0,SEEK_END);
	pics=bi.picsize;
	fread(&keyl,sizeof(int),1,fkey);
	skey=(char *)calloc(sizeof(char),keyl);
	fread(skey,sizeof(char),keyl,fkey);
	printf("\n密钥长度：%d\n",keyl);
	flag=0;
	while(pics!=0){
		pics--;
		flag=flag%keyl;
		fread(&in,sizeof(char),1,fin);
		out=in+skey[flag];
		fwrite(&out,sizeof(char),1,fout);
		flag++;
	}
	free(skey);
	free(bc);
}
#endif 
