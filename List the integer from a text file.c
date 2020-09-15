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
	    
FILE *in;
	    
FILE *out;
	    
in=fopen(argv[1],"r");
	    
out=fopen(argv[2],"w");
	    
if (!in)
	    {
	         
printf("\n can not open the input file");
	         
return -1;
	     
}

	    
if (!out)
	    
{ 
		
printf("\n can not open the output file ");
		
return -1;
	    
}
	    
int no;
	    
fscanf(in,"%d",&no);
	    
int count,t,h,i,adad;
	    
while ( !feof(in))
	    
{
         	   
count=0;
		   
h=no/2;
		    
for (i=2; i<=half; i++)
                     
{
			     
if ( (no%i)==0 )
				    
count=count+1;

		     }
		    
if ((no==1) || (no==0)) count=1;
		    
if (count==0 ) fprintf(out,"%d\n",no);
                    
fscanf(in,"%d",&no);

		    
	    
}

fclose(in);

fclose(out);

return 0;

}

