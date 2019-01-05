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
typedef int Key;				//数据元素关键字类型定义
typedef char VertexType;		//数据元素类型定义
typedef int InfoType;			//字符串类型描述 如果为NULL则不考虑

typedef struct ArcNode		//弧节点定义
{
	Key adjvex;                 //该弧所指向的结点的位置
	struct ArcNode *nextarc;    //指向下一条弧的指针
	InfoType info;
}ArcNode,*pArcNode;

typedef struct VNode		//节点定义
{
	int key;
	VertexType data;                //顶点信息
	ArcNode *firstarc;              //指向第一条依附该顶点的弧的指针
}VNode,*pVNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph		//图的顺序表节点定义
{
	char name[20];			//图的名称
	int kind=0;				//图的标志种类
	AdjList vertices;		//邻接表
	int vexnum=0;			//图的当前顶点数
	int arcnum=0;			//图的当前弧数
}ALGraph,*pALGraph;

typedef struct ALGraphList	//图顺序表定义
{
	pALGraph* elem;		//指针数组的头指针
	int length;
	int size;
}ALGraphList;

status CreateGraph(ALGraph &G, char * V, char * VR, int* arcWeight);
status DestroyGraph(ALGraph &G);
Key LocateVex(ALGraph& G, VertexType v);//v和G中的顶点具有相同特征
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

//输出N的value
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
#pragma region 图数组的初始化
	
	ALGraphList* pGL = (ALGraphList*)malloc(sizeof(ALGraphList));
	pGL->elem= (pALGraph*)malloc(GRAPHLISTSIZE * sizeof(pALGraph));	//指针数组
	for (int i = 0; i < GRAPHLISTSIZE; i++)
	{
		pGL->elem[i] = NULL;
	}
	pGL->size = GRAPHLISTSIZE;
	pGL->length = 0;
#pragma endregion

	//一些变量的初始化
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
	int arcWeight[50] = {0};		//边权值
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
		printf("    请选择你的操作[0~16]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1://1. CreateGraph
			printf("请输入你要初始化的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if (*opGraph != NULL)
			{
				printf("图%d已存在\n",opIndex);
				getchar(); getchar();
				break;
			}	
			*opGraph = (pALGraph)malloc(sizeof(ALGraph));
			(*opGraph)->kind = 0;				//默认 无向无权
			(*opGraph)->vexnum = 0;
			(*opGraph)->arcnum = 0;
			vexnum = (*opGraph)->vexnum;
			arcnum = (*opGraph)->arcnum;
			printf("请输入图名称\n");
			scanf("%s%*c", name);
			strcpy((*opGraph)->name, name);
			printf("请输入图种类  无向图：0  有向图：1  无向网：2  有向网：3  \n");
			scanf("%d%*c", &kind);
			if (kind < 0 || kind>3)
			{
				printf("输入种类错误！\n");
				getchar(); getchar();
				break;
			}
			printf("请给出各顶点:\n");
			fgets(vex, 100, stdin);
			printf("请给出边的集合，用边的顶点表示即可（示例：边a->b,c->d,输入abcd即可）:\n");
			fgets(arc, 200, stdin);
			if ((strlen(arc)-1) % 2)//末尾/n
			{
				printf("输入的边集合有误！\n");
				getchar(); getchar();
				break;
			}
			arcNum = strlen(arc) / 2;
			pArcStr = arc;
			if (kind == 2 || kind == 3)//2 3 有权
			{
				for (size_t i = 0; i < arcNum; i++)
				{
					printf("请输入第%d条边的边权值\n",i+1);
					printf("边为%c->", *pArcStr++);
					printf("%c\n", *pArcStr++);
					scanf("%d", &arcWeight[i]);
				}
			}
			if (CreateGraph(**opGraph, vex, arc, arcWeight) == OK)
			{
				printf("图创建成功！\n");
			}
			else
			{
				printf("图创建失败！\n");
				DestroyGraph(**opGraph);
			}
			getchar(); getchar();
			break;
		
		case 2://2.DestroyGraph
			printf("请输入你要销毁的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在,无法销毁", opIndex);
				getchar(); getchar();
				break;
			}
			if (DestroyGraph(**opGraph))
			{
				printf("销毁成功！");
				*opGraph = NULL;
			}
			else
			{
				printf("销毁失败！");
			}
			getchar(); getchar();
			break;
		
		case 3://3. LocateVex
			printf("请输入你要获取元素的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入获取的元素【值】：");
			scanf(" %c", &v);
			if ((ans = LocateVex(**opGraph, v)) != -1)
			{
				printf("顶点位置为%d.\n", ans);
			}
			else
			{
				printf("未找到该顶点！\n");
			}
			getchar(); getchar();
			break;

		case 4://4. GetVex
			printf("请输入你要获取元素的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入获取的顶点的编号（key）:");
			scanf("%d", &key);
			if (!(0 <= key&& key < (*opGraph)->vexnum))//编号不在范围内
			{
				printf("当前图无此节点\n");
				getchar(); getchar();
				break;
			}
			if ((value = GetVex(**opGraph, key)) !=DEFAULTVALUE)
			{
				printf("顶点值为%c\n", value);
			}
			else
			{
				printf("未找到该顶点！\n");
			}
			getchar(); getchar();
			break;

		case 5://5. PutVex
			printf("请输入你要赋值元素的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入赋值的顶点的编号（key）:");
			scanf("%d%*c", &key);
			printf("请输入赋值的顶点的值（value）:");
			scanf("%c", &value);
			if (!(0 <= key&& key < (*opGraph)->vexnum))//编号不在范围内
			{
				printf("当前图无此节点\n");
				getchar(); getchar();
				break;
			}
			if ((ans = PutVex(**opGraph, key,value)) != ERROR)
			{
				printf("赋值成功");
			}
			else
			{
				printf("未找到该顶点！\n");
			}
			getchar(); getchar();
			break;

		case 6://6. FirstAdjVex
			printf("请输入你要获取第一个邻接节点的的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入你要获取第一个邻接节点的节点的编号:");
			scanf("%d", &key);
			if (!(0 <= key&& key < (*opGraph)->vexnum))//编号不在范围内
			{
				printf("当前图无此节点\n");
				getchar(); getchar();
				break;
			}
			if ((returnVNode=FirstAdjVex(**opGraph, key))!=NULL)
			{
				printf("第%d节点的第一个邻接节点的编号%d",key,returnVNode->key);
			}
			else
			{
				printf("该节点不存在！");
			}
			getchar(); getchar();
			break;

		case 7://7. NextAdjVex
			printf("请输入你要获取下一个邻接节点的的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入你要获取下一个邻接节点的节点的编号:");
			scanf("%d%*c", &keyV);
			if (!(0 <= keyV&& keyV < (*opGraph)->vexnum))//编号不在范围内
			{
				printf("当前图无此节点\n");
				getchar(); getchar();
				break;
			}
			printf("请输入你要获取下一个邻接节点的相对节点的编号:");
			scanf("%d", &keyW);
			if (!(0 <= keyW&& keyW < (*opGraph)->vexnum))//编号不在范围内
			{
				printf("当前图无此节点\n");
				getchar(); getchar();
				break;
			}
			if ((returnVNode=NextAdjVex(**opGraph,keyV,keyW))!=NULL)
			{
				printf("下一个邻接节点的编号为：%d", returnVNode->key);
			}
			else
			{
				printf("未找到下一个邻接节点！");
			}
			getchar(); getchar();
			break;

		case 8://8. InsertVex
			printf("请输入你要获取插入节点的的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入你要插入节点的值:");
			scanf(" %c%*c", &valueV);
			if (InsertVex(**opGraph, valueV))
			{
				keyV = GetKeyByValue(**opGraph,valueV);
				printf("插入成功,节点%d的值为%c",keyV,valueV);
			}
			else
			{
				printf("插入失败");
			}
			getchar(); getchar();
			break;

		case 9://9. DeleteVex
			printf("请输入你要获取删除节点的的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入你要删除节点的值:");
			scanf("%c%*c", &valueV);
			keyV = LocateVex(**opGraph, valueV);
			if (keyV == NOTFOUND)
			{
				printf("当前图无此节点\n");
				getchar(); getchar();
				break;
			}
			if (DeleteVex(**opGraph, valueV))
			{		
				printf("删除成功,节点%d的值为%c已删除", keyV, valueV);
			}
			else
			{
				printf("删除失败");
			}
			getchar(); getchar();
			break;

		case 10://10. InsertArc
			printf("请输入你要获取插入弧的的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入你要插入弧的尾节点值:");
			scanf(" %c%*c", &valueV);
			if (LocateVex(**opGraph, valueV) == NOTFOUND)
			{
				printf("此节点值不存在！");
				getchar(); getchar();
				break;
			}
			printf("请输入你要插入弧的头节点值:");
			scanf(" %c%*c", &valueW);
			if (LocateVex(**opGraph, valueW) == NOTFOUND)
			{
				printf("此节点值不存在！");
				getchar(); getchar();
				break;
			}
			kind = (*opGraph)->kind;
			if (kind == 2 || kind == 3)//2 3 有权
			{
				printf("请输入你要插入弧的权值:");
				scanf(" %d%*c", &arcW);
			}
			if (InsertArc(**opGraph, valueV, valueW,arcW))
			{
				printf("插入成功!");
			}
			else
			{
				printf("插入失败");
			}
			getchar(); getchar();
			break;
			
		case 11://11. DeleteArc
			printf("请输入你要获取删除弧的的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			printf("请输入你要删除弧的尾节点值(无向图顺序随意):");
			scanf(" %c%*c", &valueV);
			printf("请输入你要删除弧的头节点值:");
			scanf(" %c%*c", &valueW);
			if (DeleteArc(**opGraph, valueV, valueW))
			{
				printf("删除成功!");
			}
			else
			{
				printf("删除失败");
			}
			getchar(); getchar();
			break;

		case 12://12. DFSTraverse
			printf("请输入你要获取深度优先遍历的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			DFSTraverse(**opGraph, visit);
			getchar(); getchar();
			break;

		case 13://13. BFSTraverse
			printf("请输入你要获取深度优先遍历的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			BFSTraverse(**opGraph, visit);
			getchar(); getchar();
			break;
			
		case 14://14. ShowVexArc
			printf("请输入你要获取显示信息的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			ShowVexArc(**opGraph);
			getchar(); getchar();
			break;

		case 15://SaveToFile
			printf("请输入你要保存的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) == NULL)
			{
				printf("图%d不存在", opIndex);
				getchar(); getchar();
				break;
			}
			if (SaveToFile(fileName, **opGraph))
			{
				printf("成功\n");
			}
			else
			{
				printf("失败\n");
			}
			getchar(); getchar();
			break;

		case 16://LoadFromFile
			printf("请输入你要载入的图的编号(0~100):");
			scanf("%d", &opIndex);
			if (opIndex > 100)
			{
				printf("你输入了错误的编号！");
				getchar(); getchar();
				break;
			}
			opGraph = &(pGL->elem)[opIndex];
			if ((*opGraph) != NULL)
			{
				printf("图%d已存在", opIndex);
				getchar(); getchar();
				break;
			}
			*opGraph = (pALGraph)malloc(sizeof(ALGraph));
			(*opGraph)->kind = 0;				//默认 无向无权
			(*opGraph)->vexnum = 0;
			(*opGraph)->arcnum = 0;
			vexnum = (*opGraph)->vexnum;
			arcnum = (*opGraph)->arcnum;
			if (LoadFromFile(fileName, **opGraph))
			{
				printf("成功\n");
			}
			else
			{
				printf("失败\n");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()

 //初始条件：图G不存在,V是图的顶点集，VR是图的关系集,arcWeight是权重集合；
 //操作结果：按V，VR和arcWeight和的定义构造图G。
status CreateGraph(ALGraph &G, char * V, char * VR,int* arcWeight)
{
	//printf("%d", G.vexnum);
	G.kind = kind;
	if (G.vexnum>0)   //如果图已被创建，返回失败
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

//初始条件：图G存在。
//操作结果：销毁图G。
status DestroyGraph(ALGraph &G)
{
	pALGraph pG = &G;
	pArcNode p,pre;
	for (int i = 0; i < G.vexnum; i++)             //遍历所有头结点
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
	free(pG);                   //释放G所指的头结点数组的内存空间
	return OK;
}

//获取节点的Key
//初始条件：图G存在，u和G中的顶点具有相同特征；
//操作结果：若u在图G中存在，返回顶点u的位置信息，否则返回其它信息。
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

//获取节点的Value
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

//初始条件:图G存在，v是G的一个顶点, w是v的邻接顶点；
//操作结果:返回v的（相对于w）下一个邻接顶点，如果w是最后一个邻接顶点，返回“空”。
VNode * NextAdjVex(ALGraph & G,Key v,Key w)
{
	assert(v<G.vexnum&&w<G.vexnum);//确保图中存在二者
	pArcNode pArc;
	pArc = G.vertices[v].firstarc;
	while (pArc!=NULL)
	{
		if (pArc->adjvex == w)
		{
			if (pArc->nextarc != NULL)//w无下一个邻接节点
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
	return NULL;//未找到节点w
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

//初始条件：图G存在，v和G中的顶点具有相同特征(属于同一类型)。
//操作结果：在图G中增加新顶点v。
status InsertVex(ALGraph & G, VertexType v)
{
	G.vertices[G.vexnum].data = v;
	G.vertices[G.vexnum].key = G.vexnum;
	G.vertices[G.vexnum].firstarc = NULL;
	printf("插入节点Key=%d,value=%c\n", G.vertices[G.vexnum].key, G.vertices[G.vexnum].data);
	G.vexnum++;
	return OK;
}


//初始条件：图G存在，v是G的一个顶点。
//操作结果：根据图的类型 在图G中删除顶点v和与v相关的弧。
status DeleteVex(ALGraph & G, VertexType v)
{
	int key=0;
	if ((key = LocateVex(G, v)) == NOTFOUND)//判断当前点是否在图中
	{
		return ERROR;
	}
	pArcNode cur=NULL;
	for (cur = G.vertices[key].firstarc; cur!=NULL; cur = cur->nextarc) //删除以v为弧尾的弧 删除v出度
	{
		free(cur);
		G.arcnum--;
	}
	for (int i = key; i < G.vexnum; i++)				//v之后的节点向前移动
	{
		G.vertices[i] = G.vertices[i + 1];
	}
	for (int i = 0; i < G.vexnum; i++)					//删除以v为弧头的弧，并修正其他弧指向的顶点位置
	{
		if ((cur = G.vertices[i].firstarc)==NULL)		//如果没有关联的弧 当前节点没有出度
		{
			continue;
		}
		if (cur->adjvex == key)							//如果顶点的第一条弧指向v
		{
			G.vertices[i].firstarc = cur->nextarc;
			free(cur);
			cur = G.vertices[i].firstarc;
			G.arcnum--;
		}
		for (; cur!=NULL; cur = cur->nextarc)			//其他情况
		{
			if (cur->adjvex >key)						//所有节点的编号减1
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

//初始条件：图G存在，v、w是G的顶点Value,arcW为边权。
//操作结果：在图G中增加弧<v, w>
status InsertArc(ALGraph & G, VertexType v, VertexType w,InfoType arcW)
{
	int kind = G.kind;
	pArcNode vwArc = NULL, wvArc = NULL;
	int s = isExistedArcByValue(G, v, w, vwArc, wvArc);
	if (s != 0)
	{
		if (kind == 0 || kind == 2)//0 2无向
		{
			printf("二者之间存在弧!\n");
			return ERROR;
		}
		else
		{
			if (s==1)
			{
				printf("二者之间存在弧!\n");
				return ERROR;
			}
		}
	}
	int vKey=-1, wKey=-1;
	if (((vKey = GetKeyByValue(G, v)) == NOTFOUND) || ((wKey = GetKeyByValue(G, w)) == NOTFOUND))     //没找到v或w，返回错误
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
		//输出插入弧的信息
		printf("插入弧%d(%c)->%d(%c)", vKey, v, wKey, w);
		if (kind == 2 || kind == 3)//2 3有权
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
		printf("插入弧%d(%c)->%d(%c)", vKey, v, wKey, w);
		if (kind == 2 || kind == 3)//2 3有权
		{
			printf("\t%d\n", arcW);
		}
		else
		{
			printf("\n");
		}
	}
	if (kind == 0 || kind == 2)//0 2 无向
	{
		pArc = G.vertices[wKey].firstarc;
		ArcNode *arc2 = (ArcNode *)malloc(sizeof(ArcNode));
		if (pArc == NULL)
		{
			G.vertices[wKey].firstarc = arc2;
			arc2->info = arcW;										//此处需处理info
			arc2->adjvex = vKey;
			arc2->nextarc = NULL;
			printf("插入弧%d(%c)->%d(%c)", wKey, w, vKey, v);
			if (kind == 2)//2有权
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
			arc2->info = arcW;										//此处需处理info
			arc2->adjvex = vKey;
			arc2->nextarc = NULL;
			printf("插入弧%d(%c)->%d(%c)", wKey, w, vKey, v);
			if (kind == 2)//2有权
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

//初始条件：图G存在，v、w是G的顶点。
//操作结果：无向图：在图G中删除弧<v, w> <w,v>
//			有方图：在图G中弧<v, w> 
//			若二者之间不存在弧 return ERROR
status DeleteArc(ALGraph &G, VertexType v, VertexType w)
{
	int kind = G.kind;
	pArcNode vwArc=NULL, wvArc=NULL;
	int s=isExistedArcByValue(G, v, w, vwArc, wvArc);
	if (s== 0)//二者之间无弧
	{
		printf("二者之间无弧\n");
		return ERROR;
	}
	else//二者存在弧
	{
		if (kind == 0 || kind == 2)	//无向图
		{
			if (s != 3)
			{
				printf("无向图中存在单向弧，错误！\n");
				return ERROR;
			}
		}
		if (kind == 1 || kind == 3)	//有向图
		{
			if (s != 1&&s!=3)
			{
				printf("该弧不存在！\n");
			}	
		}
	}
	int vKey, wKey;
	if (((vKey = GetKeyByValue(G, v)) == NOTFOUND) || ((wKey = GetKeyByValue(G, w)) == NOTFOUND))     //没找到v或w，返回错误
	{
		return ERROR;
	}
	//删除 
	//有向图
	pArcNode pArc = G.vertices[vKey].firstarc;
	if (pArc ==vwArc)		//为第一个弧节点
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
	if (kind == 0 || kind == 2)	//无向图另外删除wv
	{
		pArcNode pArc = G.vertices[wKey].firstarc;
		if (pArc == wvArc)		//为第一个弧节点
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

//节点深度优先遍历函数
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

//初始条件：图G存在。
//操作结果：对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函
//          数printf访问一次，且仅访问一次。
void DFSTraverse(ALGraph G, void(*visit)(pVNode N))
{
	int visited[MAX_VERTEX_NUM] = { 0 };    //存储是否访问过的信息
	for (int i = 0; i < G.vexnum; i++)      //对每个顶点进行深度优先遍历
	{
		if (!visited[i])
		{
			DFS(G, i, visited,visit);
		}
	}
}

//初始条件：图G存在。
//操作结果：对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函
//          数visit访问一次，且仅访问一次。
void BFSTraverse(ALGraph G, void(*visit)(pVNode N))
{
	int visited[MAX_VERTEX_NUM] = { 0 };    //存储是否访问过
	int queue[MAX_VERTEX_NUM] = { 0 };		//使用队列存储访问访问信息
	int head = 0, rear = 0;
	for (int v = 0; v < G.vexnum; v++)      //对每个顶点进行广度优先遍历
	{
		if (visited[v])     //如果已经遍历过，跳过
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

//初始条件：图G存在
//操作结果：显示图中的信息
void ShowVexArc(ALGraph G)
{
	kind = G.kind;
	printf("顶点为：\n");
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("%c ", G.vertices[i].data);
	}
	printf("\n弧为：\n");
	for (int i = 0; i < G.vexnum; i++)
	{
		for (ArcNode *arc = G.vertices[i].firstarc; arc!=NULL; arc = arc->nextarc)
		{
			printf("%d(%c)->%d(%c)", LocateVex(G,G.vertices[i].data), G.vertices[i].data, LocateVex(G, G.vertices[arc->adjvex].data), G.vertices[arc->adjvex].data);
			if (kind == 2 || kind == 3)//2 3有权
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
		printf("图的种类为无向图\n");
		break;
	case 1:
		printf("图的种类为有向图\n");
		break;
	case 2:
		printf("图的种类为无向网\n");
		break;
	case 3:
		printf("图的种类为有向网\n");
		break;
	default:
		break;
	}
	printf("图的名称为%s。\n", G.name);
	printf("顶点总数为%d，弧总数为%d。\n", G.vexnum, G.arcnum);
	//输出邻接表
	printf("----------------以下为临接表--------------------\n");
	for (int i = 0; i < G.vexnum; i++)
	{
		bool first = true;
		printf("%c", G.vertices[i].data);
		for (ArcNode *arc = G.vertices[i].firstarc; arc != NULL; arc = arc->nextarc)
		{
			printf("-->");
			VertexType arcHeadValue = G.vertices[arc->adjvex].data;
			if (kind == 2 || kind == 3)//2 3有权
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


//判断二者之间是否存在弧
//Input:G,V,W  传入二者的值
//Output：0二者之间无
//		  1二者之间vw
//		  2二者之间wv
//		  3二者之间vwwv
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
	//遍历以v为弧尾的节点
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
	//遍历以w为弧尾的节点
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


//初始条件：图G存在
//操作结果：保存图到文件 若文件打开失败 则返回ERROR
status SaveToFile(char * filename, ALGraph &G)
{
	FILE  *fp;
	printf("请输入文件名: ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("文件写入错误\n ");
		return ERROR;
	}
	printf("节点数：%d", G.vexnum);
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

//初始条件：图G存在
//操作结果：从文件读取 若文件打开失败 则返回ERROR
status LoadFromFile(char * filename, ALGraph &G)
{
	FILE  *fp;
	printf("请输入文件名: ");
	scanf("%s", filename);
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("文件读取错误\n ");
		return ERROR;
	}

	pALGraph pG = &G;
	kind = G.kind;
	fread(pG, sizeof(ALGraph), 1, fp);
	fread(pG->name, sizeof(char), 20, fp);
	fread(pG->vertices, sizeof(VNode),20, fp);
	for (int i = 0; i < G.vexnum; i++)
	{
		printf("节点%d:%c\n",i, G.vertices[i].data);
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
			printf("插入弧%d(%c)->%d(%c)", i, G.vertices[i].data, pArc->adjvex, G.vertices[pArc->adjvex].data);
			if (kind == 2 || kind == 3)//2 3有权
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
				pArc = (pArcNode)malloc(sizeof(ArcNode));//重新分配内存
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
			pArc = (pArcNode)malloc(sizeof(ArcNode));//重新分配内存
		}		

	}
	fclose(fp);
	return OK;
}
