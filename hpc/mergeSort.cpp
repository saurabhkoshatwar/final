#include<iostream>
#include<omp.h>
using namespace std;

double total_time_serial,total_time_parallel;
void check(int *arr,int n)
{
    bool flag=true;	
	for(int i=0;i<n-2;i++)
     {
		 if(arr[i]>arr[i+1])
		 {
            cout<<i<<endl;
            flag=false;
            break;
         }	
     }

	if(flag)
	cout<<"\ncorrect";
	else
	cout<<"\nIncorrect";
}
void merge(int arr[],int l,int m,int r)
{
    int size1 = m - l + 1;
    int size2 = r - m;
    int i,j,k;

    int L[size1],R[size2];
    for(i=0;i<size1;i++)
       L[i] = arr[l+i];
    for(j=0;j<size2;j++)
       R[j] = arr[m + 1 + j];   

    i=0;
    j=0;
    k=l;
    while(i<size1 && j<size2)
    {
        if(L[i]<R[j])
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        else{
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    while(i<size1)
    {
        arr[k]=L[i];
        i++;
        k++;
    }

    while(j<size2)
    {
        arr[k]=R[j];
        j++;
        k++;
    }

}

void mergeSort(int arr[],int l,int r)
{

    if(l<r)
    {
        //cout<<"hello"<<" ";
        int m = (l+r)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        merge(arr,l,m,r);
    }

}

void mergeSortParallel(int arr[],int l,int r)
{

    if(l<r)
    {
        int m = (l+r)/2;

        #pragma omp task firstprivate(arr,l,r) 
        mergeSort(arr,l,m);

        #pragma omp task firstprivate(arr,l,r) 
        mergeSort(arr,m+1,r);

        #pragma omp taskwait
        merge(arr,l,m,r);
    }

}
int main()
{
    long n = 100000;
    int arr[n],arr2[n];
    double start, end;
    int num_thread;

        for(int i=0;i<n;i++)
        {
            arr[i] = rand()%100; 
            // cout<<arr[i]<<" ";
	    	arr2[i] = arr[i];   
        }
        start = omp_get_wtime();
        mergeSort(arr,0,n-1);
        // check(arr,n);
        end = omp_get_wtime();
        total_time_serial = end - start;
        cout<<"MergeSort Serial Time: "<<total_time_serial<<endl;

        start = omp_get_wtime();
        mergeSortParallel(arr2,0,n-1);
        // check(arr2,n);
        end = omp_get_wtime();
        total_time_parallel = end - start;
        cout<<"MergeSort Parallel Time: "<<total_time_parallel<<endl;


    return 0;
}