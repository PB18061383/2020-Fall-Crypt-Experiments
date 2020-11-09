#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"BMP.h"
#ifndef __AES_H
#define __AES_H
//这是用于AES加密BMP图像的基本操作。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191031于中国科学技术大学） 
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
//表代换 
unsigned char Sbox0(unsigned char in,unsigned char *sb0){
	return(sb0[in]);
}
unsigned int Tlist00(unsigned char in,unsigned char *tl00){
	unsigned int *res;
	res=(unsigned int *)tl00;
	return(res[in]);
}
unsigned int Tlist01(unsigned char in,unsigned char *tl01){
	unsigned int *res;
	res=(unsigned int *)tl01;
	return(res[in]);
}
unsigned int Tlist02(unsigned char in,unsigned char *tl02){
	unsigned int *res;
	res=(unsigned int *)tl02;
	return(res[in]);
}
unsigned int Tlist03(unsigned char in,unsigned char *tl03){
	unsigned int *res;
	res=(unsigned int *)tl03;
	return(res[in]);
}
//密钥扩展函数 
int GFunc(int in,int n,unsigned char *sb0){
	unsigned int R[11]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36},flag,out;
	char *s;
	out=in<<8|in>>24;
	s=(char *)&out;
	for(flag=0;flag<4;flag++){
		s[flag]=Sbox0(s[flag],sb0);
	}
	out=out^R[n];
	return(out);
}
void KeyExpand(unsigned char *key,unsigned char *sb0){
	int flag,*res;
	res=(int *)key;
	for(flag=4;flag<44;flag++){
		if(flag%4==0){
			res[flag]=res[flag-4]^GFunc(res[flag-1],flag/4,sb0);
		}
		else{
			res[flag]=res[flag-4]^res[flag-1];
		}
	}
}
unsigned int Key(unsigned char *key,unsigned int j){
	unsigned int res;
	res=(key[j]<<24)+(key[4+j]<<16)+(key[8+j]<<8)+(key[12+j]);
	return(res);
}
void AESE(unsigned char *&in,unsigned char *key,unsigned int *&out,unsigned char *sb0,unsigned char *tl00,unsigned char *tl01,unsigned char *tl02,unsigned char *tl03){
	unsigned int flag1,flag2,*res;
	KeyExpand(key,sb0);
	for(flag1=0;flag1<9;flag1++){
		for(flag2=0;flag2<4;flag2++){
			out[flag2]=Tlist00(in[flag2%4],tl00)^Tlist01(in[4+(flag2+1)%4],tl01)^Tlist02(in[8+(flag2+2)%4],tl02)^Tlist03(in[12+(flag2+3)%4],tl03)^Key(&(key[flag1*4]),flag2);
		}
		res=out;
		out=(unsigned int *)in;
		in=(unsigned char *)res;
	}
	for(flag2=0;flag2<4;flag2++){
		out[flag2]=Sbox0(in[flag2%4],sb0)^Sbox0(in[4+(flag2+1)%4],sb0)^Sbox0(in[8+(flag2+2)%4],sb0)^Sbox0(in[12+(flag2+3)%4],sb0)^Key(&(key[40]),flag2);
	}
}
int AESEncode(FILE *fin,FILE *fkey,FILE *fout){
	//用AES算法加密，n调色板字节数，pics色块字节数，keyl密钥字节数，in读入数据，skey存放密钥，out写出数据 
	unsigned int n,pics,keyl,*out,flag;
	unsigned char sb0[256],tl00[1024],tl01[1024],tl02[1024],tl03[1024],*in,key[4*44];
	FILE *fsb0,*ftl00,*ftl01,*ftl02,*ftl03;
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
	fread(key,sizeof(unsigned char),keyl,fkey);
	printf("\n密钥长度：%d\n",keyl);
	flag=0;
	fsb0=fopen("sbox0.dat","rb");
	if(fsb0==NULL){
		printf("sbox0读取失败\n");
		return(1);
	}
	ftl00=fopen("tlist00.dat","rb");
	if(ftl00==NULL){
		printf("tlist00读取失败\n");
		return(1);
	}
	ftl01=fopen("tlist01.dat","rb");
	if(ftl01==NULL){
		printf("tlist01读取失败\n");
		return(1);
	}
	ftl02=fopen("tlist02.dat","rb");
	if(ftl02==NULL){
		printf("tlist02读取失败\n");
		return(1);
	}
	ftl03=fopen("tlist03.dat","rb");
	if(ftl03==NULL){
		printf("tlist03读取失败\n");
		return(1);
	}
	fread(sb0,sizeof(unsigned char),256,fsb0);
	fread(tl00,sizeof(unsigned char),256*4,ftl00);
	fread(tl01,sizeof(unsigned char),256*4,ftl01);
	fread(tl02,sizeof(unsigned char),256*4,ftl02);
	fread(tl03,sizeof(unsigned char),256*4,ftl03);
	in=(unsigned char *)malloc(sizeof(char)*16);
	out=(unsigned int *)malloc(sizeof(int)*4);
	while(pics>=16){
		pics=pics-16;
		fread(in,sizeof(unsigned char),16,fin);
		AESE(in,key,out,sb0,tl00,tl01,tl02,tl03);
		fwrite(out,sizeof(unsigned char),16,fout);
	}
	if(pics>0){
		memset(in,0,sizeof(char)*16);
		fread(in,sizeof(unsigned char),pics,fin);
		AESE(in,key,out,sb0,tl00,tl01,tl02,tl03);
		fwrite(out,sizeof(unsigned char),16,fout);
	}
	return(0);
}
#endif
