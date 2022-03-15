#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>


#define DYNMC_ARRAY_SIZE 200
#define MAX_INT_NUM   	  13
#define MIN_NUM_TYPE 	   0
#define MAX_NUM_TYPE 	   1
#define MEAN_TYPE   	   2
#define STD_TYPE           3
#define TOTAL_OPERATION    4


typedef struct node_s{

	int x;
	struct node_s * next;

}node_t;

typedef struct nums_s{
	
	int n1;
	int n2;
	
}nums_t;


int *read_array(char *filename,int *byte_arr);
node_t *read_linkedlist(char *filename,int *byte_ll);
float * stats_array(int *dynmc_arr);
float * stats_linkedlist(node_t *node);
int *read_save_array();
node_t *read_save_linkledlist();
nums_t *find_different_numbers(int *num_arr,node_t *node_n,int *counter);


int main(){
	
	int i;				/* variable for loop */
	int *dynamic_array;		/* dynamic array for part 1 */
	node_t *root;			/* root of linkedlist for part 1 */
	
	float *stats_arr;		/* dynamic array of stats of array for part 1 */
	float *stats_ll;		/* dynamic array of stats of linkedlist for part 1 */
	
	int total_byte_arr = 0;		/* variable for total usage of bytes of array */
	int total_byte_ll  = 0;		/* variable for total usage of bytes of linkedlist */
	
	clock_t start,end;		/* variables for measuring time */
	double func_time_arr = 0.0;	/* variable for time of array function */
	double func_time_ll  = 0.0;	/* variable for time of linkedlist function */
	
	int *dynamic_input_arr;		/* dynamic array for part 2 */
	int diff_counter = 1;		/* different numbers counter */
	node_t *input_root;		/* root of linkedlist for part 2 */
	nums_t *wrong_nums;		/* dynamic array for different numbers */
	
	printf("\t\t---FIRST PART---\n");
	
	/* To prevent biasing one method over the other in speed, repeat the above reading steps a few times in different orders. */
	start = clock();
		dynamic_array = read_array("list.txt",&total_byte_arr);
	end = clock();
	func_time_arr = func_time_arr + (double) (end-start) / CLOCKS_PER_SEC ;
	free(dynamic_array);
	
	start = clock();
		root = read_linkedlist("list.txt",&total_byte_ll);
	end = clock();
	func_time_ll =func_time_ll + (double) (end-start) / CLOCKS_PER_SEC ;
	free(root);
	
	start = clock();
		root = read_linkedlist("list.txt",&total_byte_ll);
	end = clock();
	func_time_ll =func_time_ll + (double) (end-start) / CLOCKS_PER_SEC ;
	free(root);
	
	start = clock();
		dynamic_array = read_array("list.txt",&total_byte_arr);
	end = clock();
	func_time_arr = func_time_arr + (double) (end-start) / CLOCKS_PER_SEC ;
	free(dynamic_array);
	
	start = clock();
		dynamic_array = read_array("list.txt",&total_byte_arr);
	end = clock();
	func_time_arr = func_time_arr + (double) (end-start) / CLOCKS_PER_SEC ;
	free(dynamic_array);
	
	start = clock();
		root = read_linkedlist("list.txt",&total_byte_ll);
	end = clock();
	func_time_ll =func_time_ll + (double) (end-start) / CLOCKS_PER_SEC ;
	free(root);
	
	/* read_array function */
	total_byte_arr = 0;
	start = clock();
		dynamic_array = read_array("list.txt",&total_byte_arr);
	end = clock();
	func_time_arr = func_time_arr + (double) (end-start) / CLOCKS_PER_SEC ;
	printf("\nAverage time(4 times) for read_array function is %.4lf(s).\n",func_time_arr/4);
	printf("Total byte usage for dynamic array is: %d\n",total_byte_arr);
	
	/* read_linkedlist function */
	total_byte_ll = 0;
	start = clock();
		root = read_linkedlist("list.txt",&total_byte_ll);
	end = clock();
	func_time_ll =func_time_ll + (double) (end-start) / CLOCKS_PER_SEC ;
	printf("\nAverage time(4 times) for read_linkedlist function is %.4lf(s).\n",func_time_ll/4);
	printf("Total byte usage for linkedlist is: %d\n",total_byte_ll);
	
	/* stats_array function */
	start = clock();
		stats_arr = stats_array(dynamic_array);
	end = clock();
	func_time_arr = (double) (end-start) / CLOCKS_PER_SEC ;
	printf("\n\n--STATS OF DYNAMIC ARRAY--\n");
	printf("\nThe time for stats_array function is %.4lf(s).\n",func_time_arr);
	printf("Minimum number = %.0f\n",stats_arr[MIN_NUM_TYPE]);
	printf("Maximum number = %.0f\n",stats_arr[MAX_NUM_TYPE]);
	printf("Mean of numbers = %.3f\n",stats_arr[MEAN_TYPE]);
	printf("Standard derivation of numbers = %.3f\n",stats_arr[STD_TYPE]);
		
	/* stats_linkedlist function */
	start = clock();
		stats_ll = stats_linkedlist(root);
	end = clock();
	func_time_ll = (double) (end-start) / CLOCKS_PER_SEC ;
	printf("\n\n--STATS OF LINKEDLIST--\n");
	printf("\nThe time for stats_linkedlist function is %.4lf(s).\n",func_time_ll);
	printf("Minimum number = %.0f\n",stats_ll[MIN_NUM_TYPE]);
	printf("Maximum number = %.0f\n",stats_ll[MAX_NUM_TYPE]);
	printf("Mean of numbers = %.3f\n",stats_ll[MEAN_TYPE]);
	printf("Standard derivation of numbers = %.3f\n",stats_ll[STD_TYPE]);
	
	printf("\n----------First part successfully done.----------\n\n");
	printf("\t\t---SECOND PART---\n\n");
	
	/* receiving numbers from user */
	dynamic_input_arr = read_save_array();
	input_root       = read_save_linkledlist();
	
	/* finding different numbers between array and linkedlist */
	wrong_nums = find_different_numbers(dynamic_input_arr,input_root,&diff_counter);
	
	/* printing results */
	printf("\nDifferent Numbers Between Array and Linkedlist:\n\n");
	if(wrong_nums[0].n1 == -1){
		printf("There is not any different number between array and linkedlist.\n");
	}
	else{	
		for(i=0;i<diff_counter-1;i++){
			printf("%d.Encountered Different Number:\nNumber in array:%d -- Number in linkedlist:%d.\n\n",(i+1),wrong_nums[i].n1,wrong_nums[i].n2);
		}
	}	
	printf("\n----------Second part successfully done.----------\n\n");
	
	/* freeing dynamicly allocated things */
	free(root);
	free(dynamic_array);
	free(stats_arr);
	free(stats_ll);
	free(dynamic_input_arr);
	free(input_root);
	free(wrong_nums);
	printf("Have a Nice Day :)\n");
	return 0;
}

/* This function, reads numbers from file and saves it to dynamic array. The size of array growing dynamically. Returns the address of array. */
int *read_array(char *filename,int *byte_arr){

	int *dynmc_array;	/*  dynamic array */	
	int counter = 0;	/* variable for elements of array */
	int i = 1;		/* variabe for increase the size of array */
	int j=0;		/* variable for elements of char array(string) */
	char *number;		/* number string */
	FILE *fptr;
	
	fptr = fopen(filename,"r");
	if(fptr == NULL){
		printf("\n!ERROR!--Failed to open file--\n");	
		return 0;
	}
	dynmc_array = (int *) malloc(sizeof(int));	/* creating first element of array in order to realloc */
	number = (char*) calloc(MAX_INT_NUM,sizeof(char));	/* creating dynamicly char array to hold numbers */
	
	while( (number[j] = getc(fptr))  != EOF){	/* reading numbers and saving the to number string till encounter with EOF char */
		
		if(number[j]  ==','){			/* when encountered with ',' character, save the number to the dynamic array. */
		
					
			if(counter%DYNMC_ARRAY_SIZE == 0){ /* when all the elements of array is filled, increase dynamic array size dynamically. */
				dynmc_array = (int *) realloc(dynmc_array,i*DYNMC_ARRAY_SIZE*sizeof(int));
				i++;
			}
			dynmc_array[counter] = strtol(number,NULL,10);	/* converting string to integer */
			counter++;

			j = 0;	/* resetting string index */
				}
		else j++;
	}
	
	/* Here, is a terminate number. Increase array size by one in order to prevent segmentation fault. */
	dynmc_array = (int *) realloc(dynmc_array,((i-1)*DYNMC_ARRAY_SIZE*sizeof(int))+1);
	dynmc_array[counter] = -1;
	
	/* Calculating total usage of byte.(here multiply with i-1,because i starts with 1) */
	*byte_arr = ( (i-1)*DYNMC_ARRAY_SIZE*sizeof(int) ) + sizeof(int) ;
	free(number);	/* freeing number string */
	fclose(fptr);
	return dynmc_array;
}

/* This function, reads number from file and saves it to linkedlist. The nodes of linkedlist created each time the number is read. Returns the root of linkedlist. */
node_t *read_linkedlist(char *filename,int *byte_ll){

	int j = 0;	/* variable for elements of char array(string) */
	char *number;	/*number string */
	FILE *fptr;
	node_t *root;	/* root of linkedlist */
	node_t *node;	/* nodes of linkedlist */

	fptr = fopen(filename,"r");
	if(fptr == NULL){
		printf("\n!ERROR!--Failed to open file--\n");	
		return 0;
	}
	number = (char*) calloc(MAX_INT_NUM,sizeof(char));	/* creating dynamicly char array to hold numbers */
	
	root = (node_t*) malloc(sizeof(node_t));	/* creating root of linkedlist */
	*byte_ll = *byte_ll +sizeof(node_t);		/* increment total usage of byte */
	node = root;					/* to not lose the root of linkedlist,assign root to another pointer*/
	
	while( (number[j] = getc(fptr))  != EOF){	/* reading numbers and saving the to number string till encounter with EOF char */
		
		if(number[j]  ==','){			/* when encountered with ',' character, save the number to the linkedlist */
			node->x = strtol(number,NULL,10); /* converting string to integer */
			node->next = (node_t*) malloc(sizeof(node_t)); /* creating new node of list */
			node = node->next;
			node->next = NULL;	
			j = 0;
			*byte_ll = *byte_ll +sizeof(node_t);
		}
		else j++;		
	}
	free(number);
	fclose(fptr);
	return root;
}

float * stats_array(int *dynmc_arr){
	int i = 0;	/* variable for elements of array */
	float *stats;	/* dynamic stats array */
	
	stats = (float*)calloc(TOTAL_OPERATION,sizeof(float));
	
	/* Performing; finding min/max number, mean of numbers and std of numbers operations */
	stats[MIN_NUM_TYPE] = stats[MAX_NUM_TYPE] = dynmc_arr[0];
	stats[MEAN_TYPE] =  stats[STD_TYPE] = 0.0;
	
	while(dynmc_arr[i] != -1){
		if(stats[MIN_NUM_TYPE] > dynmc_arr[i]){
			stats[MIN_NUM_TYPE] = dynmc_arr[i];
		}
		if(stats[MAX_NUM_TYPE] < dynmc_arr[i]){
			stats[MAX_NUM_TYPE] = dynmc_arr[i];
		}
		stats[MEAN_TYPE] = stats[MEAN_TYPE] + dynmc_arr[i];
		i++;
	}
	
	stats[MEAN_TYPE] = stats[MEAN_TYPE] / i;
	i = 0;
	while(dynmc_arr[i] != -1){
		
		stats[STD_TYPE] = stats[STD_TYPE]+( (dynmc_arr[i] - stats[MEAN_TYPE]) * (dynmc_arr[i] - stats[MEAN_TYPE]) );
		i++;
	}
	stats[STD_TYPE] = sqrt( stats[STD_TYPE] / (i-1));
	
	return stats;	/* returning dynamic array */
}

float * stats_linkedlist(node_t *node){
	
	int i = 0;
	float *stats_l;
	node_t *temp;
	
	temp = node;
	stats_l = (float*)calloc(TOTAL_OPERATION,sizeof(float));
	
	stats_l[MIN_NUM_TYPE] = stats_l[MAX_NUM_TYPE] = node->x;
	stats_l[MEAN_TYPE] = stats_l[STD_TYPE] = 0.0;
	
	/* Performing; finding min/max number, mean of numbers and std of numbers operations */
	while(node->next != NULL){
		
		if(stats_l[MIN_NUM_TYPE] > node->x){
			stats_l[MIN_NUM_TYPE] = node->x;
		}
		if(stats_l[MAX_NUM_TYPE] < node->x){
			stats_l[MAX_NUM_TYPE] = node->x;
		}
		stats_l[MEAN_TYPE] = stats_l[MEAN_TYPE] + node->x;
		i++;
		
		node = node->next;
	}
	stats_l[MEAN_TYPE] = stats_l[MEAN_TYPE] / i;
	i = 0;

	while(temp->next  != NULL){
		
		stats_l[STD_TYPE] = stats_l[STD_TYPE]+( (temp->x - stats_l[MEAN_TYPE]) * (temp->x  - stats_l[MEAN_TYPE]) );
		i++;
		temp = temp->next;
	}
	stats_l[STD_TYPE] = sqrt( stats_l[STD_TYPE] / (i-1));
	
	return stats_l; /* returning dynamic array */
}

/* This function receive numbers from user and save them dynamic array. Returns dynamic array. */
int *read_save_array(){

	int counter = 1;
	int number;
	int *inpnum_arr;
	
	printf("Please type numbers to save array and type -1 to terminate:\n");
	inpnum_arr = (int*)malloc(sizeof(int));

	do{
		printf("%d- ",counter);
		scanf("%d",&number);
		if(counter != 1){ /* realloacting inpnum_arr array when it is not the first time(because the first element allocating before loop). */
			inpnum_arr = (int*)realloc(inpnum_arr,counter*sizeof(int));	
		}	
		inpnum_arr[counter-1] = number;
		counter++;
	}while(number != -1);

	return inpnum_arr;
}

/* This function receive numbers from user and save them linkedlist. Returns root of linkedlist. */
node_t *read_save_linkledlist(){

	int number;
	int counter = 1;
	node_t *root;
	node_t *iter;

	printf("Please type numbers to save linkedlist and type -1 to terminate:\n");
	printf("%d- ",counter);
	scanf("%d",&number);
	counter++;
	
	root = (node_t*)malloc(sizeof(node_t));
	root->x = number;
	iter = root;

	while(number != -1){	/* receving number from user ,creating linkedlist and saving number to the linkedlist. */
		printf("%d- ",counter);
		scanf("%d",&number);
		
		iter->next = (node_t*)malloc(sizeof(node_t));
		iter = iter->next;
		iter->x = number;
		iter->next = NULL;
		counter++;
	}
	return root;
}

/* This function finds different numbers between dynamic array and linkedlist. Returns struct array of different numbers. */
nums_t *find_different_numbers(int *num_arr,node_t *node_n,int *counter){
	
	int i= 0;
	nums_t *diff_nums;
	
	diff_nums = (nums_t *)malloc(sizeof(nums_t));
	diff_nums[0].n1 = diff_nums[0].n2 = -1;	/* assign -1 to first element in order to determine when the array and ll is same. */
	
	while(num_arr[i] != -1 && node_n->next != NULL){
		
		if( num_arr[i] != node_n->x){	/* when the elements of array and ll is not same */
			
			if(*counter != 1){	/* realloacting diff_nums array when it is not the first time(because the first element allocating before loop). */
				diff_nums = (nums_t *)realloc(diff_nums,(*counter)*sizeof(nums_t));
			}
			diff_nums[*counter-1].n1 = num_arr[i];
			diff_nums[*counter-1].n2 = node_n->x;
			*counter = *counter + 1 ;	
		}
		
		node_n = node_n->next;
		i++;
	}
	return diff_nums;
}


