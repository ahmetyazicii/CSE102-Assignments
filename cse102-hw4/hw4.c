#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define MAX_TRACK_MAP 11
#define MIN_TRACK_MAP 1
#define BASE_TRACK_MAP 6


void menu();
int char_to_int(char value); /* This is a additional function.This function converts character number to integer number */
void decrypt_and_print(char* file_path);
char decrypt_numbers(int number);
void deep_decrypt_and_print(char* file_path);
void track_machine();
void refresh_position(int *X,int *Y, double *D,double *R);
void encrypt_messages(char* file_path); 
int encrypt_characters(char chrcter);	/* This is a additional function.This function converts decrypted characters to proper numbers(for part4)
						(inverse of decrypt_numbers function) */



int main(){

	srand(time(NULL)); /* i use time function becase of creating random numbers every time */
	
	menu();
	
	return 0;
	
}



void menu(){
	
	int choice;

	do{
		printf("1-) Decrypt and print encrypted_p1.img\n");
		printf("2-) Decrypt and print encrypted_p2.img\n");
		printf("3-) Switch on the tracking machine\n");
		printf("4-) Encrypt the message\n");
		printf("5-) Switch off\n");
		printf("Please make your choice:\n");
		scanf("%d",&choice);
	
		switch(choice){
	
			case 1:	decrypt_and_print("encrypted_p1.img");
				break;
		
			case 2: deep_decrypt_and_print("encrypted_p2.img");
				break;
		
			case 3: track_machine();
				break;
			
			case 4: encrypt_messages("decrypted_p4.img");
				break; 
		}	
	
		printf("\n");
	
	} while(choice!=5);

}


/*This function convertes characters numbers to integer numbers by substracting  character of 0 */
int char_to_int(char value){	

	int num;
	
	num=value-'0';
	return num;
}


void decrypt_and_print(char* file_path){

	int number;
	char inp,outp;
	
	FILE *fptr;
	fptr=fopen(file_path,"r");	
	
	/* There is a loop that read all the file till the reach the end of the file */
	do{		
		
	
		fscanf(fptr,"%c",&inp);
		number=char_to_int(inp);	
	
		outp=decrypt_numbers(number);	/* sending number to function and receiving the corresponding character */
		printf("%c",outp);		
	
	} while(!feof(fptr));	
	
	fclose(fptr);		
}


char decrypt_numbers(int number){

	char rtrn;
	
	switch(number){		
	
		case 0: rtrn=' '; 
			break;
		
		case 1: rtrn='-';
			break;
		
		case 2: rtrn='_';
			break;
		
		case 3: rtrn='|';
			break;
		
		case 4: rtrn='/';
			break;
		
		case 5: rtrn='\\';
			break;
		
		case 6: rtrn='O';
			break; 
		
		default: rtrn='\n';	
	}
	return rtrn;
}


void deep_decrypt_and_print(char* file_path){


	int num;	
	int check=0;	/* variable for checking the end of the line */
	int sum=0;	
	int i;		
	
	char rec;	/* variable for reading from file */
	char out;	/* variable for printing character */
	
	FILE *fptr;	
	fptr=fopen(file_path,"r");	
	
	while(!feof(fptr)){					
		
		if(check==0){				/* There is a condition for normal cases */
			fseek(fptr,-2L,SEEK_CUR);	/* There is a fseek function for going back and forth in file-in this case going back 2bytes from current position */
		}
		if(check!=0){				/* There is a condition when the file indicator reaches the end of the line */
			fseek(fptr,0L,SEEK_CUR);	/* There is a fseek function for going back and forth in file-in this case going forth as usual   */
			check=0; 					
		}				
		
		for(i=0;i<3;i++){			/* There is a loop that reads 3 characters from file */
		
			fscanf(fptr,"%c",&rec);		
			
			if(rec=='\n'){			/* If the file indicator reachs end of line the value sets 0 and check variable be true(1) */
				rec='0';
				check=1;
			}	
			num=char_to_int(rec);			
			sum=sum+num;				
		}
		sum=sum%7;				/* some operations according the formula */		
		out=decrypt_numbers(sum);			
		printf("%c",out);		
		sum=0;					/* resetting sum variable */		
		
		if(check==1){				/* printing new line the output when the file indicator reaches the end of line */	
			printf("\n");		
		}	
	}		
	fclose(fptr); 	
}


void track_machine(){

	int x,y; 			/* variables for printing map */
	int enemx=0,enemy=0;		
	int check=0;			/* variable for control some cases(initial case,when enemy found base) */
	char cmmnd=0;			/* variable for input command */
	double dist=0,distcamp=0;	
	
	do{	
		/* There is a loop for printing map */				
		for(x=MIN_TRACK_MAP;x<=MAX_TRACK_MAP;x++){				/* loop for x coordination(new lines) */
		
			for(y=MIN_TRACK_MAP;y<=MAX_TRACK_MAP;y++){			/* loop for y coordination(priting dots and locations */
			
				
				if(x==enemx && y==enemy){				/* printing enemy */
					printf("E\t");
				}
				else if(x==BASE_TRACK_MAP && y==BASE_TRACK_MAP){ 	/* priting base */
					printf("O\t");
				}
				else{ /*printing dots */
					printf(".\t");
				}			
			}
			printf("\n");
		}
		
		/* This condition for inital map.In initial map enemies position is (0,0),enemy does not seen in map. */
		if(enemx==0 && enemy==0){		
			printf("The enemy not in range.We are safe in a while...");		
		}	
		
		/* This condition for when enemy and base coordinations are same.Here,printing message and set control variable to 1(in order to exit map) */ 
		else if(enemx==BASE_TRACK_MAP && enemy==BASE_TRACK_MAP){		
			printf("The enemy found us.Mission failed...\n");
			check=1;
		}
		
		/* This condition for when everything is ok */
		else if(check==0){
			printf("Enemies X position: %d, Y position: %d, Displacement: %.2f, Distance to our camp: %.2f",enemx,enemy,dist,distcamp);
		}
		
		/* This condition for receiving command from user */
		if(check==0){
			printf("\nCommand waiting...: ");
		
			do{	/* There is a loop in order to receive valid input ('R' or 'E') from user */
				scanf(" %c",&cmmnd);
				if(cmmnd!='R' && cmmnd !='E'){
					printf("\nInvalid input.Please press R to refresh map and E to stop.Command waiting...: ");
				}
			} while(cmmnd!='R' && cmmnd!='E');
		}
		
		
		refresh_position(&enemx,&enemy,&distcamp,&dist);	
		
	
	} while(check==0 && cmmnd=='R');	 /* This loop will countine as long as control variable is 0 and user input is 'R' */
}


void refresh_position(int *X,int *Y, double *D,double *R){

	int enem_old_x,enem_old_y;
	
	enem_old_x=*X;
	enem_old_y=*Y;
		
	/* changing values of X and Y with rand function. There are some calculations in order to change the value by range(from 1 to 11)*/
	*X=((rand()%(MAX_TRACK_MAP+1-MIN_TRACK_MAP))+MIN_TRACK_MAP);	
	*Y=((rand()%(MAX_TRACK_MAP+1-MIN_TRACK_MAP))+MIN_TRACK_MAP);
	
	/* There is a calculations in order to find distance between old and new position of x and y(enemies coordiantions) */
	*R=sqrt( ( (enem_old_x-*X) * (enem_old_x-*X) ) + ( (enem_old_y-*Y) * (enem_old_y-*Y) ) );
	
	/*There is a calculations in order to find distance between base and enemy location */
	*D=sqrt( ( (BASE_TRACK_MAP-*X) * (BASE_TRACK_MAP-*X) ) + ( (BASE_TRACK_MAP-*Y) * (BASE_TRACK_MAP-*Y) ) );

}


void encrypt_messages(char* file_path){
	
	
	int check=0;
	int number;    		/* variable for printing to the file */
	int i,sum=0,temp;
	char inp;		/* variable for reading from decrypted file */
	char cntrl_inp;		/* variable for reaading from encrypted file */
	
	
	FILE *fptr_read;
	FILE *fptr_save;
	
	
	fptr_read=fopen(file_path,"r");
	fptr_save=fopen("encrypted_p4.img","w+");
	
	fscanf(fptr_read,"%c",&inp);						
	number=	encrypt_characters(inp);
	
	
	
	/* printing first number */
	for(i=0;i<3;i++){
		fprintf(fptr_save,"%d",number);		
	}	
	
	while(!feof(fptr_read)){					
		
		if(check==1){
		
			fscanf(fptr_read,"%c",&inp);						
			number=	encrypt_characters(inp);
	
			for(i=0;i<3;i++){
				fprintf(fptr_save,"%d",number);		
			}	
			check=0;
		}
		
		
		fseek(fptr_save,-2L,SEEK_END);
		
		/* reading 2 number from save file in order to write next proper value by formula  */
		for(i=0;i<2;i++){
			fscanf(fptr_save,"%c",&cntrl_inp);
			temp=char_to_int(cntrl_inp);
			sum=sum+temp;
			
		}	
		
		fscanf(fptr_read,"%c",&inp);
		
		
		/* checking new line */
		if(inp=='\n'){
			check=1;
		
		}
		number=	encrypt_characters(inp);
		
		/* There is a some mathematical calulations to find proper next number by formula. */
		if(sum<=7){
		
			number+=7;
			number=number-sum;
			number=abs(number);
			number%=7;
		}
		else if(sum<=14){
		
			number+=14;
			number=number-sum;
			number=abs(number);
			number%=7;
		}
		else{
		
			number+=21;
			number=number-sum;
			number=abs(number);
			number%=7;
		}
		
		/* printing number to the file */	
		fseek(fptr_save,0L,SEEK_END);
		fprintf(fptr_save,"%d",number);
		
		if(check==1){
			fprintf(fptr_save,"\n");
		
		}		
		sum=0;
	}
		
	printf("The selected operation have successfully done.\n");
	fclose(fptr_read);
	fclose(fptr_save);
}

int encrypt_characters(char chrcter){

	int rtrn;
	
	switch(chrcter){
		
		case ' ': rtrn=0; 
			  break;
		
		case '-': rtrn=1;
			  break;
		
		case '_': rtrn=2;
			  break;
		
		case '|': rtrn=3;
			  break;
		
		case '/': rtrn=4;
			  break;
		
		case '\\':rtrn=5;
			  break;
		
		case 'O': rtrn=6;
			  break;
		
		default: rtrn=0;	
	
	}

	return rtrn;
}

