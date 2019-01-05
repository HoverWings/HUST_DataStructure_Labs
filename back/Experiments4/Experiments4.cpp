/*
File name:	Experiments4
Author:		Xiang Pan,IOT1601,HUST
GitHub:		HoverWings
Email:		hover@hust.edu.cn
Description:Graph structure based on adjacency list 
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Assert.h>
#include <iostream>
#include <string.h>
#include <cstring>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define NOTFOUND -1
#define INFEASTABLE -1
#define OVERFLOW -2
#define EMPTYMAP -3
#define BOUNDARY -4

#define DEFAULTVALUE '#'
#define MAX_VERTEX_NUM 20
#define GRAPHLISTSIZE 101
typedef int status;
typedef int Key;				//����Ԫ�عؼ������Ͷ���
typedef char VertexType;		//����Ԫ�����Ͷ���
typedef int InfoType;			//�ַ����������� ���ΪNULL�򲻿���

typedef struct ArcNode		//���ڵ㶨��
{
	Key adjvex;                 //�û���ָ��Ľ���λ��
	struct ArcNode *nextarc;    //ָ����һ������ָ��
	InfoType info;
}ArcNode,*pArcNode;

typedef struct VNode		//�ڵ㶨��
{
	int key;
	VertexType data;                //������Ϣ
	ArcNode *firstarc;              //ָ���һ�������ö���Ļ���ָ��
}VNode,*pVNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph		//ͼ��˳���ڵ㶨��
{
	char name[20];			//ͼ������
	int kind=0;				//ͼ�ı�־����
	AdjList vertices;		//�ڽӱ�
	int vexnum=0;			//ͼ�ĵ�ǰ������
	int arcnum=0;			//ͼ�ĵ�ǰ����
}ALGraph,*pALGraph;

typedef struct ALGraphList	//ͼ˳�����
{
	pALGraph* elem;		//ָ�������ͷָ��
	int length;
	int size;
}ALGraphList;

status CreateGraph(ALGraph &G, char * V, char * VR, int* arcWeight);
status DestroyGraph(ALGraph &G);
Key LocateVex(ALGraph& G, VertexType v);//v��G�еĶ��������ͬ����
VertexType GetVex(ALGraph& G, Key v);
status PutVex(ALGraph &G, Key v, VertexType value);
VNode* FirstAdjVex(ALGraph &G, Key v);
VNode * NextAdjVex(ALGraph & G, Key v, Key w);
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, VertexType v);
status InsertArc(ALGraph & G, VertexType v, VertexType w, InfoType arcW);
status DeleteArc(ALGraph &G, VertexType v, VertexType w);
void DFSTraverse(ALGraph G, void(*visit)(pVNode N));
void BFSTraverse(ALGraph G, void(*visit)(pVNode N));
void ShowVexArc(ALGraph G);
int isExistedArcByValue(ALGraph &G, VertexType v, VertexType w, pArcNode &vwArc, pArcNode &wvArc);
status SaveToFile(char * filename, ALGraph &G);
status LoadFromFile(char * filename, ALGraph &G);

//���N��value
void visit(pVNode N)
{
	printf("%c\t", N->data);
}

Key GetKeyByValue(ALGraph G, VertexType v);
pVNode GetNodeByKey(ALGraph G, Key key)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].key == key)
		{
			return &(G.vertices[i]);
		}
	}
	return NULL;
}

bool isExisted(ALGraph G)
{
	if (G.vexnum)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int vexnum = 0;
int arcnum = 0;
int kind=0;

int main()
{
#pragma region ͼ����ĳ�ʼ��
	
	ALGraphList* pGL = (ALGraphList*)malloc(sizeof(ALGraphList));
	pGL->elem= (pALGraph*)malloc(GRAPHLISTSIZE * sizeof(pALGraph));	//ָ������
	for (int i = 0; i < GRAPHLISTSIZE; i++)
	{
		pGL->elem[i] = NULL;
	}
	pGL->size = GRAPHLISTSIZE;
	pGL->length = 0;
#pragma endregion

	//һЩ�����ĳ�ʼ��
	char name[20];
	char fileName[20];
	char v;
	int key = 0;
	int keyV = 0;
	int keyW = 0;
	char valueV = DEFAULTVALUE;
	char valueW = DEFAULTVALUE;
	char vex[100];
	char arc[200];
	int arcWeight[50] = {0};		//��Ȩֵ
	int arcW=0;
	char* pArcStr = arc;
	pVNode returnVNode=NULL;

	int opIndex = 0;		// the ALGraphListNum to operate
	int op = 1;
	int ans;			// save the return state
	char value=DEFAULTVALUE;
	int arcNum = 0;
	pALGraph *opGraph = NULL;
	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. CreateGraph		 12. DFSTraverse\n");
		printf("    	  2. DestroyGraph		 13. BFSTraverse\n");
		printf("    	  3. LocateVex			 14. ShowVexArc\n");
		printf("    	  4. GetVex			 15. SaveToFile\n");
		printf("    	  5. PutVex			 16. LoadFromFile\n");
		printf("    	  6. FirstAdjVex         \n");
		printf("    	  7. NextAdjVex	         \n");
		printf("    	  8. InsertVex           \n");
		printf("    	  9. DeleteVex           \n");
		printf("    	  10. InsertArc          \n");
		printf("    	  11. DeleteArc          \n");
		printf("    					         \n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~16]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1://1. CreateGraph
			printf("��������Ҫ��ʼ����ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if (*opGraph != NULL)
			{
				printf("ͼ%d�Ѵ���\n",opIndex);
				getchar(); getchar();
				break;
			}	
			*opGraph = (pALGraph)malloc(sizeof(ALGraph));
			(*opGraph)->kind = 0;				//Ĭ�� ������Ȩ
			(*opGraph)->vexnum = 0;
			(*opGraph)->arcnum = 0;
			vexnum = (*opGraph)->vexnum;
			arcnum = (*opGraph)->arcnum;
			printf("������ͼ����\n");
			scanf("%s%*c", name);
			strcpy((*opGraph)->name, name);
			printf("������ͼ����  ����ͼ��0  ����ͼ��1  ��������2  ��������3  \n");
			scanf("%d%*c", &kind);
			if (kind < 0 || kind>3)
			{
				printf("�����������\n");
				getchar(); getchar();
				break;
			}
			printf("�����������:\n");
			fgets(vex, 100, stdin);
			printf("������ߵļ��ϣ��ñߵĶ����ʾ���ɣ�ʾ������a->b,c->d,����abcd���ɣ�:\n");
			fgets(arc, 200, stdin);
			if ((strlen(arc)-1) % 2)//ĩβ/n
			{
				printf("����ı߼�������\n");
				getchar(); getchar();
				break;
			}
			arcNum = strlen(arc) / 2;
			pArcStr = arc;
			if (kind == 2 || kind == 3)//2 3 ��Ȩ
			{
				for (size_t i = 0; i < arcNum; i++)
				{
					printf("�������%d���ߵı�Ȩֵ\n",i+1);
					printf("��Ϊ%c->", *pArcStr++);
					printf("%c\n", *pArcStr++);
					scanf("%d", &arcWeight[i]);
				}
			}
			if (CreateGraph(**opGraph, vex, arc, arcWeight) == OK)
			{
				printf("ͼ�����ɹ���\n");
			}
			else
			{
				printf("ͼ����ʧ�ܣ�\n");
				DestroyGraph(**opGraph);
			}
			getchar(); getchar();
			break;
		
		case 2://2.DestroyGraph
			printf("��������Ҫ���ٵ�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������,�޷�����", opIndex);
				getchar(); getchar();
				break;
			}
			if (DestroyGraph(**opGraph))
			{
				printf("���ٳɹ���");
				*opGraph = NULL;
			}
			else
			{
				printf("����ʧ�ܣ�");
			}
			getchar(); getchar();
			break;
		
		case 3://3. LocateVex
			printf("��������Ҫ��ȡԪ�ص�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("�������ȡ��Ԫ�ء�ֵ����");
			scanf(" %c", &v);
			if ((ans = LocateVex(**opGraph, v)) != -1)
			{
				printf("����λ��Ϊ%d.\n", ans);
			}
			else
			{
				printf("δ�ҵ��ö��㣡\n");
			}
			getchar(); getchar();
			break;

		case 4://4. GetVex
			printf("��������Ҫ��ȡԪ�ص�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("�������ȡ�Ķ���ı�ţ�key��:");
			scanf("%d", &key);
			if (!(0 <= key&& key < (*opGraph)->vexnum))//��Ų��ڷ�Χ��
			{
				printf("��ǰͼ�޴˽ڵ�\n");
				getchar(); getchar();
				break;
			}
			if ((value = GetVex(**opGraph, key)) !=DEFAULTVALUE)
			{
				printf("����ֵΪ%c\n", value);
			}
			else
			{
				printf("δ�ҵ��ö��㣡\n");
			}
			getchar(); getchar();
			break;

		case 5://5. PutVex
			printf("��������Ҫ��ֵԪ�ص�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("�����븳ֵ�Ķ���ı�ţ�key��:");
			scanf("%d%*c", &key);
			printf("�����븳ֵ�Ķ����ֵ��value��:");
			scanf("%c", &value);
			if (!(0 <= key&& key < (*opGraph)->vexnum))//��Ų��ڷ�Χ��
			{
				printf("��ǰͼ�޴˽ڵ�\n");
				getchar(); getchar();
				break;
			}
			if ((ans = PutVex(**opGraph, key,value)) != ERROR)
			{
				printf("��ֵ�ɹ�");
			}
			else
			{
				printf("δ�ҵ��ö��㣡\n");
			}
			getchar(); getchar();
			break;

		case 6://6. FirstAdjVex
			printf("��������Ҫ��ȡ��һ���ڽӽڵ�ĵ�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("��������Ҫ��ȡ��һ���ڽӽڵ�Ľڵ�ı��:");
			scanf("%d", &key);
			if (!(0 <= key&& key < (*opGraph)->vexnum))//��Ų��ڷ�Χ��
			{
				printf("��ǰͼ�޴˽ڵ�\n");
				getchar(); getchar();
				break;
			}
			if ((returnVNode=FirstAdjVex(**opGraph, key))!=NULL)
			{
				printf("��%d�ڵ�ĵ�һ���ڽӽڵ�ı��%d",key,returnVNode->key);
			}
			else
			{
				printf("�ýڵ㲻���ڣ�");
			}
			getchar(); getchar();
			break;

		case 7://7. NextAdjVex
			printf("��������Ҫ��ȡ��һ���ڽӽڵ�ĵ�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("��������Ҫ��ȡ��һ���ڽӽڵ�Ľڵ�ı��:");
			scanf("%d%*c", &keyV);
			if (!(0 <= keyV&& keyV < (*opGraph)->vexnum))//��Ų��ڷ�Χ��
			{
				printf("��ǰͼ�޴˽ڵ�\n");
				getchar(); getchar();
				break;
			}
			printf("��������Ҫ��ȡ��һ���ڽӽڵ����Խڵ�ı��:");
			scanf("%d", &keyW);
			if (!(0 <= keyW&& keyW < (*opGraph)->vexnum))//��Ų��ڷ�Χ��
			{
				printf("��ǰͼ�޴˽ڵ�\n");
				getchar(); getchar();
				break;
			}
			if ((returnVNode=NextAdjVex(**opGraph,keyV,keyW))!=NULL)
			{
				printf("��һ���ڽӽڵ�ı��Ϊ��%d", returnVNode->key);
			}
			else
			{
				printf("δ�ҵ���һ���ڽӽڵ㣡");
			}
			getchar(); getchar();
			break;

		case 8://8. InsertVex
			printf("��������Ҫ��ȡ����ڵ�ĵ�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("��������Ҫ����ڵ��ֵ:");
			scanf(" %c%*c", &valueV);
			if (InsertVex(**opGraph, valueV))
			{
				keyV = GetKeyByValue(**opGraph,valueV);
				printf("����ɹ�,�ڵ�%d��ֵΪ%c",keyV,valueV);
			}
			else
			{
				printf("����ʧ��");
			}
			getchar(); getchar();
			break;

		case 9://9. DeleteVex
			printf("��������Ҫ��ȡɾ���ڵ�ĵ�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("��������Ҫɾ���ڵ��ֵ:");
			scanf("%c%*c", &valueV);
			keyV = LocateVex(**opGraph, valueV);
			if (keyV == NOTFOUND)
			{
				printf("��ǰͼ�޴˽ڵ�\n");
				getchar(); getchar();
				break;
			}
			if (DeleteVex(**opGraph, valueV))
			{		
				printf("ɾ���ɹ�,�ڵ�%d��ֵΪ%c��ɾ��", keyV, valueV);
			}
			else
			{
				printf("ɾ��ʧ��");
			}
			getchar(); getchar();
			break;

		case 10://10. InsertArc
			printf("��������Ҫ��ȡ���뻡�ĵ�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("��������Ҫ���뻡��β�ڵ�ֵ:");
			scanf(" %c%*c", &valueV);
			if (LocateVex(**opGraph, valueV) == NOTFOUND)
			{
				printf("�˽ڵ�ֵ�����ڣ�");
				getchar(); getchar();
				break;
			}
			printf("��������Ҫ���뻡��ͷ�ڵ�ֵ:");
			scanf(" %c%*c", &valueW);
			if (LocateVex(**opGraph, valueW) == NOTFOUND)
			{
				printf("�˽ڵ�ֵ�����ڣ�");
				getchar(); getchar();
				break;
			}
			kind = (*opGraph)->kind;
			if (kind == 2 || kind == 3)//2 3 ��Ȩ
			{
				printf("��������Ҫ���뻡��Ȩֵ:");
				scanf(" %d%*c", &arcW);
			}
			if (InsertArc(**opGraph, valueV, valueW,arcW))
			{
				printf("����ɹ�!");
			}
			else
			{
				printf("����ʧ��");
			}
			getchar(); getchar();
			break;
			
		case 11://11. DeleteArc
			printf("��������Ҫ��ȡɾ�����ĵ�ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			printf("��������Ҫɾ������β�ڵ�ֵ(����ͼ˳������):");
			scanf(" %c%*c", &valueV);
			printf("��������Ҫɾ������ͷ�ڵ�ֵ:");
			scanf(" %c%*c", &valueW);
			if (DeleteArc(**opGraph, valueV, valueW))
			{
				printf("ɾ���ɹ�!");
			}
			else
			{
				printf("ɾ��ʧ��");
			}
			getchar(); getchar();
			break;

		case 12://12. DFSTraverse
			printf("��������Ҫ��ȡ������ȱ�����ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			DFSTraverse(**opGraph, visit);
			getchar(); getchar();
			break;

		case 13://13. BFSTraverse
			printf("��������Ҫ��ȡ������ȱ�����ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			BFSTraverse(**opGraph, visit);
			getchar(); getchar();
			break;
			
		case 14://14. ShowVexArc
			printf("��������Ҫ��ȡ��ʾ��Ϣ��ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			ShowVexArc(**opGraph);
			getchar(); getchar();
			break;

		case 15://SaveToFile
			printf("��������Ҫ�����ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("ͼ%d������", opIndex);
				getchar(); getchar();
				break;
			}
			if (SaveToFile(fileName, **opGraph))
			{
				printf("�ɹ�\n");
			}
			else
			{
				printf("ʧ��\n");
			}
			getchar(); getchar();
			break;

		case 16://LoadFromFile
			printf("��������Ҫ�����ͼ�ı��(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("�������˴���ı�ţ�");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) != NULL)
			{
				printf("ͼ%d�Ѵ���", opIndex);
				getchar(); getchar();
				break;
			}
			*opGraph = (pALGraph)malloc(sizeof(ALGraph));
			(*opGraph)->kind = 0;				//Ĭ�� ������Ȩ
			(*opGraph)->vexnum = 0;
			(*opGraph)->arcnum = 0;
			vexnum = (*opGraph)->vexnum;
			arcnum = (*opGraph)->arcnum;
			if (LoadFromFile(fileName, **opGraph))
			{
				printf("�ɹ�\n");
			}
			else
			{
				printf("ʧ��\n");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

 //��ʼ������ͼG������,V��ͼ�Ķ��㼯��VR��ͼ�Ĺ�ϵ��,arcWeight��Ȩ�ؼ��ϣ�
 //�����������V��VR��arcWeight�͵Ķ��幹��ͼG��
status CreateGraph(ALGraph &G, char * V, char * VR,int* arcWeight)
{
	//printf("%d", G.vexnum);
	G.kind = kind;
	if (G.vexnum>0)   //���ͼ�ѱ�����������ʧ��
	{
		return ERROR;
	}
	char *pV = V;
	for (pV; *pV != '\n'; pV++)
	{
		InsertVex(G, *pV);
	}
	char *pVR = VR;
	while (*pVR != '\n')
	{
		char v, w;
		int arcW=0;
		v = *pVR;
		w = *++pVR;
		arcW = *arcWeight++;
		InsertArc(G, v, w, arcW);
		pVR++;
	}
	return OK;
}

//��ʼ������ͼG���ڡ�
//�������������ͼG��
status DestroyGraph(ALGraph &G)
{
	pALGraph pG = &G;
	pArcNode p,pre;
	for (int i = 0; i < G.vexnum; i++)             //��������ͷ���
	{
		pre=G.vertices[i].firstarc;
		if (pre != NULL)
		{
			p = pre->nextarc;
			while (p != NULL)
			{
				free(pre);
				pre = p;
				p = p->nextarc;
			}
			free(pre);
		}
	}
	free(pG);                   //�ͷ�G��ָ��ͷ���������ڴ�ռ�
	return OK;
}

//��ȡ�ڵ��Key
//��ʼ������ͼG���ڣ�u��G�еĶ��������ͬ������
//�����������u��ͼG�д��ڣ����ض���u��λ����Ϣ�����򷵻�������Ϣ��
Key LocateVex(ALGraph& G, VertexType v)
{
	
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == v)
		{
			return i;
		}
	}
	return NOTFOUND;
}

//��ȡ�ڵ��Value
VertexType GetVex(ALGraph& G, Key v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].key == v)
		{
			return G.vertices[i].data;
		}
	}
	return DEFAULTVALUE;
}

status PutVex(ALGraph & G, Key v, VertexType value)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].key == v)
		{
			G.vertices[i].data = value;
			return OK;
		}
	}
	return ERROR;
}

VNode * FirstAdjVex(ALGraph & G, Key v)
{
	if (G.vertices[v].firstarc!=NULL)
	{
		int key= G.vertices[v].firstarc->adjvex;
		return GetNodeByKey(G, key);		
	}
	return NULL;
}

//��ʼ����:ͼG���ڣ�v��G��һ������, w��v���ڽӶ��㣻
//�������:����v�ģ������w����һ���ڽӶ��㣬���w�����һ���ڽӶ��㣬���ء��ա���
VNode * NextAdjVex(ALGraph & G,Key v,Key w)
{
	assert(v<G.vexnum&&w<G.vexnum);//ȷ��ͼ�д��ڶ���
	pArcNode pArc;
	pArc = G.vertices[v].firstarc;
	while (pArc!=NULL)
	{
		if (pArc->adjvex == w)
		{
			if (pArc->nextarc != NULL)//w����һ���ڽӽڵ�
			{
				pArc = pArc->nextarc;
				int nextKey=pArc->adjvex;
				return GetNodeByKey(G,nextKey);
			}
			else
			{
				return NULL;
			}
		}
		pArc = pArc->nextarc;
	}
	return NULL;//δ�ҵ��ڵ�w
}

//Input:G,Value
//Output:Key
Key GetKeyByValue(ALGraph G, VertexType v)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == v)
		{
			return i;
		}
	}
	return NOTFOUND;
}

//��ʼ������ͼG���ڣ�v��G�еĶ��������ͬ����(����ͬһ����)��
//�����������ͼG�������¶���v��
status InsertVex(ALGraph & G, VertexType v)
{
	G.vertices[G.vexnum].data = v;
	G.vertices[G.vexnum].key = G.vexnum;
	G.vertices[G.vexnum].firstarc = NULL;
	printf("����ڵ�Key=%d,value=%c\n", G.vertices[G.vexnum].key, G.vertices[G.vexnum].data);
	G.vexnum++;
	return OK;
}


//��ʼ������ͼG���ڣ�v��G��һ�����㡣
//�������������ͼ������ ��ͼG��ɾ������v����v��صĻ���
status DeleteVex(ALGraph & G, VertexType v)
{
	int key=0;
	if ((key = LocateVex(G, v)) == NOTFOUND)//�жϵ�ǰ���Ƿ���ͼ��
	{
		return ERROR;
	}
	pArcNode cur=NULL;
	for (cur = G.vertices[key].firstarc; cur!=NULL; cur = cur->nextarc) //ɾ����vΪ��β�Ļ� ɾ��v����
	{
		free(cur);
		G.arcnum--;
	}
	for (int i = key; i < G.vexnum; i++)				//v֮��Ľڵ���ǰ�ƶ�
	{
		G.vertices[i] = G.vertices[i + 1];
	}
	for (int i = 0; i < G.vexnum; i++)					//ɾ����vΪ��ͷ�Ļ���������������ָ��Ķ���λ��
	{
		if ((cur = G.vertices[i].firstarc)==NULL)		//���û�й����Ļ� ��ǰ�ڵ�û�г���
		{
			continue;
		}
		if (cur->adjvex == key)							//�������ĵ�һ����ָ��v
		{
			G.vertices[i].firstarc = cur->nextarc;
			free(cur);
			cur = G.vertices[i].firstarc;
			G.arcnum--;
		}
		for (; cur!=NULL; cur = cur->nextarc)			//�������
		{
			if (cur->adjvex >key)						//���нڵ�ı�ż�1
			{
				cur->adjvex--;
			}
			if (cur->nextarc!=NULL)
			{
				if (cur->nextarc->adjvex == key)
				{
					pArcNode p = cur->nextarc;			//whether is NULL OR NOT NULL
					cur->nextarc = cur->nextarc->nextarc;
					free(p);
					G.arcnum--;
				}
			}
		}
	}
	return OK;
}

//��ʼ������ͼG���ڣ�v��w��G�Ķ���Value,arcWΪ��Ȩ��
//�����������ͼG�����ӻ�<v, w>
status InsertArc(ALGraph & G, VertexType v, VertexType w,InfoType arcW)
{
	int kind = G.kind;
	pArcNode vwArc = NULL, wvArc = NULL;
	int s = isExistedArcByValue(G, v, w, vwArc, wvArc);
	if (s != 0)
	{
		if (kind == 0 || kind == 2)//0 2����
		{
			printf("����֮����ڻ�!\n");
			return ERROR;
		}
		else
		{
			if (s==1)
			{
				printf("����֮����ڻ�!\n");
				return ERROR;
			}
		}
	}
	int vKey=-1, wKey=-1;
	if (((vKey = GetKeyByValue(G, v)) == NOTFOUND) || ((wKey = GetKeyByValue(G, w)) == NOTFOUND))     //û�ҵ�v��w�����ش���
	{
		printf("vKey%d\n", vKey);
		printf("wKey%d\n", wKey);
		return ERROR;
	}
	ArcNode *arc1 = (ArcNode *)malloc(sizeof(ArcNode));
	pArcNode pArc = G.vertices[vKey].firstarc;
	if (pArc == NULL)
	{
		G.vertices[vKey].firstarc = arc1;
		arc1->info = arcW;										
		arc1->adjvex = wKey;
		arc1->nextarc = NULL;
		G.arcnum++;
		//������뻡����Ϣ
		printf("���뻡%d(%c)->%d(%c)", vKey, v, wKey, w);
		if (kind == 2 || kind == 3)//2 3��Ȩ
		{
			printf("\t%d\n", arcW);
		}
		else
		{
			printf("\n");
		}
	}	
	else
	{
		while (pArc->nextarc!=NULL)
		{
			pArc = pArc->nextarc;
		}
		pArc->nextarc = arc1;
		arc1->info = arcW;										
		arc1->adjvex = wKey;
		arc1->nextarc = NULL;
		G.arcnum++;
		printf("���뻡%d(%c)->%d(%c)", vKey, v, wKey, w);
		if (kind == 2 || kind == 3)//2 3��Ȩ
		{
			printf("\t%d\n", arcW);
		}
		else
		{
			printf("\n");
		}
	}
	if (kind == 0 || kind == 2)//0 2 ����
	{
		pArc = G.vertices[wKey].firstarc;
		ArcNode *arc2 = (ArcNode *)malloc(sizeof(ArcNode));
		if (pArc == NULL)
		{
			G.vertices[wKey].firstarc = arc2;
			arc2->info = arcW;										//�˴��账��info
			arc2->adjvex = vKey;
			arc2->nextarc = NULL;
			printf("���뻡%d(%c)->%d(%c)", wKey, w, vKey, v);
			if (kind == 2)//2��Ȩ
			{
				printf("\t%d\n", arcW);
			}
			else
			{
				printf("\n");
			}
		}
		else
		{
			while (pArc->nextarc != NULL)
			{
				pArc = pArc->nextarc;
			}
			pArc->nextarc = arc2;
			arc2->info = arcW;										//�˴��账��info
			arc2->adjvex = vKey;
			arc2->nextarc = NULL;
			printf("���뻡%d(%c)->%d(%c)", wKey, w, vKey, v);
			if (kind == 2)//2��Ȩ
			{
				printf("\t%d\n", arcW);
			}
			else
			{
				printf("\n");
			}
		}
	}
	return OK;
}

//��ʼ������ͼG���ڣ�v��w��G�Ķ��㡣
//�������������ͼ����ͼG��ɾ����<v, w> <w,v>
//			�з�ͼ����ͼG�л�<v, w> 
//			������֮�䲻���ڻ� return ERROR
status DeleteArc(ALGraph &G, VertexType v, VertexType w)
{
	int kind = G.kind;
	pArcNode vwArc=NULL, wvArc=NULL;
	int s=isExistedArcByValue(G, v, w, vwArc, wvArc);
	if (s== 0)//����֮���޻�
	{
		printf("����֮���޻�\n");
		return ERROR;
	}
	else//���ߴ��ڻ�
	{
		if (kind == 0 || kind == 2)	//����ͼ
		{
			if (s != 3)
			{
				printf("����ͼ�д��ڵ��򻡣�����\n");
				return ERROR;
			}
		}
		if (kind == 1 || kind == 3)	//����ͼ
		{
			if (s != 1&&s!=3)
			{
				printf("�û������ڣ�\n");
			}	
		}
	}
	int vKey, wKey;
	if (((vKey = GetKeyByValue(G, v)) == NOTFOUND) || ((wKey = GetKeyByValue(G, w)) == NOTFOUND))     //û�ҵ�v��w�����ش���
	{
		return ERROR;
	}
	//ɾ�� 
	//����ͼ
	pArcNode pArc = G.vertices[vKey].firstarc;
	if (pArc ==vwArc)		//Ϊ��һ�����ڵ�
	{
		G.vertices[vKey].firstarc = vwArc->nextarc;
		free(vwArc);
		G.arcnum--;
	}
	else
	{
		for (; pArc->nextarc; pArc = pArc->nextarc)
		{
			if (pArc->nextarc->adjvex == wKey)
			{
				pArc->nextarc = vwArc->nextarc;
				free(vwArc);
				G.arcnum--;
				break;
			}
		}
	}
	if (kind == 0 || kind == 2)	//����ͼ����ɾ��wv
	{
		pArcNode pArc = G.vertices[wKey].firstarc;
		if (pArc == wvArc)		//Ϊ��һ�����ڵ�
		{
			G.vertices[wKey].firstarc = wvArc->nextarc;
			free(wvArc);
			return OK;
		}
		for (; pArc->nextarc; pArc = pArc->nextarc)
		{
			if (pArc->nextarc->adjvex == vKey)
			{
				pArc->nextarc = wvArc->nextarc;
				free(wvArc);
				return OK;
			}
		}
	}
	return OK;
}

//�ڵ�������ȱ�������
void DFS(ALGraph& G, int v, int *visited, void(*visit)(pVNode N))
{
	visited[v] = 1;
	visit(&G.vertices[v]);
	for (pArcNode pArc = G.vertices[v].firstarc; pArc; pArc = pArc->nextarc)
	{
		if (!visited[pArc->adjvex])
		{
			DFS(G, pArc->adjvex, visited,visit);
		}
	}
}

//��ʼ������ͼG���ڡ�
//�����������ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú�
//          ��printf����һ�Σ��ҽ�����һ�Ρ�
void DFSTraverse(ALGraph G, void(*visit)(pVNode N))
{
	int visited[MAX_VERTEX_NUM] = { 0 };    //�洢�Ƿ���ʹ�����Ϣ
	for (int i = 0; i < G.vexnum; i++)      //��ÿ���������������ȱ���
	{
		if (!visited[i])
		{
			DFS(G, i, visited,visit);
		}
	}
}

//��ʼ������ͼG���ڡ�
//�����������ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú�
//          ��visit����һ�Σ��ҽ�����һ�Ρ�
void BFSTraverse(ALGraph G, void(*visit)(pVNode N))
{
	int visited[MAX_VERTEX_NUM] = { 0 };    //�洢�Ƿ���ʹ�
	int queue[MAX_VERTEX_NUM] = { 0 };		//ʹ�ö��д洢���ʷ�����Ϣ
	int head = 0, rear = 0;
	for (int v = 0; v < G.vexnum; v++)      //��ÿ��������й�����ȱ���
	{
		if (visited[v])     //����Ѿ�������������
		{
			continue;
		}
		visited[v] = 1;
		printf("%c\t", G.vertices[v].data);
		queue[rear++] = v;
		while (head < rear)
		{
			int u = queue[head++];
			for (ArcNode *arc = G.vertices[u].firstarc; arc; arc = arc->nextarc)
			{
				if (!visited[arc->adjvex])
				{
					visited[arc->adjvex] = 1;
					printf("%c\t", G.vertices[arc->adjvex].data);
					queue[rear++] = arc->adjvex;
				}
			}
		}
	}
}

//��ʼ������ͼG����
//�����������ʾͼ�е���Ϣ
void ShowVexArc(ALGraph G)
{
	kind = G.kind;
	printf("����Ϊ��\n");
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("%c ", G.vertices[i].data);
	}
	printf("\n��Ϊ��\n");
	for (int i = 0; i < G.vexnum; i++)
	{
		for (ArcNode *arc = G.vertices[i].firstarc; arc!=NULL; arc = arc->nextarc)
		{
			printf("%d(%c)->%d(%c)", LocateVex(G,G.vertices[i].data), G.vertices[i].data, LocateVex(G, G.vertices[arc->adjvex].data), G.vertices[arc->adjvex].data);
			if (kind == 2 || kind == 3)//2 3��Ȩ
			{
				printf("\t%d\n", arc->info);
			}
			else
			{
				printf("\n");
			}
		}
	}
	switch (G.kind)
	{
	case 0:
		printf("ͼ������Ϊ����ͼ\n");
		break;
	case 1:
		printf("ͼ������Ϊ����ͼ\n");
		break;
	case 2:
		printf("ͼ������Ϊ������\n");
		break;
	case 3:
		printf("ͼ������Ϊ������\n");
		break;
	default:
		break;
	}
	printf("ͼ������Ϊ%s��\n", G.name);
	printf("��������Ϊ%d��������Ϊ%d��\n", G.vexnum, G.arcnum);
	//����ڽӱ�
	printf("----------------����Ϊ�ٽӱ�--------------------\n");
	for (int i = 0; i < G.vexnum; i++)
	{
		bool first = true;
		printf("%c", G.vertices[i].data);
		for (ArcNode *arc = G.vertices[i].firstarc; arc != NULL; arc = arc->nextarc)
		{
			printf("-->");
			VertexType arcHeadValue = G.vertices[arc->adjvex].data;
			if (kind == 2 || kind == 3)//2 3��Ȩ
			{
				printf("%c,arcWeight=%d", arcHeadValue, arc->info);
			}
			else
			{
				printf("%c", arcHeadValue);
			}
		}
		printf("--> NULL");
		printf("\n");
	}
}


//�ж϶���֮���Ƿ���ڻ�
//Input:G,V,W  ������ߵ�ֵ
//Output��0����֮����
//		  1����֮��vw
//		  2����֮��wv
//		  3����֮��vwwv
int isExistedArcByValue(ALGraph &G, VertexType v, VertexType w,pArcNode &vwArc, pArcNode &wvArc)
{
	//assert(v < G.vexnum&&w < G.vexnum);
	int keyV = GetKeyByValue(G, v);
	int keyW = GetKeyByValue(G, w);
	if (keyV == NOTFOUND || keyW == NOTFOUND)
	{
		return ERROR;
	}
	bool vw = false;
	bool wv = false;
	//������vΪ��β�Ľڵ�
	pArcNode cur;
	for (cur = G.vertices[keyV].firstarc; cur != NULL; cur = cur->nextarc) 
	{
		if (cur->adjvex == keyW)
		{
			vw = true;
			vwArc = cur;
			break;
		}
	}
	//������wΪ��β�Ľڵ�
	for (cur = G.vertices[keyW].firstarc; cur != NULL; cur = cur->nextarc) 
	{
		if (cur->adjvex == keyV)
		{
			wv = true;
			wvArc = cur;
			break;
		}
	}
	if (!vw && !wv)
	{
		return 0;
	}
	if (vw&&!wv)
	{
		return 1;
	}
	if (!vw && wv)
	{
		return 2;
	}
	if (vw && wv)
	{
		return 3;
	}
	return ERROR;
}


//��ʼ������ͼG����
//�������������ͼ���ļ� ���ļ���ʧ�� �򷵻�ERROR
status SaveToFile(char * filename, ALGraph &G)
{
	FILE  *fp;
	printf("�������ļ���: ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("�ļ�д�����\n ");
		return ERROR;
	}
	printf("�ڵ�����%d", G.vexnum);
	pALGraph pG = &G;
	fwrite(&G, sizeof(ALGraph), 1, fp);
	fwrite(pG->name, sizeof(char),20, fp);
	fwrite(pG->vertices, sizeof(VNode), 20, fp);
	int i1 = 1;
	int i2 = 2;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (ArcNode *arc = G.vertices[i].firstarc; arc != NULL; arc = arc->nextarc)
		{
			fwrite(arc, sizeof(ArcNode), 1, fp);
		}
	}
	fclose(fp);
	return OK;
}

//��ʼ������ͼG����
//������������ļ���ȡ ���ļ���ʧ�� �򷵻�ERROR
status LoadFromFile(char * filename, ALGraph &G)
{
	FILE  *fp;
	printf("�������ļ���: ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("�ļ���ȡ����\n ");
		return ERROR;
	}

	pALGraph pG = &G;
	kind = G.kind;
	fread(pG, sizeof(ALGraph), 1, fp);
	fread(pG->name, sizeof(char), 20, fp);
	fread(pG->vertices, sizeof(VNode),20, fp);
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("�ڵ�%d:%c\n",i, G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	pArcNode pArc=NULL;
	pArcNode preArc = NULL;
	for (int i = 0; i < G.vexnum; i++)
	{
		bool first = true;
		pArc = (pArcNode)malloc(sizeof(ArcNode));
		while (fread(pArc, sizeof(ArcNode), 1, fp))
		{
			printf("���뻡%d(%c)->%d(%c)", i, G.vertices[i].data, pArc->adjvex, G.vertices[pArc->adjvex].data);
			if (kind == 2 || kind == 3)//2 3��Ȩ
			{
				printf("\t%d\n", pArc->info);
			}
			else
			{
				printf("\n");
			}
			pVNode pW = GetNodeByKey(G, pArc->adjvex);
			if (first)
			{
				G.vertices[i].firstarc = pArc;
				preArc = pArc;
				first = false;
				pArc = (pArcNode)malloc(sizeof(ArcNode));//���·����ڴ�
				continue;
			}
			preArc->nextarc = pArc;
			preArc = pArc;	
			if (pArc->nextarc == NULL)
			{
				break;
			}		
			else
			{
				pArc->nextarc = NULL;
			}
			pArc = (pArcNode)malloc(sizeof(ArcNode));//���·����ڴ�
		}		

	}
	fclose(fp);
	return OK;
}
