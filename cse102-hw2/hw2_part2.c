#include<stdio.h>
#include<math.h>

int number_length(int number);
int find_digit(int number,int index); 

int main(){

	int number; 	/* variable for input number */
	int length;	/* variable for length of number */
	int index;	/* variable for input index */
	int digit;	/* variable for calculated digit */
	
	printf("Enter a number(maximum 6 digits):\n");
	scanf("%d",&number);
	
	length=number_length(number); /* finding the length of number */
	
	if(length==0){ /* Condition for 7 or more digits number */
	
		printf("Please enter maximum 6 digits number.\n");
	
	
	
	}
	
	
	else {
	
		printf("Your number has %d digits.\n\n",length);
	
	  	printf("When your number is written 100 times next to each other,which digit of this number would you like to see\n");
		scanf("%d",&index);
	
		if(index==0){ /* Condition for 0.th index */
	
			printf("\n%d.th digit of the big number sequence is not exist. \n",index);
	
	
		}
	
		else {
	
			digit= find_digit(number,index); /* finding the digit of the number */
	
			printf("\n%d.th digit of the big number sequence: %d \n",index,digit);
		}
	
	}
	
	return 0;
	
}

int number_length(int number){

	int n_leng;
	
	
	/* Here, I divide number from 10 to the 5(100.000) to 1 and checks the quotinent.
	If the quotinent equal or greater than 1, we find the length of number.For example, our number is 14.458.
	First we divide it to 100.000. Quotinent of this division less than 0.It means that ,our number cannot be 6 digit.
	Then we divide it 10.000. Quotinent of this division bigger than 1. Our number is 5 digit. */
	
	 if((number/pow(10,6))>=1){
	
		n_leng=0;
	
	}
	
	else if((number/pow(10,5))>=1){
	
		n_leng=6;
	
	}
	
	else if((number/pow(10,4))>=1){
	
		n_leng=5;
	
	}
	
	else if((number/pow(10,3))>=1){
	
		n_leng=4;
	
	}
	
	else if((number/pow(10,2))>=1){
	
		n_leng=3;
	
	}
	
	else if((number/pow(10,1))>=1){
	
		n_leng=2;
	
	}
	
	else if(number>=1){
	
		n_leng=1;
	
	}
	
	else {
	
		n_leng=0;
	
	}

	return (n_leng);

}


int find_digit(int number,int index){

	int length; 	/* variable for length of the number */
	int digit;	/* variable for digit */
	
	
	
	length=number_length(number); /* find the length of the number */
	
	/* Firstly, I determine the which digit of the number will be compute.Then, divide the number to power of 10 to digit,
	and find the quotinent.Finally, find the remainder.*/
	
	
	digit=index%length;
	
	if(digit==0){  /* Condition for last digit of number */
	
		digit=number%10;
	
	
	}
	
	else {
	
		digit=length-digit;
	
		digit=(number/(pow(10,digit)));
	
		digit %=10;
		
	}
	
	return (digit);
	
}
