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
    int n = 1000;
    int ** mat = new int*[n];
    for(int i=0;i<n;i++)
    {
        mat[i] = new int[n];
    }
    int ** mat2 = new int*[n];
    for(int i=0;i<n;i++)
    {
        mat2[i] = new int[n];
    }
    int ** SerialAns = new int*[n];
    for(int i=0;i<n;i++)
    {
        SerialAns[i] = new int[n];
    }
    int ** ParallelAns = new int*[n];
    for(int i=0;i<n;i++)
    {
        ParallelAns[i] = new int[n];
    }

    double start,end;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            mat[i][j] = rand()%100;
            mat2[i][j] = rand()%100;
            SerialAns[i][j] = 0;
            ParallelAns[i][j] = 0;
        }
    }

    start = omp_get_wtime();
    for(int i=0;i<n;i++)
    {        
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                SerialAns[i][j] += mat[i][k]*mat2[k][j];
            }
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
            
            #pragma omp for collapse(3)
            for(int i=0;i<n;i++)
            {        
                for(int j=0;j<n;j++)
                {
                    for(int k=0;k<n;k++)
                    {
                        SerialAns[i][j] += mat[i][k]*mat2[k][j];
                    }
                }
            }
            
        }
            end = omp_get_wtime();
            total_parallel_time = end - start;
            cout<<"Total Parallel time with threads("<<num_threads<<"): "<<total_parallel_time<<endl;

    }
    

return 0;    
}