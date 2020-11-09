#ifndef __BM_H
#define __BM_H
//这是用于BM算法的基本操作。 
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20201109于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h>
#include"STRINGHEAP.h"
//函数内容 
int StringToBool(String *s,bool *b){
	//将字符串转化成布尔序列，成功返回0，失败返回1 
	int flag;
	for(flag=0;flag<s->length;flag++){
		if(s->str[flag]=='0'){	
			b[flag]=0;
		}
		else if(s->str[flag]=='1'){
			b[flag]=1;
		}
		else{
			return(1);
		}
	}
	return(0);
}
bool Distance(bool *c,bool *s,int j,int l){
	//计算第j轮迭代的下一步离差 
	int flag;
	bool d; 
	d=s[j];
	for(flag=1;flag<=l;flag++){
		d=d^(c[flag]&s[j-flag]);
	}
	return(d);
} 
int PrintFomula(bool *c,int l){
	int flag;
	printf("1");
	if(l>1){
		printf("+");
	}
	for(flag=1;flag<l;flag++){
		if(c[flag]==1){
			printf("D^%d+",flag);
		}
	}
	if(l>1){
		printf("D^%d\n",l);
	}
	return(0);
}
#endif 
