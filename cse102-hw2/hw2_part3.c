#include<stdio.h>

#define DOLLAR_RATE 6.14 	/* define the dollar constant */
#define EURO_RATE 6.69		/* define the euro constant */

int main(){

	int selection1,selection2; 	/* variable for selections */
	
	double input_money;		/* variable for input money */	
	double output_money; 		/* variable for output money */
	
	printf("*****Welcome to Most Reliable Exchange Office*****\n");
	
	printf("Enter the amount:\n");
	scanf("%lf",&input_money);
	
	printf("\nPlease select your currency\n"); 
	printf("1. Turkish Lira\n2. Euro\n3. Dollar\n\n");
	scanf("%d",&selection1);
	
	
	/* Switch statement for first selection. In this part, I convert all the currencies to Turkish Liras in order to use 		   second switch statement. */
	   	
	
	switch(selection1){ 
	
		case 1:
			
			printf("You have %lf Turkish Liras\n",input_money);
			
			break;
			
		case 2:
		
			printf("You have %lf Euro \n",input_money);
			
			input_money=input_money*EURO_RATE;
			
			break;
			
		case 3:
		
			printf("You have %lf Dollar\n",input_money);
			
			input_money=input_money*DOLLAR_RATE;
			
			break;
			
		default:	/* condition for wrong choice */
		
			printf("\nYour selection is invalid!\n");
				
	}
	
	printf("Choose  which currency you want to convert\n");
	scanf("%d",&selection2);
	
	
	/* Switch statement for second selection(conversion).First part of code,i converted all the currencies to Turkish Liras.
	In this part, according the  user choice , i convert money to other currencies. */
	
	
	switch(selection2){
	
		case 1:
			
			output_money=input_money;
					
			printf("\nYou have %lf Turkish Liras\n",output_money);
					
			break;
			
		case 2:
		
			output_money=input_money/EURO_RATE;
			
			printf("\nYou have %lf Euro\n",output_money);
			
			break;
			
		case 3:
		
			output_money=input_money/DOLLAR_RATE;
			
			printf("\nYou have %lf Dollar\n",output_money);
			
			break;
		
		default:   	/* condition for wrong choice */
		
			printf("\nYour selection is invalid!\n");
		
	}
		
	return 0;
	
}
