#include<iostream>
#include<omp.h>
using namespace std;

double total_serial_time,total_parallel_time;

int main()
{
    long long n = 5000000;
    int arr[n];
    int arr2[n];
    int sum_serial[n];
    int sum_parallel[n];
    //     int n = 100000000;
    // int * arr = new int[n];
    // int * arr2 = new int[n];
    // int * sum_serial = new int[n];
    // int * sum_parallel = new int[n];

    double start,end;

    for(int i=0;i<n;i++)
    {
        arr[i] = rand()%100;
        arr2[i]= rand()%100;
    }

    start = omp_get_wtime();
    for(int i=0;i<n;i++)
    {
        sum_serial[i] = arr[i] + arr2[i];
    }
    end = omp_get_wtime();
    total_serial_time = end - start;
    cout<<"Total Serial time: "<<total_serial_time<<endl;

    int num_threads;

    for(int k=1;k<=4;k++)
    {
        omp_set_num_threads(k);
        start = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single
            {
                num_threads = omp_get_num_threads();
            }
            
            #pragma omp for
            for(int i=0;i<n;i++)
            {
                sum_serial[i] = arr[i] + arr2[i];
            }
            
        }
            end = omp_get_wtime();
            total_parallel_time = end - start;
            cout<<"Total Parallel time with threads("<<num_threads<<"): "<<total_parallel_time<<endl;

    }
    

return 0;    
}