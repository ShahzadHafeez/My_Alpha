#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<unistd.h>
#include <cstring>

using namespace std;

void merge(int arr[], int L[], int R[], int n1,int n2,int l)
{
    int i=0, j=0, k=l;
 
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
   
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int arr[], int l, int r)
{
    
   
    if (l < r)
    {       
		pid_t pid=0;
		pid_t pid2=0;

		int fd[2];
                int fd2[2];
		int piped = pipe(fd);
int piped1 = pipe(fd2);
                int m = l+(r-l)/2;
		
       
       // mergeSort(arr, l, m);
        //mergeSort(arr, m+1, r);
		
		int n1 = m - l + 1;
		int n2 =  r - m;
		
        int L[n1], R[n2];
		for (int i = 0; i < n1; i++)            //left array
			L[i] = arr[l + i];
		
        for (int j = 0; j < n2; j++)           //right array
			R[j] = arr[m + 1+ j];
        

		//close(fd[0]);                             //left array to pipe
	         write(fd[1], L, n1*sizeof(int));

          //   close(fd[1]);
        

       
       // close(fd2[0]);                           //right array to pipe2
        
         write(fd2[1],R, n2*sizeof(int));
      //  close(fd2[1]);
	  
    
        
     pid=fork();
        if (pid<0)
            cout<<"fork error"<<endl;
        else if(pid==0)
        {

            if (n1<=2)
            {
                int array_receive[n1];

                
                
                read(fd[0], array_receive, n1*sizeof(int));
               // close(fd[0]);
                for(int i=0;i<n1;i++)

                if(array_receive[0]>array_receive[1]){
                    int temp=array_receive[0];
                    array_receive[0]=array_receive[1];
                    array_receive[1]=temp;
                }

               


              //  close(fd[0]);                         
                 write(fd[1],array_receive, n1*sizeof(int));
               // close(fd[1]);
               
	  
                
            }
            sleep(10);exit(0);
                
        }
        else
        {
            //wait(NULL);        //////////////////////////////////////////////////////////

            pid2=fork();
            if (pid2<0)
                cout<<"fork error at pid2"<<endl;
            else if (pid==0)
            {
                if (n2<=2)
                {
                    int array_receive[n2];

                    close(fd2[1]);
                   
                     read(fd2[0], array_receive, n2*sizeof(int));
                    close(fd2[0]);

                    if(array_receive[0]>array_receive[1]){
                    int temp=array_receive[0];
                    array_receive[0]=array_receive[1];
                    array_receive[1]=temp;
                }
                       

                    close(fd2[0]);                         
                    
                     write(fd2[1],array_receive, n2*sizeof(int));
                    close(fd2[1]);


                }
		
                sleep(10);exit(0);
                
            }
            else
            {
                //wait(NULL);                /////////////////////////////////////////////////////////

                close(fd[1]);
             
                read(fd[0], L, n1*sizeof(int));
                close(fd[0]);
                
                
               for (int t=0;t<n1;t++)
                     cout<<L[t]<<" "<<endl;;
               cout<<endl;


                close(fd2[1]);
                
                read(fd2[0], R, n2*sizeof(int));
                close(fd2[0]);
                
                 for (int t=0;t<n1;t++)
                     cout<<R[t]<<" "<<endl;
               cout<<endl;

                 merge(arr, L, R, n1,n2,l);
               cout<<"after merge"<<endl;   
               for (int t=0;t<n1+n2;t++)
                     cout<<arr[t]<<" "<<endl;
               cout<<endl;
                
                
            }
            
        }   
		
		
    }
}
int main()
{
int arr[]={'3','2','0','1'};
mergeSort(arr,0,3);
return 0;
}