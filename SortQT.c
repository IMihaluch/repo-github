#include <stdio.h>
#include <stdlib.h>
#define SIZE 30


void thickSplitQ(int *ar, int lt, int rt)

{
                 int vt; 
                     int l_q = lt; 
                          int r_q = rt; 
                              vt = ar[lt];
       while (lt < rt) 
     
                {
                   
                       while ((ar[rt] >= vt) && (lt < rt))
                             rt--; 
                             if (lt != rt) 
                             {
           
                               ar[lt] = ar[rt]; 
                                 lt++; 
                             }
    
                       while ((ar[lt] <= vt) && (lt < rt))
                             lt++; 
                             if (lt != rt) 
    
                    {
                             ar[rt] = ar[lt]; 
                             rt--; 
                    }
              
                }
       
                             ar[lt] = vt; 
                             vt = lt;
                             lt = l_q;
                             rt = r_q;
                             if (lt < vt) 
                             
    thickSplitQ(ar, lt, vt - 1);
    
                             if (rt > vt)
                             
    thickSplitQ(ar, vt + 1, rt);
}
int main()

{
     int a[rzmr];
  
         for (int i = 0; i<rzmr; i++)
         
             a[i] = rand() % 301 - 100;
  
         for (int i = 0; i<rzmr; i++)
         
             printf("%4d ", a[i]);
             printf("\n");
    
  thickSplitQ(a, 0, rzmr-1); 
            
         for (int i = 0; i<rzmr; i++)
  
             printf("%4d ", a[i]);
             printf("\n");
  
    
  return 0;
  
}
