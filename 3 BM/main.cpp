//根据BM算法对string.txt的0/1串，计算线性复杂度和相应的联结多项式 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"STRINGHEAP.h"
#include"BM.h"
main(){
	bool *c,*s,*b,*t,*res,d;
	int l,m,j,flag;
	String *st;
	FILE *fp;
	//1 
	l=0;
	m=0;
	j=0;
	InitString(st);
	fp=fopen("string.txt","r");
	if(fp==NULL){
		printf("文件初始化错误\n");
		return(1);
	}
	FileScanString(st,fp);
	c=(bool *)calloc(sizeof(bool),st->length);
	s=(bool *)calloc(sizeof(bool),st->length);
	b=(bool *)calloc(sizeof(bool),st->length);
	t=(bool *)calloc(sizeof(bool),st->length);
	res=(bool *)calloc(sizeof(bool),st->length);
	memset(c,0,sizeof(bool)*st->length);
	memset(s,0,sizeof(bool)*st->length);
	memset(b,0,sizeof(bool)*st->length);
	memset(t,0,sizeof(bool)*st->length);
	memset(res,0,sizeof(bool)*st->length);
	StringToBool(st,s);
	c[0]=1;
	b[0]=1;
	do{
		//2 
		d=Distance(c,s,j,l);
		//3 
		m++;
		//4 
		if(d!=0){
			for(flag=0;flag<st->length;flag++){
				//4.a.1 
				t[flag]=c[flag];
				//4.a.2 
				if(flag>=m){
					res[flag]=c[flag]^b[flag-m];
				}
				else{
					res[flag]=c[flag];
				}
			}
			//4.a.2 
			for(flag=0;flag<st->length;flag++){
				c[flag]=res[flag];
			}
			//4.b 
			if(l<=j/2){
				l=j+1-l;
				for(flag=0;flag<st->length;flag++){
					b[flag]=t[flag];
				}
				m=0;
			}
		}
		j++;
	}while(j<st->length);
	printf("0/1串长度为：%d\n",st->length);
	printf("线性复杂度为：%d\n",l);
	printf("对应联结多项式为：");
	PrintFomula(c,l);
	DestroyString(st);
	free(c);
	free(s);
	free(b);
	free(t);
	free(res);
} 
