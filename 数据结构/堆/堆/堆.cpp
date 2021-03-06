// 堆.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
typedef struct HeapStruct *MaxHeap;
struct HeapStruct {
	int *elements;//存储堆元素的数组
	int size;//堆当前元素个数
	int capacity;//堆的最大容量
};
MaxHeap Creat(int MaxSize)
{
	MaxHeap H = new(HeapStruct);
	H->elements = new int[MaxSize+1];
	H->size = 0;
	H->capacity = MaxSize;
	H->elements[0] =1000000;//哨兵
	return H;
}
void Insert(MaxHeap H, int item)
{
	int i;
	if (H->size == H->capacity)
	{
		printf("堆已满");
		return;
	}
	i = ++H->size;
	for (; H->elements[i / 2] < item; i / 2)//有哨兵挡住
		H->elements[i] = H->elements[i / 2];
	H->elements[i] = item;
}
int DeleteMax(MaxHeap H)
{
	int Parent, Child;
	int MaxItem, temp;
	if (H->size == 0)
	{
		printf("最大堆已空");
		return NULL;
	}
	MaxItem = H->elements[1];
	temp = H->elements[H->size--];
	for (Parent = 1; Parent * 2 <= H->size; Parent = Child)
	{
		Child = Parent * 2;
		if (Child != H->size&&H->elements[Child] < H->elements[Child + 1])
			Child++;
		if (temp >= H->elements[Child])break;
		else
			H->elements[Parent] = H->elements[Child];
	}
	H->elements[Parent] = temp;
	return MaxItem;
}

int main()
{
    return 0;
}

