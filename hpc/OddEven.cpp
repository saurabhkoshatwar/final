#include<iostream>
#include<omp.h>
using namespace std;
double bbs_serial_time,oes_serial_time,oes_parallel_time;

void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b =temp;
}

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
int main()
{

int n =40000;
int arr1[n];
int arr2[n];
int arr3[n];
int arr4[n];
double start,end;

    for(int i=0;i<n;i++)
    {
        arr1[i] = rand()%100;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
    }

    start = omp_get_wtime();
    //Bubble Sort
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr1[j] > arr1[j+1])
            {
                swap(arr1[j],arr1[j+1]);
            }
        }

    }
    // check(arr1,n);
    end = omp_get_wtime();
    bbs_serial_time = end - start;
    cout<<"Bubble Sort Serial Time: "<<bbs_serial_time<<endl;

    start = omp_get_wtime();
    //Odd Even sort
    bool isSorted = false;
    while(!isSorted)
    {
        isSorted = true;
        for(int i=1;i<=n-2;i=i+2)
        {
            if(arr2[i] > arr2[i+1])
            {
                swap(arr2[i],arr2[i+1]);
                isSorted = false;
            }
        }

        for(int i=0;i<=n-2;i=i+2)
        {
            if(arr2[i] > arr2[i+1])
            {
                swap(arr2[i],arr2[i+1]);
                isSorted = false;
            }
        }
    }
    // check(arr2,n);
    end = omp_get_wtime();
    oes_serial_time = end - start;
    cout<<"OddEven Sort Serial Time: "<<oes_serial_time<<endl;

    int act_num_threads;
    for(int k=1;k<=4;k++)
    {
            for(int i=0;i<n;i++)
        	{   
			arr3[i] = arr4[i];    
        	}

            omp_set_num_threads(k);

            #pragma omp parallel
            {
                act_num_threads = omp_get_num_threads();
            }    

            start = omp_get_wtime();
            //Odd Even sort
            isSorted = false;
            while(!isSorted)
            {
                isSorted = true;

            #pragma omp parallel
            {
                    bool PrivateisSorted = true;
                    #pragma omp for
                    for(int i=1;i<=n-2;i=i+2)
                    {
                        if(arr3[i] > arr3[i+1])
                        {
                            swap(arr3[i],arr3[i+1]);
                            PrivateisSorted = false;
                        }
                    }

                    #pragma omp for
                    for(int i=0;i<=n-2;i=i+2)
                    {
                        if(arr3[i] > arr3[i+1])
                        {
                            swap(arr3[i],arr3[i+1]);
                            PrivateisSorted = false;
                        }
                    }

                    if(PrivateisSorted == false)
                    {
                        #pragma omp critical
                        {
                            isSorted = false;
                        }
                    }
                }
            }
            // check(arr3,n);
            end = omp_get_wtime();
            oes_parallel_time = end - start;
            cout<<"OddEven Sort Parallel Time with threads("<<act_num_threads<<"): "<<oes_parallel_time<<endl;
    }

return 0;
}