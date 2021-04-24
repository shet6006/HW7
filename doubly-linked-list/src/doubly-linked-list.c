/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	setvbuf(stdout, NULL, _IONBF, 0); // Windows �� Eclipse�� Consoleâ ���� �� ������ ���� ����
	setvbuf(stderr, NULL, _IONBF, 0);
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("---------------------[�赿��] [2020039023]-------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			//insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			//deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			//deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			//invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	if(*h!=NULL){
		freeList(*h); //�ʱ�ȭ�� ���� ��������͸� �ʱ�ȭ���� ����Ʈ�� ����ش�
	}
	*h = (headNode*)malloc(sizeof(headNode)); //����Ʈ�� ��������Ƿ� ����Ʈ�� ����ų ��带 �����Ҵ����ش�
	(*h)->first = NULL; //����Ʈ�� ����ִ»��·� ��������͸� �ʱ�ȭ�� �ش�
	return 1;
}

int freeList(headNode* h){
	listNode* node = h->first; //��尡 ��带 ����Ű���� �Ѵ�
	listNode* llink; //����� llink�� ����Ű�� �� ������
	while(node!=NULL) {
		llink=node; //llink�� node�� ��ġ �Ҵ� (�޸� ������ ����Ʈ�� �ּ�)
		node=node->rlink; //��带 �Űܰ��� ����Ʈ Ž��
		free(llink); //�޸� ����
	}
	free(node); //����Ʈ�� �ҷ��Դ� ����� �޸𸮵� ����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */

int insertLast(headNode* h, int key) {
	listNode* NewNode=(listNode*)malloc(sizeof(listNode)); //������ ���ο� ��� ����
	listNode* node; //����Ʈ�� �ѷ����� ���� ���
	node=h->first; //node�� ����Ʈ�� �ּҸ� �־���
	NewNode->key=key; //���ο� ����� Ű�� �Է¹���Ű �Ҵ�
	if(h->first==NULL){ //��尡 ��������� ����Ʈ�� ù ���� NewNode ����
		h->first=NewNode;
		NewNode->rlink=NULL; //NewNode�� rlink�� ��� ���� ��尡 �� �� �ֵ��� ��
	}
	else { //��� �ڷ� ����Ʈ�� �����ϴ� ���
		while(node->rlink!=NULL){ //��带 rlink�� �Ű��ָ鼭 ����Ʈ Ž�� (����Ʈ ������)
			node=node->rlink;
		}
		node->rlink=NewNode; //����Ʈ�� ������ ����� rlink�� NewNode�� ����
		NewNode->llink=node; //���� �����ϰ� NewNode�� llink�� ����� ��ġ�� �־� �̾���
		NewNode->rlink=NULL; //���� ��带 ������ �� �ֵ��� ��带 �����
	}
	return 0;
}



/**
 * list�� ������ ��� ����

int deleteLast(headNode* h) {


	return 0;
}*/



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode* NewNode=(listNode*)malloc(sizeof(listNode)); //������ ���ο� ��� ����
	NewNode->key=key; //���ο� ����� Ű�� �Է¹���Ű �Ҵ�
	if(h->first==NULL){ //��尡 ��������� ����Ʈ�� ù ���� NewNode ����
		h->first=NewNode;
		NewNode->rlink=NULL; //NewNode�� rlink�� ��� ���� ��尡 �� �� �ֵ��� ��
	}
	else{ //��� �ڷ� ����Ʈ�� �����ϴ� ���
		h->first->llink=NewNode; //����� ù ����� ��ũ�� NewNode �ּ� ����
		NewNode->rlink=h->first; //NewNode�� rlink�� ����� �ּ� ����
		h->first=NewNode; //���� NewNode ����
	}
	return 0;
}

/**
 * list�� ù��° ��� ����
 */

int deleteFirst(headNode* h) {
	if(h->first==NULL){
		return 0;
	} //����Ʈ�� ������� �� ��ó��
	else{ //����Ʈ�� ������� ���� ��
		listNode* node; //����Ʈ�� �ѷ����� ���� ���
		node=h->first; //node�� ����Ʈ�� �ּҸ� �־���
		h->first=node->rlink; //����Ʈ�� ������ ����� rlink�� �Ű��ָ鼭 ù ��° ��带 �����
	}
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ

int invertList(headNode* h) {

	return 0;
}*/



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(headNode* h, int key) {

	return 0;
}*/


/**
 * list���� key�� ���� ��� ����
 */
/*int deleteNode(headNode* h, int key) {

	return 1;
}*/


