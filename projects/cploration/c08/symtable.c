#include "symtable.h"

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];//variable to store in hashtable

int hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(char* key, hack_addr addr) {

   struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
   item->addr = addr;  
   item->name = strdup(key);

   //get the hash 
   int hashIndex = hash(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }
	
   hashArray[hashIndex] = item;
}

struct Symbol *symtable_find(char * key){
    //get the hash 
   int hashIndex = hash(key);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(strcmp(hashArray[hashIndex]->name, key) == 0)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }        
	
   return NULL;        

}
void symtable_display_table() {
   int i = 0;
	
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" (%s,%d)",hashArray[i]->name,hashArray[i]->addr);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}

void symtable_print_labels(){
    int i = 0;
	
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
	
        if(hashArray[i] != NULL){
            printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
    }
}

