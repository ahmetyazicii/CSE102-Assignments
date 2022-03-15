#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define LEN_GAME_NAME 100
#define LEN_GENRE_PLAT 20
#define LEN_ROW 200
#define MAX_ROW 2000 /* first row not included */
#define LEN_DATA 8
#define NUM_OPERATIONS 7
#define GENRE_NUM 0
#define PLATF_NUM 1
#define YEAR_NUM 2
#define NA_NUM 3
#define EU_NUM 4
#define GLOBAL_NUM 5
#define SCORE_NUM 6


void read_all(char entiref[][LEN_ROW]);
void seperate_ggp(char entiref[][LEN_ROW],char games[][LEN_GAME_NAME],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],int *len_g,int * len_p);
int check_genres(char genres[][LEN_GENRE_PLAT],char *temp,int i);
int check_platforms(char platf[][LEN_GENRE_PLAT],char *temp,int i);

void keep_data(char entiref[][LEN_ROW],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_g,int len_p);
float coresspond_genre(char genres[][LEN_GENRE_PLAT],char *data_g,int g_len);
float coresspond_platf(char platf[][LEN_GENRE_PLAT],char *data_f,int f_len);

void menu(char names[][LEN_GAME_NAME],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_g,int len_p);
int user_input();

void list_of_genres(char genres[][LEN_GENRE_PLAT],int g_len);
void list_of_platf(char platf[][LEN_GENRE_PLAT],int p_len);
void games_according_years(char names[][LEN_GAME_NAME],float data[][LEN_DATA]);
int condition_for_years(float data[][LEN_DATA],int year, int chc);
void game_informations(char names[][LEN_GAME_NAME],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA]);
void average_of_games(float data[][LEN_DATA]);
void popularity_of_games(char names[][LEN_GAME_NAME],float data[][LEN_DATA]);
int check_typed_name(char names[][LEN_GAME_NAME],char inpt[]);
void frequency_of_genres(char genres[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_g);
void frequency_of_platforms(char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_p);


int main(){

	char entiref[MAX_ROW][LEN_ROW];			/* for save entire file */
	char games_names[MAX_ROW][LEN_GAME_NAME];	/* for names of games */
	char genres_names[MAX_ROW][LEN_GENRE_PLAT];	/* for names of genres */
	char platf_names[MAX_ROW][LEN_GENRE_PLAT];	/* for names of platforms */
	float game_stats[MAX_ROW][LEN_DATA];		/* for stats of games */
	int len_genres=0;				/* variable for numbers of genres */
	int len_platf=0;				/* variable for numbers of platforms */
	

	read_all(entiref);									/* reading entire file */
	/* seperate names,genres and platforms.Also determine numbers of genres and platforms. */
	seperate_ggp(entiref,games_names,genres_names,platf_names,&len_genres,&len_platf);	
	keep_data(entiref,genres_names,platf_names,game_stats,len_genres,len_platf);		/* keeping data of every game. */
	menu(games_names,genres_names,platf_names,game_stats,len_genres,len_platf);

	return 0;
}


void menu(char names[][LEN_GAME_NAME],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_g,int len_p){
	int choice;
	int check=1;
	
	do{	/* there is a loop continue till check variable not 0. When the user typed '8',check variable sets 0 and loop ends. */
		choice=user_input();	/* receive user choice */
		
		switch(choice){
			case 0:		list_of_genres(genres,len_g);
				break;
			case 1:		list_of_platf(platf,len_p);
				break;
			case 2:		games_according_years(names,data);
				break;
			case 3:		game_informations(names,genres,platf,data);
				break;
			case 4:		average_of_games(data);
				break;
			case 5:		popularity_of_games(names,data);
				break;
			case 6:		frequency_of_genres(genres,data,len_g);
				break;
			case 7:		frequency_of_platforms(platf,data,len_p);
				break;
			case 8:		printf("\nSEE YOU LATER..\n");	
					check=0;
				break;
			default:	printf("\nTRY AGAIN.\n");	/* For invalid user choices E.g 15 . */
		}
	}while(check!=0);

}

/* This function reads every row of file except first row since first row does not keep any information about game.Its just title of file. */
void read_all(char entiref[][LEN_ROW]){
	
	int i=0;	/* variable for array indexes. */
	char c;		/* temporary variable for passing the first row */
	FILE *fptr;
	fptr=fopen("Video_Games.txt","r");
	
	if(fptr==NULL){	/* When file could not opened, printing error message. */
		printf("\n!ERROR!--Failed to open file--\n");
	}
	else{
		do{	/* passing first row ,because it is not contain any information  about games.(It is just a title) */
			fscanf(fptr,"%c",&c);
		}while(c!='\n');
		
		while(!feof(fptr)){
			fgets(entiref[i],LEN_ROW,fptr);	
			entiref[i][strcspn(entiref[i],"\n")]='\0';	/* Here ,sets new line index to NULL char. strcspn returns position of new line char. */
			i++;
		}
	}
}

/* This function fills names,genres and platform arrays.Also keep track the length of genre and platfrom arrays. */
void seperate_ggp( char entiref[][LEN_ROW],char games[][LEN_GAME_NAME],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],int *len_g,int * len_p){
	int i;
	char temp_entire[LEN_ROW];	
	char *temp_names;		/* temp strings for strtok */
	char *temp_genre;
	char *temp_platf;
	
	/* Here i used strtok in order to divide arrays parts(tokens) with comma.Then copied them arrays.
	   I searched information about strtok from online and book (ANSI C -Brian And Dennis).*/
	for(i=0;i<MAX_ROW;i++){
		
		strcpy(temp_entire,entiref[i]); /* copying original array to temp array in order to make sure that original date is not change. */
		
		/* divide array in to parts with strtok func. */
		temp_names=strtok(temp_entire,",");
		temp_genre=strtok(NULL,",");
		temp_platf=strtok(NULL,",");
		
		/* coping temp strings to arrays */
		strcpy(games[i],temp_names);
		if(check_genres(genres,temp_genre,*len_g)==1){	 /* checks that genre is saved before or not.If not ,save and increment len_g. */
			strcpy(genres[*len_g],temp_genre);
			*len_g=*len_g+1;
		}		
		if(check_platforms(platf,temp_platf,*len_p)==1){ /* checks that platform is saved before or not.If not ,save and increment len_p. */
			strcpy(platf[*len_p],temp_platf);
			*len_p=*len_p+1;
		}		
	}
}

/* cheks that given array is saved before or not.If read,return 0. */
int check_genres(char genres[][LEN_GENRE_PLAT],char *temp,int i){
	int rtrn=1;
	for(;i>=0;i--){
		if(strcmp(genres[i],temp)==0) rtrn=0;
	}
	return rtrn;
}
/* cheks that given array is saved before or not.If read,return 0. */
int check_platforms(char platf[][LEN_GENRE_PLAT],char *temp,int i){
	int rtrn=1;
	for(;i>=0;i--){
		if(strcmp(platf[i],temp)==0) rtrn=0;
	}
	return rtrn;
}

/* This funciton saves games stats. */
void keep_data(char entiref[][LEN_ROW],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_g,int len_p){
	int i;
	char temp_entire[LEN_ROW];
	char *temp;
	/* temp strings for strtok func. */
	char *temp_g;
	char *temp_p;
	char *temp_y;
	char *temp_na;
	char *temp_eu;
	char *temp_gbl;
	char *temp_s;

	for(i=0;i<MAX_ROW;i++){
		
		strcpy(temp_entire,entiref[i]); 
		temp=strtok(temp_entire,",");
		temp_g=strtok(NULL,",");
		temp_p=strtok(NULL,",");
		temp_y=strtok(NULL,",");
		temp_na=strtok(NULL,",");
		temp_eu=strtok(NULL,",");
		temp_gbl=strtok(NULL,",");
		temp_s=strtok(NULL,",");
		
		data[i][GENRE_NUM]=coresspond_genre(genres,temp_g,len_g);
		data[i][PLATF_NUM]=coresspond_platf(platf,temp_p,len_p);
		data[i][YEAR_NUM]=strtod(temp_y,&temp);
		data[i][NA_NUM]=strtod(temp_na,&temp);
		data[i][EU_NUM]=strtod(temp_eu,&temp);
		if(strtod(temp_gbl,&temp)==0){	/* When encountered with not_availiable string,sets the value to -1 */
			data[i][GLOBAL_NUM]=-1.0;
		}
		else{				
			data[i][GLOBAL_NUM]=strtod(temp_gbl,&temp);
		}
		data[i][SCORE_NUM]=strtod(temp_s,&temp);
	}
} 

/* This function returns float value for word strings of genres. E.g-> simulation returns 0.0,shooter returns 1.0.  */
float coresspond_genre(char genres[][LEN_GENRE_PLAT],char *data_g,int g_len){
	int i;
	float rtrn;

	for(i=0;i<g_len;i++){
		if(strcmp(genres[i],data_g)==0){
			rtrn=i;
		}
	}
	return rtrn;
}
/* This function returns float value for word strings of platforms. E.g-> pc returns 0.0,ps returns 1.0.  */
float coresspond_platf(char platf[][LEN_GENRE_PLAT],char *data_f,int f_len){
	int i;
	float rtrn;

	for(i=0;i<f_len;i++){
		if(strcmp(platf[i],data_f)==0){
			rtrn=i;
		}
	}
	return rtrn;
}

/* This function prints menu and receives input from user.And returns that input. */
int user_input(){
	int inpt;
	printf("\n");
	printf("0: List of the Genres\n1: List of the Platforms\n");
	printf("2: List of the Games Through the Years\n");
	printf("3: All Informations of a Single Game\n");
	printf("4: Average of the User Scores\n");
	printf("5: Georographical Information of a Single Game\n");
	printf("6: Frequence of the Genres\n7: Frequence of the Platforms\n");
	printf("8: Exit\n");
	
	printf("Please select an operation: ");
	scanf("%d",&inpt);

	return inpt;
}

/* This function prints genres. g_len--> numbers of genres.(0.th part of menu)*/
void list_of_genres(char genres[][LEN_GENRE_PLAT],int g_len){
	int i;
	
	printf("\n\n");		/* printing new lines in order to avoid visual confliction. */
	for(i=0;i<g_len;i++){
		printf("%s\n",genres[i]);
	}
}

/* This function prints platforms. p_len--> numbers of platforms (1.st part of menu) */
void list_of_platf(char platf[][LEN_GENRE_PLAT],int p_len){
	int i;
	
	printf("\n\n");		/* printing new lines in order to avoid visual confliction. */
	for(i=0;i<p_len;i++){
		printf("%s\n",platf[i]);
	}
}

/* This function prints games according the year information which is received from user.(2.nd part of menu) */
void games_according_years(char names[][LEN_GAME_NAME],float data[][LEN_DATA]){

	int i;
	int inpt_year;	
	int choice;	/* variable for period choice */
	int check;
	
	do{
		printf("\nEnter a year:\n");
		scanf("%d",&inpt_year);
		
		printf("Until (0) or Since (1)  %d: ",inpt_year);
		scanf("%d",&choice);
	
		check=condition_for_years(data,inpt_year,choice); /* If the conditions not okay, checks is 0.If okay,checks is 1 and loop ends. */
		if(check==0){					  /* Error message. */
			printf("\nTRY AGAIN.\n");
		}
	}while(check!=1);
	
	printf("\n");
	for(i=0;i<MAX_ROW;i++){
		if(choice==0 && data[i][YEAR_NUM]<inpt_year){	/* When choice is 0(until),and if the year of game is smaller than typed year, print name of game. */ 
			printf("%s\n",names[i]);
		}
		if(choice==1 && data[i][YEAR_NUM]>inpt_year){	/* When choice is 1(since),and if the year of game is grater than typed year, print name of game.
																	(equality does not count) */ 
			printf("%s\n",names[i]);
		}
	}
}

/* This function checks for proper years and proper periods. */
int condition_for_years(float data[][LEN_DATA],int year, int chc){
	int rtrn=1;
		
	if(year<data[0][YEAR_NUM]) 			rtrn=0;		/* data[0][YEAR_NUM] is the year of the oldest game. */
	if(year==data[0][YEAR_NUM] && chc==0) 		rtrn=0;
	if(year>data[MAX_ROW-1][YEAR_NUM]) 		rtrn=0;		/* data[MAX_ROW-1][YEAR_NUM] is the year of the newest game. */
	if(year==data[MAX_ROW-1][YEAR_NUM] && chc==1)	rtrn=0; 
	if(chc!=0 && chc !=1)				rtrn=0;
	
	return rtrn;
}

/* This function determines the index of typed games.If the game not in list, returns -1.If in list,returns index of game. */
int check_typed_name(char names[][LEN_GAME_NAME],char inpt[]){
	int i;
	int rtrn=-1;
	for(i=MAX_ROW-1;i>=0;i--){		/* Some game names are some and i need to pick first one.For this reason,i start for loop from top(bottom of file). */
		if(strcmp(names[i],inpt)==0){
			rtrn=i;
		}
	
	}
	return rtrn;
}

/* This function prints informations about game. (3.rd part of menu) */
void game_informations(char names[][LEN_GAME_NAME],char genres[][LEN_GENRE_PLAT],char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA]){

	char inpt_name[LEN_GAME_NAME];	
	int check=0;
	int name_index;
	int genre_index;
	int platf_index;
	do{
		printf("\nPlease enter the name of the game:\n");
		scanf("%s",inpt_name);
		
		name_index=check_typed_name(names,inpt_name);	/* Here, finds typed game index. */
		if(name_index!=-1){
			
			genre_index=data[name_index][GENRE_NUM];
			platf_index=data[name_index][PLATF_NUM];
			
			printf("Name:	        %s\n",names[name_index]);
			printf("Genre:		%s\n",genres[genre_index]);
			printf("Platform:	%s\n",platf[platf_index]);
			printf("Year:		%.0f\n",data[name_index][YEAR_NUM]);
			printf("Sales In NA:	%f\n",data[name_index][NA_NUM]);
			printf("Sales In EU:	%f\n",data[name_index][EU_NUM]);
			
			if(data[name_index][GLOBAL_NUM]==-1.0){	/* If global sales equals -1.0 ,it means "Not avaliable." */
				printf("Total Sales:	Not available\n");
			}
			else{
				printf("Total Sales:	%f\n",data[name_index][GLOBAL_NUM]);
			}
			
			printf("User Score:	%f\n",data[name_index][SCORE_NUM]);
			
						
			check=1;	/* sets check variable to 1 in order to end the loop. */
		}
		else{	/* When typed game not in list. */
			printf("The game which typed,is not in the list.TRY AGAIN.\n");
		
		}
	}while(check!=1);
}

/* This function finds average score of all games and prints it.(4.th part of menu) */
void average_of_games(float data[][LEN_DATA]){
	float sum=0;
	int i;
	for(i=0;i<MAX_ROW;i++){
		sum=sum+data[i][SCORE_NUM];	
	}
	printf("\nAverage: %f\n",(sum/MAX_ROW));
}

/* This function finds out the typed game more popular in which region.(5.th part of menu) */
void popularity_of_games(char names[][LEN_GAME_NAME],float data[][LEN_DATA]){
	char inpt_name[LEN_GAME_NAME];
	int check=0;
	int name_index;
	
	do{
		printf("\nPlease enter the name of the game:\n");
		scanf("%s",inpt_name);
		
		name_index=check_typed_name(names,inpt_name);
		if(name_index==-1){	/* When typed game not in list. */
			printf("The game which typed,is not in the list.TRY AGAIN.\n");
		}
		if(name_index!=-1){
			if(data[name_index][NA_NUM]<data[name_index][EU_NUM]){
				printf("This game was more popular in Europe.\n");
			}
			else if(data[name_index][NA_NUM]>data[name_index][EU_NUM]){
				printf("This game was more popular in North America.\n");
			}
			else{	/* When popularity is same. */
				printf("This game has equal populartiy in Europe and NA.\n");
			}
						
			check=1;	/* sets check variable to 1 in order to end the loop. */
		}	
	}while(check!=1);
}

/* This function prints frequency of genres.(6.th part of menu) */
void frequency_of_genres(char genres[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_g){
	int i,j;
	int freq;
	
	printf("\n");
	for(i=0;i<len_g;i++){					/* This loop increments genres. E.g when i=0 it represents "simulation". */
		freq=0;						/* sets freq to 0,for each genre. */
		for(j=0;j<MAX_ROW;j++){				/* There loop increments rows(games).*/
			if(data[j][GENRE_NUM]==i){		/* If the genre num of game equals i, increment freq by one. */
				freq++;
			}
		}
		printf("%-15s  %4d\n",genres[i],freq);		/* Here, i used -15s and 4d in order to make a better output view. */
	}
}

/* This function prints frequency of platforms.Very similar to frequency_of_genres function.(7.th part of menu) */
void frequency_of_platforms(char platf[][LEN_GENRE_PLAT],float data[][LEN_DATA],int len_p){
	int i,j;
	int freq;
	
	printf("\n");
	for(i=0;i<len_p;i++){
		freq=0;						
		for(j=0;j<MAX_ROW;j++){
			if(data[j][PLATF_NUM]==i){		
				freq++;
			}
		}
		printf("%-15s  %4d\n",platf[i],freq);		/* Here, i used -15s and 4d in order to make a better output view. */
	}
}
