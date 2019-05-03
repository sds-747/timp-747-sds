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


void preorder(struct tree* root) 
{ 
    struct tree *current, *pre; 
    if (root == NULL) 
        return; 
    current = root; 
    while (current != NULL) { 
		if (current->left == NULL) {  
			printf("%d ", current->data);      
            current = current->right; 
        } 
        else { 
            pre = current->left; 
            while (pre->right != NULL && pre->right != current) 
                pre = pre->right; 
            if (pre->right == NULL) { 
                pre->right = current; 
                printf("%d ", current->data); 
                current = current->left; 
            } 
            else { 
                pre->right = NULL; 
                current = current->right; 
            }
        }
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
	printf("\n"); preorder(root);
}
