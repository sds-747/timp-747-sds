#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree {
	int value;
	int height;
	struct tree* left;
	struct tree* right;
	struct tree* parent;
}tree;

struct tree* root;

void init_tree() { root = NULL; }
int is_empty_tree() { return root == NULL; }
void clear(struct tree* t)	{
	if(t){ 
		clear(t->left); 
		clear(t->right); 
		free(t);
	}
 	root=NULL;
}	

struct tree* create_tree(int val)
{
	struct tree* t = (struct tree*)malloc(sizeof(struct tree));
	t->value = val;
	t->left = NULL;
	t->right = NULL;
	t->parent = NULL;
	return t;
}

int insert(struct tree* r, struct tree* t)
{
	if (t->value == r->value) return 0;
	else if (t->value < r->value) {
		if (r->left == NULL) r->left = t;
		else insert(r->left, t);
	}
	else {
		if (r->right == NULL) r->right = t;
		else insert(r->right, t);
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

struct tree* search(struct tree *t, int key)
{
	if (t == NULL)return NULL;
	else if (key == t->value) return t;
	else if (key < t->value) return search(t->left, key);
	else return search(t->right, key);
}

struct tree* findP(struct tree *tr, int key)
{
	struct tree* t = root;
	struct tree* parent = NULL;
	while( t != NULL)
	{
		if (key == t->value) break;
	else {
		parent =t;
		if(key < t->value) t=t->left;
		else t= t->right;
	}
	}
	return parent;
}

struct tree* findLC(struct tree *tr, int key)
{
	struct tree* t = root;
	struct tree* left_child = t->left;
	while( t != NULL)
	{
		if (key == t->value) break;
	else {
		if(key < t->value){
			t=t->left;
			left_child =t->left;
		}
		else{
			t= t->right;
			left_child = t->left;
		}
		}
	}
	return left_child;
}

struct tree* findRC(struct tree *tr, int key)
{
	struct tree* t = root;
	struct tree* right_child = t->right;
	while( t != NULL)
	{
		if (key == t->value) break;
	else {
		if(key < t->value){
			t=t->left;
			right_child = t->right;
		}
		else{
			t= t->right;
			right_child = t->right;
		} 
	}
	}
	return right_child;
}

int find(int key)
{
	struct tree* n = search(root, key);
	struct tree* p;
	struct tree* lc;
	struct tree* rc;
	if (n != NULL){
		p = findP(root,key);
		lc = findLC(root,key);
		rc = findRC(root,key);
		if (p != NULL)
		{
			printf("parent: %d \n",p->value);
		}
		else{
			printf("_ (parent missing)\n");
		}
		if (lc != NULL)
		{
		printf("left child: %d \n",lc->value);
		}
		else{
			printf("_ (left child missing)\n");
		}
		if (rc != NULL)
		{
		printf("right child: %d \n",rc->value);
		}
		else{
			printf("_ (right child missing)\n");
		}
	}
	else
		printf("- (not founded element)\n");
}

void delete(struct tree *parent, struct tree *node)
{
	struct tree *child, *succ, *succp;
	if ((node->left == NULL && node->right == NULL))
	{
		if (parent == NULL) root = NULL;
		else {
			if (parent->left == node)
				parent->left = NULL;
			else parent->right = NULL;
		}
	}
	else if (node->left == NULL || node->right == NULL) {
		child = (node->left != NULL) ? node->left : node->right;
		if (node == root) root = child;
		else {
			if (parent->left == node)
				parent->left = child;
			else parent->right = child;
		}
	}
	else {
		succp = node;
		succ = node->right;
		while (succ->left != NULL) {
			succp = succ;
			succ = succ->left;
		}
		if (succp->left == succ)
			succp->left = succ->right;
		else succp->right = succ->right;

		node->value = succ->value;
		node = succ;
	}
	free(node);
}

void delete_BST(int key)
{
	struct tree *parent = NULL;
	struct tree *node = root;
	if (node == NULL) return;
	while (node != NULL && node->value != key) {
		parent = node;
		node = (key < node->value) ? node->left : node->right;
	}
	if (node == NULL)
		printf("value missing\n");
	else delete(parent, node);
}

int count_node(struct tree* t)
{
	if (t == NULL)return 0;
	return 1 + count_node(t->left) + count_node(t->right);
}

int maxHeight(struct tree* t)
{
	if(t==NULL)
		return 0;
	else{
		int l = maxHeight(t->left);
		int r = maxHeight(t->right);
		if (l > r)
			return l+1;
		else return r+1;
	}
}

int spacing(int level) {
  int i,result = 2;
  for (i = 0; i < level; i++)
    result += result;
  return result;
}

void printSubtree(struct tree *subtree, int depth, int level,bool first) {
  if (depth > 0) {
    if (subtree == NULL) {
      printSubtree(subtree, depth-1, level, first);
      printSubtree(subtree, depth-1, level, false);
    } else {
      printSubtree(subtree->left, depth-1,level, first);
      printSubtree(subtree->right, depth-1,level, false);
	} 
  } 
	else if (subtree == NULL){
		printf("%*s",(first)?spacing(level)/2:spacing(level),"-");
	}
  	else{
  	    printf("%*d",(first)?spacing(level)/2:spacing(level),subtree->value);
  	}
}

void print() {
  if (root == NULL) return;
  else {
    int max = maxHeight(root);
    int depth;
    for (depth = 0; depth < max; depth++) {
      printSubtree(root, depth, max-depth+1, true);
      printf("\n");
    }
  } 
} 

void rotateLeft(struct tree* t) {
       struct tree* replacement = t->right;
       t->right = replacement->left;
       if (replacement->left!=NULL)
           replacement->left->parent = t;
       replacement->parent = t->parent;
       if (t->parent==NULL)
           root = replacement;
       else if (t->parent->left == t)
           t->parent->left = replacement;
       else
           t->parent->right = replacement;
       replacement->left = t;
       t->parent = replacement;
}
void rotateRight(struct tree* t) {
        struct tree* replacement = t->left;
        t->left = replacement->right;
        if (replacement->right!=NULL)
            replacement->right->parent = t;
        replacement->parent = t->parent;
        if (t->parent==NULL)
            root = replacement;
        else if (t->parent->right == t)
            t->parent->right = replacement;
        else
            t->parent->left = replacement;
        replacement->right = t;
        t->parent = replacement;
    }
    
void main()
{
	int input_value;
	int delete_value;
	int search;
	int i;
	init_tree(); // 1. ñîçäàòü ïóòñîå äåðåâî

	// 1. ñ÷èòàòü 4 ýëåìåíòîâ è çàíåñòè â äåðåâî
	for (i = 0; i < 4; i++)
	{
		scanf("%d", &input_value); // 1.ñ÷èòàòü
		insert_BST(input_value);  // 1.çàíåñòè
	}
	printf("\n");
	print(root); // 2. âûâîä äåðåâà
	printf("\n");
	
	//3. ñ÷èòàòü 3 ýëåìåíòà è çàíåñòè â äåðåâî
	for (i = 0; i < 3; i++)
	{
		scanf("%d", &input_value); //3. ñ÷èòàòü
		insert_BST(input_value); // 3. çàíåñòè
	}
	printf("\n");
	print(root);// 4. âûâîä äåðåâà
	printf("\n");
	
	scanf("%d", &search);
	find(search); // 5. ïîèñê ïðåäêà è ïîòîìêà

	scanf("%d", &search);
	find(search); // 6. ïîèñê ïðåäêà è ïîòîìêà
	
	//7.óäàëèòü ýëåìåíò
	scanf("%d", &delete_value);
	delete_BST(delete_value);
	printf("\n");
	print(root); //8. âûâîä äåðåâà
	printf("\n");
	
	//9. âûïîëíèòü ëåâûé ïîâîðîò 
	printf("\n");
	while (root->right !=NULL){
			rotateLeft(root);
	}
	print(root);
	printf("\n");
	//10. ïîêàç äåðåâà
	//11. âûïîëíèòü ïðàâûé ïîâîðîò 12. âûâåñòè äåðåâî
	printf("\n");
	while (root->left !=NULL){
		rotateRight(root);
	}
	print(root);
	printf("\n");
	
	//13. âûâîä êîëè÷åñòâî ýëåìåíòîâ â äåðåâå
	printf("count: %d\n", count_node(root));
	printf("\n");

	//14 î÷èñòèòü äåðåâî 15. âûâîä äåðåâî
	clear(root);
	print(root);
	printf("\n");
}
