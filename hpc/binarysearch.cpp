    #include<iostream>
    #include<omp.h>
    using namespace std;

    int binary(int *a,int low,int high,int key)
    {
        int mid = (low + high)/2;
        int low1,low2,high1,high2,mid1,mid2,found,loc;
        
        #pragma omp parallel section
        {   
            #pragma omp section
            {
                low1=low;
                high1 = mid;
                while(low1<=high1)
                {   
                    mid1 = (low1+high1)/2;
                    if(key==a[mid1])
                    {
                        found = 1;
                        loc=mid1;
                        low1 = high1+1;
                    }
                    else if(key>a[mid1])
                        low1=mid1 + 1;
                    else
                        high1 = mid1-1;    
                }
            }

            #pragma omp section
            {
                low2=mid+1;
                high2 = high;
                while(low2<=high2)
                {
                    mid2 = (low2+high2)/2;
                    if(key==a[mid2])
                    {
                        found = 1;
                        loc=mid2;
                        low2 = high2+1;
                    }
                    else if(key>a[mid2])
                        low2=mid2+1;
                    else
                        high2 = mid2-1;    
                }

            }
        }

        return loc;
    }

    int main()
    {
        int *a,i,n,key,loc=-1;
        cout<<"\n enter total no of elements=>"; 
        cin>>n; 
        a=new int[n];  
        cout<<"\n enter elements=>"; 
        for(i=0;i<n;i++) 
        { 
            cin>>a[i]; 
        }  
          cout<<"\n enter key to find=>";
        cin>>key; 
        loc = binary(a,0,n-1,key);
        if(loc==-1)
            cout<<"\n Key not found."; 
        else 
            cout<<"\n Key found at position=>"<<loc+1;

    
       return 0; 
    }