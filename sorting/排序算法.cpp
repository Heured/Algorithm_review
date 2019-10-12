#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

// ѡ��,O(n^2)
// ��i�������Ϊ(0,i-1)��������(i,n-1)������ 
// ÿ��ѭ����������r[i]�Ժ��Ԫ�����ҳ���Сֵ��λ�ã�
//  ��r[i]���λ�õ�ֵ����,i++
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

// ð��,O(n^2)
// ��bound�������Ϊ(0,bound)��������(bound+1,n-1)������
// ÿ��ѭ����(0,bound)������ֵ�û���r[bound]��ʱj=bound-1 
void BubbleSort(int r[],int n){
	int bound,exchange = n-1;	//exchange��¼�ϴ�ѭ�����һ��ֵ������λ��
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


// ����,O(n^2)
// ��i�������Ϊ(0,i-1)��������(i,n-1)������
// ÿ��ѭ����r[i]����(0,i-1),i++
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

//����,O(nlog2n)
//���õݹ�ķ����������黮��Ϊ�������򣬲�������������r[pivot]�����ֵ����
// ����������������ݹ����»���
int Partition(int r[],int first,int end){
	int i=first, j=end;
	while(i<j){
		// ������ɨ�� 
		while(i<j&&r[i] <= r[j])
			j--;
		// ����Сֵ�û���ǰ�� 
		if(i<j){
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i++;
		}
		// ������ɨ��		
		while(i<j&&r[i] <= r[j])
			i++;
		// ���ϴ�ֵ�û������� 
		if(i<j){
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			j--;
		}
	}
	// ���i��j�ύ����һ������
	return i;
}
void QuickSort(int r[],int first,int end){
	int pivot;
	if(first<end){
		pivot = Partition(r,first,end);	//���֣�pivotΪ��ֵ
		QuickSort(r,first,pivot-1);	//���ֵ�С����1
		QuickSort(r,pivot+1,end);	//���ֵ�С����2 
	}
}

// �鲢��O(nlog2n)
// �԰��Ϊ���������У��ݹ����·֣�
// ���������кϲ����ݹ����Ϻϲ�
void Merge(int r[],int r1[],int s,int m, int t){
	int i=s,j=m+1,k=s; 
	while(i<=m&&j<=t){
		// ȡr[i]��r[j]��С�ķ���r1[k] 
		if(r[i]<=r[j])
			r1[k++] = r[i++];
		else
			r1[k++] = r[j++];
	}
	// ��һ��������û������ 
	while(i<=m)
		r1[k++] = r[i++];
	// �ڶ���������û������ 
	while(j<=t)
		r1[k++] = r[j++];
}
void MergeSort(int r[],int s,int t){
	int m,r1[1000];
	if(s==t) return;	//�ݹ�߽����� 
	else{
		m = (s+t)/2;
		MergeSort(r,s,m);	// ���������1���鲢����ǰ���������
		MergeSort(r,m+1,t);	// ���������2���鲢������������� 
		Merge(r,r1,s,m,t);	// �ϲ��������������У�����r1 
		// ���������д�������r 
		for(int i=s;i<=t;i++)
			r[i] = r1[i];
	}
}

// ������
void SiftHeap(int r[],int k,int n){
	int i,j,temp;
	i=k;	// iΪҪɸ�Ľڵ� 
	j=2*i+1;	// jΪi������ 
	while(j<n){
		// �Ƚ�i�����Һ��ӣ�ȡ�ϴ��� 
		if(j<n-1 && r[j]<r[j+1]) j++;
		// ���ڵ��Ѿ��������Һ����еĽϴ��� 
		if(r[i]>r[j])
			break;
		// ����ɸѡ�����ڵ�j���� 
		else{
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;

			i = j;
			j = 2*i+1;
		}
	}
}
// ����Ѷ����� 
void HeapSort(int r[],int n){
	int i,temp;
	// ��ʼ���ѣ����һ����֧���±���(n-1)/2 
	for(i=(n-1)/2;i>=0;i--)
		SiftHeap(r,i,n);
	// ��ʱr[0]Ϊ���ֵ��������n-i��ֵ�û���
	//  ��ʣ�µ�(0,n-i-1)���½�����ѭ��ȡ���ڵ�ֵ 
	for(i=1;i<=n-1;i++){
		temp = r[0];
		r[0] = r[n-i];
		r[n-i] = temp;
		
		SiftHeap(r,0,n-i);
	}
}

// ϣ������ 
void ShellSort(int r[],int n){
	// ���з��飬�ʼ������(gap)Ϊ���鳤�ȵ�һ��
	for(int gap = n/2;gap>0;gap/=2){
		// �Ը���������в������� 
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


// ��������
void CountingSort(int r[],int n){
	int max,min;
	//��ȡ�����Сֵ 
	for(int i=0;i<n;i++){
		if(i==0){
			max = r[i];
			min = r[i];
		}else{
			if(max<r[i]) max = r[i];
			if(min>r[i]) min = r[i];
		}
	}
	
	int size = max-min+1;	//���������鳤�� 
	int count[size],psort[n];
	memset(count,0,sizeof(int)*size);	//��������Ԫ����0 
	memset(psort,0,sizeof(int)*n);
	// ��¼����r��ÿ��Ԫ�ظ��� 
	for(int i=0;i<n;i++)
		count[r[i]-min]++;
	// �ۼ�����¼λ�� 
	for(int i=1;i<size;i++)
		count[i]+=count[i-1];
	// ��λ��ӳ�䵽��������ʵ������ 
	for(int i=n-1;i>=0;i--){
		count[r[i]-min]--;
		psort[count[r[i]-min]] = r[i];
	}
	// ���������Ԫ�ظ��ƻ�ԭ���� 
	for(int i=0;i<n;i++)
		r[i] = psort[i];
	
	/*// ����������ʱ�临�Ӷȣ�����û���ȶ���
	// ��ν�ȶ��Ա�ʾ:һȺѧ��������ѧ���ź�����
	//	����Ҫ�������������һ����
	//	��ʱ�����ͬ�ļ���ͬѧ��Ȼ����ʹ��ѧ�������Ⱥ�
	for(int i=0,k=0;i<size;i++){
		while(count[i]>0){
			r[k++] = i+min;
			count[i]--;
		}
	}
	*/
}

//��������
void RadixSort(int r[],int n){
	int result[n];
	int count[10];	//ÿλֻ��0-9ʮ�ֿ��� 
	memset(count,0,sizeof(int)*10);
	int max=r[0],gap=0;//���������������λ�� 
	
	for(int i=1;i<n;i++)
		if(max<r[i]) max = r[i];
	while(max>0){
		max/=10;
		gap++;
	}
	cout<<gap<<endl;
	
	for(int j=0;j<gap;j++){
		int division = (int)pow(10,j);
		//��¼���� 
		for(int i=0;i<n;i++){
			int num = r[i]/division%10;
			count[num]++;
		}
		
		//�ۼӼ�¼λ�� 
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
