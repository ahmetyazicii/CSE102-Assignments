#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define ARRAY_SIZE 501		/* here i define array size 501,however, program only use first 500 elements.Last element just for terminate when finding sum of elements. */
#define STRING_SIZE 150
#define N 8
#define HAS_WATER 111


void menu();

void menu_for_part1();
void generate_hofstadters_sequence (int *a, int n);
int find_max (int arr[], int index, int max_value);
int sum_array (int arr[]);
double std_array (int arr[], double *mean, int n, int index);

void install_pipes (int visited[N][N], int x, int y, int orientation,int *counter);

char* remove_duplicates (char* str);


int main(){

	menu();
	return 0;
}


void menu(){
	
	int choice;				/* variable for user input.*/
	char inp_str[STRING_SIZE];		/* array for part3 */
	int field[N][N]={0};			/* array for part2 */
	int x=0,y=0,or=0,counter=0;		/* variables for part2 */
	
	
	
	
	
	printf("\nWelcome to Homework 8, please chose one of the parts to continue\n--------------------\n");
	
	printf("1) Execute Part 1\n2) Execute Part 2\n3) Execute Part 3\n4) Exit\n");
	scanf("%d",&choice);
	
	switch(choice){
		case 1:		menu_for_part1();
			break;
		case 2:		
				printf("\nThe Complete Orientation for Filling All the Field is:\n");
				install_pipes(field,x,y,or,&counter);
			
			

			break;
		case 3:		printf("Please write the string that wants to fix.(max 150 character)\n");
				scanf(" %[^\n]s",inp_str);	/* get string with ignoring white spaces. */
				
				remove_duplicates(inp_str);
				
				printf("\nThe fixed string is:\n");
				printf("%s\n",inp_str);
			break;
		case 4:		printf("----!See You Later!----\n");
			break;
		default:	printf("Please select from menu\n");
	}	
	
	if(choice!=4){
		menu();	
	}
}

void menu_for_part1(){
	int oprt;			/* variable for menu */
	int array[ARRAY_SIZE]={0};	
	int term;			/* variable for items of the Hofstadter's Q-Sequence */
	int i;
	int max;			/* variable for max number of array. */
	int sum;			/* variable for sum of the array */
	double mean;			/* variable for mean of array. */
	double std;			/* variable for standard deviation of array. */
	
	do{
	
		printf("\nPlease make your choice:\n ------------------\n");
		printf("1) Fill Array\n2) Find Biggest Number\n3) Calculate Sum\n4) Calculate Standard Deviation\n5) Exit\n");
		scanf("%d",&oprt);
		
		switch(oprt){
			case 1:		
					for(i=0;i<ARRAY_SIZE;i++){	/* fills the array with 0 */
						array[i]=0;	
					}			

					printf("Please typed the number n number of the Hofstadter's Q-Sequence(from 1 to 500):   ");
					scanf("%d",&term);
					
					generate_hofstadters_sequence(array,term-1);
					printf("The array has been filled succesfully.\n");
				break;
			case 2:		
					max=0;			/* assign 0 to variable in order to use again. */
					max=find_max(array,0,max);
					printf("The Biggest Number is: %d\n",max);
				break;
			case 3:		
					
					sum=sum_array(array);
					printf("The Sum of Numbers is: %d\n",sum);
				break;
			case 4:		
					mean=0.0;		/* assign 0 to variables in order to use again. */
					std=0.0;
					std=sqrt(std_array(array,&mean,term,0));	/* taking sqrt of returining value in order to calculate std. */
					
					printf("The Sample Standard Deviation is: %lf\n",std);
					printf("The Mean of the Array is: %lf\n",mean);
				break;
			case 5:		printf("Returning main menu...\n");
				break;
			default:	printf("Please select from menu\n");	
		}
	}while(oprt!=5);
}

/* This function recursively fills the array with the Hofstadter's Q-Sequence.(according the formula) */
void generate_hofstadters_sequence (int *a, int n){

	if(n>0)		generate_hofstadters_sequence(a,n-1);
	if(n==0) 	a[n]=1;
	if(n==1) 	a[n]=1;
	if(n>1)		a[n]=a[n-a[n-1]]+a[n-a[n-2]];	
}

/* This function recursively finds max number in the array. It searches all elements of the array. */
int find_max (int arr[], int index, int max_value){

	if(index<ARRAY_SIZE-1) {
		max_value=find_max(&arr[1],index+1,max_value);
	}
	if(arr[0]>max_value) {
		return arr[0];
	}
	else {
		return max_value;
	}
}

/* This funciton recursively finds the sum of array. It continues till reach the '0'. */
int sum_array (int arr[]){	
	if(arr[0]!=0) {
		return (arr[0]+sum_array(&arr[1]));
	}
	else {
		return 0;
	}
}

/* This function recursively calculate std of numbers.
The function first find mean, return the sum of square of std.(sqrt operation does not perform here.  */
double std_array (int arr[], double *mean, int n, int index){

	if(index<n){	
			*mean=*mean+arr[index];
			return  ( ( std_array(arr,mean,n,index+1) ) +  pow((arr[index] - *mean),2.0) / (n-1) ) ;
				/* this part for calculate mean.*/
				/*after calculation, this part returns 0*/
	}
	else {
		*mean=*mean/n;
		return 0;
	}
}

/* This function recursively fills field, and prints the orientations. */
void install_pipes (int visited[N][N], int x, int y, int orientation, int *counter){
		
	if(*counter==N*N){			/* coniditon for printing last orientation. */
			printf("O%d\n",orientation);
			return;
	}
	
	if(visited[x+2][y+1]!=HAS_WATER){	/* orientation-1 */
	
		if(x+2<8 && y+1<8){		/* checking the borders. */

			if(orientation!=0){	/* condition for not printing inital case. */
				printf("O%d, ",orientation);
			}
			visited[x+2][y+1]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x+2,y+1,1,counter);	
		}
	}
	
	if(visited[x+1][y-2]!=HAS_WATER){	/* orientation-2 */					
		
		if(x+1<8 && y-2<8 && y-2>=0){	/* checking the borders. */
			printf("O%d, ",orientation);
			
			visited[x+1][y-2]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x+1,y-2,2,counter);
		}
	}
	
	if(visited[x-2][y-1]!=HAS_WATER){	/* orientation-3 */
	
		if(x-2<8 && y-1<8 && x-2>=0 && y-1>=0){ /* checking the borders. */
			printf("O%d, ",orientation);
			
			visited[x-2][y-1]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x-2,y-1,3,counter);
		}
	
	}
	
	if(visited[x-1][y+2]!=HAS_WATER){	/* orientation-4 */

		if(x-1<8 && x-1>=0 && y+2<8){	/* checking the borders. */
			printf("O%d, ",orientation);
			
			visited[x-1][y+2]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x-1,y+2,4,counter);
		}
	}
	
	if(visited[x+1][y+2]!=HAS_WATER){	/* orientation-5 */
		
		if(x+1<8 && y+2<8){		/* checking the borders. */
			printf("O%d, ",orientation);
			
			visited[x+1][y+2]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x+1,y+2,5,counter);
		}
	}
	
	if(visited[x+2][y-1]!=HAS_WATER){	/* orientation-6 */

		if(x+2<8 && y-1<8 && y-1>=0){	/* checking the borders. */
			printf("O%d, ",orientation);
		
			visited[x+2][y-1]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x+2,y-1,6,counter);
		}
	}
	
	if(visited[x-1][y-2]!=HAS_WATER){	/* orientation-7 */

		if(x-1<8 && y-2<8 && x-1>=0 && y-2>=0){ /* checking the borders. */
			printf("O%d, ",orientation);
		
			visited[x-1][y-2]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x-1,y-2,7,counter);
		}
	}	
	
	if(visited[x-2][y+1]!=HAS_WATER){	/* orientation-8 */

		if(x-2<8 && x-2>=0 && y+1<8){	/* checking the borders. */
			printf("O%d, ",orientation);
			
			visited[x-2][y+1]=HAS_WATER;
			*counter=*counter+1;
			install_pipes(visited,x-2,y+1,8,counter);
		}
	}
	
	else{
		return;
	}
}

char* remove_duplicates (char* str){
	int i=1;	/* variable for loop (shifting text). */
	
	if(str[0]!='\0'){		/* this is the recursive condition. Unless, function reaches null char(end of string) ,function countinues. */
		if(str[0]==str[1]){	/* when the consecutive words are same. */
			while(str[i]!='\0'){		/* shifting text. */
				str[i]=str[i+1];
				i++;
			}
			return remove_duplicates(str);	/* return same string in order to deal like 'aaaaa' strings. */
		}		
		else{
			return remove_duplicates(str+1);	/* return one step forward. */	
		}
	}
	else{
		return str;
	}
}


