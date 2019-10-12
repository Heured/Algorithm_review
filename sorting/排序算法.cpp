#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

// 选择,O(n^2)
// 由i将数组分为(0,i-1)有序区，(i,n-1)无序区 
// 每次循环在数组中r[i]以后的元素内找出最小值的位置，
//  将r[i]与该位置的值互换,i++
void SelectSort(int r[],int n){
	int i,j,temp,index;
	for(int i=0;i<n-1;i++){
		index = i;
		for(int j=i+1;j<n;j++)
			if(r[j]<r[index])
				index = j;
		if(index!=i){
			temp = r[i];
			r[i] = r[index];
			r[index] = temp;
		}
	}
}

// 冒泡,O(n^2)
// 由bound将数组分为(0,bound)无序区和(bound+1,n-1)有序区
// 每次循环将(0,bound)里的最大值置换到r[bound]此时j=bound-1 
void BubbleSort(int r[],int n){
	int bound,exchange = n-1;	//exchange记录上次循环最后一次值交换的位置
	while(exchange != 0){
		bound = exchange;
		exchange = 0;
		for(int j=0;j<bound;j++){
			if(r[j]>r[j+1]){
				int temp = r[j];
				r[j] = r[j+1];
				r[j+1] = temp;
				exchange = j;
			}
		}
	}
}


// 插入,O(n^2)
// 由i将数组分为(0,i-1)有序区和(i,n-1)无序区
// 每次循环将r[i]插入(0,i-1),i++
void swap(int r[],int j,int k){
	int temp=r[j];
	r[j] = r[k];
	r[k] = temp;
}
void InsertSort(int r[],int n){
	for(int i=1;i<n;i++){
		for(int j=i;j>0;j--){
			if(r[j]<r[j-1]){
				swap(r,j,j-1);
			}
		}
	}
}
void InsertSort2(int r[],int n){
	for(int i=1;i<n;i++){
		int j;
		int temp = r[i];
		for(j=i; j>0&&temp<r[j-1]; j--){
			r[j] = r[j-1];
		}
		r[j] = temp;
	}
}

//快排,O(nlog2n)
//采用递归的方法，将数组划分为两个区域，并且两个区域由r[pivot]这个轴值划分
// 接下来将两个区域递归向下划分
int Partition(int r[],int first,int end){
	int i=first, j=end;
	while(i<j){
		// 右向左扫描 
		while(i<j&&r[i] <= r[j])
			j--;
		// 将较小值置换到前面 
		if(i<j){
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i++;
		}
		// 左向右扫描		
		while(i<j&&r[i] <= r[j])
			i++;
		// 将较大值置换到后面 
		if(i<j){
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			j--;
		}
	}
	// 最后i，j会交汇在一个点上
	return i;
}
void QuickSort(int r[],int first,int end){
	int pivot;
	if(first<end){
		pivot = Partition(r,first,end);	//划分，pivot为轴值
		QuickSort(r,first,pivot-1);	//划分的小问题1
		QuickSort(r,pivot+1,end);	//划分的小问题2 
	}
}

// 归并，O(nlog2n)
// 对半分为两个子序列，递归向下分，
// 升序子序列合并，递归向上合并
void Merge(int r[],int r1[],int s,int m, int t){
	int i=s,j=m+1,k=s; 
	while(i<=m&&j<=t){
		// 取r[i]和r[j]较小的放入r1[k] 
		if(r[i]<=r[j])
			r1[k++] = r[i++];
		else
			r1[k++] = r[j++];
	}
	// 第一个子序列没处理完 
	while(i<=m)
		r1[k++] = r[i++];
	// 第二个子序列没处理完 
	while(j<=t)
		r1[k++] = r[j++];
}
void MergeSort(int r[],int s,int t){
	int m,r1[1000];
	if(s==t) return;	//递归边界条件 
	else{
		m = (s+t)/2;
		MergeSort(r,s,m);	// 求解子问题1，归并排序前半个子序列
		MergeSort(r,m+1,t);	// 求解子问题2，归并排序后半个子序列 
		Merge(r,r1,s,m,t);	// 合并两个有序子序列，存入r1 
		// 将有序序列传回数组r 
		for(int i=s;i<=t;i++)
			r[i] = r1[i];
	}
}

// 堆排序
void SiftHeap(int r[],int k,int n){
	int i,j,temp;
	i=k;	// i为要筛的节点 
	j=2*i+1;	// j为i的左孩子 
	while(j<n){
		// 比较i的左右孩子，取较大者 
		if(j<n-1 && r[j]<r[j+1]) j++;
		// 根节点已经大于左右孩子中的较大者 
		if(r[i]>r[j])
			break;
		// 将被筛选结点与节点j交换 
		else{
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;

			i = j;
			j = 2*i+1;
		}
	}
}
// 大根堆堆排序 
void HeapSort(int r[],int n){
	int i,temp;
	// 初始建堆，最后一个分支的下标是(n-1)/2 
	for(i=(n-1)/2;i>=0;i--)
		SiftHeap(r,i,n);
	// 此时r[0]为最大值，将其与n-i的值置换，
	//  将剩下的(0,n-i-1)重新建树，循环取根节点值 
	for(i=1;i<=n-1;i++){
		temp = r[0];
		r[0] = r[n-i];
		r[n-i] = temp;
		
		SiftHeap(r,0,n-i);
	}
}

// 希尔排序 
void ShellSort(int r[],int n){
	// 进行分组，最开始的增量(gap)为数组长度的一半
	for(int gap = n/2;gap>0;gap/=2){
		// 对各个分组进行插入排序 
		for(int i=gap; i<n; i++){
			int temp = r[i];
			int j;
			for(j=i; j>0&&temp<r[j-gap]; j-=gap){
				r[j] = r[j-gap];
			}
			r[j] = temp;
		}
	}
}


// 计数排序
void CountingSort(int r[],int n){
	int max,min;
	//获取最大最小值 
	for(int i=0;i<n;i++){
		if(i==0){
			max = r[i];
			min = r[i];
		}else{
			if(max<r[i]) max = r[i];
			if(min>r[i]) min = r[i];
		}
	}
	
	int size = max-min+1;	//计算新数组长度 
	int count[size],psort[n];
	memset(count,0,sizeof(int)*size);	//将新数组元素置0 
	memset(psort,0,sizeof(int)*n);
	// 记录数组r的每种元素个数 
	for(int i=0;i<n;i++)
		count[r[i]-min]++;
	// 累加来记录位置 
	for(int i=1;i<size;i++)
		count[i]+=count[i-1];
	// 将位置映射到新数组来实现排序 
	for(int i=n-1;i>=0;i--){
		count[r[i]-min]--;
		psort[count[r[i]-min]] = r[i];
	}
	// 将新数组的元素复制回原数组 
	for(int i=0;i<n;i++)
		r[i] = psort[i];
	
	/*// 这样会增加时间复杂度，并且没有稳定性
	// 所谓稳定性表示:一群学生事先用学号排好了序
	//	现在要他们用身高再排一次序
	//	此时身高相同的几个同学依然保持使用学号来分先后
	for(int i=0,k=0;i<size;i++){
		while(count[i]>0){
			r[k++] = i+min;
			count[i]--;
		}
	}
	*/
}

//基数排序
void RadixSort(int r[],int n){
	int result[n];
	int count[10];	//每位只有0-9十种可能 
	memset(count,0,sizeof(int)*10);
	int max=r[0],gap=0;//最大的数，最大数的位数 
	
	for(int i=1;i<n;i++)
		if(max<r[i]) max = r[i];
	while(max>0){
		max/=10;
		gap++;
	}
	cout<<gap<<endl;
	
	for(int j=0;j<gap;j++){
		int division = (int)pow(10,j);
		//记录个数 
		for(int i=0;i<n;i++){
			int num = r[i]/division%10;
			count[num]++;
		}
		
		//累加记录位置 
		for(int i=1;i<10;i++)
			count[i] += count[i-1];
			
		for(int i=0;i<10;i++){
			cout<<count[i]<<' ';
		}
		cout<<endl;
		
		for(int i=n-1;i>=0;i--){
			int num = r[i]/division%10;
			result[--count[num]] = r[i];
		}
		memcpy(r,result,sizeof(int)*n);
		memset(count,0,sizeof(int)*10);
		
		for(int i=0;i<n;i++){
			cout<<r[i]<<' ';
		}
		cout<<endl;
	}
	
}


main(){;
//	int r[]={9,6,1,3,5},n=5;
	int r[]={421,240,115,532,305,430,124},n=7;
//	CountingSort(r,n);
//	QuickSort(r,0,n-1);
	RadixSort(r,n);
	for(int i=0;i<n;i++){
		cout<<r[i]<<' ';
	}
}
