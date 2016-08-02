#pragma once
#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
void Print(int *a,int n)
{
	for(int i=0;i<10;i++)
	{
	 cout<<a[i]<<" ";
	}
	cout<<endl;
}
//1直接插入排序
void InsertSort(int* a,int n)
{
	assert(a);
	int i,j ,tmp;
	for(i=1;i<n;i++)
	{
		 if(a[i-1]>a[i])
		 {
			 tmp=a[i];
			 j=i;
			 while(j>=0&&a[j-1]>tmp)
			 {
			  a[j]=a[j-1];
			  j--;
			 }
			 a[j]=tmp;
		 }
	}
}

//2希尔排序
void ShellSort(int *a,int n)
{
	 assert(a);
	 int gap=n;
	 while(gap>1)
	 {
		 gap=gap/3+1;
		 for(int i=0;i<n-gap;i++)
		 {
			  int end=i;
			  int tmp=a[end+gap];
		  while(end>=0&&a[end]>tmp)
			  {
			   a[end+gap]=a[end];
			   end=end-gap;
			  }
			  a[end+gap]=tmp;
		 }
	 }
}
//3选择排序
void SeclectSort(int *a,int n)
{
	assert(a);
	int minindex;
	for(int i=0;i<n-1;i++)
	{
	  minindex=i;
	  for(int j=i+1;j<n;j++)
	  {
	   if(a[j]<a[minindex])
	   {
	   minindex=j;
	   }
	  }
	  swap(a[minindex],a[i]);
	}
}
//4选择排序的优化(每次都选出一个最大值和一个最小值)
void SeclectSortop(int *a,int n)
{
	assert(a);
	int left=0;
	int right=n-1;
	while(left<right)
	{
		 int minindex=left;
		 int maxindex=left;
		 for(int i=left+1;i<=right;i++)
		 {
			  if(a[i]<a[minindex])
			  {
			   minindex=i;
			  }
			  if(a[i]>a[maxindex])
			  {
			   maxindex=i;
			  }
			  
		 }
		 //{9,5,4,9,3,6,8,7,1,0};
		 //存在缺陷，当最大的占了最小的位置或者最小的占了最大的位置时交换会失败
		/* swap(a[left],a[minindex]);
	     swap(a[right],a[maxindex]);
		 ++left;
	     --right;*/
		 swap(a[left],a[minindex]);
		 if(a[maxindex]==a[left])
		 {
		  maxindex=minindex;
		 }
		 swap(a[right],a[maxindex]);
		 ++left;
		 --right;
	}

}
//5堆排序
void _AdjustDown(int* a,int n,int parent)
 {
	  assert(a);
	  int child=2*parent+1;
	  while(child<n)
	  {
			if(child+1<n &&a[child]<a[child+1])
			{
			++child;
			}
			if(a[parent]<a[child])
			{
			  swap(a[parent],a[child]);
			  parent=child;
			  child=2*parent+1;
			}
			else
			{
			 break;
			}
	  }
 }
void HeapSort(int* a,int n)
{
	//1建大堆
	for(int i=(n-2)/2;i>=0;i--)
	{
	 _AdjustDown(a,n,i);
	}
	//2选出一个数据交换到末尾
	for(int j=n-1;j>=0;j--)
	{
		swap(a[0],a[j]);
	 _AdjustDown(a,j,0);
	}
}
//6冒泡排序
void Bubsort(int* a,int n)
{
  assert(a);
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n-i-1;j++)
	{
	  if(a[j]>a[j+1])
	  {
	  swap(a[j],a[j+1]);
	  }
	 
	}
  }
}
//7快速排序(挖坑法)
int partsort1(int *a,int left,int right)
 {
    int begin=left;
	int end=right;
	int key=a[left];
	while(begin<end)
	{
	while(begin<end&& a[end]>=key)
		end--;
	if(begin<end)
	{
		a[begin]=a[end];
	    begin++;
	
	}
	while(begin<end && a[begin]<=key)
		begin++;
	if(begin<end)
	{
	a[end]=a[begin];
	end--;
	}
 }
	a[begin]=key;
	return begin;
}

void Quicksort1(int *a,int left,int right)
{
	assert(a);
	if(left<right)
	{
		 int div=partsort1(a,left,right);
		 Quicksort1(a,left,div-1);
		 Quicksort1(a,div+1,right);
	 
	}
 }

 

 int GetMidindex(int* a,int left,int right)
 {
	  int mid=left+(right-left)/2;
	  if(a[left]<a[mid])
	  {
        if(a[mid]<a[right])
			return a[mid];
		else if(a[left]>a[right])
			return a[left];
		else
			return a[right];
	  }
	  else
	  {
        if(a[mid]>a[right])
			return a[mid];
		else if(a[left]<a[right])
			return a[left];
		else
			return a[right];
	  }
 }


 //8快速排序优化(prev-cur）
 void Quicksort2(int* a,int left,int right)
 {
	int mid=GetMidindex(a,left,right);
	swap(mid,right);
	int cur=left;
	int prev=left-1;
	while(cur<right)
	{
	  if(a[cur]<a[right] &&++prev!=cur)
	    swap(a[++prev],a[cur]);
	     ++cur;
	}
	swap(a[++prev],a[right]);

	if(prev-1>left)
	   Quicksort2(a,left,prev-1);
	if(prev+1<right)
	   Quicksort2(a,prev+1,right);

 }
 //9快速排序处理大数据时的优化
 void Quicksort3(int* a,int left,int right)
 {
	  assert(a);
	  if(left>=right)
	  {
	   return;
	  }
	  if(right-left<16)
	  {
	  InsertSort(a+left,right-left+1);
	  }
	  else
	  {
	   int div=partsort1(a,left,right);
	   Quicksort3(a,left,div-1);
	   Quicksort3(a,div+1,right);
	  }
 }

//11快速排序的非递归实现方法,将一个函数由递归变为非递归有两种方法，分别为循环和栈

 void QuickSort_NonR(int* a,int left,int right)
 {
	 assert(a);
	 stack<int>s;
	 s.push(left);
	 s.push(right);
	 size_t max=0;
		  while(!s.empty())
		  {
			  if(s.size()>max)
				  max=s.size ();

			  int end=s.top();
			  s.pop();
			  int begin=s.top();
			  s.pop();
			  int mid=partsort1(a,begin,end);
			  if(begin<mid-1)
			  {
			  s.push(begin);
			  s.push(mid-1);
			  }
			  if(mid+1<end)
			  {
			  s.push(mid+1);
			  s.push(end);
			  }
		  }
	 }
	 

 //12归并排序
 void Merge(int* a,int* tmp,int begin1,int end1,int begin2,int end2)
 {
	  int index=begin1;
	  while(begin1<=end1 && begin2<=end2)
	  {
		   if(a[begin1]<a[begin2])
		   {
			tmp[index]=a[begin1];
			++begin1;
		   }
		   else
		   {
			tmp[index]=a[begin2];
			++begin2;
		   }
		   ++index;
	 }

	  while(begin1<=end1)
	  {
	  tmp[index++]=a[begin1++];
	  }

	  while(begin2<=end2)
	  {
	   tmp[index++]=a[begin2++];
	  }

 }

void  mergesort(int* a,int* tmp,int left,int right)
{
	//只有一个数据或没有数据则直接返回
	if(left>=right)
		return;
	int mid=left+(right-left)/2;
	//[left,mid] [mid+1,right]
	mergesort(a,tmp,left,mid);
	mergesort(a,tmp,mid+1,right);
	Merge(a,tmp,left,mid,mid+1,right);
	memcpy(a+left,tmp+left,(right-left+1)*sizeof(int));

}

void  Mergesort(int* a,int n) 
{
	assert(a);
	//开辟一个和a同等大小的空间，用来存放排好的数据
	int* tmp=new int[n];
	mergesort(a,tmp,0,n);
	delete [] tmp;
}

//13记数排序---最快的排序 时间复杂度为O（n）
//15基数排序---时间复杂度 O(N*位数) 空间复杂度O(N)

int Maxbit(int* a,int n)//获取数组中最大数的位数
{
	int max=10;
	int bit=1;
	for(int i=0;i<n;i++)
	{
	 if(a[i]>max)
	 {
	 ++bit;
	 max*=10;
	 }
	}
	return bit;
}
//
void _PartRadix(int* a,int n,int div)
{
	int count[10]={0};
	//处理数组count统计每个数字的个，十，拜，等位出现的次数
	for(int i=0;i<n;i++)
	{
	 int num=a[i]/div;
	 count[num%10]++;
	}
	//统计每个元素的起始位置
	int start[10]={0};
	for(int i=1;i<n;i++)
	{
	start[i]=start[i-1]+count[i-1];
	}
	//
}

void Radixsort(int* a,int n)
{
	assert(a);
	for(int i=1;i<=Maxbit(a,n);i++)
	{
	 int div=1;
	 int k=i;
	 while(--k)
	 {
	 div*=10;
	 }
	 _PartRadix(a,n,div);
	}
}








