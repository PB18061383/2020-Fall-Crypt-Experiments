#ifndef __STRINGHEAP_H
#define __STRINGHEAP_H
//这是用于堆式串的基本操作，使用时请手动改STRINGSIZE、STRINGADDON定义，并按需修改TraverseString函数。
//由于赶工繁忙，可能有些许bug，对此本人深感抱歉。如有建设性建议，可通过QQ：1345578933联系（麻治昊，20191017于中国科学技术大学） 
#include<stdio.h>
#include<stdlib.h>
//串最小长度，缺省500 
#define STRINGSIZE 10
//串每次申请新元素增量，缺省100 
#define STRINGADDON 5 
//堆式串数据类型 
struct String{
	char *str;
	int length;
	int size;
};
//函数内容 
int InitString(String *&s){
	//初始化串s，s的默认长度是STRINGSIZE,可以增删。成功返回0，s空返回1，str空返回2 
	int flag;
	s=(String *)malloc(sizeof(String));
	if(s==NULL){
		return(1);
	}
	s->str=(char *)calloc(STRINGSIZE,sizeof(char));
	if(s->str==NULL){
		return(2);
	}
	s->length=0;
	s->size=STRINGSIZE;
	return(0);
}
void DestroyString(String *&s){
	//销毁串s 
	free(s->str); 
	free(s);
	s=NULL;
	return;
}
int ClearString(String *&s){
	//将串s置空，成功返回0，str空返回1 
	s->length=0;
	if(s->size>STRINGSIZE){
		s->str=(char *)realloc(s->str,STRINGSIZE*sizeof(char));
		if(s->str==NULL){
		    return(1);
	    }
		s->size=STRINGSIZE;
	}
	return(0); 
}
int StringEmpty(String *&s){
	//判断串s是否为空，是返回1，不是返回0 
	if(s->length==0){
		return(1);
	}
	else{
		return(0);
	}
}
int StringFull(String *&s){
	//判断串s是否为满，是返回1，不是返回0 
	if(s->length==s->size){
		return(1);
	}
	else{
		return(0);
	}
}
int StringLength(String *&s){
	//返回串s长度 
	return(s->length);
}
int StringInsert(String *&s,String *&t,int i){
	//在s的i位置前插入t，若i为0，则在后方插入。成功返回0，i不合法返回1，内存不足返回2 
	int flag,add;
	if(i<0||i>s->length){
		return(1);
	} 
	if(s->length+t->length>=s->size){
		add=(s->length+t->length-s->size)/STRINGADDON+1;
		s->str=(char *)realloc(s->str,(s->size+add*STRINGADDON)*sizeof(char));
		if(s->str==NULL){
			return(2);
		}
		s->size=s->size+add*STRINGADDON;
	}
	if(i==0){
		for(flag=0;flag<t->length;flag++){
			s->str[s->length+flag]=t->str[flag];
		}
		s->length=s->length+t->length;
		return(0);
	}
	for(flag=s->length-1;flag>=i-1;flag--){
		s->str[flag+t->length]=s->str[flag];
	}
	for(flag=0;flag<t->length;flag++){
		s->str[flag+i-1]=t->str[flag];
	}
	s->length=s->length+t->length;
	return(0);
}
int StringDelete(String *&s,String *&t,int i,int l){
	//删除s的i位置后长为l的串并赋值给t。成功返回0，i不合法返回1，内存不足返回2 
	int flag,add;
	if(i<1||i>s->length){
		return(1);
	}
	if(l>=t->size){
		add=(l-t->size)/STRINGADDON+1;
		t->str=(char *)realloc(t->str,(t->size+add*STRINGADDON)*sizeof(char));
		if(t->str==NULL){
			return(2);
		}
		t->size=t->size+add*STRINGADDON;
	}
	for(flag=0;flag<i+l-1;flag++){
		t->str[flag]=s->str[flag+i-1];
	}
	t->length=l;
	for(flag=i-1;flag<s->length;flag++){
		s->str[flag]=s->str[flag+l];
	}
	s->length=s->length-l;
	if(s->size-s->length>STRINGADDON&&s->size>STRINGSIZE){
		add=(s->size-s->length)/STRINGADDON-1;
		s->str=(char *)realloc(s->str,(s->size-add*STRINGADDON)*sizeof(char));
		if(s->str==NULL){
			return(2);
		}
		s->size=s->size-add*STRINGADDON;
	}
	return(0);
}
int StringCompare(String *&s,String *&t){
	//比较字符顺序，返回最后一位的差值 
	int flag,i;
	for(flag=0;flag<s->length&&flag<t->length;flag++){
		i=s->str[flag]-t->str[flag];
		if(i!=0){
			return(i);
		}
	}
	if(s->length>t->length){
		return(s->str[t->length]);
	}
	else if(s->length<t->length){
		return(-t->str[s->length]);
	}
	return(0);
}
int StringCopy(String *&s,String *&t){
	//把串t复制给串s，成功返回0，失败返回1 
	int flag,add;
	ClearString(s);
	if(t->length>=s->size){
		add=(t->length-s->size)/STRINGADDON+1;
		s->str=(char *)realloc(s->str,(s->size+add*STRINGADDON)*sizeof(char));
		if(s->str==NULL){
			return(1);
		}
		s->size=s->size+add*STRINGADDON;
	}
	for(flag=0;flag<t->length;flag++){
		s->str[flag]=t->str[flag];
	} 
	s->length=t->length;
	return(0);
}
int Concat(String *&s,String *&t1,String *&t2){
	//将串t1与t2串接，存到另一个串s中，成功返回0，失败返回1 
	int flag,add;
	ClearString(s);
	if(t1->length+t2->length>=s->size){
		add=(t1->length+t2->length-s->size)/STRINGADDON+1;
		s->str=(char *)realloc(s->str,(s->size+add*STRINGADDON)*sizeof(char));
		if(s->str==NULL){
			return(1);
		}
		s->size=s->size+add*STRINGADDON;
	}
	for(flag=0;flag<t1->length;flag++){
		s->str[flag]=t1->str[flag];
	}
	for(flag=t1->length;flag<t1->length+t2->length;flag++){
		s->str[flag]=t2->str[flag-t1->length];
	}
	s->length=t1->length+t2->length;
	return(1);
}
int SubString(String *&s,String *&t,int i,int l){
	//求串s的i位置连续l的子串存到t中，成功返回0，i不合法返回1，l不合法返回2，内存不足返回3 
	int flag,add;
	if(i<1||i>s->length){
		return(1);
	} 
	if(l<1||i+l-1>s->length){
		return(2);
	}
	ClearString(t);
	if(l>=t->size){
		add=(l-t->size)/STRINGADDON+1;
		t->str=(char *)realloc(t->str,(t->size+add*STRINGADDON)*sizeof(char));
		if(t->str==NULL){
			return(1);
		}
		t->size=t->size+add*STRINGADDON;
	}
	for(flag=i-1;flag<i+l-1;flag++){
		t->str[flag-i+1]=s->str[flag];
	}
	t->length=l;
	return(0);
}
int Index(String *&s,String *&t,int i){
	//返回s中i位置后第一个含t的子串位置,没有就返回0，i不合法返回-1 
	int flag1,flag2,flag3;
	if(i<1||i>s->length-t->length+1){
		return(-1);
	} 
	for(flag1=i-1;flag1<s->length;flag1++){
		flag3=flag1;
		for(flag2=0;flag2<t->length;flag2++,flag3++){
			if(s->str[flag3]!=t->str[flag2]){
				break;
			}
		}
		if(flag2==t->length){
			return(flag1+1);
		}
	}
	return(0);
}
int Replace(String *&s,String *&t,String *&v){
	//用串v替换s中所有不重叠的含t的非重叠子串，成功返回0，失败返回1  
	int flag,err;
	String *j;
	flag=1;
	err=InitString(j);
	if(err!=0){
		return(1);
	} 
	flag=Index(s,t,flag);
	do{
		StringDelete(s,j,flag,t->length);
		if(flag+t->length==s->length+1){
			StringInsert(s,v,0);
		}
		else{
			StringInsert(s,v,flag);
		}
		flag=flag+v->length;
		flag=Index(s,t,flag);
	}while(flag<=s->length&&flag>0);
	DestroyString(j);
	return(0);
}
int ScanString(String *&s){
	//输入s的串内容，#结束，成功返回0，失败返回1 
	char c;
	int flag,add;
	ClearString(s);
	flag=0;
	c=getchar();
	while(c!='#'){
		s->str[flag]=c;
		s->length=flag+1;
		flag++;
		c=getchar();
		if(s->length>=s->size){
			add=(s->length-s->size)/STRINGADDON+1;
			s->str=(char *)realloc(s->str,(s->size+add*STRINGADDON)*sizeof(char));
			if(s->str==NULL){
				return(1);
			}
			s->size=s->size+add*STRINGADDON;
		}
	}
	fflush(stdin);
	return(0);
}
void PrintString(String *&s){
	//输出s的串内容 
	int flag;
	for(flag=0;flag<s->length;flag++){
		printf("%c",s->str[flag]);
	}
	printf("#");
	return;
}
int FileScanString(String *&s,FILE *fp){
	//输入s的串内容，#结束，成功返回0，失败返回1 
	char c;
	int flag,add;
	ClearString(s);
	flag=0;
	c=fgetc(fp);
	while(c!='#'){
		s->str[flag]=c;
		s->length=flag+1;
		flag++;
		c=fgetc(fp);
		if(s->length>=s->size){
			add=(s->length-s->size)/STRINGADDON+1;
			s->str=(char *)realloc(s->str,(s->size+add*STRINGADDON)*sizeof(char));
			if(s->str==NULL){
				return(1);
			}
			s->size=s->size+add*STRINGADDON;
		}
	}
	return(0);
}
void FilePrintString(String *&s,FILE *fp){
	//输出s的串内容至文件，#结束 
	int flag;
	for(flag=0;flag<s->length;flag++){
		fprintf(fp,"%c",s->str[flag]);
	}
	fprintf(fp,"#");
	return;
}
void TraverseString(String *&s){
	//遍历s的所有内容执行自定义操作 
	int flag;
	for(flag=0;flag<s->length;flag++){
		//自定义操作，缺省打印 
		printf("%d\n",s->str[flag]);
	}
	return;
}
#endif 
