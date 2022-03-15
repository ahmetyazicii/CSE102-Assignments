#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX_LINE_LEN     70
#define MAX_NUM_OBJECT  100
#define LEN_NAME_OBJECT   4
#define MAX_POLYGON	 20
#define POINT_TYPE	  1
#define LINE_TYPE         2
#define POLYGON_TYPE      3


typedef struct point_2d{
	
	double xpoint;
	double ypoint;
	char name[LEN_NAME_OBJECT];

}p_2d;

typedef struct line_2d{
	
	p_2d start;
	p_2d end;
	char name[LEN_NAME_OBJECT];

}l_2d;

typedef struct polygons_2d{

	p_2d 	 corner[MAX_POLYGON];
	l_2d	 edge  [MAX_POLYGON];
	char name[LEN_NAME_OBJECT];

}pg_2d;


void read_data_from_file(p_2d points_arr[], l_2d lines_arr[], pg_2d polygons_arr[]);

void get_newline_file(FILE *stream);
void find_specific_name(FILE *fptr,char *name);

void save_points_to_Struct(char *data, p_2d *p2d);
void save_lines_to_Struct(char *data, p_2d points_arr[], l_2d *l2d);
int find_point_array(p_2d points_arr[], char *t_name);
void save_polyg_to_Struct(char *data, p_2d points_arr[], l_2d lines_arr[], pg_2d *pg2d);
int find_line_array(l_2d lines_arr[], char *t_name);

int determine_type_of_data(char *data);


int main(){

	p_2d 		points_arr[MAX_NUM_OBJECT];
	l_2d  		lines_arr[MAX_NUM_OBJECT];
	pg_2d 		polygons_arr[MAX_NUM_OBJECT];

	read_data_from_file(points_arr,lines_arr,polygons_arr);
	
	printf("%s %s %s %s %s\n",polygons_arr[1].edge[0].name,
				  polygons_arr[1].edge[1].name,
				  polygons_arr[1].edge[2].name,
				  polygons_arr[1].corner[0].name,
				  polygons_arr[1].name);
	
	
	return 0;
}


void read_data_from_file(p_2d points_arr[], l_2d lines_arr[], pg_2d polygons_arr[]){

	int i;		/* variable for loops */
	int num_2d;	/* variable for number of 2D objects */
	int type;
	int l_p  = 0,	/* variable for points array. */
	    l_l  = 0,	/* variable for lines array. */
	    l_pg = 0;	/* variable for polygons array. */
	char _line[MAX_LINE_LEN];
	
	FILE *fptr;
	fptr=fopen("commands.txt","r");
	
	if(fptr==NULL){
		printf("\n!ERROR!--Failed to open file--\n");
		return;
	}	

	find_specific_name(fptr,"data"); 	/* Here, sets location of file indicator to after given word. */
			
	fscanf(fptr,"%d",&num_2d);
	
	get_newline_file(fptr);
	
	
	for(i=0;i<10;i++){
		
		fgets(_line,MAX_LINE_LEN,fptr);
		type=determine_type_of_data(_line);
		
		
		switch(type){
		
			case POINT_TYPE:
					save_points_to_Struct(_line,&points_arr[l_p]);
					printf("x:%lf y:%lf %s\n",points_arr[l_p].xpoint,points_arr[l_p].ypoint,points_arr[l_p].name);
					l_p++;
				break;
			
			case LINE_TYPE:
					save_lines_to_Struct(_line,points_arr,&lines_arr[l_l]);
					printf("x:%s y:%s %s\n",lines_arr[l_l].start.name,lines_arr[l_l].end.name,lines_arr[l_l].name); 
					l_l++;	
				break;
			
			case POLYGON_TYPE:
					save_polyg_to_Struct(_line,points_arr,lines_arr,&polygons_arr[l_pg]);
					l_pg++;	
				break;
		}	
	
	}
	fclose(fptr);
}

void get_newline_file(FILE *stream){
	char c;
	
	do{	
		fscanf(stream,"%c",&c);		
	}while(c!='\n');
}

void find_specific_name(FILE *fptr,char *name){

	char temp_l[MAX_LINE_LEN];

	fseek(fptr,0L,SEEK_SET);
	
	do{
		fgets(temp_l,strlen(name)+1,fptr);
		temp_l[strlen(temp_l)] = '\0';

	}while( strcmp(temp_l,name) != 0);
	
}

int determine_type_of_data(char *data){

	int type;

	if( strstr(data,"PG") != NULL ){
		type = POLYGON_TYPE;
	}
	else if( strstr(data,"L")  != NULL ){
		type = LINE_TYPE;
	}
	else{
		type = POINT_TYPE;
	}
	return type;
}

void save_points_to_Struct(char *data, p_2d *p2d){

	
	char *temp_x;
	char *temp_y;
	char *temp_name;

	
   
	temp_x      = strtok(data," \t\r\n");
	temp_y	    = strtok(NULL," \t\r\n");
	temp_name   = strtok(NULL," \t\r\n");



	p2d->xpoint = strtod(temp_x,&temp_x);
	p2d->ypoint = strtod(temp_y,&temp_y);
	

	strcpy(p2d->name,temp_name);
	
}

void save_lines_to_Struct(char *data, p_2d points_arr[], l_2d *l2d){

	int l_start;
	int l_end;
	
	char *temp_end;
	char *temp_start;
	char *temp_name;

	
	
	temp_start  = strtok(data," \t");
	temp_end    = strtok(NULL," \t");
	temp_name   = strtok(NULL," \t");
	
	l_start     = find_point_array(points_arr,temp_start);
	l_end       = find_point_array(points_arr,temp_end);
	
	l2d->start  = points_arr[l_start];
	l2d->end    = points_arr[l_end];
	
	strncpy(l2d->name,temp_name,3);
	l2d->name[3]='\0';

}

void save_polyg_to_Struct(char *data, p_2d points_arr[], l_2d lines_arr[], pg_2d *pg2d){

	char *temp_obj;
	int type;
	int check=0;
	int i=0;
	int j=0;
	
	temp_obj = strtok(data," \t");
	do{	
		type     = determine_type_of_data(temp_obj);
		
		switch(type){
			case POINT_TYPE:
					pg2d->corner[i] = points_arr[find_point_array(points_arr,temp_obj)];
					i++;		
				break;
				
			case LINE_TYPE:
					pg2d->edge[j]   = lines_arr[find_line_array(lines_arr,temp_obj)];
					j++;
				break;
			case POLYGON_TYPE:
					strncpy(pg2d->name,temp_obj,3);
					pg2d->name[3]='\0';
					check = 1;
				break;
	
		}
		temp_obj = strtok(NULL," \t");
	}while(check != 1);
}

int find_point_array(p_2d points_arr[], char *t_name){
	
	int i=0;
	
	while(strcmp(points_arr[i].name,t_name) != 0){
		i++;
	}
	return i;
}

int find_line_array(l_2d lines_arr[], char *t_name){
	
	int i=0;
	
	while(strcmp(lines_arr[i].name,t_name) != 0){
		i++;
	}
	return i;
}






















