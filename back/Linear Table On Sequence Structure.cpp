/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���


#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct
{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;

status IntiaList(SqList & L);
status DestroyList(SqList & L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType & e);
status LocateElem(SqList L,ElemType e); //�򻯹�
status PriorElem(SqList L,ElemType cur,ElemType & pre_e);
status NextElem(SqList L,ElemType cur,ElemType & next_e);
status ListInsert(SqList & L,int i,ElemType e);
status ListDelete(SqList & L,int i,ElemType & e);
status ListTrabverse(SqList L);  //�򻯹�
status LoadFromFile(char * filename,SqList & L);
status SaveToFile(char * filename,SqList  L); 
/*--------------------------------------------*/
int main()
{
  SqList L;  int op=1;
  ElemType  e,ans;
  int i;
  char fileName[20];
  while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList       7. LocateElem\n");
	printf("    	  2. DestroyList     8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty     10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem       12. ListTrabverse\n");
	printf("    	  0. Exit\n");
	printf("          13.Save           14.Load\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~14]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 //printf("\n----IntiaList���ܴ�ʵ�֣�\n");
		 if(IntiaList(L)==OK) printf("���Ա����ɹ���\n");
		     else printf("���Ա���ʧ�ܣ�\n");
		 getchar();getchar();
		 break;
	   case 2:
		 //printf("\n----DestroyList���ܴ�ʵ�֣�\n");
		 if(DestroyList(L)==OK) printf("���Ա�ɾ���ɹ���\n");
		     else printf("���Ա�ɾ��ʧ�ܣ�\n");     
		 getchar();getchar();
		 break;
	   case 3:
		 //printf("\n----ClearList���ܴ�ʵ�֣�\n"); 
		 if(ClearList(L)==OK) printf("���Ա���ճɹ���\n");
		     else printf("���Ա����ʧ�ܣ�\n");    
		 getchar();getchar();
		 break;
	   case 4:
		 //printf("\n----ListEmpty���ܴ�ʵ�֣�\n"); 
		 if(ListEmpty(L)==TRUE) printf("�����Ա�Ϊ�գ�\n");
		     else printf("�����Ա�ǿգ�\n");    
		 getchar();getchar();
		 break;
	   case 5:
		 //printf("\n----ListLength���ܴ�ʵ�֣�\n"); 
		 int len; 
		 if((len=ListLength(L))>=0) printf("�����Ա�Ϊ����Ϊ%d��\n",len);
		     else printf("�޴����Ա�\n");    
		 getchar();getchar();
		 break;
	   case 6:
		 //printf("\n----GetElem���ܴ�ʵ�֣�\n");
		 int i; ElemType  e;
		 printf("������Ҫ��ȡ��Ԫ��λ�ã�\n");
		 scanf("%d",&i); 
		 if(GetElem(L,i,e)) printf("�����Ա��λ�õ�Ԫ��Ϊ:%d\n",e);
		     else printf("��������\n");    
		 getchar();getchar();
		 break;
	   case 7:
		 //printf("\n----LocateElem���ܴ�ʵ�֣�\n");  
		 int ans;    
		 printf("��������Ҫ��ȡ��Ԫ�أ�\n");
		 scanf("%d",&e);
		 if((ans=LocateElem(L,e))) printf("�����Ա��Ԫ�ص�λ��Ϊ:%d\n",ans);
		     else printf("û�д�Ԫ�أ�\n"); 
		 getchar();getchar();
		 break;
	   case 8:
		 //printf("\n----PriorElem���ܴ�ʵ�֣�\n");     
		 printf("��������Ҫ��ȡǰһ��Ԫ�ص�Ԫ�أ�\n");
		 scanf("%d",&e);
		 if((ans=PriorElem(L,e,ans))) printf("�����Ա��Ԫ�ص�ǰһ��Ԫ��Ϊ:%d\n",ans);
		     else printf("û�д�Ԫ�أ�\n");
		 getchar();getchar();
		 break;
	   case 9:
		 //printf("\n----NextElem���ܴ�ʵ�֣�\n");     
		 printf("��������Ҫ��ȡ��һ��Ԫ�ص�Ԫ�أ�\n");
		 scanf("%d",&e);
		 if((ans=NextElem(L,e,ans))) printf("�����Ա��Ԫ�صĺ�һ��Ԫ��Ϊ:%d\n",ans);
		     else printf("û�д�Ԫ�أ�\n"); 
		 getchar();getchar();
		 break;
	   case 10:
		 //printf("\n----ListInsert���ܴ�ʵ�֣�\n");   
		 printf("��������Ҫ����Ԫ�ص�λ�ã�\n");
		 scanf("%d",&i);
		 printf("��������Ҫ�����Ԫ�أ�\n");
		 scanf("%d",&e);
		 if(ListInsert(L,i,e)) printf("�ѳɹ����룡\n");
		     else printf("��������\n");     
		 getchar();getchar();
		 break;
	   case 11:
		 //printf("\n----ListDelete���ܴ�ʵ�֣�\n");  
		 printf("��������Ҫɾ��Ԫ�ص�λ�ã�\n");
		 scanf("%d",&i);
		 if(ListInsert(L,i,e)) printf("�ѳɹ�ɾ����Ԫ��Ϊ��%d\n",e);
		     else printf("��������\n");       
		 getchar();getchar();
		 break;
	   case 12:
		 //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");     
		 if(!ListTrabverse(L)) printf("���Ա��ǿձ�\n");
		 getchar();getchar();
		 break;
	   case 13:
		 //printf("\n----SaveToFile���ܴ�ʵ�֣�\n");     
		 printf("\n������Ҫ������ļ�����\n");
		 scanf("%s",fileName);
		 if(SaveToFile(fileName,L)) printf("�ѳɹ��������ļ�!");
		 else printf("����ʧ�ܣ�"); 
		 getchar();getchar();
		 break;
	   case 14:
		 //printf("\n----LoadFromFile���ܴ�ʵ�֣�\n");     
		 printf("\n������Ҫ��ȡ���ļ�����\n");
		 scanf("%s",fileName);
		 if(LoadFromFile(fileName,L)) printf("�ѳɹ����ļ���ȡ!");
		 else printf("��ȡʧ�ܣ�"); 
		 getchar();getchar();
		 break;
	   case 0:
         break;
	}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
}//end of main()

status IntiaList(SqList & L){
	//����һ���յ����Ա�L 
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW); //�洢����ʧ�� 
	L.length=0;                 //�ձ���Ϊ0 
    L.listsize=LIST_INIT_SIZE;  //��ʼ�洢���� 
	return OK;
}

status DestroyList(SqList & L){
	if(!L.elem) return OK;   //L������	
	free(L.elem);              //�ͷ��ڴ� 
	L.length=0;                //�ձ������� 
	L.listsize=0;              //��ʼ������0 
	return OK;
} 

status ClearList(SqList &L){
	if(!L.elem) exit(ERROR); 
	L.length=0;                 //�ձ���Ϊ0 
    L.listsize=LIST_INIT_SIZE;  //��ʼ�洢���� 
	return OK;
} 

status ListEmpty(SqList L){
	if(!L.elem) exit(ERROR); //�쳣���� 
	if(L.length==0) return TRUE; //�ձ� 
	else return FALSE;           //�ǿ� 
} 

int ListLength(SqList L){
	if(!L.elem) exit(ERROR); //�쳣����  
	return L.length;
} 

status GetElem(SqList L,int i,ElemType & e){
	if(!L.elem) exit(ERROR); //�쳣����  
	if(i>L.length) exit(OVERFLOW);
	e=L.elem[i-1];
	return OK;
}

status LocateElem(SqList L,ElemType e){
	int i=1; //i�ĳ�ֵΪ��һ��Ԫ�ص�λ�� 
	ElemType *p=L.elem; //p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ�� 
	while(i<=L.length&&((*p++)==e)) ++i;
	if(i<=L.length) return i;
	else return 0;
}

status PriorElem(SqList L,ElemType cur,ElemType & pre_e){
	for(int i=1;i<L.length;i++){ //�ӵڶ�����ʼ���� 
		if(L.elem[i]==cur){
			pre_e=L.elem[i-1];
			return  OK;  //�ҵ��� 
		}
	} 
	return ERROR;  //δ�ҵ� 
} 

status NextElem(SqList L,ElemType cur,ElemType & next_e){
	for(int i=0;i<L.length-1;i++){
		if(L.elem[i]==cur){
			next_e=L.elem[i+1];
			return  OK;  //�ҵ��� 
		}
	} 
	return ERROR;      //δ�ҵ� 
}

status ListInsert(SqList & L,int i,ElemType e){
	//��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e 
	//i�ĺϷ�λ��Ϊ1<=i<=ListLength_Sq(L)+1
	if(i<1||i>L.length+1) return ERROR;  //iֵ���Ϸ� 
	if(L.length>=L.listsize){   //��ǰ�洢�ռ����������ӷ��� 
		ElemType * newbase =(ElemType *) realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);    //�洢����ʧ�� 
		L.elem=newbase;                 //�»�ַ 
		L.listsize+=LISTINCREMENT;      //���Ӵ洢���� 
	} 
	ElemType * q=&(L.elem[i-1]);
	for(ElemType *p=&(L.elem[L.length-1]);p>=q;--p) *(p+1) =*p;   //����λ�ü�֮���Ԫ������ 
	
	*q =e;    //����e
	++L.length;     //����1
	return OK; 
} 

status ListDelete(SqList & L,int i,ElemType & e){
    //��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
	//i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L) 
	if((i<1)||(i>L.length)) return ERROR;  //iֵ���Ϸ� 
	ElemType *p=&(L.elem[i-1]);            //pΪ��ɾ��Ԫ�ص�λ�� 
	e=*p;                                  //��ɾ��Ԫ�ص�ֵ����e 
	ElemType * q=L.elem+L.length-1;        //��βԪ�ص�λ�� 
	for(++p;p<=q;++p) *(p-1)=*p;           //��ɾ��Ԫ��֮���Ԫ������ 
	--L.length;                            //����1 
	return OK;
} 

status ListTrabverse(SqList L){
   int i;
   printf("\n-----------all elements -----------------------\n");
   for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
   printf("\n------------------ end ------------------------\n");
   return L.length;
}

status LoadFromFile(char * filename,SqList & L){
	IntiaList(L);
	FILE  *fp;
	if ((fp=fopen(filename,"r"))==NULL){
		printf("File open error\n ");
		return ERROR;
	}
	while(fread(&L.elem[L.length],sizeof(ElemType),1,fp))
	   L.length++;
	fclose(fp);
	return OK;
}
status SaveToFile(char * filename,SqList  L){
	FILE  *fp;   
	printf("input file name: ");
	scanf("%s",filename);
	
	//д�ļ��ķ��� 
	if ((fp=fopen(filename,"w"))==NULL){
		printf("File open error\n ");
		return ERROR;
	}
	fwrite(L.elem,sizeof(ElemType),L.length,fp);
	fclose(fp);
	return OK;
}
