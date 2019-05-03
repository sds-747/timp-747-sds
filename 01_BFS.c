#include <stdio.h>
#include <stdlib.h>

struct tree {
	int data;
	struct tree* left;
	struct tree* right;
}tree;
struct tree* root;

void init_tree() { root = NULL; }
int is_empty_tree() { return root == NULL; }

struct tree* create_tree(int val)
{
	struct tree* n = (struct tree*)malloc(sizeof(tree));
	n->data = val;
	n->left = NULL;
	n->right = NULL;
	return n;
}

int insert(struct tree* r, struct tree* n)
{
	if (n->data == r->data) return 0;
	else if (n->data < r->data) {
		if (r->left == NULL) r->left = n;
		else insert(r->left, n);
	}
	else {
		if (r->right == NULL) r->right = n;
		else insert(r->right, n);
	}
	return 1;
}

void insert_BST(int key)
{
	struct tree* n = create_tree(key);
	if (is_empty_tree())
		root = n;
	else if (insert(root, n) == 0)
		free(n);
}

void printSubtree(struct tree* subtree, int level) 
{ 
    if (subtree == NULL) 
        return; 
    if (level > 0) 
    { 
        printSubtree(subtree->left, level-1); 
        printSubtree(subtree->right, level-1); 
    } 
    else
        printf("%d ", subtree->data);
} 

void print() 
{ 
    int max = maxHeight(root); 
    int depth; 
    for (depth=0; depth<max; depth++) 
        printSubtree(root, depth); 
} 

int maxHeight(struct tree* t) 
{ 
    if (t==NULL) 
        return 0; 
    else{ 
        int l = maxHeight(t->left); 
        int r = maxHeight(t->right); 
        if (l > r) 
            return l+1; 
        else return r+1; 
    } 
} 
  
void main()
{
	int input_data;
	int i;
	init_tree();
	for (i = 0; i < 7; i++)
	{
		scanf("%d", &input_data);
		insert_BST(input_data);
	}
	printf("\n"); print();
}
