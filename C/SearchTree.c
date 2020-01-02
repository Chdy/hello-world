//
// Created by 邓岩 on 2019-09-02.
//

/*
 * 二叉搜索树
 * 非常好的二叉树代码，不需要头节点，删除节点后返回删除节点后的树
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct Node {
	int v;
	struct Node * left;
	struct Node * right;
} TreeNode;

typedef TreeNode * SearchTree;
typedef TreeNode * Position;

SearchTree MakeEmpty(SearchTree T) {
	if (T != NULL) {
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return T;
}


Position Find(SearchTree T, int x) {
	if (T == NULL)
		return NULL;
	if (T->v > x)
		return Find(T->left, x);
	else if (T->v < x)
		return Find(T->right, x);
	else
		return T;
}

Position FindMax(SearchTree T) {
	while (T && T->right)
		T = T->right;

	return T;
}

Position FindMin(SearchTree T) {
	while (T && T->left)
		T = T->left;

	return T;
}

SearchTree Insert(SearchTree T, int x) {
	if (T == NULL) {
		T = (TreeNode *)malloc(sizeof(TreeNode));
		if (T == NULL)
			exit(-1);

		T->v = x;
		T->left = T->right = NULL;
	} else if (T->v > x) {
		T->left = Insert(T->left, x);
	} else
		T->right = Insert(T->right, x);

	return T;
}

SearchTree Delete(SearchTree T, int x) {
	if (T == NULL)
		return NULL;
	if (T->v > x) //删除点在左子树上 
		T->left = Delete(T->left, x);
	else if (T->v < x) //删除点在右子树上
		T->right = Delete(T->right, x); 
	else if (T->left && T->right) { //删除元素有两个孩子
		/*
			由于有两个孩子，所以直接删除元素后需要找到代替元素
			这里可以选择的两个元素分别是右子树上的最小元素或者是左子树上的最大元素
			将这两个元素任意一个放置到被删除的元素位置都仍然可以保持二叉搜索树的性质
			这里使用右子树的最小孩子来进行代替
		*/
		Position tmp = FindMin(T->right);
		T->v = tmp->v;
		T->right = Delete(T->right, tmp->v); 
		/*
			这里的Delete和上面的FindMin进行了两次路径搜索
			如果使用一个改写的FindMin获取tmp的父亲则可以只用一次
			因为被用来替换的那个节点必然没有左孩子
		*/
	} else { //处理只有一个孩子或者没有孩子的情况
		Position tmp = T;

		if (T->left == NULL)
			T = T->right;
		else if (T->right == NULL)
			T = T->left;

		free(tmp);
	}

	return T;
}

void MidTraverse(SearchTree T) {
	if (T->left != NULL)
		MidTraverse(T->left);
	printf("%d ", T->v);
	if (T->right != NULL)
		MidTraverse(T->right);
}


int main(void) {
	SearchTree T = NULL;
	for (int i = 0; i < 10; i++) {
		int x;
		scanf("%d", &x);
		T = Insert(T, x);
	}
	T = Delete(T, 5); 
	//赋值给T，防止树中只有根节点一个节点，而且正好删除的是根节点
	//这样能让T指向NULL，而不是被free后的节点
	MidTraverse(T);
	return 0;
}