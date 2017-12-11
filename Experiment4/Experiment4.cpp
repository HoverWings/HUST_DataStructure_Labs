// line table base on linked list with head node
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Assert.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define EMPTYLIST -3

#define DEFAULTDATA -101

typedef int status;
typedef int ElemType; //数据元素类型定义



#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10


typedef struct LNode // sequence list node definition
{
	ElemType data;
	LNode *next;
}*Link, *Position, LNode;

typedef struct
{
	Link head, tail;
	int len;
}LinkList;


status MakeNode(Link&p, ElemType e)
{
	p = (Link)malloc(sizeof(LNode));
	if (p == NULL)
	{
		return false;
	}
	p->data = e;
	p->next = NULL;
	return true;
}

void FreeNode(Link&p)
{
	free(p);
}

status IntiaList(LinkList & L);
status DestroyList(LinkList & L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType & e);
status LocateElem(LinkList L, ElemType e); //简化过
status PriorElem(LinkList L, ElemType cur, ElemType & pre_e);
status NextElem(LinkList L, ElemType cur, ElemType & next_e);
status ListInsert(LinkList & L, int i, ElemType e);
status ListDelete(LinkList & L, int i, ElemType & e);
status ListTraverse(LinkList L, void(*visit)(Position p));
status LoadFromFile(char * filename, LinkList & L);
status SaveToFile(char * filename, LinkList  L);

void visit(Position p);
bool isExisted(LinkList &L);
bool isInitedButEmpty(LinkList &L);


//int main()
//{
//	//declare 3 LinkList
//	LinkList L1;
//	L1.head = NULL;
//	L1.tail = NULL;
//	LinkList L2;
//	L2.head = NULL;
//	L2.tail = NULL;
//	LinkList L3;
//	L3.head = NULL;
//	L3.tail = NULL;
//
//	LinkList* pL = NULL;//use it as a temp pointer which point to 1/2/3
//						//LinkList L;
//
//
//	int op = 1;
//	char fileName[20];
//	ElemType  e;
//	int ans;
//	int opIndex;// the LinkListNum to operate
//	bool errorNum = false;
//
//	while (op)
//	{
//		system("cls");
//		printf("\n\n");
//		printf("      Menu for Linear Table On Sequence Structure \n");
//		printf("------------------------------------------------------\n");
//		printf("    	  1. IntiaList       8. PriorElem\n");
//		printf("    	  2. DestroyList     9. NextElem\n");
//		printf("    	  3. ClearList       10. ListInsert\n");
//		printf("    	  4. ListEmpty       11. ListDelete\n");
//		printf("    	  5. ListLength      12. ListTraverse\n");
//		printf("    	  6. GetElem         13. SaveToFile\n");
//		printf("    	  7. LocateElem      14. LoadFromFile\n");
//		printf("    	  0. Exit\n");
//		printf("------------------------------------------------------\n");
//		printf("    请选择你的操作[0~14]:");
//		scanf("%d", &op);
//		switch (op)
//		{
//		case 1://1. IntiaList
//			printf("请输入你要初始化的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法初始化");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (isExisted(*pL))
//			{
//				printf("当前线性表已存在\n");
//				if (IntiaList(*pL) == OK)
//					printf("线性表%d初始化成功！\n", opIndex);
//				else
//					printf("线性表%d初始化失败！\n", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (IntiaList(*pL) == OK)
//				printf("线性表%d创建成功！\n", opIndex);
//			else
//				printf("线性表%d创建失败！\n", opIndex);
//			getchar(); getchar();
//			break;
//
//		case 2://2. DestroyList
//			printf("请输入你要销毁的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法销毁");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在,无法销毁", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (DestroyList(*pL) == OK)
//				printf("线性表%d删除成功！\n", opIndex);
//			else
//				printf("线性表%d删除失败！\n", opIndex);
//			getchar(); getchar();
//			break;
//
//		case 3:
//			printf("请输入你要清空的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (ClearList(*pL) == OK)
//				printf("线性表%d清空成功！\n", opIndex);
//			else
//				printf("线性表%d清空失败！\n", opIndex);
//			getchar(); getchar();
//			break;
//
//		case 4://4. ListEmpty
//			printf("请输入你要查询是否为空的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			if (ListEmpty(*pL) == TRUE)
//				printf("线性表%d为空！\n", opIndex);
//			else
//				printf("线性表%d非空！\n", opIndex);
//			getchar(); getchar();
//			break;
//
//		case 5://5. ListLength
//			printf("请输入你要获取长度的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			int length;
//			if ((length = ListLength(*pL)) >= 0)
//				printf("此线性表为长度为%d！\n", length);
//			else
//				printf("无此线性表！\n");
//			getchar(); getchar();
//			break;
//
//		case 6://6. GetElem
//			printf("请输入你要获取长度的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (ListEmpty(*pL))
//			{
//				printf("线性表%d为空无法操作", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			printf("请输入要获取的元素位置：\n");
//			int i;
//			scanf("%d", &i);
//			if (GetElem(*pL, i, e))
//				printf("此线性表该位置的元素为:%d\n", e);
//			else
//				printf("输入有误！\n");
//			getchar(); getchar();
//			break;
//
//		case 7://7. LocateElem
//			printf("请输入你要获取长度的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (ListEmpty(*pL))
//			{
//				printf("线性表%d为空无法操作", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			printf("请输入你要获取的元素：\n");
//			scanf("%d", &e);
//			if ((ans = LocateElem(*pL, e)))
//				printf("此线性表该元素的位置为:%d\n", ans);
//			else
//				printf("没有此元素！\n");
//			getchar(); getchar();
//			break;
//
//		case 8://8. PriorElem
//			printf("请输入你要获取前驱的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (ListEmpty(*pL))
//			{
//				printf("线性表%d为空无法操作", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			printf("请输入你要获取前一个元素的元素：\n");
//			scanf("%d", &e);
//			if (PriorElem(*pL, e, ans))
//			{
//				printf("此线性表该元素的前一个元素为:%d\n", ans);
//			}
//			else
//			{
//				printf("没有此元素！\n");
//			}
//			getchar(); getchar();
//			break;
//
//		case 9://9. NextElem
//			printf("请输入你要获取后继的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (ListEmpty(*pL))
//			{
//				printf("线性表%d为空无法操作", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			printf("请输入你要获取后一个元素的元素：\n");
//			scanf("%d", &e);
//			if (NextElem(*pL, e, ans))
//			{
//				printf("此线性表该元素的后一个元素为:%d\n", ans);
//			}
//			else
//			{
//				printf("没有此元素！\n");
//			}
//			getchar(); getchar();
//			break;
//
//		case 10://10. ListInsert
//			printf("请输入你要插入的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			printf("请输入你要插入元素的位置：\n");
//			scanf("%d", &i);
//			printf("请输入你要插入的元素：\n");
//			scanf("%d", &e);
//			//先满足初始条件
//			/*printf("%d", ListLength(*pL));
//			printf("%d",(*pL).len);*/
//			if (1 <= i&&i <= (ListLength(*pL) + 1))
//			{
//			}
//			else
//			{
//				printf("输入插入位置有误");
//				getchar(); getchar();
//				break;
//			}
//
//			if (ListInsert(*pL, i, e))
//				printf("已成功插入！\n");
//			else
//				printf("输入有误！\n");
//			getchar(); getchar();
//			break;
//
//
//		case 11://11. ListDelete
//			printf("请输入你要删除操作的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//			if (ListEmpty(*pL))
//			{
//				printf("线性表%d为空无法操作", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//			printf("请输入你要删除元素的位置：\n");
//			scanf("%d", &i);
//			if (1 <= i&&i <= ListLength(*pL))
//			{
//			}
//			else
//			{
//				printf("输入位置有误");
//				getchar(); getchar();
//				break;
//			}
//			if (ListDelete(*pL, i, e))
//			{
//				printf("已成功删除！元素为：%d\n", e);
//			}
//			else
//			{
//				printf("输入有误！\n");
//			}
//			getchar(); getchar();
//			break;
//
//
//		case 12://12. ListTraverse 
//				//void *visitp = &visit;
//			printf("请输入你要遍历的表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//			if (!isExisted(*pL))
//			{
//				printf("线性表%d不存在", opIndex);
//				getchar(); getchar();
//				break;
//			}
//
//
//			if (!ListTraverse(*pL, visit)) printf("线性表是表不存在！\n");
//			getchar(); getchar();
//			break;
//
//
//		case 13:
//			printf("请输入你要保存的线性表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//
//			if (SaveToFile(fileName, *pL))
//			{
//				printf("已成功保存至文件!");
//			}
//			else
//			{
//				printf("保存失败！");
//			}
//			getchar(); getchar();
//			break;
//
//
//		case 14://14. LoadFromFile
//			printf("请输入你要保存的线性表的编号(1/2/3):");
//			scanf("%d", &opIndex);
//			switch (opIndex)
//			{
//			case 1:
//				pL = &L1;
//				break;
//			case 2:
//				pL = &L2;
//				break;
//			case 3:
//				pL = &L3;
//				break;
//			default:
//				printf("你输入了错误的编号！！！无法操作");
//				getchar(); getchar();
//				errorNum = true;
//				break;
//			}
//			if (errorNum)
//			{
//				break;
//			}
//
//			printf("\n请输入要读取的文件名：\n");
//			scanf("%s", fileName);
//			if (LoadFromFile(fileName, *pL))
//			{
//				printf("已成功从文件读取!");
//			}
//			else
//			{
//				printf("读取失败！");
//			}
//			getchar(); getchar();
//			break;
//
//		case 0:
//			break;
//		}//end of switch
//	}//end of while
//	printf("欢迎下次再使用本系统！\n");
//}//end of main()



