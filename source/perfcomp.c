#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern void factorial_iterative(int , int);
extern void factorial_recursive(int , int);
extern void fibonacci_recursive(int , int);
extern void fibonacci_iterative(int , int);
extern void hanoi_recursive(int , int);
extern void hanoi_iterative(int , int);


void factorial_iterative_c(int number , int silent)
{	
	int count=number-2,i,result=number;	
	if(number==0 || number==1)
	{	
		if(silent==1)
			printf("1\n");
		return;	
	}
	else if(number==2)
	{
			
		printf("2\n");
		return;
	}
		
	for(i=0 ; i < count ; i++)
	{
		result = result * (number - 1);
		number--;
	}
	if(silent==1)	
		printf("%d\n",result);
}

int factorial_recursive_c(int number)
{
	if(number == 0 || number == 1)
      		return 1;
   	else
      		return number * ( factorial_recursive_c (number - 1) );
}


void fibonacci_iterative_c(int number , int silent)
{	
	int i,first=0,second=1,result=0;
	
	if(number == 1 || number == 2)
	{
		if(silent==1)		
			printf("1\n");	
		return;
	}	
	for(i = 1 ; i < number ; i++)
	{
		result = first + second;
		first = second;
		second = result;	
	}
	if(silent==1)	
		printf("%d\n",result);
	
}

int fibonacci_recursive_c(int number)
{
	if(number == 0)
		return 0;
	else if(number == 1 || number==2)
		return 1;
	return fibonacci_recursive_c( number - 1) + fibonacci_recursive_c(number - 2);

}

void hanoi_recursive_c(int number , int silent ,  int tower1 , int tower3 , int tower2)
{
	if (number == 1) 
	{
		if(silent==1)		
			printf("%d ---> %d\n", tower1 , tower3);
		return;
	}

	hanoi_recursive_c(number - 1 , silent , tower1 , tower2 , tower3);
	if(silent==1)
		printf("%d ---> %d\n", tower1 , tower3);
	hanoi_recursive_c(number - 1, silent , tower2 , tower3 , tower1);	
}

void hanoi_iterative_c(int number , int silent)
{
	int x;	
	for (x=1; x < (1 << number); x++)
	{
		if(silent==1)
			printf( "%d ---> %d\n",(x&x-1)%3+1, ((x|x-1)+1)%3+1 );
	}
	if(silent==1)	
		printf("\n");
}		

void compare(char * comp_func , int number)
{
	int i;
	clock_t start ;
			
	printf("%s %d\n",comp_func,number);
	if(strcmp(comp_func,"FACI")==0)
	{
		start = clock();
		for(i=0;i<1000000;i++)
			factorial_iterative_c(number , 0);
		printf ( "C:%f sec\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );			
		start = clock();
		for(i=0;i<1000000;i++)
			factorial_iterative(number , 0);
		printf ( "ASM:%f sec\n\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );
	}
	else if(strcmp(comp_func,"FACR")==0)
	{
		start = clock();
		for(i=0;i<1000000;i++)
			factorial_recursive_c(number);
		printf ( "C:%f sec\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );			
		start = clock();
		for(i=0;i<1000000;i++)
			factorial_recursive(number , 0);
		printf ( "ASM:%f sec\n\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );	
	}
	else if(strcmp(comp_func,"FIBI")==0)
	{
		start = clock();
		for(i=0;i<1000000;i++)
			fibonacci_iterative_c(number , 0);
		printf ( "C:%f sec\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );			
		start = clock();
		for(i=0;i<1000000;i++)
			fibonacci_iterative(number , 0);
		printf ( "ASM:%f sec\n\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );	
	}
	else if(strcmp(comp_func,"FIBR")==0)
	{
		start = clock();
		for(i=0;i<1000000;i++)
			fibonacci_recursive_c(number);
		printf ( "C:%f sec\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );			
		start = clock();
		for(i=0;i<1000000;i++)
			fibonacci_recursive(number , 0);
		printf ( "ASM:%f sec\n\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );	
	}
	else if(strcmp(comp_func,"HANI")==0)
	{
		start = clock();
		for(i=0;i<1000000;i++)
			hanoi_iterative_c(number , 0);
		printf ( "C:%f sec\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );			
		start = clock();
		for(i=0;i<1000000;i++)
			hanoi_iterative(number , 0);
		printf ( "ASM:%f sec\n\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );	
	}
	else if(strcmp(comp_func,"HANR")==0)
	{
		start = clock();
		for(i=0;i<1000000;i++)
			hanoi_recursive_c(number , 0 , 1 , 3 , 2);
		printf ( "C:%f sec\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );			
		start = clock();
		for(i=0;i<1000000;i++)
			hanoi_recursive(number , 0);
		printf ( "ASM:%f sec\n\n", ( (double)clock() - start ) / CLOCKS_PER_SEC );	
	}
}


void process(char *func_name , int number)
{
	if(strcmp(func_name,"FACI_A")==0)//assembly functions
		factorial_iterative(number , 1);
	else if(strcmp(func_name,"FACR_A")==0)
		factorial_recursive(number , 1);	
	else if(strcmp(func_name,"FIBI_A")==0)		
		fibonacci_iterative(number , 1);	
	else if(strcmp(func_name,"FIBR_A")==0)	
		fibonacci_recursive(number , 1);
	else if(strcmp(func_name,"HANR_A")==0)	
		hanoi_recursive(number , 1);	
	else if(strcmp(func_name,"HANI_A")==0)	
		hanoi_iterative(number , 1);
		
	else if(strcmp(func_name,"FACI_C")==0)//C functions
		factorial_iterative_c(number , 1);
	else if(strcmp(func_name,"FACR_C")==0)
		printf("%d\n",factorial_recursive_c(number));
	else if(strcmp(func_name,"FIBI_C")==0)
		fibonacci_iterative_c(number , 1);
	else if(strcmp(func_name,"FIBR_C")==0)		
		printf("%d\n",fibonacci_recursive_c(number));
	else if(strcmp(func_name,"HANR_C")==0)	{
		hanoi_recursive_c(number,0,1,3,2); printf("\n"); }
	else if(strcmp(func_name,"HANI_C")==0)
		hanoi_iterative_c(number , 1);
}


void read(char * input_file_name)
{
	FILE *fp=fopen(input_file_name,"r");
	char  func_name[10];
	char comp_func[10];
	int number,i;
	while( !feof(fp) )
   	{	
		fscanf(fp,"%s",func_name);
		if(strcmp(func_name,"COMP")!=0)
		{
			fscanf(fp,"%d",&number);
			process(func_name , number);
			strcpy(func_name,"");
		}
		else if(strcmp(func_name,"COMP")==0)
		{
			fscanf(fp,"%s",comp_func);
			fscanf(fp,"%d",&number);
			compare(comp_func , number);				
			strcpy(func_name,"");
		}
   	}

   	fclose(fp);      
}


int main(int argc,char* argv[]) 
{
	read(argv[1]);
}
