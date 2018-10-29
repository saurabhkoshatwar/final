#include<iostream>
#include<omp.h>
using namespace std;

double total_serial_time,total_parallel_time;

int main()
{
    // int n = 20;
    // int arr[n];
    // int mat[n][n];
    // int sum_serial[n];
    // int sum_parallel[n];
    int n = 20000;
    int * arr = new int[n];
    int ** mat = new int*[n];
    for(int i=0;i<n;i++)
    {
        mat[i] = new int[n];
    }
    int * sum_serial = new int[n];
    int * sum_parallel = new int[n];

    double start,end;

    for(int i=0;i<n;i++)
    {
        arr[i] = rand()%100;
        sum_serial[i]=0;
        sum_parallel[i]=0;
        for(int j=0;j<n;j++)
        {
            mat[i][j] = rand()%100;
        }
    }

    start = omp_get_wtime();
    for(int i=0;i<n;i++)
    {        
        for(int j=0;j<n;j++)
        {
            sum_serial[i] += arr[j]*mat[i][j];
        }
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
            
            #pragma omp for collapse(2)
            for(int i=0;i<n;i++)
            {        
                for(int j=0;j<n;j++)
                {
                    sum_parallel[i] += arr[j]*mat[i][j];
                }
            }
            
        }
            end = omp_get_wtime();
            total_parallel_time = end - start;
            cout<<"Total Parallel time with threads("<<num_threads<<"): "<<total_parallel_time<<endl;

    }
    

return 0;    
}