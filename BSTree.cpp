#include <iostream>
using namespace std;

class node {
public:
	int data;
	node* left;
	node* right;
public:
	node(int data):data(data){
	
		left = NULL;
		right = NULL;
	}
};

class tree {
public:
	node* head;
public:
	tree(node* hd) {
		head = hd;
	}
	void BST_destroynode(node* node);
	void BST_destroytree(node* tree);
	node* BST_searchnode(node* tree, int target);
	void BST_insertnode(node* tree, node* child);
	node* BST_removenode(node* tree, node* parent, int target);
	node* BST_minsearch(node* tree);
};

node* createnode(int data) {
	node* nnode = new node(data);
	return nnode;

}

void tree::BST_destroynode(node* node) {
	free(node);
}

void tree::BST_destroytree(node* tree) {
	/**/
	if (tree == NULL) return;
	else if (tree->left == NULL && tree->right == NULL) {

		BST_destroynode(tree);
	}
	else {

		if (tree->left != NULL) {
			BST_destroytree(tree->left);
		}
		else {
			BST_destroytree(tree->right);
		}
	}
}

node* tree::BST_searchnode(node* tree, int target) {

	if (tree == NULL) return NULL;
	else {
		if (tree->data == target) return tree;
		else if (tree->data > target) return BST_searchnode(tree->left, target);
		else if (tree->data < target) return BST_searchnode(tree->right, target);
	}

}

void tree::BST_insertnode(node* tree, node* child) {    //insert the child node

	if (child->data > tree->data) {

		if (tree->right == NULL) {
			tree->right = child;
		}

		else {
			BST_insertnode(tree->right, child);
		}

	}
	else {

		if (tree->left == NULL) {
			tree->left = child;
		}

		else {
			BST_insertnode(tree->left, child);
		}

	}
}

/*

	Node* insertNode(Node* root, int data){
		if(root==NULL){
			root= (Node*)malloc(sizeof(Node));
			root->left=NULL;
			root->right=NULL;
			root->data=data;
			return root;

		}
		else{
			if(data<root->data){
				
				root->left = insertNode(root->left,data);

			}
			else{

				root->right = insertNode(root->right,data);

			}
		}
		return root;


	}


*/

node* tree::BST_minsearch(node* tree) {

	node* min = tree->right;
	while (min->left != NULL) {
		min = min->left;
	}
	return min;

}

node* tree::BST_removenode(node* tree, node* parent, int target) {
	
	node* renode=NULL;

	if (tree == NULL) return NULL;
	else if (tree->data > target) {
		renode = BST_removenode(tree->left, tree, target);
	}
	else if (tree->data < target) {
		renode = BST_removenode(tree->right, tree, target);
	}
	/**/

	else {

		renode = tree;
		if (tree->left == NULL && tree->right == NULL) {

			if (parent->left == tree) {
				parent->left = NULL;
			}
			else if (parent->right == tree) {
				parent->right = NULL;
			}
		}
		else if (tree->left != NULL && tree->right != NULL) {

			node*min = BST_minsearch(tree);
			tree->data = min->data;
			min = BST_removenode(tree, NULL, min->data);

		}
		else {

			node* temp = NULL;
			if (tree->left == NULL) {
				temp = tree->right;
				if (parent->left == tree) {
					parent->left = temp;
				}
				else {
					parent->right = temp;
				}
			}
			else {
				temp = tree->left;
				if (parent->left == tree) {
					parent->left = temp;
				}
				else {
					parent->right = temp;
				}
			}
		}
	}
	return renode;
}

void inorderprint(node* tree) {
	if (tree == NULL) { return; }
	inorderprint(tree->left);
	cout << tree->data << ' ';
	inorderprint(tree->right);
}

int main() {

	node* head = new node(123);
	tree* tr = new tree(head);
	tr->BST_insertnode(head, createnode(22));
	tr->BST_insertnode(head, createnode(9918));
	tr->BST_insertnode(head, createnode(424));
	tr->BST_insertnode(head, createnode(17));
	tr->BST_insertnode(head, createnode(3));
	tr->BST_insertnode(head, createnode(98));
	tr->BST_insertnode(head, createnode(34));
	tr->BST_insertnode(head, createnode(760));
	tr->BST_insertnode(head, createnode(317));
	tr->BST_insertnode(head, createnode(1));

	inorderprint(head);
	cout << endl;
	cout << "removal start" << endl;

	node* Node = tr->BST_removenode(head, NULL, 98);
	tr->BST_destroynode(Node);

	inorderprint(head);
	cout << endl;
	cout << "destroy tree" << endl;
	tr->BST_destroytree(head);
	//inorderprint(head);

}