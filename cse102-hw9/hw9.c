#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define CARDS_FACE 13
#define CARDS_SUIT 4
#define CARDS_NUM 52
#define CARDS_NAME 10


struct card {
	const char *face;
	const char *suit;
};


struct Hospital {
	char *name;
	char citiesServed[3];
};


/* Here, i used static int for hospital numbers in part2.The reason that,i use the user input  for termination condition.
   Therefore, the input changes.However, program needs to unchange user input. */
static int stcHospitalnum;	


void menu();
void stay_home_problem();
int numPathsHome(int street, int avenue);
void health_coverage();
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]);
int checkHospitals(char _cities[6],int _numHospitals,struct Hospital results[4]);
void shuffleDeck();
void checkrandoms(int *face,int *suit,int saved[CARDS_SUIT][CARDS_FACE]);



int main(){

	srand(time(NULL));

	menu();
	return 0;
}



/* This is a menu function. This function continues until the user types 0(terminate condition). */
void menu(){

	int choice;

	do{
		printf("\n(1) - Stay Home Problem\n");
		printf("(2) - COVID-19 Health Coverage\n");
		printf("(3) - Mixing The Deck\n");
		printf("(0) - Exit\n");
		
		printf("\nPlease make your choice:\n");
		scanf("%d",&choice);
		
	
		switch(choice){
		
			case 1:		stay_home_problem();
				break;
				
			case 2:		health_coverage();
				
				break;
			case 3:		shuffleDeck();
				
				break;
				
			case 0:		printf("\n---!Good Bye.Please Stay Safe!---\n");
				break;
				
			default:	printf("\nPlease select from menu:\n");		
		}
	}while(choice!=0);
}


/* This function for 1.part of homework. */ 
void stay_home_problem(){
	
	int strt,aven;
	int paths;
	
	printf("\nEnter the street number: ");
	scanf("%d",&strt);
	
	printf("Enter the avenue number: ");
	scanf("%d",&aven);
	
	paths=numPathsHome(strt,aven);

	printf("Number of optimal paths to take back home: %d\n",paths);
}

/* This function recursively found the number of paths.The method is similar to placing each corner 1 and sum up all them till reach the last place. */
int numPathsHome(int street, int avenue){
	
	if(street==1 || avenue==1){
		return 1;
	}
	
	return ( numPathsHome(street-1,avenue) + numPathsHome(street,avenue-1) );
}


/* This function for 2.part of homework. */
void health_coverage(){

	char cities[6]={'A','B','C','D','E','F'};
	char locations[4][3]={ {'A','B','C'} , {'A','C','D'} , {'B','F'} , {'C','E','F'} };
	int num_hospital;
	int i;		/* variable for loop */
	int j=1;	/* variable for count hospital number. */
	struct Hospital result[4];
	
	printf("Enter the maximum number of hospitals that can be constructed: ");
	scanf("%d",&num_hospital);

	stcHospitalnum=num_hospital;	/* assign to static variable. */
	
	switch(num_hospital){
		
		case 0:		printf("We need to build hospitals!!\n");
			break;
		case 1:
		case 2:
		case 3:
		case 4:
				if(canOfferCovidCoverage(cities,locations,num_hospital,result)==1){
					printf("Yes,can offer health care to all!\n\n");
					
					for(i=0;i<num_hospital;i++){
						printf("Hospital -%d\n",j);
						printf("Hospital locations: %c%c%c \n",result[i].citiesServed[0],result[i].citiesServed[1],result[i].citiesServed[2]);
						j++;
					}
				}
				else{
					printf("No,some cities are not covered.\n");
				}
			break;
		default:	printf("We can not afford that much hospitals :(\n");
	}
}

/* This function recursively checks that whether or not is it possible to covers all cities with typed hospital numbers(int _numHospitals). */
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]){


	switch(_numHospitals){
		case 0:		/* save cities to struct array(results). */
				results[_numHospitals].citiesServed[0] = _locations[_numHospitals][0];
				results[_numHospitals].citiesServed[1] = _locations[_numHospitals][1];
				results[_numHospitals].citiesServed[2] = _locations[_numHospitals][2];
				return checkHospitals(_cities,stcHospitalnum,results);
				
			break;
		case 1:		/* save cities to struct array(results). */
				results[_numHospitals].citiesServed[0] = _locations[_numHospitals][0];
				results[_numHospitals].citiesServed[1] = _locations[_numHospitals][1];
				results[_numHospitals].citiesServed[2] = _locations[_numHospitals][2];
			break;
		case 2:		/* save cities to struct array(results). */
				results[_numHospitals].citiesServed[0] = _locations[_numHospitals][0];
				results[_numHospitals].citiesServed[1] = _locations[_numHospitals][1];
				results[_numHospitals].citiesServed[2] = _locations[_numHospitals][2];
			break;
		case 3:		/* save cities to struct array(results). */
				results[_numHospitals].citiesServed[0] = _locations[_numHospitals][0];
				results[_numHospitals].citiesServed[1] = _locations[_numHospitals][1];
				results[_numHospitals].citiesServed[2] = _locations[_numHospitals][2];
			break;

	}
	if(canOfferCovidCoverage(_cities,_locations,_numHospitals-1,results)==0){
		return(canOfferCovidCoverage(_cities,&(_locations[1]),_numHospitals-1,results));
	}
	
	return(canOfferCovidCoverage(_cities,_locations,_numHospitals-1,results));
}

/* This function checks that whether the saved hospitals covers the entire city or not. */
int checkHospitals(char _cities[6],int _numHospitals,struct Hospital results[4]){
	int counter=0;		/* variable for city counter */
	int rtrn=0;		/* variable for returing value */
	int i,j,k;		/* variables for loops */
	
	for(k=0;k<6;k++){	/* loop for all cities. */
		
		for(i=0;i<_numHospitals;i++){
			
			for(j=0;j<3;j++){	
				
				if(results[i].citiesServed[j]==_cities[counter]){	
					counter++;
				}
			}
		}
	}
	if(counter>=6){		/* when all cities covered ,sets return value to 1.otherwise return value stays 0 */
		rtrn=1;
	}
	
	return ( rtrn );
}


/* This function for 3.part of homework. */
/* This function shuffles deck. Firstly, manually save faces and deck string array.Then randomly assign this arrays the each card struct. */
void shuffleDeck(){

	char deckface[CARDS_FACE][CARDS_NAME]={"Ace",
					       "Deuce",
					       "Three",
					       "Four",
					       "Five",
					       "Six",
					       "Seven",
					       "Eight",
					       "Nine",
					       "Ten",
					       "Jack",
					       "Quenn",
					       "King"};
	
	char decksuit[CARDS_SUIT][CARDS_NAME]={"Hearts",
					       "Diamonds",
					       "Clubs",
					       "Spades"};
	
	int randomface;					/* variable for create random face number */
	int randomsuit;					/* variable for create random suit number */
	int i;						/* variable for loop ( deck )		  */
	int genNumbers[CARDS_SUIT][CARDS_FACE]={0};	/* array for save created random cards.   */
	
	struct card deck[CARDS_NUM];			/* struct array for all cards in deck	  */
	
	for(i=0;i<CARDS_NUM;i++){	/* loop for saving cards to struct array. */
		
		checkrandoms(&randomface,&randomsuit,genNumbers); /* receiving proper random card numbers from function. */
		
		deck[i].suit=decksuit[randomsuit];
		deck[i].face=deckface[randomface];
	}
	
	printf("\n");		
	
	for(i=0;i<CARDS_NUM;i+=2){ 	/* loop for printing cards in order to given format(as in hw pdf). */
		
		printf("%s of %s",deck[i].face,deck[i].suit);
		printf("               %s of %s\n",deck[i+1].face,deck[i+1].suit);
	}
}

/* This function randomly crate a card and checks that whether card is created before or not .If card okay(not created before) , returns card face and suit numbers.*/
void checkrandoms(int *face,int *suit,int saved[CARDS_SUIT][CARDS_FACE]){
	
	int check=0;	
	int tempf;
	int temps;
	
	while(check!=1){
		
		tempf=rand()%CARDS_FACE+0;
		temps=rand()%CARDS_SUIT+0;
		
		if(saved[temps][tempf]!=1){
			check=1;
		}
	
	}
	
	saved[temps][tempf]=1;
	*face=tempf;
	*suit=temps;
}



