#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	struct node* left;
	struct node* right;
	int val;
}node;
typedef node* nodeptr;
nodeptr new_node(int val) {//���ο� ��带 ���������
	nodeptr ret = (nodeptr)calloc(sizeof(node), 1);
	ret->val = val;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}
int end = 0;
nodeptr make_tree(int s, int e, int* inorder) {//s+1~e : ROOT�� �ڽĵ��� �ִ� ����, S : ROOT�� �ִ� ��, inorder : �迭
	nodeptr ret = new_node(inorder[s]); //root ��带 �������
	if (s + 1 > e) return ret; 
	int val = inorder[s];
	int ch = 0;
	int idx = -1;
	for (int i = s + 1; i <= e; i++) {//BST�� ���Ǹ� �����ϱ� ���ؼ���  S+1~E �������� (������ | ū��) �̷��� �̺й������� ������ �����Ѵ�.
		if (!ch&&val <= inorder[i]) { 
			idx = i;
			ch = 1;
		}
		if (ch&&val >= inorder[i]) { 
			end = 1; 
			return ret;
		}
	}
	if (idx != -1) {
		if (idx != s + 1) {
			ret->left = make_tree(s + 1, idx - 1, inorder); 
			ret->right = make_tree(idx, e, inorder); 
		}
		else {
			ret->right = make_tree(s + 1, e, inorder); 
		}
	}
	else if (idx == -1) {
		ret->left = make_tree(s + 1, e, inorder);
	}
	return ret;
}
void print_inorder(nodeptr root) { //inorder ���
	if (!root) return;
	print_inorder(root->left);
	fprintf(stdout," %d", root->val);
	print_inorder(root->right);
}
void print_postorder(nodeptr root) { //postorder���
	if (!root) return;
	print_postorder(root->left);
	print_postorder(root->right);
	fprintf(stdout," %d", root->val);
}
void free_tree(nodeptr root) { //free���ֱ�
	if (!root) return;
	nodeptr left = root->left;
	nodeptr right = root->right;
	free(root);
	free_tree(left);
	free_tree(right);
}
int main() {
	int inorder[150];
	int n; fscanf(stdin,"%d", &n);
	for (int i = 0; i < n; i++) fscanf(stdin,"%d", &inorder[i]);
	nodeptr root = make_tree(0, n - 1, inorder);
	if (end) fprintf(stdout,"cannot construct BST\n");
	else {
		fprintf(stdout,"Inorder:");
		print_inorder(root);
		fprintf(stdout,"\n");
		fprintf(stdout,"Postorder:");
		print_postorder(root);
		fprintf(stdout, "\n");
	}
	free(root);
}