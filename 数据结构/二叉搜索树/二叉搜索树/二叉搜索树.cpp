
#include "stdafx.h"
#include <iostream>
template<typename T>
class TreeNode{
private:
	T element;
	TreeNode* left;
	TreeNode* right;
public:
	TreeNode();
	TreeNode* find(T x);
	TreeNode* insert(T x);
	TreeNode* findMax();
	TreeNode* findMin();
	TreeNode* TreeNode<T>::Delete(T x);
};
template<typename T>
TreeNode<T>::TreeNode()
{
	this = NULL;
	left = 0;
	right = 0;
}
template<typename T>
TreeNode<T>* TreeNode<T>::find(T x) {
	while (this) {
		if (x < this->element)
			this = this->left;
		else if (x > this->element)
			this = this->right;
		else
			return this;
	}
		return NULL;
	
}
template<typename T>
TreeNode<T>* TreeNode<T>::insert(T x) {
	while(1){

		if (!this) {
			this = new(thisNode);
			this->element = x;
			this->lest = this->right = NULL;
			break;
		}
		else
			if (x < this->element)
				this = this->left;
			else if (x > this->element)
				this = this->right;
	}
	return this;
}
template<typename T>
TreeNode<T>* TreeNode<T>::findMin() {
	if (this != NULL)
	{
		while (left != NULL)
			this = left;
	}
	return this;
}
template<typename T>
TreeNode<T>* TreeNode<T>::findMax() {
	if (this != NULL)
	{
		while (right != NULL)
			this = right;
	}
	return this;
}
template<typename T>
TreeNode<T>* TreeNode<T>::Delete(T x) {
	TreeNode* tmp;
	if (!this)
	{
		printf("删除的元素不存在\n");
	}
	else if (x < this->element)
		this->left = this->left->Delete(x);
	else if (x > this->element)
		this->right = this->right->Delete(x);
	else
		if (left&&right)
		{
			tmp = right->findMin();
			element = tmp->element;
			right = right->Delete();
		}
		else {
			tmp = this;
			if (!left)
				this = right;
			else if (!right)
				this = left;
			free(tmp);
		}
		return this;
}
int main()
{

    return 0;
}

