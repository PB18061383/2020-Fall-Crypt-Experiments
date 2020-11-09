//��plt.txt����key1.txtͨ��Vigenere�㷨���ܴ洢��cip1.txt 
//Ϊ�˱���ʶ��,ÿ��txt�ı����ı�����֮�󶼻���һ��'#'��Ϊ������ 
#include<stdio.h>
#include"STRINGHEAP.h"
#include"VIGENERE.h"
main(){
	int err;
	FILE *fkey,*fplt,*fcip;
	String *skey,*splt,*scip;
	//��ʼ�� 
	fkey=fopen("key.txt","r");
	if(fkey==NULL){
		printf("key.txt��ȡʧ��\n");
		return(1);
	}
	fplt=fopen("plt.txt","r");
	if(fplt==NULL){
		printf("plt.txt��ȡʧ��\n");
		return(1);
	}
	fcip=fopen("cip.txt","w");
	if(fcip==NULL){
		printf("cip.txt��ȡʧ��\n");
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
	//��ȡ�ַ��� 
	FileScanString(skey,fkey);
	printf("Read key succeed\n\n");
	FileScanString(splt,fplt);
	printf("Read plaintext succeed\n\n");
	//����
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
