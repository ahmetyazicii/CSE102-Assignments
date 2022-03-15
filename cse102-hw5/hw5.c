#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 500
#define PATH_SIZE 11

/* Here,i set the size of the file path array to 11.However in homework pdf it was 10.T
he reason for doing this is the file path of news is "news/1.txt".It is 10+1(NULL character).So that i had to create array with 11 element. */

void menu();
void read_news(char buffer[BUFFER_SIZE], char file_path[PATH_SIZE], int is_Only_Title);
void append_file(char* file_path, char c);
void read_magic_numbers(char buffer_magic[PATH_SIZE], char buffer_news[BUFFER_SIZE]);
double f_func(int x);
double g_func(double f(int x), int a);

/* These are a additional functions. The reasons behind using this functions are ,improve the readability of code and avoid rewriting code */
void print_entire_news(char buffer[BUFFER_SIZE], char file_path[PATH_SIZE],int choice,int append_choice);
void print_title_of_news(char buffer[BUFFER_SIZE], char file_path[PATH_SIZE]);
int check_readed_news(char *file_path,int news);
void print_readed_news(char *file_path);


int main(){
	
	menu();
	return 0;
}


void menu(){
	
	char file_path[PATH_SIZE]={"news/1.txt"};	/* initialize array with "1.txt" string.
						The reason that,increasing the fifth element of array by one and reaches all news files (1,2,3,4)	*/
	char buffer[BUFFER_SIZE];
	char choice_menu;  			/*  variable for first menu choice     								   	*/
	int  choice_newsid;			/*  variable for 'a' option in menu.To choose which news will be read					*/
	int  choice_ra;				/*  variable for to choose whether or not to read again readed news 					*/
	int  choice4;				/*  variable for to choose whether or not to continue 							*/
	char choice5;				/*  variable for 'b' option in menu.To choose whether or not to continue 				*/
	int  check=1;				/*  variable for menu loop. If check sets 0 ,the loop  breaks and program will ends 			*/
	
	printf("**********Daily Press**********\n\nToday's news are listed for you:\n");	
	
	/* There is a loop that depending on the value of check variable. As long as the value of check is 1,the loop continues. */
	do{
		/* printing titles of news.(details are explained in function)*/
		print_title_of_news(buffer,file_path);
		
		printf("\nWhat do you want to do?\n");
		printf("a.Read a new\nb.List the readed news\nc.Get decrypted information from the news\n");
		scanf(" %c",&choice_menu);
	
		switch(choice_menu){
		
			case 'a':	printf("Which news text you want to read?:");
					scanf("%d",&choice_newsid);
					
					choice_ra=1;
					
					/* This if statement checks whether the news readed or not*/
					if(check_readed_news("readed_news_id.txt",choice_newsid)==1){
					
						printf("This news has been read before. Do you want to read it again? Yes(1) / No(0)\n");
						scanf("%d",&choice_ra);
					
					}
					/* The inital value for choice_ra is 1.If user types 0 and does not want to read the news again, choice_ra will be 0.
					Then the news does not print. For other cases(read first time and read again), news prints. */
					
					if(choice_ra!=0){													
						/* Here,passing 1 to the function.Because, readed information is required. */
						print_entire_news(buffer,file_path,choice_newsid,1);						
					}			
									
					printf("\nDo you want to continue reading? Yes(1) / No(0)\n");
					scanf("%d",&choice4);			
					/* Here,If user selects not to continue reading,program sets check to 0.Then loop ends. */
					if(choice4==0){
						check=0;
					}	
				break;
			
			case 'b':	printf("\nReaded news are listed below:\n");
					print_readed_news("readed_news_id.txt");
						
					printf("\nDo you want to continue? Yes(y) / No(n)\n");					
					scanf(" %c",&choice5);				
					/* Here,If user selects not to continue reading,program sets check to 0.Then loop ends. */
					if(choice5=='n'){
						check=0;
					}			
				break;
			
			case 'c':	printf("Which news would you like to decrypt?:");
					scanf("%d",&choice_newsid);
								
					switch(choice_newsid){
					
						case 1:		file_path[5]='1';
								read_magic_numbers(file_path,buffer);
							break;
						case 2:		file_path[5]='2';
								read_magic_numbers(file_path,buffer);
							break;
						case 3:		file_path[5]='3';
								read_magic_numbers(file_path,buffer);
							break;
						case 4:		file_path[5]='4';
								read_magic_numbers(file_path,buffer);
							break;	
					}
					printf("\nDo you want to continue? Yes(y) / No(n)\n");					
					scanf(" %c",&choice5);				
					/* Here,If user selects not to continue reading,program sets check to 0.Then loop ends. */
					if(choice5=='n'){
						check=0;
					}			
				break;
	
		}
	
	}while(check==1);
	
	printf("\nStay Home,Stay Safe...Good Bye!\n");	
}

void read_news(char buffer[BUFFER_SIZE], char file_path[PATH_SIZE], int is_Only_Title){
	
	FILE *fptr_news;
	fptr_news=fopen(file_path,"r");
	
	if(is_Only_Title==0){
		
		printf("\n\n");		/* Printing new lines to avoid visual confusion */
		
		/* Reading entire text with fgets function,untill reach the end of file.Every time reading 20 value from text.*/	
		while(!feof(fptr_news)){
	
			fgets(buffer,20,fptr_news);
			printf("%s",buffer);
		}	
		printf("\n\n");		/* Printing new lines to avoid visual confusion */
	}
	else{	
		
		fgets(buffer,BUFFER_SIZE,fptr_news); /* Reading given(here 500) size of character in to the array from file, untill encounter with new line */
		
	
	}
	fclose(fptr_news);
}

/* This is a additional function. The reason behind using this functions is ,improve the readability of code and avoid rewriting code */
void print_title_of_news(char buffer[BUFFER_SIZE], char file_path[PATH_SIZE]){

	int  i    ;
	char c='0';	
	
	/* 
	The received file path from menu function ,which is "1.txt" here, is increased by one.So that,the program will reaches all news files.After that, the file path
	and "buffer" array sending the read_news function.In that function, array is filling.Finally,the string(title of news) will be printing the screen
	*/
	printf("\n");
	for(i=1;i<=4;i++){		
		c++;			/* increasing character number by one   						*/
		
		file_path[5]=c;		/* sets the fifth element of array to character number(e.g. "1.txt" will be "2.txt")	*/
		read_news(buffer,file_path,1);
		printf("Title of %d. News: %s",i,buffer);	
		
	}

}

/* This is a additional function. The reason behind using this functions is ,improve the readability of code and avoid rewriting code */
/*
	Similar to print_title_of_news function, this function prints the entire text as a user choice.However,unlike print_title_of_news function,if append_choice is 1,
	program saves readed-news information to the file.
	
*/

void print_entire_news(char buffer[BUFFER_SIZE], char file_path[PATH_SIZE],int choice,int append_choice){

	switch(choice){
					
		case 1:		file_path[5]='1';			
				read_news(buffer,file_path,0);
				if(append_choice==1){
					append_file("readed_news_id.txt",'1');
				}				
			break;
							
		case 2: 	file_path[5]='2';
				read_news(buffer,file_path,0);
				if(append_choice==1){
					append_file("readed_news_id.txt",'2');
				}				
			break;
							
		case 3: 	file_path[5]='3';
				read_news(buffer,file_path,0);
				if(append_choice==1){
					append_file("readed_news_id.txt",'3');
				}				;
			break;
							
		case 4: 	file_path[5]='4';
				read_news(buffer,file_path,0);
				if(append_choice==1){
					append_file("readed_news_id.txt",'4');
				}				
			break;
		
		default:	printf("Invalid number of news.Please select from 1 to 4..\n");
				
	}
}


/*In this function, we append the readed information to the file.However,when the news readed different times,program should not add news again.
  Therefore,firsly we check that the our news readed before or not.For this checking operation,we use additonal(helper) function which is check_readed_news .
  If the news was not readed before,program adds news number to the file.
*/
void append_file(char* file_path, char c){

	int cntrl;	
	FILE *fptr;
	
	/* Here, i convert char variable c to integer before sending function.Because the parameter of function is integer. */
	cntrl=check_readed_news(file_path,(c-'0')); 

	
	if(cntrl==0){ 				    /* If check equals 0,it means that news has not read before. */
		fptr=fopen(file_path,"a");
		fprintf(fptr,"%c\n",c);
		fclose(fptr);
	}
}

/* This is a additional function. The reason behind using this functions is ,improve the readability of code and avoid rewriting code */
/*This function searchs entire file and checks that the given news is readed or not.If it is readed,returns 1.If it is not readed,returns 0. */
int check_readed_news(char *file_path,int news){

	int readed;
	int rtrn=0;
	
	FILE *fptr;
	fptr=fopen(file_path,"r");
	
	while(!feof(fptr)){
		
		fscanf(fptr,"%d",&readed);		
		if(readed==news){
			rtrn=1;		
		}
	}
	fclose(fptr);
	return (rtrn);	
}

/* This is a additional function. The reason behind using this functions is ,improve the readability of code and avoid rewriting code */
/*This function prints readed news file.*/
void print_readed_news(char *file_path){

	int cntrl=0;	/* variable for printing message to non readed news. */
	char readed;
	
	FILE *fptr;
	fptr=fopen(file_path,"r");
	
	while(!feof(fptr)){
	
		fscanf(fptr,"%c",&readed);	
		
		if(readed<'9' && readed>'0'){ 	/* The reason of this if statement,just prints numbers. */
			printf("%c. news is readed\n",readed);
			cntrl=1;
		}	
	}
	if(cntrl==0){
		printf("No news has been read so far.\n");
	}
	fclose(fptr);
}

void read_magic_numbers(char buffer_magic[PATH_SIZE], char buffer_news[BUFFER_SIZE]){

	int mgc_number,choice;
	double sum=0.0;
	char hashtag;	
	
	FILE *fptr;
	fptr=fopen(buffer_magic,"r");
	
	/* To find user choice, i use fifth element of buffer_magic array(file path). E.g. If array is something like "4.txt",then fifth element of array is 4. 
   	   And user choice is 4. */
	choice=buffer_magic[5]-'0';
	print_entire_news(buffer_news,buffer_magic,choice,0);	/* Here,passing 0 to the function.Because, readed information is not required. */
	
	while(!feof(fptr)){
	
		fscanf(fptr,"%c",&hashtag);
		if(hashtag=='#'){
			
			fscanf(fptr,"%d",&mgc_number);	
			sum=sum+g_func(f_func,mgc_number);
		}
	}
	
	switch(choice){
		case 1:		printf("The number of tests performed=%.2lf \n",sum);
			break;
		
		case 2:		printf("The number of sick people=%.2lf \n",sum);
			break;
		
		case 3:		printf("The number of deaths=%.2lf \n",sum);
			break;
			
		case 4:		printf("Expected number of sick people=%.2lf \n",sum);
			break;
	}	
	fclose(fptr);
}

double f_func(int x){

	double result;
	
	result=(x*x*x)-(x*x)+2;
	return (result);


}

double g_func(double f(int x), int a){

	double result;
	
	result=(f(a)*f(a));
	return (result);

}

