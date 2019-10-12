#include<iterator>
#include<iostream>
#include<vector>
using namespace std;
const int BUCKET_NUM = 10;

struct ListNode{
	explicit ListNode(int i=0): mData(i),mNext(NULL){}
	ListNode* mNext;
	int mData;
};

// ��Ԫ�ز����������� 
ListNode* Insert(ListNode* head,int val){
	ListNode dummyNode;
	ListNode *newNode = new ListNode(val);
	ListNode *pre,*curr;
	dummyNode.mNext = head;
	pre = &dummyNode;
	curr = head;
	while(curr!=NULL && curr->mData<=val){
		pre = curr;
		curr = curr->mNext;
	}
	newNode->mNext = curr;
	pre->mNext = newNode;
	return dummyNode.mNext;
}

// ��������鲢 
ListNode* Merge(ListNode *head1, ListNode *head2){
	ListNode dummyNode;
	ListNode *dummy = &dummyNode;
	while(head1!=NULL && head2!=NULL){
		if(head1->mData <= head2->mData){
			dummy->mNext = head1;
			head1 = head1->mNext;
		}else{
			dummy->mNext = head2;
			head2 = head2->mNext;
		}
		dummy = dummy->mNext;
	}
	if(head1!=NULL) dummy->mNext = head1;
	if(head2!=NULL) dummy->mNext = head2;

	return dummyNode.mNext;
}

void BucketSort(int r[], int n){
	int min,max,bucketNum;
	// ȷ��Ͱ���� 
	for(int i=0;i<n;i++){
		if(i==0){
			min = r[i];
			max = r[i];
		}else{
			if(min>r[i]) min = r[i];
			if(max<r[i]) max = r[i];
		}
	}
	bucketNum = max/10 - min/10 +1;
	
	// ����������Ԫ����Ͱ 
	vector<ListNode*> buckets(bucketNum,(ListNode*)(0));
	for(int i=0;i<n;++i){
		int index = r[i]/10 - min/10; // ��ַӳ�� 
		ListNode *head = buckets.at(index);
		buckets.at(index) = Insert(head,r[i]);
	}
	// ���й鲢 
	ListNode *head = buckets.at(0);
	for(int i=1;i<bucketNum;++i){
		head = Merge(head,buckets.at(i));
	}
	// ������ӳ������� 
	for(int i=0;i<n;++i){
		r[i] = head->mData;
		head = head->mNext;
	}

}

main(){
	int a[] = {63,157,189,51,101,47,141,121,157,156,194,117,98,139,67,133,181,13,28,109};
	int n = 20;
	
	
	BucketSort(a,n);
	for(int i=0;i<n;i++){
		cout<<a[i]<<' ';
	}
}


