#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>

#include <fcntl.h>

#include <string.h>


int main(int parameter, char *argv[])

{
	     
if (parameter != 3)
	         	
{
		        
printf("not enough parameters for the program\n");

		        
return -1;
		  
      
}
	    
FILE *IN;
	
FILE *OUT;
	    
IN=fopen(argv[1],"rb+");
	    
OUT=fopen(argv[2],"wb+");
            
if (!IN)
  	    
{
   	    
printf("\n can not open the input file");
	     
return -1;
	    
}
    	    
if (!OUT)
 	    
{ 
  		
printf("\n can not open the output file ");
		
return -1;
	    
}
            
int no;
	    
fread(&no,sizeof(int),1,IN);
	    
int count,t,h,i,adad;
	    
while ( !feof(IN))
	    
{
         	   
count=0;
		   
h=no/2;
		    
for (i=2; i<=half; i++)
                     
{
			     
if ( (no%i)==0 )
				    
count=count+1;

		     
}
		    
if ((no==1) || (no==0)) 
count=1;
		    
if (count==0 ) 
fwrite(&no,sizeof(int),1,OUT);
                    
fread(&no,sizeof(int),1,IN);

		    
	    
}

fclose(IN);

fclose(OUT);

return 0;

}

