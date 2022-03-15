#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h> /* For toupper function */


#define ROW_SIZE 20
#define COLUMN_SIZE 20
#define WORDS_NUM 10
#define WORDS_SIZE 20
#define WORDS_MAX 100
#define DIRECTIONS_SIZE 8


void inital_puzzle_map(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE]);

void select_random_words(char words[][WORDS_SIZE]);
void word_number_selection(int numbers[]);
int check_wfile(int nums[],int can_num,int len);
void print_words_list(char words[][WORDS_SIZE]);
void print_puzzle(char puzzle[][COLUMN_SIZE]);

void fill_puzzle_random(char puzzle[][COLUMN_SIZE]);
char random_chars();
void fill_array_null(char puzzle[][COLUMN_SIZE]);
void fill_puzzle_words(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE]);

void row_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt);
void column_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt);
void diagonally_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt);
void rev_diagonally_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt);

int check_row_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type);
int check_column_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type);
int check_diagonally_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type);
int check_rev_diagonally_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type);

int game_on(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE]);
int user_input(char guess_word[WORDS_SIZE],int *r,int *c);
int check_word_on_map(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],char guess_word[WORDS_SIZE],int words_place[][WORDS_SIZE],int r,int c);

void upper_case_on_row(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_on_rev_row(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_on_column(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_on_rev_column(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_on_diagonally(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_on_diagonally_rev(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_on_rev_diagonally(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_on_rev_diagonally_rev(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len);
void upper_case_words(char words[][WORDS_SIZE],int word_num,int len);


int main(){

	char words[WORDS_NUM][WORDS_SIZE];
	char game_setup[ROW_SIZE][COLUMN_SIZE];
	int words_place[WORDS_NUM][WORDS_SIZE];
	
	srand(time(NULL));
	printf("\nWelcome to The Word Hunter Game\n");
	inital_puzzle_map(words,game_setup,words_place);
	
	if(game_on(words,game_setup,words_place)==0) printf("\nBye.See You Later...\n");
	else printf("\nCongratulations.You won!\n");

	return 0;
}


void inital_puzzle_map(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE]){

	fill_array_null(puzzle);
	select_random_words(words);
	fill_puzzle_words(words,puzzle,words_place);
	fill_puzzle_random(puzzle);
	print_words_list(words);
	print_puzzle(puzzle);

}

/* This function fills puzzle with null char.In order to,fill with random chars later. */
void fill_array_null(char puzzle[][COLUMN_SIZE]){

	int r,c;
	
	for(r=0;r<ROW_SIZE;r++){
		for(c=0;c<COLUMN_SIZE;c++){
			puzzle[r][c]='\0';
		}
	}
}

/* This fucntion selects random words (10 different words) from file and save them into array as a string. */
void select_random_words(char words[][WORDS_SIZE]){

	int row_num,i,count;
	int numbers[WORDS_NUM];
	char buffer[WORDS_SIZE];
	
	FILE *fptr;
	fptr=fopen("words.txt","r");
	
	word_number_selection(numbers);
	
	for(i=0;i<WORDS_NUM;i++){
		
		row_num=numbers[i];	
		count=0;	
		while(count!=(row_num-1)){
		
			fgets(buffer,WORDS_SIZE,fptr);
			count++;	
		}
		fgets(words[i],WORDS_SIZE,fptr);
		fseek(fptr,0L,SEEK_SET);
	}
	fclose(fptr);
}


/* This function selects random words locations (rows numbers) from file and save them into array. */
void word_number_selection(int numbers[]){

	int count=0;
	int num;
	
	num=((rand()%(WORDS_MAX))+1);
	numbers[count]=num;
	count++;
	
	while(count<WORDS_NUM){
		num=((rand()%(WORDS_MAX))+1);
		if(check_wfile(numbers,num,count)!=0){
			numbers[count]=num;
			count++;
		}	
	}
}


/* This function checks that the number(words row) is selected before or not.If selected returns 0,otherwise returns 1. */
int check_wfile(int nums[],int can_num,int len){

	int i;
	int rtrn=1;
	
	for(i=0;i<=len;i++){
		if(nums[i]==can_num){
			rtrn=0;
		}
	}	
	return (rtrn);
}

void print_words_list(char words[][WORDS_SIZE]){

	int i;
	printf("\nWords List:\n");
	for(i=0;i<WORDS_NUM;i++){
		printf("%s\n",words[i]);
	}
}

/* This function creates random letters(a to z and lower case). */
char random_chars(){
	char c;
	c=((rand()%(26))+'a');
	return(c);
}

/* Fills puzzle array(map) with random chars.If the place is null(not occupied before),fills with random chars. */
void fill_puzzle_random(char puzzle[][COLUMN_SIZE]){

	int r,c;
			
	for(r=0;r<ROW_SIZE;r++){
		for(c=0;c<COLUMN_SIZE;c++){
			if(puzzle[r][c]=='\0'){
				puzzle[r][c]=random_chars();
			}
		}
	}
}

/* This function writes words to puzzle map randomly. */
void fill_puzzle_words(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE]){

	int i,pref;
	int chck=0;

	for(i=0;i<WORDS_NUM;i++){
		/* There is a while loop.The reason that is avoid infinite loops.Each operation try its chace 3 times.
		   If operation fails 3 times, program selects another operation and does the same. */
		do{
		chck=0;		
		pref=((rand()%DIRECTIONS_SIZE)+1);
		if(pref==1) row_word(words,puzzle,words_place,i,0,&chck); 	
		if(pref==2) row_word(words,puzzle,words_place,i,1,&chck); 
		if(pref==3) column_word(words,puzzle,words_place,i,0,&chck);
		if(pref==4) column_word(words,puzzle,words_place,i,1,&chck);
		if(pref==5) diagonally_word(words,puzzle,words_place,i,0,&chck);
		if(pref==6) diagonally_word(words,puzzle,words_place,i,1,&chck);
		if(pref==7) rev_diagonally_word(words,puzzle,words_place,i,0,&chck);
		if(pref==8) rev_diagonally_word(words,puzzle,words_place,i,1,&chck);
		}while(chck==0);
	}
}

void print_puzzle(char puzzle[][COLUMN_SIZE]){

	int r,c;
	char letter='A';
	int i=0;

	printf("  %d",i);			/* Printing frames for better game experience. */
	for(i=1;i<COLUMN_SIZE;i++){
		printf("   %2d",i);
	}
	for(r=0;r<ROW_SIZE;r++){
		printf("\n%c-",letter+r);
		for(c=0;c<COLUMN_SIZE;c++){
			printf("%c    ",puzzle[r][c]);
		}
	}
	printf("\n");
}

/* This functions write one word to puzzle map(puzzle array) on row */
void row_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt){
	
	int r,c;
	int i;
	int len;
	int check;
	int cnt=0;
	
	len=(strlen(words[word_num])-2);
	/* Here,program checks the randomized row and column numbers is avaliable to use.If not ,change 3 times.If still not,end function */
	do{
		check=0;
		r=((rand()%ROW_SIZE)+0);
		c=((rand()%COLUMN_SIZE)+0);
		check=check_row_words(puzzle,r,c,len,type);
		cnt++;
	}while(check!=1 && cnt!=3);
	if(cnt<3){
		/* Saving locations of word to the array, in order to compare later. */
		words_place[word_num][0]=r;
		words_place[word_num][1]=c;
	
		if(type==0){					/* For left to right */
			for(i=0;i<len;i++){ 			/* printing the word to the map. */
	
				puzzle[r][c]=words[word_num][i];
				c++;	
			}
			words_place[word_num][2]=1;		/* Saving direction of the spelling the word to the array. */
		}
		if(type==1){				 	/* For right to left */
			for(i=0;i<len;i++){			/* printing the word to the map. */
	
				puzzle[r][c]=words[word_num][i];
				c--;	
			}
			words_place[word_num][2]=2;		/* Saving direction of the spelling the word to the array. */
		}
		*wd_cnt=*wd_cnt+1;
	}
}

/* Very similar to row_word function.Only difference is, this function writes words on columns. */
void column_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt){

	int r,c;
	int i;
	int len;
	int check;
	int cnt=0;

	len=(strlen(words[word_num])-2);

	do{
		check=0;
		r=((rand()%ROW_SIZE)+0);
		c=((rand()%COLUMN_SIZE)+0);
		check=check_column_words(puzzle,r,c,len,type);
		cnt++;
	}while(check!=1 && cnt!=3);
	if(cnt<3){
	
		words_place[word_num][0]=r;
		words_place[word_num][1]=c;
	
		if(type==0){	/* For top to down */
			for(i=0;i<len;i++){
		
				puzzle[r][c]=words[word_num][i];
				r++;	
			}
			words_place[word_num][2]=3;
		}
		if(type==1){	/* For down to top */
			for(i=0;i<len;i++){
	
				puzzle[r][c]=words[word_num][i];
				r--;	
			}
			words_place[word_num][2]=4;		
		}
		*wd_cnt=*wd_cnt+1;
	}
}

/* Very similar previous functions.Only difference is writes diagonally*/
void diagonally_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt){

	int r,c;
	int i;
	int len;
	int check;
	int cnt=0;

	len=(strlen(words[word_num])-2);

	do{
		check=0;
		r=((rand()%ROW_SIZE)+0);
		c=((rand()%COLUMN_SIZE)+0);
		check=check_diagonally_words(puzzle,r,c,len,type);
		cnt++;		
	}while(check!=1 && cnt!=3);
		if(cnt<3){
		
			/* Saving locations of word to the array, in order to compare later. */
			words_place[word_num][0]=r;
			words_place[word_num][1]=c;

			if(type==0){	/* For south-east side */
				for(i=0;i<len;i++){
	
					puzzle[r][c]=words[word_num][i];
					r++;
					c++;	
				}	
				words_place[word_num][2]=5;
			}
			if(type==1){	/* For north-west side */
				for(i=0;i<len;i++){
	
					puzzle[r][c]=words[word_num][i];
					r--;
					c--;	
				}	
				words_place[word_num][2]=6;
			}
			*wd_cnt=*wd_cnt+1;
	}
}

/* Very similar previous functions.Only difference is writes reverse diagonally */
void rev_diagonally_word(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int type,int *wd_cnt){

	int r,c;
	int i;
	int len;
	int check;
	int cnt=0;

	len=(strlen(words[word_num])-2);

	do{
		check=0;
		r=((rand()%ROW_SIZE)+0);
		c=((rand()%COLUMN_SIZE)+0);
		check=check_rev_diagonally_words(puzzle,r,c,len,type);
		cnt++;
	}while(check!=1 && cnt!=3);

	if(cnt<3){
	
		/* Saving locations of word to the array, in order to compare later. */
		words_place[word_num][0]=r;
		words_place[word_num][1]=c;
		
		if(type==0){	/* For north-east side */
			for(i=0;i<len;i++){
	
				puzzle[r][c]=words[word_num][i];
				r--;
				c++;	
			}
			words_place[word_num][2]=7;
		}
		if(type==1){	/* For south-west side */
				for(i=0;i<len;i++){
		
				puzzle[r][c]=words[word_num][i];
				r++;
				c--;	
			}
			words_place[word_num][2]=8;
		}
		*wd_cnt=*wd_cnt+1;
	}
}

/*	This function checks the randomized row and columns is avaliable(not occupied from another word) and checks whether given word will fit that row.
	If everything okay returns 1,otherwise returns 0. */
int check_row_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type){

	int rtrn=1;
	int i;
	
	/* checks that will word fits the row or not */
	if(type==0){	/* For right to left */
		if(col>(COLUMN_SIZE-len)){
			rtrn=0;
		}	
		for(i=0;i<len;i++){	/* checks specific place is avaliable */
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			col++;
		}		
	}
	if(type==1){	/* For left to right */
		if(col>(COLUMN_SIZE-len) || col<len){
			rtrn=0;
		}
		for(i=0;i<len;i++){	/* checks specific place is avaliable */
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			col--;
		}
	}
	return (rtrn);
}

/* Similar to check_row_words function.Only difference is,checks columns. */
int check_column_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type){

	int rtrn=1;
	int i;

	if(type==0){	/* For top to down */
		if(row>(ROW_SIZE-len)){
			rtrn=0;
		}
		for(i=0;i<len;i++){
	
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			row++;
		}
	}
	if(type==1){	/* For down to top */
		if(row>(ROW_SIZE-len) || row<len){
			rtrn=0;
		}
		for(i=0;i<len;i++){
	
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			row--;
		}
	}
	return (rtrn);
}

/* Very similar to previous functions.Only difference is, checks diagonally */
int check_diagonally_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type){

	int rtrn=1;
	int i;
	
	if(col>(COLUMN_SIZE-len) || row>(ROW_SIZE-len)){
		rtrn=0;
	}
	if(row<len || col<len){
		rtrn=0;
	}
	if(type==0){	/* For south-east side */
		for(i=0;i<len;i++){
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			row++;
			col++;
		}
	}
	if(type==1){	/* For north-west side */
		for(i=0;i<len;i++){
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			row--;
			col--;
		}
	}
	return (rtrn);
}

/* Very similar to previous functions.Only difference is, checks reverse diagonally */
int check_rev_diagonally_words(char puzzle[][COLUMN_SIZE],int row,int col,int len,int type){

	int rtrn=1;
	int i;
	
	if(col>(COLUMN_SIZE-len) || row>(ROW_SIZE-len)){
		rtrn=0;
	}
	if(row<len || col<len){
		rtrn=0;
	}
	
	if(type==0){	/* For north-east side */
		for(i=0;i<len;i++){	
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			row--;
			col++;
		}
	}
	if(type==1){	/* For south-west side */
		for(i=0;i<len;i++){	
			if(puzzle[row][col]!='\0'){
				rtrn=0;
			}
			row++;
			col--;
		}
	}
	return (rtrn);
}

/* This is a game function. */
int game_on(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE]){

	char guess_word[WORDS_SIZE];
	int count=0; /* variable for word counter  */
	int r,c;
	int rtrn=1;

	do{
		if(user_input(guess_word,&r,&c)!=0){	/* There is a condition for when user not types "Exit". */
		
			count+=check_word_on_map(words,puzzle,guess_word,words_place,r,c); /* This is a word counter.When user finds words,counter increase by one. */
			print_words_list(words);
			print_puzzle(puzzle);
		}
		else{	/* There is a condition for when user  types "Exit". */
			rtrn=0;
		}
	}while(count!=WORDS_NUM && rtrn!=0); /* When the counter equals word number(which means user found every word) or user types "Exit", loop ends. */
	return rtrn;
}

int user_input(char guess_word[WORDS_SIZE],int *r,int *c){
	
	char guess_loc[WORDS_SIZE];
	int rtrn=1;
	
	printf("Please enter the coordinate and the word:\n");
	scanf("%s",guess_loc);
	
	if(strcmp(guess_loc,"Exit")==0){	/* If user types "Exit", function ends. */
		rtrn=0;	
	}
	else{					/* If user not types "Exit", program take another input. */
		scanf("%s",guess_word);		
		*r=guess_loc[0]-'A';		/* For row */
		if(strlen(guess_loc)>2){	/* For two digits column number */
			*c=(guess_loc[1]-'0')*10;
			*c+=(guess_loc[2]-'0');
		}
		else{				/* For one digit column number */
			*c=(guess_loc[1]-'0');	
		}
	}	
	return (rtrn);
}

/* This function checks that given location and word is correct or not.If coorects return 1, otherwise 0. */
int check_word_on_map(char words[][WORDS_SIZE],char puzzle[][COLUMN_SIZE],char guess_word[WORDS_SIZE],int words_place[][WORDS_SIZE],int r,int c){

	int i;
	int rtrn=0;
	int temp=-1;
	int direction;
	
	for(i=0;i<WORDS_NUM;i++){	/* There is a loop for finding which word user typed. */
		if(strncmp(guess_word,words[i],(strlen(words[i])-2))==0){
			 temp=i;
		}
	}
	if(temp!=-1){
		direction=words_place[temp][2];
		if(words_place[temp][0]==r && words_place[temp][1]==c){ /* If the locations (r and c) are true, program makes upper case word on list and map. */
			switch(direction){	/* There is a switch statement for each direction. */
				case 1:		upper_case_on_row(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
				case 2:		upper_case_on_rev_row(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
				case 3:		upper_case_on_column(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
				case 4:		upper_case_on_rev_column(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
				case 5:		upper_case_on_diagonally(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
				case 6:		upper_case_on_diagonally_rev(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
				case 7:		upper_case_on_rev_diagonally(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
				case 8:		upper_case_on_rev_diagonally_rev(puzzle,words_place,temp,strlen(guess_word));
						upper_case_words(words,temp,strlen(guess_word));
					break;
			}
		rtrn=1;
		}
	}
	return rtrn;
}

/* This function makes upper case word on row(left to right). */
void upper_case_on_row(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		c++;
	}
}
/* This function makes upper case word on row(right to left). */
void upper_case_on_rev_row(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		c--;
	}
}
/* This function makes upper case word on column(top to down). */
void upper_case_on_column(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		r++;
	}
}
/* This function makes upper case word on column(down to top). */
void upper_case_on_rev_column(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		r--;
	}
}
/* This function makes upper case word on digonally (south-east side). */
void upper_case_on_diagonally(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		r++;
		c++;
	}
}
/* This function makes upper case word on digonally (north-west side). */
void upper_case_on_diagonally_rev(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		r--;
		c--;
	}
}
/* This function makes upper case word on reverse digonally (north-east side). */
void upper_case_on_rev_diagonally(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		r--;
		c++;
	}
}
/* This function makes upper case word on reverse digonally (south-west side). */
void upper_case_on_rev_diagonally_rev(char puzzle[][COLUMN_SIZE],int words_place[][WORDS_SIZE],int word_num,int len){
	int i,r,c;
	r=words_place[word_num][0];
	c=words_place[word_num][1];
	for(i=0;i<len;i++){
		puzzle[r][c]=toupper(puzzle[r][c]);
		r++;
		c--;
	}
}

/* This function makes upper case given word on list. */
void upper_case_words(char words[][WORDS_SIZE],int word_num,int len){
	int i;
	for(i=0;i<len;i++){
		words[word_num][i]=toupper(words[word_num][i]);
	
	}
}
