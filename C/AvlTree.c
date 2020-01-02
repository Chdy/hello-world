//
// Created by 邓岩 on 2019-09-02.
//

/*
 * 自平衡二叉搜索树
 * 平衡条件:
 * 1. 任意节点的左右子树高度最多差1
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

typedef struct Node {
	int v;
	struct Node * left;
	struct Node * right;
	int height;
} TreeNode;

typedef TreeNode * AvlTree;
typedef TreeNode * Position;

AvlTree MakeEmpty(AvlTree T) {
	if (T != NULL) {
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return T;
}

Position Find(AvlTree T, int x) {
	if (T == NULL)
		return NULL;
	if (T->v > x)
		return Find(T->left, x);
	else if (T->v < x)
		return Find(T->right, x);
	else
		return T;
}

Position FindMax(AvlTree T) {
	while (T && T->right)
		T = T->right;

	return T;
}

Position FindMin(AvlTree T) {
	while (T && T->left)
		T = T->left;

	return T;
}

int Height(AvlTree T) {
	if (T == NULL)
		return -1;
	else
		return T->height;
}

int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}

AvlTree SimpleRotateWithRight(AvlTree T) { //单旋转
	AvlTree S = T->right;
	T->left = S->left;
	S->left = T;
	T->height = max(Height(T->left), Height(T->right)) + 1;
	S->height = max(Height(S->left), Height(T->right)) + 1;
	return S;
}

AvlTree SimpleRotateWithLeft(AvlTree T) { //单旋转
	AvlTree S = T->left;
	T->left = S->right;
	S->right = T;
	T->height = max(Height(T->left), Height(T->right)) + 1;
	S->height = max(Height(S->left), Height(T->right)) + 1;
	return S;
}

AvlTree DoubleRotateWithLeft(AvlTree T) { //双旋转，withleft的表示第二次被旋转的是左子树
	T->left = SimpleRotateWithRight(T->left);
	return SimpleRotateWithLeft(T);
}

AvlTree DoubleRotateWithRight(AvlTree T) { //双旋转
	T->right = SimpleRotateWithLeft(T->right);
	return SimpleRotateWithRight(T);
}


AvlTree Insert(AvlTree T, int v) {
	if (T == NULL) {
		T = (AvlTree)malloc(sizeof(TreeNode));
		if (T == NULL)
			exit(-1);

		T->left = T->right =  NULL;
		T->v = v;
		T->height = 0;
	} else if (T->v > v) {
		T->left = Insert(T->left, v);
		if (abs(Height(T->left) - Height(T->right)) >= 2) {
			if (T->left->v > v) { //v值插入到了左子树的左子树，单旋转即可
				T = SimpleRotateWithLeft(T);
			} else { //插入到了左子树的右节点上，需要双旋转
				T = DoubleRotateWithLeft(T);
			}
		}
	} else if (v > T->v) {
		T->right = Insert(T->right, v);
		if (abs(Height(T->left) - Height(T->right)) >= 2) {
			if (v > T->right->v) {
				T = SimpleRotateWithRight(T);
			} else {
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	T->height = max(Height(T->left), Height(T->right)) + 1;
	// 如果v已经存在，则什么都不做
	return T;
}

AvlTree Delete(AvlTree T, int v) { //Todo: 尚未验证是否正确
	if (T == NULL)
		return NULL;
	else if (T->v > v) {
		T->left = Delete(T->left, v);
		if (abs(T->left->height - T->right->height) >= 2) {
			if (T->left->v < v) { //v是从左子树的右子树上被删除的
				T = SimpleRotateWithRight(T);
			} else {
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if (T->v < v) {
		T->right = Delete(T->right, v);
		if (abs(T->left->height - T->right->height) >= 2) {
			if (T->right->v > v) {
				T = SimpleRotateWithLeft(T);
			} else {
				T = DoubleRotateWithRight(T);
			}
		}
	}
	else if (T->left && T->right) { //两个孩子都存在
		Position tmp = FindMin(T->right);
		T->v = tmp->v;
		T->right = Delete(T->right, v);
	} else { //最多只有一个孩子
		Position tmp = T;

		if (T->left == NULL) {
			T = T->right;
		} else if (T->right == NULL) {
			T = T->left;
		}

		free(tmp);
	}

	T->height = max(Height(T->left), Height(T->right)) + 1;
	return T;
}

int main(void) {
	

}