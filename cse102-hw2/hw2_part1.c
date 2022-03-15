#include<stdio.h>
#include<math.h>


		/* declaring the functions */

int draw_triangle(int side1,int side2,int side3);
void type_triangle(int side1,int side2,int side3);
int perimeter_triangle(int side1,int side2,int side3);
double area_triangle(int side1,int side2,int side3,int perimeter); 


int main(){

	int side1,side2,side3;	/* variables for each side of triangle */
	int draw;		/* variable for draw_triangle fucntion */
	int perimeter;		/* variable for perimeter of triangle */
	
	double area;		/* variable for area of triangle */
	
		/* receiving sides of triangle from user*/
	
	printf("The length of first side:\n");
	scanf("%d",&side1);
	
	printf("The length of second side:\n");
	scanf("%d",&side2);
	
	printf("The length of third side:\n");
	scanf("%d",&side3);
	
	draw=draw_triangle(side1,side2,side3); 
	
	if(draw==1){ /* checks the returning value from functions.If it is equals to 1 ,the traingle can drawn, else not */
	
		printf("\nAccording to the triangle inequality thorem, this triangle can be drawn.\n");
		
		type_triangle(side1,side2,side3); /* determining funtion type in function  */
	
		perimeter=perimeter_triangle(side1,side2,side3);  /* calculating perimeter of triangle in function */
	
		printf("The perimeter of the triangle:%d \n",perimeter);  /* printing the perimeter of triangle*/
	
		area=area_triangle(side1,side2,side3,perimeter); /* calculating the area of triangle in function */
	
		printf("The are of the triangle:%lf \n",area);	/* printing the area of triangle */
	
	}

	else{
	
		printf("\nAccording to the triangle inequality thorem, this triangle cannot be drawn.\n");
	
	}

	return 0;

}	
	

int draw_triangle(int side1,int side2,int side3){
	
	int i=0; /* variable for returning value */
	
	/* There are some calculations for triangle inequality theorem.
	If all the conditions ok, then returning value will be 1 ,else 0 */
	
	if(((side1+side2)>side3) && ((side1+side3)>side2) && ((side2+side3)>side1)){
	
		i=1;
	
	}

	return (i);

}


void type_triangle(int side1,int side2,int side3){

	if((side1==side3) && (side2==side3)){ /* If all the sides equal each other ,it is a Equilateral Triangle. */
	
		printf("\nIt is a Equilateral Triangle.\n");
		
	}
	else if((side1==side2) || (side1==side3) || (side2==side3)){ /* If just two sides equal each other ,
										it is aIsosceles Triangle.*/
	
	
		printf("\nIt is a Isosceles Triangle.\n");
	
	}
	
	else{	/* Else(if non of the sides equal each other) ,it is a Scalene Triangle. */
	
		printf("\nIt is a Scalene Triangle.\n");
	
	}
	
}



int perimeter_triangle(int side1,int side2,int side3){

	int perimeter; /* variable for returning value */
	
	perimeter=(side1+side2)+side3; /* calculating perimeter of the triangle */
	
	return (perimeter);

}


double area_triangle(int side1,int side2,int side3,int perimeter){

	double area; 	/* variable for returning value */
	double p; 	/* variable for half of the perimeter */
	
	p=(perimeter/2.0); /* calculating half of the perimeter. I used 2.0f in order to make result double */
	
	area=(p*(p-side1)*(p-side2)*(p-side3)); /* calculating area according to the formula */
	
	area=sqrt(area); /* calculate the square root of the area by using sqrt function(inside the math library). */

	return (area);

}





