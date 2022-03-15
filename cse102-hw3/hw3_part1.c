#include<stdio.h>


int sum(int n,int flag);
int mult(int n,int flag);


int main(){

	int number;		/* variable for integer number */
	int flag1,flag2;	/* variables for operation flags */
	int result=0;		/* variable for result of operations */
	 
	printf("Enter an integer: ");
	scanf("%d",&number);

	printf("Please enter '0' for sum,'1' for multiplication\n");
	scanf("%d",&flag1);
	
	printf("Please enter '0' to work on even numbers, '1' to work on odd number\n");
	scanf("%d",&flag2);
	
	switch(flag1){ 		/* operation selection */
	
		case 0:
			
			result=sum(number,flag2);
			
			if(result==(-1)){			/* printing error message */
			
				printf("Invalid value for odd/even selection\n");
			
			}
			else {
			
				printf("= %d \n",result);
	
			}
			
			break;
			
		case 1:
	
			result=mult(number,flag2);
			
			if(result==(-1)){			/* printing error message */
			
				printf("Invalid value for odd/even selection\n");
			
			}
			else {
			
				printf("= %d \n",result);
	
			}
			
			break;
			
		default:
			
			printf("Unsported operation.\n");
	}

	return 0;
	
}


int sum(int n,int flag){

	int i;			/* variable for loop */
	int result=0;		/* variable for result of operation */
	int counter=0;   	/* counter for operation signs */
	
	if(flag==0 || flag==1){			/* condition for valid value for odd/even selection */
	
		
		
		
		for(i=1;i<=n;i++){
	
			if(flag==0 && i%2==0){			/* condition for even numbers */
		
				printf("%d ",i);			
				result=result+i;
				
				if(counter!=((n/2)-1)){		/* condition for printing operation signs */
					
					printf("+ ");
					counter++;
				}							
			}
	
			else if(flag==1 && i%2!=0){		/* condition for odd numbers */
		
				printf("%d ",i);			
				result=result+i;
		
				if(n%2!=0 && counter!=((n/2))){			/* condition for printing operation signs of entered odd number */
				
					printf("+ ");
					counter++; 
				}
				else if(n%2==0 && counter!=((n/2)-1)){		/* condition for printing operation signs of entered even number */	
					
					printf("+ ");
					counter++;
				}									
			}
		}
	}
	
	else{		/* condition for invalid value for odd/even selection */
		
		result=(-1);    	/* returning -1 to main function in order to printf error message */		
		
	}

	return (result);

}


int mult(int n,int flag){

	int i;			/* variable for loop */
	int result=1;		/* variable for result of operation */
	int counter=0;   	/* counter for operation signs */

	if(flag==0 || flag==1){		/* condition for valid value for odd/even selection */
	
		for(i=1;i<=n;i++){
	
			if(flag==0 && i%2==0){			/* condition for even numbers */
		
				printf("%d ",i);			
				result=result*i;
				
				if(counter!=((n/2)-1)){		/* condition for printing operation signs */
				
					printf("* ");				
					counter++;
		
				}
			}

			else if(flag==1 && i%2!=0){		/* condition for odd numbers */
		
				printf("%d ",i);			
				result=result*i;
				
				if(n%2!=0 && counter!=((n/2))){			/* condition for printing operation signs of entered odd number */
				
					printf("* ");
					counter++; 
				}
				else if(n%2==0 && counter!=((n/2)-1)){		/* condition for printing operation signs of entered even number */	
					
					printf("* ");
					counter++;
				}			
			}		
		}
	}

	else{		/* condition for invalid value for odd/even selection */
	
		result=(-1);		/* returning -1 to main function in order to printf error message */
		
	}

	return (result);
		
}

