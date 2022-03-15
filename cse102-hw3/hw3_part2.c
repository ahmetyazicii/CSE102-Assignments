#include<stdio.h>
#include<math.h>


int isprime(int a);


int main(){

	int number;		/* variable for input number */
	int i;			/* variable for loop */
	int check;		/* variable for check prime or not */
	
	printf("Please enter an integer: ");
	scanf("%d",&number);
	
	for(i=2;i<=number;i++){
		
		check=isprime(i);
		
		if(check==0){		/* if returning value from function equals 0, number is prime. else not */
		
			printf("%d is a prime number\n",i);
		
		}		
		else{
		
			printf("%d is not a  prime number, it is dividible by %d\n",i,check);
		
		}
	}

	return 0;

}


int isprime(int a){

	int i; 		/* variable for loop */
	int check=0;	/* variable for returning value */
	int sqrt_a;	/* variable for square root of a(number from main) */
	
	sqrt_a=sqrt(a);
	
	for(i=sqrt_a;i>1;i--){ 		/* I decrease i in order to find least divisor number */
	
		if(a%i==0){
		
			check=i;		/* for the least divisor number */
		}	
	}
	
	return (check);		/* if number is prime function will return 0 to main */

}
