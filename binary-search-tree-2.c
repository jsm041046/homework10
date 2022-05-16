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
    printf("[----- 2021041046 ������ -----]"); //�й� �̸� ���
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
	if(ptr) { //ptr�� ����Ű�� ��尡 ������ ���
		recursiveInorder(ptr->left); //���� �켱 Ž�� �Լ� ����
		printf(" [%d] ", ptr->key); //ptr�� �� ���
		recursiveInorder(ptr->right); //������ Ž�� �Լ� ����
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
    while(1) //break���� ���� �� ���� ���ѹݺ�
    {
        while(node != NULL) //node�� ���� ����Ű�� ���� �� ���� �ݺ�
        {
            push(node); //node�� ���ÿ� ������
            node = node->left; //node�� ���� �ڽ��� ����Ű�� ��
        }
        if(top != -1) //���ÿ� ���� ������ ���
            node = pop(); //����� ���ÿ��� ������
        else
            break;
        if(node != NULL)
            printf(" [%d] ", node->key); //node�� ����Ű�� ���Ұ� ������ ��� ���
        node = node->right; //node�� ������ �ڽ� ����
        //���� : ��Ʈ���� ������ ���� �ڽĵ��� ��� ���ÿ� ���, ������ �ڽ����� �̵��ϸ鼭 �ش� ������ �ݺ������� ���� �ڽ��� ��� ���ÿ� ����, 
        //������ �ڽ��� ���� �ڽ��� ��� ������ ���� ������ Ž���� �� Ž���ϰ� �ϴ� ������
    }
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
    front = rear = 0;
    if(ptr == NULL) return; //ptr�� ��尡 ���� ��� ��� ��ȯ
    enQueue(ptr); //ť�� ptr�� ����Ű�� ��� ����
    while(front != rear) //ť�� �� �� ����
    {
        ptr = deQueue(); //ť���� ptr�� ��带 ������
        if(ptr != NULL) //ptr�� ������ ���
        {
            printf(" [%d] ",ptr->key); //ptr���
            if(ptr->left != NULL)
                enQueue(ptr->left); //���� �ڽ��� ���� ��� ť�� ����
            if(ptr->right != NULL)
                enQueue(ptr->right); //������ �ڽ��� ���� ��� ť�� ����
        }
        //���� : ť���� ���Ҹ� ���� �� �ڽ� ��带 ��� ť�� �߰�, �� ������ ť�� �� �� ���� �ݺ��Ѵ�
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
    Node* ptr = head->left; //������ ��带 ã�� ������
    Node* prev = NULL; //������ ����� �θ� ������
    while(ptr != NULL && ptr->key != key) //ptr�� ����ų ������ ����ų�, ã�� ���� ����ų �� ���� �ݺ�
    {
        prev = ptr;
        if(ptr->key > key)
            ptr = ptr->left; //ptr�� ���Ұ��� ã�� ������ Ŭ ��� ���� �ڽ����� �̵�
        else if(ptr->key < key)
            ptr = ptr->right; //ptr�� ���Ұ��� ã�� ������ ���� ��� ������ �ڽ����� �̵�
    }
    if(ptr == NULL)
    {
        printf("can't find key\n"); //ptr�� NULL�� ��� ��ã������ �˸�
        return 0;
    }
        
    if(ptr->left == NULL && ptr->right == NULL) //case1 : ���� ��� ����
    {
        if(prev != NULL) //�θ� ���� ���
        {
            if(prev->key > key)
                prev->left = NULL;
            else if(prev->key < key)
                prev->right = NULL;
            //�θ�� ���� ����� ������ ũ�⸦ ���Ͽ� ������ �θ����� ��ũ ���� ����
        } else {
            head->left = NULL; //�θ� ���� ��� ��Ʈ������� �ǹ��ϹǷ� head��带 NULL�� �ٲ۴�
        }
        free(ptr); //�ش� ��� ����
    } else if(ptr->right == NULL) { //case2 : �� �� �ϳ��� �ڽĳ�尡 ���� ���(����)
        if(prev != NULL) //�θ� ���� ���
        {
            if(prev->key > key)
                prev->left = ptr->left;
            else if(prev->key < key)
                prev->right = ptr->left;
            //�θ�� ���� ����� ������ ũ�⸦ ���Ͽ� �ٲ� �θ����� ��ũ ��ġ ����
        } else {
            head->left = ptr->left; //�θ� ���� ��� ��Ʈ������� �ǹ��ϹǷ� head��带 NULL�� �ٲ۴�
        }
        free(ptr); //�ش� ��� ����
    } else if(ptr->left == NULL) { //case2 : �� �� �ϳ��� �ڽĳ�尡 ���� ���(������)
        if(prev != NULL) //�θ� ���� ���
        {
            if(prev->key > key)
                prev->left = ptr->right;
            else if(prev->key < key)
                prev->right = ptr->right;
            //�θ�� ���� ����� ������ ũ�⸦ ���Ͽ� �ٲ� �θ����� ��ũ ��ġ ����
        } else {
            head->left = ptr->right; //�θ� ���� ��� ��Ʈ������� �ǹ��ϹǷ� head��带 NULL�� �ٲ۴�
        }
        free(ptr); //�ش� ��� ����
    } else { //case3 : �Ѵ� �ڽ� ��尡 ���� ���
        Node* ptr2 = ptr->left; //���� ��带 �������� ���� �켱��
        prev = ptr;
        while(ptr2->right != NULL)
        {
            prev = ptr2; //�θ� ����� ��ġ ����
            ptr2 = ptr2->right;
        }
        //ptr2�� ptr�� ���ʿ� �ִ� ��� �� ���� ū ��带 ����Ŵ
        ptr->key = ptr2->key; //ptr�� ptr2�� ���� ����
        if(prev == ptr)
            prev->left = NULL; //prev == ptr�� �ǹ��ϴ� �� => ptr2�� prev�� ���ʿ� �ִ� �������� ���� ������ ��� ptr�� ���ʿ� �ƹ��͵� ���� �ʴ´�
        else
            prev->right = NULL; //prev != ptr�� �ǹ��ϴ� �� => ptr2�� prev�� �����ʿ� �ִ� ��������
        free(ptr2); //���� ������ ��� ����
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
    if(top == -1) //top�� -1�� ����ų ��� ������ �� ����
    {
        printf("Stack is Empty\n");
        return NULL;
    }
    Node* temp = stack[top]; //stack[top]�� ��� ��ȯ�ع����� �Լ��� �����Ƿ� �ӽ÷� �����ϴ� ������ temp ���� �� ����
    top -= 1; //top�� 1��ŭ ����
    return temp; //temp�� ��ȯ
}

void push(Node* aNode)
{
    if(top + 1 >= MAX_STACK_SIZE) //top�� ������ ������ ��ġ�� ������ �ִ��ѵ��� ������ ��� ������ �� �� ����
    {
        printf("Stack is Full\n");
        return;
    }
    top += 1; //top�� 1��ŭ �߰�
    stack[top] = aNode; //top���ٰ� aNode���Ҹ� ����
}



Node* deQueue()
{
    if(rear == front) //rear == front�� ť�� ���� �ǹ��Ѵ�
    {
        printf("Queue is Empty\n");
        return NULL;
    }
    front = (front + 1) % MAX_QUEUE_SIZE; //front�� ����ť�� ����ĭ���� �ű�
    return queue[front]; //�Ű��� front�� ��ġ�� ���Ҹ� ��ȯ
}

void enQueue(Node* aNode)
{
    if((rear + 1) % MAX_QUEUE_SIZE == front) //rear�� ������ ĭ�� front�� ��� ť�� �� á���� �ǹ��Ѵ�(front�� ���Ұ� �� �� ����)
    {
        printf("Queue is Full\n");
        return;
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE; //rear�� ����ť�� ����ĭ���� �ű�
    queue[rear] = aNode; //�Ű��� rear�� ���Ҹ� ����
}

void printStack()
{
    for(int i = top;i > -1;i--)
    {
        printf(" [%d] ",stack[i]);
    }
}



