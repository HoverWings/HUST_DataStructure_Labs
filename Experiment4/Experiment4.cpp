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
typedef int ElemType; //����Ԫ�����Ͷ���



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
status LocateElem(LinkList L, ElemType e); //�򻯹�
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


int main()
{
	//declare 3 LinkList
	LinkList L1;
	L1.head = NULL;
	L1.tail = NULL;
	LinkList L2;
	L2.head = NULL;
	L2.tail = NULL;
	LinkList L3;
	L3.head = NULL;
	L3.tail = NULL;

	LinkList* pL = NULL;//use it as a temp pointer which point to 1/2/3
						//LinkList L;


	int op = 1;
	char fileName[20];
	ElemType  e;
	int ans;
	int opIndex;// the LinkListNum to operate
	bool errorNum = false;

	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. IntiaList       8. PriorElem\n");
		printf("    	  2. DestroyList     9. NextElem\n");
		printf("    	  3. ClearList       10. ListInsert\n");
		printf("    	  4. ListEmpty       11. ListDelete\n");
		printf("    	  5. ListLength      12. ListTraverse\n");
		printf("    	  6. GetElem         13. SaveToFile\n");
		printf("    	  7. LocateElem      14. LoadFromFile\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~14]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1://1. IntiaList
			printf("��������Ҫ��ʼ���ı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷���ʼ��");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (isExisted(*pL))
			{
				printf("��ǰ���Ա��Ѵ���\n");
				if (IntiaList(*pL) == OK)
					printf("���Ա�%d��ʼ���ɹ���\n", opIndex);
				else
					printf("���Ա�%d��ʼ��ʧ�ܣ�\n", opIndex);
				getchar(); getchar();
				break;
			}
			if (IntiaList(*pL) == OK)
				printf("���Ա�%d�����ɹ���\n", opIndex);
			else
				printf("���Ա�%d����ʧ�ܣ�\n", opIndex);
			getchar(); getchar();
			break;

		case 2://2. DestroyList
			printf("��������Ҫ���ٵı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������,�޷�����", opIndex);
				getchar(); getchar();
				break;
			}
			if (DestroyList(*pL) == OK)
				printf("���Ա�%dɾ���ɹ���\n", opIndex);
			else
				printf("���Ա�%dɾ��ʧ�ܣ�\n", opIndex);
			getchar(); getchar();
			break;

		case 3:
			printf("��������Ҫ��յı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}
			if (ClearList(*pL) == OK)
				printf("���Ա�%d��ճɹ���\n", opIndex);
			else
				printf("���Ա�%d���ʧ�ܣ�\n", opIndex);
			getchar(); getchar();
			break;

		case 4://4. ListEmpty
			printf("��������Ҫ��ѯ�Ƿ�Ϊ�յı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}

			if (ListEmpty(*pL) == TRUE)
				printf("���Ա�%dΪ�գ�\n", opIndex);
			else
				printf("���Ա�%d�ǿգ�\n", opIndex);
			getchar(); getchar();
			break;

		case 5://5. ListLength
			printf("��������Ҫ��ȡ���ȵı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}

			int length;
			if ((length = ListLength(*pL)) >= 0)
				printf("�����Ա�Ϊ����Ϊ%d��\n", length);
			else
				printf("�޴����Ա�\n");
			getchar(); getchar();
			break;

		case 6://6. GetElem
			printf("��������Ҫ��ȡ���ȵı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}
			if (ListEmpty(*pL))
			{
				printf("���Ա�%dΪ���޷�����", opIndex);
				getchar(); getchar();
				break;
			}

			printf("������Ҫ��ȡ��Ԫ��λ�ã�\n");
			int i;
			scanf("%d", &i);
			if (GetElem(*pL, i, e))
				printf("�����Ա��λ�õ�Ԫ��Ϊ:%d\n", e);
			else
				printf("��������\n");
			getchar(); getchar();
			break;

		case 7://7. LocateElem
			printf("��������Ҫ��ȡ���ȵı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}
			if (ListEmpty(*pL))
			{
				printf("���Ա�%dΪ���޷�����", opIndex);
				getchar(); getchar();
				break;
			}

			printf("��������Ҫ��ȡ��Ԫ�أ�\n");
			scanf("%d", &e);
			if ((ans = LocateElem(*pL, e)))
				printf("�����Ա��Ԫ�ص�λ��Ϊ:%d\n", ans);
			else
				printf("û�д�Ԫ�أ�\n");
			getchar(); getchar();
			break;

		case 8://8. PriorElem
			printf("��������Ҫ��ȡǰ���ı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}
			if (ListEmpty(*pL))
			{
				printf("���Ա�%dΪ���޷�����", opIndex);
				getchar(); getchar();
				break;
			}

			printf("��������Ҫ��ȡǰһ��Ԫ�ص�Ԫ�أ�\n");
			scanf("%d", &e);
			if (PriorElem(*pL, e, ans))
			{
				printf("�����Ա��Ԫ�ص�ǰһ��Ԫ��Ϊ:%d\n", ans);
			}
			else
			{
				printf("û�д�Ԫ�أ�\n");
			}
			getchar(); getchar();
			break;

		case 9://9. NextElem
			printf("��������Ҫ��ȡ��̵ı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}
			if (ListEmpty(*pL))
			{
				printf("���Ա�%dΪ���޷�����", opIndex);
				getchar(); getchar();
				break;
			}

			printf("��������Ҫ��ȡ��һ��Ԫ�ص�Ԫ�أ�\n");
			scanf("%d", &e);
			if (NextElem(*pL, e, ans))
			{
				printf("�����Ա��Ԫ�صĺ�һ��Ԫ��Ϊ:%d\n", ans);
			}
			else
			{
				printf("û�д�Ԫ�أ�\n");
			}
			getchar(); getchar();
			break;

		case 10://10. ListInsert
			printf("��������Ҫ����ı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}

			printf("��������Ҫ����Ԫ�ص�λ�ã�\n");
			scanf("%d", &i);
			printf("��������Ҫ�����Ԫ�أ�\n");
			scanf("%d", &e);
			//�������ʼ����
			/*printf("%d", ListLength(*pL));
			printf("%d",(*pL).len);*/
			if (1 <= i&&i <= (ListLength(*pL) + 1))
			{
			}
			else
			{
				printf("�������λ������");
				getchar(); getchar();
				break;
			}

			if (ListInsert(*pL, i, e))
				printf("�ѳɹ����룡\n");
			else
				printf("��������\n");
			getchar(); getchar();
			break;


		case 11://11. ListDelete
			printf("��������Ҫɾ�������ı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}
			if (ListEmpty(*pL))
			{
				printf("���Ա�%dΪ���޷�����", opIndex);
				getchar(); getchar();
				break;
			}

			printf("��������Ҫɾ��Ԫ�ص�λ�ã�\n");
			scanf("%d", &i);
			if (1 <= i&&i <= ListLength(*pL))
			{
			}
			else
			{
				printf("����λ������");
				getchar(); getchar();
				break;
			}
			if (ListDelete(*pL, i, e))
			{
				printf("�ѳɹ�ɾ����Ԫ��Ϊ��%d\n", e);
			}
			else
			{
				printf("��������\n");
			}
			getchar(); getchar();
			break;


		case 12://12. ListTraverse 
				//void *visitp = &visit;
			printf("��������Ҫ�����ı�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}
			if (!isExisted(*pL))
			{
				printf("���Ա�%d������", opIndex);
				getchar(); getchar();
				break;
			}


			if (!ListTraverse(*pL, visit)) printf("���Ա��Ǳ����ڣ�\n");
			getchar(); getchar();
			break;


		case 13:
			printf("��������Ҫ��������Ա�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}

			if (SaveToFile(fileName, *pL))
			{
				printf("�ѳɹ��������ļ�!");
			}
			else
			{
				printf("����ʧ�ܣ�");
			}
			getchar(); getchar();
			break;


		case 14://14. LoadFromFile
			printf("��������Ҫ��������Ա�ı��(1/2/3):");
			scanf("%d", &opIndex);
			switch (opIndex)
			{
			case 1:
				pL = &L1;
				break;
			case 2:
				pL = &L2;
				break;
			case 3:
				pL = &L3;
				break;
			default:
				printf("�������˴���ı�ţ������޷�����");
				getchar(); getchar();
				errorNum = true;
				break;
			}
			if (errorNum)
			{
				break;
			}

			printf("\n������Ҫ��ȡ���ļ�����\n");
			scanf("%s", fileName);
			if (LoadFromFile(fileName, *pL))
			{
				printf("�ѳɹ����ļ���ȡ!");
			}
			else
			{
				printf("��ȡʧ�ܣ�");
			}
			getchar(); getchar();
			break;

		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()



bool isExisted(LinkList &L)
{
	if (L.head != NULL&&L.tail != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isInitedButEmpty(LinkList &L)
{
	if (L.head->data == DEFAULTDATA)
	{
		if (L.len == 0)
		{
			return true;
		}
		else
		{
			printf("��BUG��");
		}
	}
}


status IntiaList(LinkList & L)// now the first elem is empty
{
	if (L.head != NULL)
	{
		ClearList(L);
		return OK;
	}
	L.head = (Link)malloc(sizeof(LNode));
	L.tail = L.head;
	L.head->data = DEFAULTDATA;
	L.len = 0;
	return true;
}

status DestroyList(LinkList & L)
{
	if (L.head == L.tail)
	{
		free(L.head);
		//���������
		L.head = NULL;
		L.tail = NULL;
		L.len = 0;
		return OK;
	}
	else//traversal and release the whole list
	{
		Position p = L.head;
		while (p != L.tail)
		{
			Position t = p->next;
			free(p);
			p = t;
		}
		free(p);
		L.len = 0;
		L.head = NULL;
		L.tail = NULL;
		L.len = 0;
		return OK;
	}
}

status ClearList(LinkList & L)
{
	if (L.head == NULL)//the LinkList is no existed  ERROR!
	{
		exit(ERROR);
		return false;
	}
	assert(L.head != NULL);
	Position p = L.head;
	while (p != L.tail)
	{
		Position t = p->next;
		free(p);
		p = t;
	}
	free(p);
	L.len = 0; //the DEFAULTDATA is not the stored data
	L.tail = L.head;// with empty node
	L.head->data = DEFAULTDATA;
	return OK;
}

status ListEmpty(LinkList L)
{
	// linked list exists 
	if (L.len == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int ListLength(LinkList L)
{
	return L.len;
}

status GetElem(LinkList L, int i, ElemType & e)
{
	Position p = L.head;
	int index = 1;
	while (p&&index < i)
	{
		p == p->next;
		index++;
	}
	if (!p || index > i)
	{
		return ERROR;
	}
	e = p->data;
	return OK;
}

status LocateElem(LinkList L, ElemType e)
{
	int index = 1;
	Position p = L.head;
	for (index = 1; index <= L.len; index++)
	{
		if (p->data == e)
		{
			return index;//the index begin from 1
		}
	}
	return -1;
}

status PriorElem(LinkList L, ElemType cur, ElemType & pre_e)
{
	Position p = L.head;
	if (p->data == cur)
	{
		printf("���ǵ�һ���ڵ㣬û��ǰ��");
		return false;
	}
	int index = 1;
	pre_e = 0;
	ElemType pre_data = DEFAULTDATA;
	for (index = 1; index <= L.len; index++)
	{
		if (p->data == cur)
		{
			pre_e = pre_data;
			return true;
		}
		pre_data = p->data;
		p = p->next;
	}
	return false;
}

status NextElem(LinkList L, ElemType cur, ElemType & next_e)
{
	if (L.tail->data == cur)
	{
		printf("�������һ���ڵ㣬û�к��");
		return false;
	}
	Position p = L.head;
	while (p != L.tail)
	{
		if (p->data = cur)
		{
			if ((p->next) != NULL)
			{
				next_e = p->next->data;
				return true;
			}
		}
	}
	return false;
}

status ListInsert(LinkList & L, int i, ElemType e)
{
	//process the init but empty linklist
	assert(L.head != NULL);

	if (L.head != NULL && L.head == L.tail && (L.head->data) == DEFAULTDATA)
	{
		if (i == 1)
		{
			Position p = L.head;
			p->data = e;
			L.len = 1;
			return true;
		}
		else
		{
			printf("���Ա�Ϊ�գ�������1������");
			return false;
		}
	}
	if (i == 1)
	{
		Position insertp;
		if (MakeNode(insertp, e))
		{
			insertp->next = L.head;
			L.head = insertp;
			L.len++;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (i == L.len + 1)
	{
		Position insertp;
		if (MakeNode(insertp, e))
		{
			insertp->next = NULL;
			L.tail->next = insertp;
			L.tail = insertp;
			L.len++;
			return true;
		}
		else
		{
			return false;
		}
	}
	int index = 1;
	Position p = L.head;
	for (index = 1; index < i - 1; i++)
	{
		p = p->next;
	}
	Position pre = p;
	p = p->next;
	Position insertp;
	if (MakeNode(insertp, e))
	{
		pre->next = insertp;
		insertp->next = p;
		L.len++;
		return true;
	}
	else
	{
		return false;
	}

}

status ListDelete(LinkList & L, int i, ElemType & e)
{
	if (L.len == 1 && i == 1)//�˴���Ҫ��������ֻ��һ���ڵ� ɾ����һ���ڵ�ĵ����
	{
		Position p = L.head;
		L.head = NULL;
		L.tail == NULL;
		L.len = 0;
		return true;
	}
	if (i == 1)
	{
		Position p = L.head;
		L.head = L.head->next;
		e = p->data;
		free(p);
		L.len--;
		return true;
	}
	if (i == L.len)//�������һ���ڵ�����
	{
		Position p = L.head;
		while (p->next != L.tail)
		{
			p = p->next;
		}
		Position pre = p;
		e = p->data;
		free(p);
		pre->next == NULL;
		L.tail = pre;
		L.len--;
		return true;
	}
	int index = 1;
	Position p = L.head;
	for (index = 1; index < i - 1; i++)
	{
		p = p->next;
	}
	Position pre = p;
	p = p->next;
	pre->next = p->next;
	e = p->data;
	free(p);
	L.len--;
	return true;
}

void visit(Position p)
{
	printf("%d\t", p->data);
}

status ListTraverse(LinkList L, void(*visit)(Position p))
{
	if (ListEmpty(L))
	{
		printf("���Ա�Ϊ�գ��������Ϊ��");
		return true;
	}
	Position p = L.head;
	while (p != L.tail)
	{
		visit(p);
		p = p->next;
	}
	visit(p);
	return true;
}

status LoadFromFile(char * filename, LinkList & L)
{
	IntiaList(L);
	FILE  *fp;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("�ļ���ʧ��\n ");
		return ERROR;
	}
	Position p = L.head;
	ElemType t = DEFAULTDATA;
	bool isFirst = true;
	while (fread(&t, sizeof(ElemType), 1, fp))
	{
		if (isFirst)
		{
			L.head->data = t;
			L.len++;
			isFirst = false;
			continue;
		}
		Position insertp;
		if (MakeNode(insertp, t))
		{
			L.tail->next = insertp;
			L.tail = insertp;
			L.len++;
		}
		else
		{
			return false;
		}
	}
	fclose(fp);
	return true;
}

status SaveToFile(char * filename, LinkList L)
{
	FILE  *fp;
	printf("�������ļ���: ");
	scanf("%s", filename);

	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("�ļ�д�����\n ");
		return ERROR;
	}
	Position p = L.head;
	while (p != L.tail)
	{
		fwrite(&(p->data), sizeof(ElemType), 1, fp);
		p = p->next;
	}
	fwrite(&(p->data), sizeof(ElemType), 1, fp);
	fclose(fp);
	return true;
}


