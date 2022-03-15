#include<stdio.h>


int andop(int a,int b);			/* function in order to calculate AND operator(homework function) */

	/* I wrote 4 additional functions in order to improve efficiency of code and reduce repetitions. */

int pow_ten(int base,int up);		/* function for power of ten(instead of pow function, however this function onlu calculates powers of ten) */	
int find_digit(int number,int length);	/* function for finding digits of number */
int number_length(int number);		/* function for finding length of the number */
int binary_check(int number);		/* function for binary check */


int main(){

	int num1,num2;		/* variables for input numbers */
	int condition=0;	/* variable for checking condition */
	int result;		/* variable for result of AND operator */
	
	do{ 			/* Here, I used do-while statement in order to find proper inputs.
				When the proper inputs found, condition will be 1 and loops ends.*/
	
		printf("First Integer: ");
		scanf("%d",&num1);
	
		printf("Second Integer: ");
		scanf("%d",&num2);
	
		if(number_length(num1)!=number_length(num2)){ 			/* searching equal number lengths */
	
			printf("Integers should have the same length, please enter 2 new integers.\n");
		}
		else if(binary_check(num1)==0 || binary_check(num2)==0){	/* searching binary numbers */
	
			printf("Integers should be binary, please enter 2 new integers.\n");
		}	
		else{					/* for proper inputs */
	
			result=andop(num1,num2);
			printf("%d AND %d = %d\n",num1,num2,result);
			condition=1;	
		}
	
	
	}while(condition!=1);

	return 0;
}


int find_digit(int number,int length){   	/*This function finds the digits of the number. */

	int digit;
	
	digit=(number/pow_ten(10,(length-1)));
	digit %=10;
	
	return (digit);
	
}


int pow_ten(int base,int up){		/* This function finds the positive powers of 10(ten). */

	int step=1;
	int result;
	
	result=base;
	
	if(up!=0){
	
		while(step!=up){
		
			result*=10;
			step++;		
		}	
	}
	else{   			/* If the power of number is 0,program returns 1 .The reason is  0th power of all numbers is 1. */
	
		result=1;
	}

	return result;
	
}

int andop(int a,int b){

	int i;
	int result=0;
	
	i=number_length(a);

			/* Here,I compare all digits of numbers.When the digit of the both numbers equal 1 at the same digit,I multiply that digit with the power of ten, and add.As a result,I found the AND operator of the numbers. */


	while(i!=0){
	
		if(find_digit(a,i)==1 && find_digit(b,i)==1){
		
			result+=pow_ten(10,(i-1));		
		}		
		i--;
	}

	return result;

}


int binary_check(int number){  		/* This function checks all the digits of the number and seeks for not binary numbers */

	int check=1;
	int i;
	
	i=number_length(number);
	
	while(i!=0){
	
		if(find_digit(number,i)!=0 && find_digit(number,i)!=1){
		
			check=0;
		}
		
		i--;
	}

	return check;		/* if number is binary number returns 1,if it is not returns 0 */


}


int number_length(int number){  	 /* This function finds the length of the number */

	int counter=0;
	
	
	do{
	
		number=number/10;
		counter++;
	
	}while(number!=0);

	return counter;

}


