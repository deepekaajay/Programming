#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>

#include <fcntl.h>

#include <string.h>


#define binout "-b"

#define txtout "-t"

int main(int parameter, char *argv[])

{
       
if (parameter != 4)
          
{
	    
printf("not enough parameters for the program\n\n");
	    
return -1;
	  
}
	 
FILE *infile;
	 
FILE *outfile;
	 
infile=fopen(argv[1],"r");
	 
outfile=fopen(argv[2],"wt");
 	 
if(argv[3]=="-b")
	      
outfile=fopen(argv[2],"wb");
         
if (!infile)
	   
{
	    
printf("\n can not open the input file");
	    
return -1;
	    
}
         
if (!outfile)
            
{
             
printf("\n can not open the output file ");
             
return -1;
             
}
    
char ch;
    
ch=getc(infile);
    
while(ch!=EOF)
	        
{
	        
fwrite(&ch,1,sizeof(ch),outfile);
	        
ch=getc(infile);
				     
}
    
fclose(infile);
    
fclose(outfile);
    
return 0;

}
