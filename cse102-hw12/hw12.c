#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define LINE_SIZE 720
#define UNIQ_CHAR_NUM 256
#define MAX_BINARY_CODE 100


typedef struct tree_s{

    	char data;
    	int freq;
    	struct tree_s *left;
    	struct tree_s *right;
    	struct tree_s *next;

}tree_t;


tree_t *encrypt_file_create_huffman();
void encrypt_message_save_file(tree_t *root);
void read_binary_save_txt(tree_t *root);
char *read_file(char *filename,char *str);
int freq_of_char(const char *s,char c);
void make_unique(const char *s,char *ct);
tree_t *create_initial_mheap(const char *str,const char *uniq_str);
tree_t *add_min_heap(tree_t *root,char data,int freq);
tree_t *create_huffmant(tree_t *root);
tree_t *min_freq_mheap(tree_t *root);
tree_t *add_node_to_mheap(tree_t *root,tree_t *node);
tree_t *delete_from_mheap(tree_t *root,tree_t *node);
void write_code_file(FILE *stream,tree_t *root,char *code,int counter,char letter);
void print_message_to_file(FILE *stream,tree_t *root,char *arr,int *counter);
void byte_compare(char *file_name_dat, char *file_name_txt);


int main(){

    	tree_t *root;

    	root = encrypt_file_create_huffman();
    	printf("Huffman Tree is successfully created.. \n");
    	encrypt_message_save_file(root);
    	printf("The message successfully received and saved the binary file.\n");
	read_binary_save_txt(root);
	printf("The message successfully printed txt file..\n");
	byte_compare("encoded.dat","decoded.txt");
	
    	return 0;
}

/* This reads entire file and creates huffman tree. */
tree_t *encrypt_file_create_huffman(){

	tree_t *root = NULL;
	char *file_str = NULL;
	char uniq_str[UNIQ_CHAR_NUM];
	
	file_str = read_file("reference.txt",file_str);
	make_unique(file_str,uniq_str);
	root = create_initial_mheap(file_str,uniq_str);
	root = create_huffmant(root);

	return root;
}

/* This function reads message file then encrypt it. Then saves it to the .dat file. */
void encrypt_message_save_file(tree_t *root){

	int i = 0;
	char *message = NULL;
	char code[MAX_BINARY_CODE];
	
	FILE *write_binary;
	write_binary = fopen("encoded.dat","wb");

	message = read_file("message.txt",message); 
	
	while(message[i] != '\0'){
		write_code_file(write_binary,root,code,0,message[i]);
    		i++;
	}
	
	fclose(write_binary);
}

/* This function reads encrypted file and decrypt it. Then saves it to the output .txt file. */
void read_binary_save_txt(tree_t *root){

	int inn_counter = 0;	/* counter for keep track of tree */
	int out_counter = 0;	/* counter for keep track of coded_message array */
	char *coded_message;
	int file_len;
	FILE *write_txt;
	FILE *read_binary;
	
	write_txt = fopen("decoded.txt","w+");
	read_binary = fopen("encoded.dat","rb");
	
	if(read_binary == NULL){
		printf("!ERROR!----Binary file(encoded.dat) could not open.----\n");
	}
	
	else{
		/*finding lenght of file. */
		fseek(read_binary,0L,SEEK_END);
		file_len = ftell(read_binary);
		fseek(read_binary,0L,SEEK_SET);
		
		coded_message = (char *) calloc(file_len+1,sizeof(char));
		fread(coded_message,sizeof(char),file_len,read_binary);
		coded_message[file_len] = '\0';
		
		while(coded_message[out_counter] != '\0'){
			inn_counter = 0;
			print_message_to_file(write_txt,root,(coded_message+out_counter),&inn_counter);
			out_counter+=inn_counter;
		}	
	}
	fclose(write_txt);
	fclose(read_binary);
}

/* This function reads files and saves it to str array. */
char *read_file(char *filename,char *str){

	FILE *fptr;
	char *temp;
	int file_len;
	
	fptr = fopen(filename,"r");
	/* finding length of the file */
	fseek(fptr,0L,SEEK_END);
	file_len = ftell(fptr);
	fseek(fptr,0L,SEEK_SET);

	while(!feof(fptr)){
		
		temp = (char *) calloc(LINE_SIZE,sizeof(char));
		
		fgets(temp,LINE_SIZE,fptr);
		
		if(str == NULL){	/* when str is empty, it created and copied temp to str */
			str = (char *) calloc(file_len,sizeof(char));
			strcpy(str,temp);
		}
		else{			/* when str is not empty, copied temp to end of str. */
			strcat(str,temp);
		}
	
		free(temp);
	}	
	fclose(fptr);
	return str;
}

/* This function finds the frequency of char c in string s. */
int freq_of_char(const char *s,char c){

    	if(s[0] == '\0'){
        	return 0;
    	}
    	else{
        	if(s[0] == c){
            		return 1 + freq_of_char(s+1,c);
        	}
        	else{
             		return freq_of_char(&s[1],c);
        	}
    	}
}

/* This function finds unique words in string c and save them to ct string. Ex:  "aaaabc" --> "abc" . */
void make_unique(const char *s,char *ct){

    	int i=0;
    	int j=0;
    	ct[j++] = s[i++];

    	while(s[i] != '\0'){

        	if(strchr(ct,s[i]) == NULL){
            	ct[j++] = s[i];
        	}
        	i++;
    	}
    	ct[j] = '\0';
}

/* This function creates sorted initial min heap. */
tree_t *create_initial_mheap(const char *str,const char *uniq_str){

    	tree_t *root = NULL;
    	int i=0;
   
    	while(uniq_str[i] != '\0'){
   
        	root = add_min_heap(root,uniq_str[i],freq_of_char(str,uniq_str[i]));
        	i++;
   	}
    	return root;
}

/* This function adds elements to the linkedlist. */
tree_t *add_min_heap(tree_t *root,char data,int freq){

    	tree_t *temp;
    	tree_t *iter = root;

    	if(root == NULL){   		/* when min heap is empty */

        	root = (tree_t *) malloc(sizeof(tree_t));
        	root->left = root->right = root->next = NULL;
        	root->data = data;
        	root->freq = freq;
       	return root;

    	}
    	else if(root->freq < freq){	/* when node's freq is bigger than root's freq */
        
        	temp = (tree_t *) malloc(sizeof(tree_t));
        	temp->left = temp->right = NULL;
        	temp->data = data;
        	temp->freq = freq;
        	temp->next = root;
        	return temp;

    	}			
    	while(iter->next != NULL && iter->next->freq > freq){
        	iter = iter->next;
    	}
  
    	temp = (tree_t *) malloc(sizeof(tree_t));
    	temp->next = iter->next ;
    	iter->next = temp;
    	temp->left = temp->right = NULL;
    	temp->data = data;
    	temp->freq = freq;

    	return root;

}

/* This function creates huffman tree recursively. */
tree_t *create_huffmant(tree_t *root){

    	tree_t *z;	
    	
    	if(root->next != NULL){
        
            	z = (tree_t *) malloc(sizeof(tree_t));
            	z->left  = min_freq_mheap(root);
           	z->right = min_freq_mheap(root);
            	z->freq = z->left->freq + z->right->freq ;            	        
          	z->data = '*';		
            	
            	root = add_node_to_mheap(root,z);           	
            	root = delete_from_mheap(root,z->right);

            	return create_huffmant(root);
	}
        else{
    		return root;
    	}

}

/* This function finds nodes with min frequencies. */
tree_t *min_freq_mheap(tree_t *root){

    	tree_t *temp;
   	
   	if(root->next == NULL){

    		return root;
   	}
 	while(root->next->next != NULL){
		root = root->next;
    	}

    	temp = root->next;
    	root->next = NULL;
    	return temp;   	  
}

/* This function adds the new internal nodes to the min heap. */
tree_t *add_node_to_mheap(tree_t *root,tree_t *node){

   	tree_t *iter = root;
   	
    	if(root->freq < node->freq){
      	 	node->next = root;
       	return node;

   	}
   	else{
   		while(iter->next != NULL && iter->next->freq > node->freq){
      			iter = iter->next;
   		}
		node->next = iter->next;
		iter->next = node;
   		return root;
	}
}

/* This function deletes nodes from min heap. (not freeing them just make them not reachable from min heap) . */
tree_t *delete_from_mheap(tree_t *root,tree_t *node){

	tree_t *iter = root;
	
	if(root == node){
		return root;
	}
	while(iter->next != NULL && iter->next != node){
		iter = iter->next;
	}
	if(iter->next == NULL){
		return root;
	}
	iter->next = iter->next->next;
	return root;
}

/* This funciton recursivly travels from root to leafs. If the leaf contains wanted letter, saves the travel path to the file. */
void write_code_file(FILE *stream,tree_t *root,char *code,int counter,char letter){

	if(root->left){
		code[counter] = '0';
		write_code_file(stream,root->left,code,counter+1,letter);
	}
	if(root->right){
		code[counter] = '1';
		write_code_file(stream,root->right,code,counter+1,letter);
	}
	if(root->right == NULL && root->left == NULL){
		if(root->data == letter){
			fwrite(code,sizeof(char),counter,stream);	
			return;
		}		
	}
}

/* This function decodes the codes the finds the letter in huffman tree. Then prints the letter to the file. */
void print_message_to_file(FILE *stream,tree_t *root,char *arr,int *counter){

	if(root->right == NULL && root->left == NULL){
		fprintf(stream,"%c",root->data);
		return;			
	}
	else if(arr[*counter] == '0'){
		*counter = *counter + 1;
		print_message_to_file(stream,root->left,arr,counter);
	}
	else if(arr[*counter] == '1'){
		*counter = *counter + 1;
		print_message_to_file(stream,root->right,arr,counter);
	}
	
}

/* This function compares the bytes of given files. */
void byte_compare(char *file_name_dat, char *file_name_txt){

	int byte_txt;
	int byte_dat;

	FILE *datfile;
	FILE *txtfile;
	
	datfile = fopen(file_name_dat,"rb");
	txtfile = fopen(file_name_txt,"r");

	fseek(datfile,0L,SEEK_END);
	byte_dat = ftell(datfile);
	fseek(datfile,0L,SEEK_SET);
	
	fseek(txtfile,0L,SEEK_END);
	byte_txt = ftell(txtfile);
	fseek(txtfile,0L,SEEK_SET);
	
	printf("\nThe total bytes of 'encoded.dat' file is: %d bytes\n",byte_dat);
	printf("The total bytes of 'decoded.txt' file is: %d bytes\n",byte_txt); 
	
	fclose(datfile);
	fclose(txtfile);
}















