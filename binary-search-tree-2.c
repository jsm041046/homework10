/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
    printf("[----- 2021041046 전설민 -----]"); //학번 이름 출력
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) { //ptr이 가르키는 노드가 존재할 경우
		recursiveInorder(ptr->left); //왼쪽 우선 탐색 함수 실행
		printf(" [%d] ", ptr->key); //ptr의 값 출력
		recursiveInorder(ptr->right); //오른쪽 탐색 함수 실행
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
    while(1) //break문이 나올 때 까지 무한반복
    {
        while(node != NULL) //node가 값을 가르키지 않을 때 까지 반복
        {
            push(node); //node를 스택에 삽입함
            node = node->left; //node를 왼쪽 자식을 가르키게 함
        }
        if(top != -1) //스택에 값이 존재할 경우
            node = pop(); //저장된 스택에서 꺼내옴
        else
            break;
        if(node != NULL)
            printf(" [%d] ", node->key); //node가 가르키는 원소가 존재할 경우 출력
        node = node->right; //node의 오른쪽 자식 접근
        //원리 : 루트부터 시작해 왼쪽 자식들은 모두 스택에 담고, 오른쪽 자식으로 이동하면서 해당 과정을 반복함으로 왼쪽 자식은 모두 스택에 담기고, 
        //오른쪽 자식은 왼쪽 자식이 담긴 스택을 먼저 꺼내서 탐색한 후 탐색하게 하는 원리다
    }
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
    front = rear = 0;
    if(ptr == NULL) return; //ptr에 노드가 없을 경우 즉시 반환
    enQueue(ptr); //큐에 ptr이 가르키는 노드 삽입
    while(front != rear) //큐가 빌 때 까지
    {
        ptr = deQueue(); //큐에서 ptr로 노드를 꺼내옴
        if(ptr != NULL) //ptr이 존재할 경우
        {
            printf(" [%d] ",ptr->key); //ptr출력
            if(ptr->left != NULL)
                enQueue(ptr->left); //왼쪽 자식이 있을 경우 큐에 삽입
            if(ptr->right != NULL)
                enQueue(ptr->right); //오른쪽 자식이 있을 경우 큐에 삽입
        }
        //원리 : 큐에서 원소를 꺼낸 후 자식 노드를 모두 큐에 추가, 이 과정을 큐가 빌 때 까지 반복한다
    }
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
    Node* ptr = head->left; //삭제할 노드를 찾는 포인터
    Node* prev = NULL; //삭제할 노드의 부모 포인터
    while(ptr != NULL && ptr->key != key) //ptr이 가르킬 범위를 벗어나거나, 찾는 값을 가르킬 때 까지 반복
    {
        prev = ptr;
        if(ptr->key > key)
            ptr = ptr->left; //ptr의 원소값이 찾는 값보다 클 경우 왼쪽 자식으로 이동
        else if(ptr->key < key)
            ptr = ptr->right; //ptr의 원소값이 찾는 값보다 작을 경우 오른쪽 자식으로 이동
    }
    if(ptr == NULL)
    {
        printf("can't find key\n"); //ptr이 NULL일 경우 못찾았음을 알림
        return 0;
    }
        
    if(ptr->left == NULL && ptr->right == NULL) //case1 : 리프 노드 삭제
    {
        if(prev != NULL) //부모가 있을 경우
        {
            if(prev->key > key)
                prev->left = NULL;
            else if(prev->key < key)
                prev->right = NULL;
            //부모와 삭제 대상의 원소의 크기를 비교하여 제거할 부모노드의 링크 방향 결정
        } else {
            head->left = NULL; //부모가 없을 경우 루트노드임을 의미하므로 head노드를 NULL로 바꾼다
        }
        free(ptr); //해당 노드 제거
    } else if(ptr->right == NULL) { //case2 : 둘 중 하나만 자식노드가 있을 경우(왼쪽)
        if(prev != NULL) //부모가 있을 경우
        {
            if(prev->key > key)
                prev->left = ptr->left;
            else if(prev->key < key)
                prev->right = ptr->left;
            //부모와 삭제 대상의 원소의 크기를 비교하여 바꿀 부모노드의 링크 위치 결정
        } else {
            head->left = ptr->left; //부모가 없을 경우 루트노드임을 의미하므로 head노드를 NULL로 바꾼다
        }
        free(ptr); //해당 노드 제거
    } else if(ptr->left == NULL) { //case2 : 둘 중 하나만 자식노드가 있을 경우(오른쪽)
        if(prev != NULL) //부모가 있을 경우
        {
            if(prev->key > key)
                prev->left = ptr->right;
            else if(prev->key < key)
                prev->right = ptr->right;
            //부모와 삭제 대상의 원소의 크기를 비교하여 바꿀 부모노드의 링크 위치 결정
        } else {
            head->left = ptr->right; //부모가 없을 경우 루트노드임을 의미하므로 head노드를 NULL로 바꾼다
        }
        free(ptr); //해당 노드 제거
    } else { //case3 : 둘다 자식 노드가 있을 경우
        Node* ptr2 = ptr->left; //왼쪽 노드를 가져오는 것을 우선시
        prev = ptr;
        while(ptr2->right != NULL)
        {
            prev = ptr2; //부모 노드의 위치 변경
            ptr2 = ptr2->right;
        }
        //ptr2는 ptr의 왼쪽에 있는 노드 중 가장 큰 노드를 가르킴
        ptr->key = ptr2->key; //ptr에 ptr2의 값을 대입
        if(prev == ptr)
            prev->left = NULL; //prev == ptr이 의미하는 것 => ptr2는 prev의 왼쪽에 있는 리프노드다 따라서 삭제할 경우 ptr의 왼쪽엔 아무것도 남지 않는다
        else
            prev->right = NULL; //prev != ptr이 의미하는 것 => ptr2는 prev의 오른쪽에 있는 리프노드다
        free(ptr2); //값을 가져온 노드 제거
    }
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
    if(top == -1) //top이 -1일 가르킬 경우 스택이 빈 것임
    {
        printf("Stack is Empty\n");
        return NULL;
    }
    Node* temp = stack[top]; //stack[top]을 즉시 반환해버리면 함수가 끝나므로 임시로 저장하는 포인터 temp 선언 후 대입
    top -= 1; //top을 1만큼 낮춤
    return temp; //temp를 반환
}

void push(Node* aNode)
{
    if(top + 1 >= MAX_STACK_SIZE) //top이 다음에 가야할 위치가 원소의 최대한도에 도달할 경우 스택이 꽉 찬 것임
    {
        printf("Stack is Full\n");
        return;
    }
    top += 1; //top을 1만큼 추가
    stack[top] = aNode; //top에다가 aNode원소를 삽입
}



Node* deQueue()
{
    if(rear == front) //rear == front는 큐가 빔을 의미한다
    {
        printf("Queue is Empty\n");
        return NULL;
    }
    front = (front + 1) % MAX_QUEUE_SIZE; //front를 원형큐의 다음칸으로 옮김
    return queue[front]; //옮겨진 front에 위치한 원소를 반환
}

void enQueue(Node* aNode)
{
    if((rear + 1) % MAX_QUEUE_SIZE == front) //rear가 가야할 칸이 front일 경우 큐가 꽉 찼음을 의미한다(front는 원소가 들어갈 수 없음)
    {
        printf("Queue is Full\n");
        return;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE; //rear를 원형큐의 다음칸으로 옮김
    queue[rear] = aNode; //옮겨진 rear에 원소를 삽입
}

void printStack()
{
    for(int i = top;i > -1;i--)
    {
        printf(" [%d] ",stack[i]);
    }
}



