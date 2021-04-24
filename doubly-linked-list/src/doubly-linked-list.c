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
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
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
	setvbuf(stdout, NULL, _IONBF, 0); // Windows 용 Eclipse의 Console창 글자 안 나오는 오류 수정
	setvbuf(stderr, NULL, _IONBF, 0);
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("---------------------[김동원] [2020039023]-------------------------\n");
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
		freeList(*h); //초기화를 위해 헤드포인터를 초기화시켜 리스트를 비워준다
	}
	*h = (headNode*)malloc(sizeof(headNode)); //리스트가 비어있으므로 리스트를 가리킬 헤드를 동적할당해준다
	(*h)->first = NULL; //리스트가 비어있는상태로 헤드포인터를 초기화해 준다
	return 1;
}

int freeList(headNode* h){
	listNode* node = h->first; //노드가 헤드를 가리키도록 한다
	listNode* llink; //노드의 llink를 가리키게 할 포인터
	while(node!=NULL) {
		llink=node; //llink에 node의 위치 할당 (메모리 해제할 리스트의 주소)
		node=node->rlink; //노드를 옮겨가며 리스트 탐색
		free(llink); //메모리 해제
	}
	free(node); //리스트를 불러왔던 헤드의 메모리도 해제
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
 * list에 key에 대한 노드하나를 추가
 */

int insertLast(headNode* h, int key) {
	listNode* NewNode=(listNode*)malloc(sizeof(listNode)); //삽입할 새로운 노드 생성
	listNode* node; //리스트를 둘러보기 위한 노드
	node=h->first; //node에 리스트의 주소를 넣어줌
	NewNode->key=key; //새로운 노드의 키에 입력받은키 할당
	if(h->first==NULL){ //헤드가 비어있으면 리스트의 첫 노드로 NewNode 삽입
		h->first=NewNode;
		NewNode->rlink=NULL; //NewNode의 rlink를 비워 다음 노드가 올 수 있도록 함
	}
	else { //헤드 뒤로 리스트가 존재하는 경우
		while(node->rlink!=NULL){ //노드를 rlink로 옮겨주면서 리스트 탐색 (리스트 끝까지)
			node=node->rlink;
		}
		node->rlink=NewNode; //리스트의 마지막 노드의 rlink에 NewNode를 삽입
		NewNode->llink=node; //위와 동일하게 NewNode의 llink에 노드의 위치를 넣어 이어줌
		NewNode->rlink=NULL; //다음 노드를 삽입할 수 있도록 노드를 비워줌
	}
	return 0;
}



/**
 * list의 마지막 노드 삭제

int deleteLast(headNode* h) {


	return 0;
}*/



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* NewNode=(listNode*)malloc(sizeof(listNode)); //삽입할 새로운 노드 생성
	NewNode->key=key; //새로운 노드의 키에 입력받은키 할당
	if(h->first==NULL){ //헤드가 비어있으면 리스트의 첫 노드로 NewNode 삽입
		h->first=NewNode;
		NewNode->rlink=NULL; //NewNode의 rlink를 비워 다음 노드가 올 수 있도록 함
	}
	else{ //헤드 뒤로 리스트가 존재하는 경우
		h->first->llink=NewNode; //헤드의 첫 노드의 링크에 NewNode 주소 저장
		NewNode->rlink=h->first; //NewNode의 rlink에 헤드의 주소 저장
		h->first=NewNode; //헤드와 NewNode 연결
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */

int deleteFirst(headNode* h) {
	if(h->first==NULL){
		return 0;
	} //리스트가 비어있을 때 전처리
	else{ //리스트가 비어있지 않을 때
		listNode* node; //리스트를 둘러보기 위한 노드
		node=h->first; //node에 리스트의 주소를 넣어줌
		h->first=node->rlink; //리스트의 시작을 노드의 rlink로 옮겨주면서 첫 번째 노드를 떼어내줌
	}
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치

int invertList(headNode* h) {

	return 0;
}*/



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {

	return 0;
}*/


/**
 * list에서 key에 대한 노드 삭제
 */
/*int deleteNode(headNode* h, int key) {

	return 1;
}*/


