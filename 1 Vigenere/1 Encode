//把plt.txt按照key1.txt通过Vigenere算法加密存储到cip1.txt 
//为了便于识别,每个txt文本在文本结束之后都会有一个'#'作为结束符 
#include<stdio.h>
#include"STRINGHEAP.h"
#include"VIGENERE.h"
main(){
	int err;
	FILE *fkey,*fplt,*fcip;
	String *skey,*splt,*scip;
	//初始化 
	fkey=fopen("key.txt","r");
	if(fkey==NULL){
		printf("key.txt读取失败\n");
		return(1);
	}
	fplt=fopen("plt.txt","r");
	if(fplt==NULL){
		printf("plt.txt读取失败\n");
		return(1);
	}
	fcip=fopen("cip.txt","w");
	if(fcip==NULL){
		printf("cip.txt读取失败\n");
		return(1);
	}
	err=InitString(skey);
	if(err!=0){
		printf("String error\n");
		return(2);
	}
	err=InitString(splt);
	if(err!=0){
		printf("String error\n");
		return(2);
	}
	err=InitString(scip);
	if(err!=0){
		printf("String error\n");
		return(2);
	}
	//读取字符串 
	FileScanString(skey,fkey);
	printf("Read key succeed\n\n");
	FileScanString(splt,fplt);
	printf("Read plaintext succeed\n\n");
	//加密
	err=VigenereEncode(skey,splt,scip);
	if(err!=0){
		printf("Encode error\n");
		return(3);
	}
	printf("Encode result:\n\n");
	PrintString(scip);
	printf("\n\n");
	FilePrintString(scip,fcip);
	printf("The ciphertext has been saved at cip.txt. Please exit to check it\n\n");
	fclose(fkey);
	fclose(fplt);
	fclose(fcip);
	DestroyString(skey);
	DestroyString(splt);
	DestroyString(scip);
}
