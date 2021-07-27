////Реализовать пузырьковую сортировку двумерного массива например, массив 1,9,2 5,7,6 4,3,8 должен на выходе стать 1,2,3 4,5,6 7,8,9////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main ()

{   
    const int a=3,b=3;

              int Array_Mass[a][b] = {{1, 9, 2}, {5, 7, 6}, {4, 3, 8}};
     
                  int i,j,temp=0;
    
                      for(i=0;i<a;i++)
                 {
    
                          for(j=0;j<b;j++)
        
                       {
                             printf("%d, ", Array_Mass[i][j] );
            
                           };
        
                                    printf("\n \n");
        
};
 
printf("\n*********\n\n");
 
     bool exit=false;
    
               while(!exit)
    
              {
                    exit=true;
    
                         for(i=0;i<a;i++)
        
                    {
                    
                             for(j=0;j<b;j++)
            
                          {
                          
                                 if(Array_Mass[i][j]>Array_Mass[i][j+1])
                
                                {
                
                                temp=Array_Mass[i][j];
                
                            Array_Mass[i][j]=Array_Mass[i][j+1];
                
                       Array_Mass[i][j+1]=temp;
                
                 exit=false;
                
            };
                
        };
            
    };
        
};
 
    for(i=0;i<a;i++)
    
    {
           for(j=0;j<b;j++)
        
          {
               printf("%d, ", Array_Mass[i][j] );
        
               };
        
                      printf("\n \n");
        
};
 
    
    return 0;
///}


////// Реализовать алгоритм Трабба-Прадо-Кнута в коде на языке С////////


 
////int main () /// MAIN up
{
     double Ar_in[11], l;
     
            int i;
 
                  printf ("\nEnter 11  nombers:");
 
                          for (i = 0; i < 11; i++)
                          {
                          
                               scanf ("%lf", &Ar_in[i]);
}
 
  printf ("\n\n\nWe make calculations using the formula f (x)= (sqrt(fabs(x)) + 5.0 * pow(x, 3.0)):\n");
 
          for (i = 10; i >= 0; i--)
          
               {
               
                 l = sqrt (fabs (Ar_in[i])) + 5 * pow (Ar_in[i], 3);
  
                        
  
                          if (l > 400.0)
                          
                             {
                              
                                printf ("%d = The result of calculations exceeds 400!\n", i);
                                
                                        }
 
                                      else
                                      
                                                      
                                        {
                                        
                                printf("%d = %f\n", i, l);
                                
                              }
                              
                        }
 
          return 0;
          
}
 
