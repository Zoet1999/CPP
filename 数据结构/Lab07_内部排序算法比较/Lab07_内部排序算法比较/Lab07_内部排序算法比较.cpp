// Lab07_内部排序算法比较.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <time.h>

#define MAXSIZE 1000
typedef int KeyType;
typedef struct {
	KeyType key;//关键字		//关键字数据
	int info;		//其他数据
}RedType;						//数据类型
typedef struct {
	RedType r[MAXSIZE + 1];		//r[0]闲置或用做哨兵
	int length;					//顺序表长度
	int swapT;
	int compareT;
}SqList;						//顺序表类型
int swapTimes;
int compareTimes;

void procTable(SqList& L,int length) {
	//随机创建无序表
	srand(rand());
	//0号位闲置
	L.length = length;
	for (int i = 1; i <= length; i++) {
		L.r[i].info = i;
		L.r[i].key=(rand() % 1000);
	}
}
//直接插入排序
SqList InsertionSort(SqList L) {
	//直接插入排序
	swapTimes = 0;
	compareTimes = 0;
	int i, j;
	for (i = 2; i <= L.length;i++) {						
		if (L.r[i].key < L.r[i - 1].key) {				//如果为真，需要将r[i]插入有序子表
			compareTimes++;
			L.r[0] = L.r[i];							//将待查入的记录暂存到监视哨
			L.r[i] = L.r[i - 1];						//r[i-1]后移
			swapTimes += 2;
			for (j = i - 2; L.r[0].key < L.r[j].key; j--)//从后向前寻找插入位置
			{
				compareTimes++;
				swapTimes++;
				L.r[j + 1] = L.r[j];					//记录逐个后移，直到找到插入位置
			}
			L.r[j + 1] = L.r[0];						//将r[0]即原r[i],插入到正确位置
			swapTimes++;
		}
	}
	return L;
}
//二分插入排序
SqList BinaryInsertionSort(SqList L) {
	//折半插入排序
	compareTimes == 0;
	swapTimes = 0;
	int  i, j,low,high,m;
	for (i = 2; i <= L.length; i++) {
		if (L.r[i].key < L.r[i - 1].key) {				//如果为真，需要将r[i]插入有序子表
			compareTimes++;
			L.r[0] = L.r[i];							//将待查入的记录暂存到监视哨
			swapTimes++;
			low = 1;
			high = i - 1;								//置查找区间初值
			while (low <= high) {						//在r[low..high]中折半查找插入的位置
				m = (low + high) / 2;					//折半
				compareTimes++;
				if (L.r[0].key < L.r[m].key) {
					high = m - 1;						//插入点在前一子表
				}
				else {
					low = m + 1;						//插入点在后一子表
				}
			}
			for (j = i - 1; j >= high + 1; j--) {
				L.r[j + 1] = L.r[j];					//记录后移
				swapTimes++;
			}
			L.r[high + 1] = L.r[0];						//将r[0]即原r[i],插入到正确位置
			swapTimes++;
		}
	}
	return L;
}
//二路插入排序
SqList TwoWayInsertionSort(SqList L) {
	//二路插入排序
	swapTimes = 0;
	compareTimes = 0;
	int i, first, last, j;
	RedType temp[MAXSIZE];
	first = last = 0;
	temp[0] = L.r[1];
	swapTimes++;
	for (i = 2; i <= L.length; i++) {
		if (L.r[i].key < temp[first].key) { // 待插入元素比最小的元素小 
			compareTimes++;
			swapTimes++;
			first = (first - 1 + L.length) % L.length;
			temp[first] = L.r[i];
		}
		else if (L.r[i].key > temp[last].key) { // 待插入元素比最大元素大 
			compareTimes++;
			swapTimes++;
			last = (last + 1) % L.length;
			temp[last] = L.r[i];
		}
		else { // 插入元素比最小大，比最大小 
			j = (last + 1 ) % L.length;
			while (temp[((j - 1) + L.length) % L.length].key > L.r[i].key) {
				compareTimes++;
				temp[j] = temp[(j - 1 + L.length) % L.length];
				j = (j - 1 + L.length) % L.length;
			}
			swapTimes++;
			temp[j ] = L.r[i];
			last = (last + 1 ) % L.length;
		}
	}

	// 将排序记录复制到原来的顺序表里 
	for (j = 0; j < L.length; j++) {
		L.r[j+1] = temp[(first + j) % L.length];
		swapTimes++;
	}
	return L;
}
//希尔排序
void ShellInsert(SqList &L, int dk) {
	//对顺序表L做一趟增量是dk的希尔插入排序
	int i, j;
	for (i = dk + 1; i <= L.length; i++) {
		if (L.r[i].key < L.r[i - dk].key) {//需将L.r[i]插入有序增量子表
			compareTimes++;
			swapTimes++;
			L.r[0] = L.r[i];				//暂存在L.r[0]
			for (j = i - dk; j > 0 && L.r[0].key < L.r[j].key; j -= dk) {
				L.r[j + dk] = L.r[j];		//记录后移，直到找到插入位置
				compareTimes++;
				swapTimes++;
			}
			swapTimes++;
			L.r[j + dk] = L.r[0];			//将r[0]即原r[i],插入到正确位置
		}
	}
}
SqList ShellSort(SqList L) {
	//希尔排序
	swapTimes = 0;
	compareTimes = 0;
	int dt[MAXSIZE/4];
	int k;
	for (int i = 0; i < MAXSIZE / 4; i++) {//得到增量表
		dt[MAXSIZE / 4-i-1] = i * 2 + 1;
	}
	for (k = (MAXSIZE-L.length)/4; k < MAXSIZE / 4; k++) {
		ShellInsert(L, dt[k]);				//一趟增量为dt[k]的希尔插入排序
	}
	return L;
}
//冒泡排序
SqList BubbleSort(SqList L) {
	// 起泡排序
	swapTimes = 0;
	compareTimes = 0;
	int j;
	RedType t;
	int m = L.length - 1,flag = 1;//falg用来标记某一趟排序是否发送交换
	while ((m > 0) && flag == 1) {
		flag = 0;				//flag置为0，如果本趟排序没有发生交换，则不会执行下一趟排序
		for(j=1;j<=m;j++)
			if (L.r[j].key > L.r[j + 1].key) {
				swapTimes+=3;
				compareTimes++;
				flag = 1;		//flag置为1，表示本次排序发生了交换
				t = L.r[j];		//交换前后的两个记录
				L.r[j] = L.r[j + 1];
				L.r[j + 1] = t;
			}
		m--;
	}
	return L;
}
//快速排序
int Partition(SqList &L, int low ,int  high) {
	L.r[0] = L.r[low];			//用子表的第一个记录做枢轴记录
	swapTimes+=2;
	int pivotkey = L.r[low].key;//枢轴记录关键字保存在pivotkey中
	while (low < high) {		//从表两端交替地向中间扫描
		while (low < high&&L.r[high].key >= pivotkey) {
			high--;
			compareTimes++;
		}
		swapTimes++;
		L.r[low] = L.r[high];	//将比枢轴记录小的记录移到低端
		while (low < high&&L.r[low].key <= pivotkey) {
			low++;
			compareTimes++;
		}
		swapTimes++;
		L.r[high] = L.r[low];	//将比枢轴记录大的记录移到高端
	}
	swapTimes++;
	L.r[low] = L.r[0];			//枢轴记录到位
	return low;					//返回枢轴位置
}
void QSort(SqList &L, int low, int high) {
	int pivotloc;
	if (low < high) {				//长度大于1
		pivotloc = Partition(L, low, high);//将L.r[low..high]一分为二，pivotloc是枢轴位置
		QSort(L,low,pivotloc-1);		//对左子表递归排序
		QSort(L, pivotloc +1,high);		//对右子表递归排序
	}
}
SqList QuickSort(SqList L) {
	//快速排序
	swapTimes = 0;
	compareTimes = 0;
	QSort(L, 1, L.length);
	return L;
}
//简单选择排序
SqList SelectionSort(SqList L) {
	//简单选择排序
	swapTimes = 0;
	compareTimes = 0;
	int i, j, k;
	RedType t;
	for (i = 1; i < L.length; i++) {		//在L.r[i..L.length]中选择关键字最小的记录
		k = i;
		for (j = i + 1; j <= L.length; j++) {
			if (L.r[j].key < L.r[k].key) {	//k指向此趟排序中关键字最小的记录
				k = j;
				compareTimes++;
			}
		}
		if (k != i) {					//交换r[i]与r[k]
			swapTimes += 3;
			t = L.r[i];
			L.r[i] = L.r[k];
			L.r[k] = t;
		}
	}
	return L;
}
//堆排序
void HeapAdjust(SqList &L, int s, int m) {
	//调整为大根堆
	RedType rc = L.r[s];
	swapTimes++;
	int j;
	for (j = 2 * s; j <= m; j *= 2) {		//沿Key较大的孩子结点向下筛选
		if (j < m&&L.r[j].key < L.r[j + 1].key) {
			j++;							//j为key较大的记录的下标
			compareTimes++;
		}
		if (rc.key >= L.r[j].key) {
			compareTimes++;
			break;							//rc应该插入在位置s上
		}
		L.r[s] = L.r[j];
		swapTimes++;
		s = j;
	}
	L.r[s] = rc;							//插入
	swapTimes++;
}
void CreatHeap(SqList &L) {
	//无序序列建成大根堆
	int n = L.length;
	for (int i = n / 2; i > 0; i--) {		//反复调用HeapAdjust
		HeapAdjust(L, i, n);
	}
}
SqList HeapSort(SqList L) {
	//堆排序
	swapTimes = 0;
	compareTimes = 0;
	RedType t;
	CreatHeap(L);							//把无序表建成大根堆
	for (int i = L.length; i > 1; i--) {
		swapTimes += 3;
		t = L.r[1];							//将堆顶记录和当前为经排序子序列中最后一个记录互换
		L.r[1] = L.r[i];
		L.r[i] = t;
		HeapAdjust(L, 1, i - 1);			//重新调整为大根堆
	}
	return L;
}
//归并排序
void Merge(RedType R[], RedType T[], int low, int mid, int high) {
	//将有序表R[low..mid]和R[mid+1..high]归并程有序表T[low..high]
	int i = low, j = mid + 1, k = low;
	while (i <= mid&&j <= high) {
		compareTimes++;
		swapTimes++;
		if (R[i].key <= R[j].key)
			T[k++] = R[i++];
		else
			T[k++] = R[j++];
	}
	while (i <= mid) {
		T[k++] = R[i++];
		swapTimes++;
	}
	while (j <= high) {
		T[k++] = R[j++];
		swapTimes++;
	}
}
void MSort(RedType R[], RedType T[], int low, int high) {
	//R归并排序后放入T中
	RedType S[MAXSIZE];
	int mid;
	if (low == high) {
		T[low] = R[low];
		swapTimes++;
	}
	else {
		mid = (low + high) / 2;
		MSort(R, S, low, mid);
		MSort(R, S, mid + 1, high);
		Merge(S, T, low, mid, high);
	}
}
SqList MergeSort(SqList L) {
	//归并排序
	swapTimes = 0;
	compareTimes = 0;
	MSort(L.r, L.r, 1, L.length);
	return L;
}

void printList(SqList L) {
	//打印
	int i;
	printf("\n");
	for (i = 1; i <= L.length; i++) {//打印关键字
		printf("%-4d  ", L.r[i].key);
	}
	printf("\n原顺序              ");
	printf("\n");
	for (i = 1; i <= L.length; i++) {//打印原顺序
		printf("%-4d  ", L.r[i].info);
	}
	printf("\n");
	
}
void getStandardDeviation(SqList L[],int m) {
	//计算标准差
	double compareAll=0;
	double swapAll = 0;
	double compareVari=0;
	double swapVari=0;
	for (int i = 0; i < m; i++) {
		compareAll += L[i].compareT;
		swapAll += L[i].swapT;
	}
	compareAll /= double(m);
	swapAll /= double(m);
	for (int i = 0; i < m; i++) {
		compareVari += ((L[i].compareT- compareAll)*(L[i].compareT - compareAll));
		swapVari += ((L[i].swapT- swapAll)*(L[i].swapT - swapAll));
	}
	compareVari /= double(m);
	swapVari /= double(m);
	printf("\n\n标准差—— 交换：%-6.2f，比较：%-6.2f\n",sqrt(swapVari), sqrt(compareVari));
}
bool isStable(SqList L) {
	int i;
	for (i = 2; i <= L.length; i++) {
		if ((L.r[i - 1].key == L.r[i].key)&& (L.r[i - 1].info > L.r[i].info)) {
			printf("该排序不稳定\n");
			return false;
		}
	}
	printf("该排序稳定\n");
	return true;
}

void method1() {
	std::cout << "请输入表长(大于100，小于1000)：";
	int n;
	std::cin >> n;
	SqList L = SqList();
	procTable(L, n);
	printf("\n无序表:             ");
	printList(L);
	printf("\nInsertionSort:      ");
	printList(InsertionSort(L));
	isStable(InsertionSort(L));
	printf("\nBinaryInsertionSort:");
	printList(BinaryInsertionSort(L));
	isStable(BinaryInsertionSort(L));
	printf("\nTwoWayInsertionSort:");
	printList(TwoWayInsertionSort(L));
	isStable(TwoWayInsertionSort(L));
	printf("\nShellSort:          ");
	printList(ShellSort(L));
	isStable(ShellSort(L));
	printf("\nBubbleSort:         ");
	printList(BubbleSort(L));
	isStable(BubbleSort(L));
	printf("\nQuickSort:          ");
	printList(QuickSort(L));
	isStable(QuickSort(L));
	printf("\nSelectionSort:      ");
	printList(SelectionSort(L));
	isStable(SelectionSort(L));
	printf("\nHeapSort:           ");
	printList(HeapSort(L));
	isStable(HeapSort(L));
	printf("\nMergeSort:          ");
	printList(MergeSort(L));
	isStable(MergeSort(L));
}
void method2() {
	std::cout << "请输入表长(大于100，小于1000)：";
	int n;
	std::cin >> n;
	std::cout << "请输入循环次数：";
	int m;
	std::cin >> m;
	SqList L[100];
	for (int i = 0; i < m; i++) {
		L[i] = SqList();
		procTable(L[i], n);
	}
	printf("\nInsertionSort:      ");
	for (int i = 0; i < m; i++) {
		InsertionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nBinaryInsertionSort:");
	for (int i = 0; i < m; i++) {
		BinaryInsertionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nTwoWayInsertionSort:");
	for (int i = 0; i < m; i++) {
		TwoWayInsertionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nShellSort:          ");
	for (int i = 0; i < m; i++) {
		ShellSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nBubbleSort:         ");
	for (int i = 0; i < m; i++) {
		BubbleSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nQuickSort:          ");
	for (int i = 0; i < m; i++) {
		QuickSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nSelectionSort:      ");
	for (int i = 0; i < m; i++) {
		SelectionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nHeapSort:           ");
	for (int i = 0; i < m; i++) {
		HeapSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nMergeSort:          ");
	for (int i = 0; i < m; i++) {
		MergeSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);

}
void method3() {
	std::cout << "请输入表长初值与增量：";
	int n;
	std::cin >> n;
	int d;
	std::cin >> d;
	std::cout << "请输入循环次数：";
	int m;
	std::cin >> m;
	SqList L[100];
	printf("表长：              ");
	for (int i = 0; i < m; i++) {
		printf("%-29d", n);
		L[i] = SqList();
		procTable(L[i], n);
		n += d;
	}
	
	printf("\n\nInsertionSort:      ");
	for (int i = 0; i < m; i++) {
		InsertionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nBinaryInsertionSort:");
	for (int i = 0; i < m; i++) {
		BinaryInsertionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nTwoWayInsertionSort:");
	for (int i = 0; i < m; i++) {
		TwoWayInsertionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nShellSort:          ");
	for (int i = 0; i < m; i++) {
		ShellSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nBubbleSort:         ");
	for (int i = 0; i < m; i++) {
		BubbleSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nQuickSort:          ");
	for (int i = 0; i < m; i++) {
		QuickSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nSelectionSort:      ");
	for (int i = 0; i < m; i++) {
		SelectionSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nHeapSort:           ");
	for (int i = 0; i < m; i++) {
		HeapSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
	printf("\nMergeSort:          ");
	for (int i = 0; i < m; i++) {
		MergeSort(L[i]);
		printf("交换：%-6d，比较：%-6d   ", swapTimes, compareTimes);
		L[i].compareT = compareTimes;
		L[i].swapT = swapTimes;
	}
	getStandardDeviation(L, m);
}
void method4() {
	std::cout << "请输入表长(大于100，小于1000)：";
	int n;
	std::cin >> n;
	SqList L = SqList();
	procTable(L, n);

	printf("\nInsertionSort:      ");
	isStable(InsertionSort(L));
	printf("\nBinaryInsertionSort:");
	isStable(BinaryInsertionSort(L));
	printf("\nTwoWayInsertionSort:");
	isStable(TwoWayInsertionSort(L));
	printf("\nShellSort:          ");
	isStable(ShellSort(L));
	printf("\nBubbleSort:         ");
	isStable(BubbleSort(L));
	printf("\nQuickSort:          ");
	isStable(QuickSort(L));
	printf("\nSelectionSort:      ");
	isStable(SelectionSort(L));
	printf("\nHeapSort:           ");
	isStable(HeapSort(L));
	printf("\nMergeSort:          ");
	isStable(MergeSort(L));
}
int main()
{
	srand((unsigned)time(0));
	int n;
	std::cout << "1，查看排序结果\n2，查看两个指标计算几组数据的波动\n3，检查两个指标相关于表长的变化关系\n4，检验每种排序的稳定性\n请选择操作：";
	std::cin >> n;
	switch (n) {
	case 1:
		method1();
		break;
	case 2:
		method2();
		break;
	case 3:
		method3();
		break;
	case 4:
		method4();
		break;
	}
	
	return 0;
}

