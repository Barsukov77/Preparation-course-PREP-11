/*Написать программу, которая в качестве аргумента командной строки принимает имя текстового фай-
ла, содержащего элементы трёх видов:
+ <неотрицательное целое число>
− <неотрицательное целое число>
? <неотрицательное целое число>
	Элементы отделяются друг от друга одним или несколькими разделителями – пробелами, табуляци-
ями, символами новой строки.
	Число с предшествующим плюсом добавляется в двоичное дерево поиска, если его там ещё нет (ключом
при построении дерева должно являться само число). Если числу предшествует минус, то это число
удаляется из дерева (если оно было в нём). Если перед числом стоит вопрос, то оно печатается в выходной
поток в отдельной строке вместе со словом Yes или No в зависимости от того, присутствует ли это число
в построенном на тот момент дереве поиска.*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define ARGUMENTS -1
#define OPENING -2
#define BUF_OVERFLOW -3 
#define EMPTY_FILE -4
#define MEMORY_ERROR -5
#define READING -6
#define WORD_OVERFLOW -7
#define FOUND -8
#define EMPTY_NODE -9
#define NOT_STATED -10
#define EMPTY_TREE NULL
#define MALLOC NULL

typedef struct Tree
{
	struct Node* root;

}Tree;

typedef struct Node
{
	int num;
	struct Node* pred;
	struct Node* left;
	struct Node* right;

}Node;

int add_in_tree(Tree *tree, int val);
void insert(Node *node, Node *temp);
int search_element(Node* node,int val);
Node* del_node(Node* node, int val);

void print_tree(Node *node);
int print_node(Node *node);

void free_tree(Tree *tree);
void free_node(Node *node);
void Free_tree(Node *node);

Tree* create_tree()
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if(tree == NULL)
		return NULL;
	tree->root = NULL;
	return tree;
}
int read_elem(FILE* f)
{
	int num;
	if(fscanf(f,"%d",&num) != 1)
 	{
        return READING;
 	}
 	if(num == -1)
 	{
 		return WORD_OVERFLOW;
 	}
 	return num;
}

int selector(FILE* f, Tree* tree)
{
	for(int x; (x = fgetc(f)) != EOF;)
 	{
 		int num = 0;
 		if(x == '+' || x == '-' || x == '?')
 		{
 			num = read_elem(f);
 			if(num < 0)
 				return num;

 			if(x == '+')
 			{	
 				add_in_tree(tree, num);
 				printf("insert : %d\n",num);
 			}
 			if(x =='-')
 			{
 	 			printf("delete : %d\n",num);
                tree->root = del_node(tree->root, num);
 			}
 			if(x == '?')
 			{
 				if(search_element(tree->root,num) == FOUND)
 					printf("%d YES\n",num);
 				else
 					printf("%d NO\n",num);
 			}
 		}
 	}
 	return 0;
}

int add_in_tree(Tree *tree, int val)
{
	if(tree->root == NULL) 
	{
        tree->root = (Node*) malloc(sizeof(Node));
        if(tree->root == NULL)
        	return MEMORY_ERROR;
        tree->root->left = NULL; 
        tree->root->right = NULL;
        tree->root->num = val;
        tree->root->pred = NULL;
    }
    else
    {
        Node *node = (Node*) malloc(sizeof(Node));
        if(node == NULL)
        	return MEMORY_ERROR;
        node->left = NULL; 
        node->right = NULL;
        node->pred = NULL;
        node->num = val;
        insert(tree->root, node);
    }
    return 0;
}

void insert(Node *node, Node *temp) 
{
    while(node != NULL)
    {
        if(temp->num > node->num)
        {
            if(node->right != NULL)
                node = node->right;
            else
            {
                temp->pred = node;
                node->right = temp;
                break;
            }
        }
        else if(temp->num <= node->num)
        {
            if(node->left != NULL)
                node = node->left;
            else
            {
                temp->pred = node;
                node->left = temp;
                break;
            }
        }
    }
}

void print_tree(Node *node) 
{
    if(node->left != NULL)
    	print_tree(node->left);
    print_node(node);
    if(node->right != NULL)
        print_tree(node->right);
}

int print_node(Node *node)
{
    if(node)
    {
        printf("%d\n", node->num);
        return 0;
    }
    return -1;
}

int search_element(Node* node, int val)
{
    if(node == NULL)
        return NOT_STATED;
    if(node->num == val)
        return FOUND;
    if(node->num > val)
        search_element(node->left, val);
    if(node->num < val)
        search_element(node->right, val);
}

Node* del_node(Node* node, int val)
{
    if(node == NULL)
        return node;

    if(val == node->num)
    {
        Node* tmp;
        if(node->right == NULL)
            tmp = node->right;
        else
        {
            Node* ptr = node->right;
            if(ptr->left == NULL)
            {
                ptr->left = node->left;
                tmp = ptr;
            }
            else
            {
                Node* pmin = ptr->left;
                while(pmin->left != NULL)
                {
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = node->left;
                pmin->right = node->right;
                tmp = pmin;
            }
        }
        free(node);
        return tmp;
    }
    else if (val < node->num)
        node->left = del_node(node->left, val);
    else
        node->right = del_node(node->right, val);
    return node;
}

void free_tree(Tree *tree)
{
    if(tree)
    {
        Free_tree(tree->root);
        free(tree);
    }
}

void Free_tree(struct Node *node)
{
    if (node)
    {
        Free_tree(node->left);
        Free_tree(node->right);
        free_node(node);
    }
}

void free_node(struct Node *node)
{
    free(node);
}

int main(int argc, char const *argv[])
{
	if(argc < 2)
	{
		puts("Enter filename with numbers\n");
		return ARGUMENTS;
	}

	FILE* f = fopen(argv[1], "r");
    if(f == NULL) 
	{
 		printf("ERROR OPENING %s\n",strerror(errno));
   		return OPENING;
 	}

 	if(fseek(f, 0, SEEK_END) != 0)
 	{
 		printf("Buffer is overflow\n");
 		fclose(f);
 		return BUF_OVERFLOW;
 	}

 	if(ftell(f) <= 0)
 	{
 		printf("Empty file\n");
 		fclose(f);
 		return EMPTY_FILE;
 	}

 	rewind(f);

 	Tree* tree = create_tree();
 	if(tree == NULL)
 	{
 		printf("ERROR MALLOC %s\n",strerror(errno));
 		fclose(f);
 		free_tree(tree);
   		return MEMORY_ERROR;
 	}

 	int key = selector(f, tree);
 	if(key != 0)
 	{
 		if(key == WORD_OVERFLOW)
 		{
 			printf("ERROR: len of word is overflow\n");
 			return WORD_OVERFLOW;
 		}
 		if(key == READING)
 		{
 			printf("ERROR: reading element from file\n");
 			return READING;
 		}
 		fclose(f);
 		free_tree(tree);
 	}

 	//print_tree(tree->root);

    free_tree(tree);

	return 0;
}
