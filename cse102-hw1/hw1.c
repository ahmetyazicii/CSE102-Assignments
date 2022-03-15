#include<stdio.h> 	/* definition of printf and scanf */
#include<math.h> 	/* definition of sqrt */

void find_root(void);
void find_newtonian_root(void);
int find_multiple_closest(int a,int b);

int main(){

	int num1,num2; 			/* input - two integers for divisible number */
	int result;    			/* output - divisible number */

	find_root(); 			/* Calling function which finds the roots of the equation */
	
	printf("\n"); 			/* Printing new line to avoid visual confusion */
	
	find_newtonian_root(); 		/* Calling function which searchs the roots of the equation by Newton's Algorithm*/

	printf("\n");			/* Printing new line to avoid visual confusion */

	/* Receiving inputs from user in order to find the closest divisible integer */	

	printf("Enter the first integer: ");
	scanf("%d",&num1);
	
	printf("Enter the second integer: ");
	scanf("%d",&num2);

	

	result=find_multiple_closest(num1,num2); /* Sending values to function and put the returning value into result variable */
	
	/* Printing the output by correct condition.*/

	if(result==num2){
		
		printf("Closest number to %d that is multpile of %d itself.\n",num1,num2);
	}
	
	else {
		
		printf("Closest number to %d that is multpile of %d is %d.\n",num1,num2,result);
	}

	return 0;
}

void find_root(void){

	int coeff1,coeff2,coeff3; 		/* input - coefficients of the quadric equation */
	int delta; 				/* Variable for delta */
	
	double sqrt_delta; 			/* Variable for square root of delta */
	double root1,root2; 			/* Variables for roots of quadric equation */
	double temp;				/* Temporary variable */

	/* Receiving coefficients  from user*/

	printf("Please enter the first coefficient: ");
	scanf("%d",&coeff1);

	printf("Please enter the second coefficient: ");
	scanf("%d",&coeff2);

	printf("Please enter the third coefficient: ");
	scanf("%d",&coeff3);

	delta=(coeff2*coeff2)-(4*coeff1*coeff3); 	/* Calculating the delta(delta=b^2-4ac) */

	/* There are 3 possible situation for delta. First one,if delta  greater than 0,equation has real roots.
	Second one, if delta equals 0, equation has only one real root.Last one,if delta less than 0,equation has not any real roots.*/

	if(delta>0){   /* In this situation, equation has two real roots.*/

		sqrt_delta=sqrt(delta); /*Calculate the square root of delta by using sqrt function(inside the math.h library) */

	/*Finding roots by using roots formula*/

		root1=(-coeff2+sqrt_delta)/(2*coeff1);
		root2=(-coeff2-sqrt_delta)/(2*coeff1);

		if(root2>root1){  /*Making sorting operation in order to printing descending order */
		
			temp=root1;
			root1=root2;
			root2=temp;
	
		}
		
		/* Here, I used 4 if/else statement in order to print '+','-' sign for each coefficient. 
		Instead of using if/else statement,i could use %+d. However, i am not sure that %+d is the right way */	


		if((coeff2>=0) && (coeff3>=0)){ 

			printf("Your equation %dx^2+%dx+%d have real roots {%.3lf,%.3lf}.\n",coeff1,coeff2,coeff3,root1,root2);

		}
		else if((coeff2>=0) && (coeff3<0)){

			printf("Your equation %dx^2+%dx%d have real roots {%.3lf,%.3lf}.\n",coeff1,coeff2,coeff3,root1,root2);

		}
		else if((coeff2<0) && (coeff3<0)){

			printf("Your equation %dx^2%dx%d have real roots {%.3lf,%.3lf}.\n",coeff1,coeff2,coeff3,root1,root2);
		}
		else if((coeff2<0) && (coeff3>=0)){

			printf("Your equation %dx^2%dx+%d have real roots {%.3lf,%.3lf}.\n",coeff1,coeff2,coeff3,root1,root2);

		}
	
	
	}
	
	else if(delta==0){ /*In this situation, equation has one real root */
	
		sqrt_delta=sqrt(delta); /*Calculate the square root of delta by using sqrt function(inside the math.h library) */

		root1=(-coeff2+sqrt_delta)/(2*coeff1); /*Finding root by using roots formula*/
	
		/* Here, I used 4 if/else statement in order to print '+','-' sign for each coefficient. 
		Instead of using if/else statement,i could use %+d. However, i am not sure that %+d is the right way. */			
	
		if((coeff2>=0) && (coeff3>=0)){

			printf("Your equation %dx^2+%dx+%d have a real root {%.3lf}.\n",coeff1,coeff2,coeff3,root1);

		}
		else if((coeff2>=0) && (coeff3<0)){

			printf("Your equation %dx^2+%dx%d have a real root {%.3lf}.\n",coeff1,coeff2,coeff3,root1);

		}
		else if((coeff2<0) && (coeff3<0)){

			printf("Your equation %dx^2%dx%d have a real root {%.3lf}.\n",coeff1,coeff2,coeff3,root1);

		}
		else if((coeff2<0) && (coeff3>=0)){

			printf("Your equation %dx^2%dx+%d have a real root {%.3lf}.\n",coeff1,coeff2,coeff3,root1);

		}
	
	}

	else if(delta<0){ /* In this situation, equation has not any real roots.*/

	
		/* Here, I used 4 if/else statement in order to print '+','-' sign for each coefficient. 
		Instead of using if/else statement,i could use %+d.However, i am not sure that %+d is the right way . */			

		if((coeff2>=0) && (coeff3>=0)){

			printf("Your equation %dx^2+%dx+%d not have any real roots.\n",coeff1,coeff2,coeff3);

		}
		else if((coeff2>=0) && (coeff3<0)){

			printf("Your equation %dx^2+%dx%d not have any real roots.\n",coeff1,coeff2,coeff3);

		}
		else if((coeff2<0) && (coeff3<0)){

			printf("Your equation %dx^2%dx%d not have any real roots.\n",coeff1,coeff2,coeff3);

		}
		else if((coeff2<0) && (coeff3>=0)){

			printf("Your equation %dx^2%dx+%d not have any real roots.\n",coeff1,coeff2,coeff3);

		}

	}
	
}


void find_newtonian_root(void){
	
	float coeff1,coeff2,coeff3; 		/*  input - coefficients of the quadric equation */
	float x0; 				/* input - initial guess */
	float delta; 				/* Variable for delta */
	
	double x1,x2,x3,x4,x5; 			/* Variables for estimated roots */
	double f_x;				/* Variable for f(x) (for applying Newton's Algorithm) */
	double diff;				/* Variable for difference (between actual root and estimated root) */
	double sqrt_delta;			/* Variable for square root of delta */
	double root1,root2;			/* Variables for actual roots */
	double temp; 				/* Temporary variable */

	/* Receiving coefficients and the initial value(x0) from user*/

	printf("Please enter the first coefficient: ");
	scanf("%f",&coeff1);

	printf("Please enter the second coefficient: ");
	scanf("%f",&coeff2);

	printf("Please enter the third coefficient: ");
	scanf("%f",&coeff3);

	printf("Please Enter the initial: ");
	scanf("%f",&x0);

	/* Calculating the actual roots as in function find_root*/
	
	delta=(coeff2*coeff2)-(4*coeff1*coeff3);

	
	if(delta>0){   

		sqrt_delta=sqrt(delta); 


		root1=(-coeff2+sqrt_delta)/(2*coeff1);
		root2=(-coeff2-sqrt_delta)/(2*coeff1);

		if(root2>root1){ 
		
			temp=root1;
			root1=root2;
			root2=temp;
	
		}
		
	}
	
	else if(delta==0){
	
		sqrt_delta=sqrt(delta);

		root1=(-coeff2+sqrt_delta)/(2*coeff1);
	
	}
					/* End of the roots calculation */
	


	if(root2>x0){ 		/* If the entered initial less than the smallest root, 
				the program changes the roots among themselvse in order to compare the difference between actual and estimated root. */
		
		root1=root2;	
			
	}


					/* Printing the schema of output */


		/* Here, I used 4 if/else statement in order to print '+','-' sign for each coefficient. 
		Instead of using if/else statement,i could use %+f. However, i am not sure that %+f is the right way . */	

	if((coeff2>=0) && (coeff3>=0)){

		printf("\nYour equation is %.0fx^2+%.0fx+%.0f and iterations are\n\n",coeff1,coeff2,coeff3);

	}
	else if((coeff2>=0) && (coeff3<0)){

		printf("\nYour equation is %.0fx^2+%.0fx%.0f and iterations are\n\n",coeff1,coeff2,coeff3);

	}
	else if((coeff2<0) && (coeff3<0)){

		printf("\nYour equation is %.0fx^2%.0fx%.0f and iterations are\n\n",coeff1,coeff2,coeff3);
	}
	else if((coeff2<0) && (coeff3>=0)){

		printf("\nYour equation is %.0fx^2%.0fx+%.0f and iterations are\n\n",coeff1,coeff2,coeff3);
	}

	printf("Step		x	  f(x)	    Difference\n\n");
	
	/* Applying Newton's Algorithm (x=x0-(f(x0)/f'(x0)) 5 times. */	

	x1=x0-(((x0*x0)*coeff1)+(coeff2*x0)+coeff3)/((2*coeff1*x0)+coeff2);
	f_x=((x1*x1)*coeff1+(coeff2*x1)+coeff3);
	diff=x1-root1;
	
	if(diff<0){ 		/* Absolute value for difference */

		diff=-diff;
	}
	
	printf("x1		%.4lf %.5lf	   %.4lf\n",x1,f_x,diff);

	x2=x1-(((x1*x1)*coeff1)+(coeff2*x1)+coeff3)/((2*coeff1*x1)+coeff2);
	f_x=((x2*x2)*coeff1+(coeff2*x2)+coeff3);
	diff=x2-root1;
	
	if(diff<0){		/* Absolute value for difference */
		
		diff=-diff;
	}
	
	printf("x2		%.4lf %.5lf	   %.4lf\n",x2,f_x,diff);

	x3=x2-(((x2*x2)*coeff1)+(coeff2*x2)+coeff3)/((2*coeff1*x2)+coeff2);
	f_x=((x3*x3)*coeff1+(coeff2*x3)+coeff3);
	diff=x3-root1;	

	if(diff<0){		/* Absolute value for difference */
		
		diff=-diff;
	}	
	
	printf("x3		%.4lf %.5lf	   %.4lf\n",x3,f_x,diff);

	x4=x3-(((x3*x3)*coeff1)+(coeff2*x3)+coeff3)/((2*coeff1*x3)+coeff2);
	f_x=((x4*x4)*coeff1+(coeff2*x4)+coeff3);
	diff=x4-root1;
	
	if(diff<0){		/* Absolute value for difference */
		
		diff=-diff;
	}
		
	printf("x4		%.4lf %.5lf	   %.4lf\n",x4,f_x,diff);

	x5=x4-(((x4*x4)*coeff1)+(coeff2*x4)+coeff3)/((2*coeff1*x4)+coeff2);
	f_x=((x5*x5)*coeff1+(coeff2*x5)+coeff3);
	diff=x5-root1;
	
	if(diff<0){		/* Absolute value for difference */
	
		diff=-diff;
	}
		
	printf("x5		%.4lf %.5lf	   %.4lf\n",x5,f_x,diff);
	
}

int find_multiple_closest(int a,int b){

	int rem; 	 	/* The remainder value of the division process */
	int quot;	 	/* The quotinent value of the division process */
	int result;		/* Variable for result */

	quot=a/b; 		/* Finding quotinent */
	rem=a%b;		/* Finding remainder */

	if(rem==0){ 		/* If there are not any remainder, closest number to first integer is second integer  */ 

		return(b);	/*Returning divisor number to main function */

	}

	 if(rem>=(b/2)){ 	/* If remainder equal or greater than the half of the divisor number,
				 closest number to first integer is the divisor number times (quotinent number +1) */

		result=b*(quot+1);

		return (result);/* Returning result to the main funtion */

	}

	else if(rem<(b/2)){	/* If remainder less than the half of the divisor number, 
				 closest number to first integer is the divisor number times quotinent number.*/

		result=b*(quot);

		return(result);/* Returning result to the main funtion */

	}

	return 0;
}


