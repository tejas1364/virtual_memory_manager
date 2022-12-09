//Libraries
#include "vmm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>

// Memory Manager implementation

int policy;
void *vm_ptr;
int vm_size;
int num_frames;
int page_size;

//FIFO Replacement Global Variables
int write_back;
int curr_frame = -1;

//Third Chance Replacement Global Variables
int mBit;
int position = -1;


//Data Structure Element
struct element {
	int page;
	int frame;
	int permission;
	int r;
	int m;
	int tcv;
	void *addr;
	struct element *next;
};


struct element *head = NULL;
struct element *current = NULL;




void getData(int p, void *vm, int size, int frames, int p_size){
	policy = p;
	vm_ptr = vm;
	vm_size = size;
	num_frames = frames;
	page_size = p_size;
}



int getLength() {
	int length = 0;
	struct element *current;
	if(policy == 1){
		for(current = head; current != NULL; current = current->next) {
			length++;
		}
		return length; 
	}
	else{
		current = head;
		for(int i = 0; i < num_frames; i++){
			if(current->page == -1){
				return length;
			}
			length++;
			current = current->next;
		}
	}
}



int deleteLastPage() { //mprotect the last page to none
	struct element *previous = NULL;
	struct element *current = head;
	int deleted_page = -1;

	if(head == NULL){
		write_back = 0;
		curr_frame = -1;
		return -1;
	}
	
	if(current->next == NULL){
		deleted_page = head->page;
		write_back = head->permission;
		curr_frame = head->frame;
		head = NULL;
		return deleted_page;
	}
	
	while(current->next != NULL){
		previous = current;
		current = current->next;
	}
	
	deleted_page = current->page;
	write_back = current->permission;
	curr_frame = current->frame;
	previous->next = NULL;
	return deleted_page;
}



int checkPageExistence(int page) {
	struct element* current = head;
	if(policy == 1){
		if(head == NULL){
			return 0; //Doesnt exist
		}

		while(current->page != page){
			if(current->next == NULL){
				return 0;
			}
			else{
				current = current->next;
			}
		}
		return 1;    //Exists 
	}
	else{
		for(int i = 0; i < num_frames; i++){
			if(current->page == page){
				return 1;       // Exists
			}
			current = current->next;
		}
		return 0;          // Does not exist
	}
}



int getFrame(int virt_page){
	struct element *current;
	if(policy == 1){
		for(current = head; current != NULL; current = current->next){
			if(current->page == virt_page){
				return current->frame;
			}
		}
	}
	else{
		current = head;
		for(int i = 0; i < num_frames; i++){
			if(current->page == virt_page){
				return current->frame;
			}
			current = current->next;
		}
		return -1;
	}
}



int getWriteBack(){
	return write_back;
}



int getModifiedBit(){
	return mBit;
}



int getPermission(int page){
	struct element *current = head;
	for(int x = 0; x < num_frames; x++){
		if(current->page == page){
			return current->permission;
		}
		current = current->next;
	}
	return -1;
}



int evict(){
	struct element *current;
	current = head;

	if(num_frames == 1){
		position = current->next->page;
		return current->page;
	}
	else{
		while(/*position != -1 &&*/ current->page != position){
			current = current->next;
		}
	}
	
	if(getLength() != num_frames){
		return current->page;
	}
	
	while(head){
		if (current->r == 0 && current->tcv == 0){
			position = current->next->page;
			return current->page;
		}
		else if(current->r == 1 && current->tcv == 0){
			current->r = 0;
			mprotect(current->addr, page_size, PROT_NONE);
			if(current->m == 1){
				current->tcv = 1;
				//mprotect(current->addr, page_size, PROT_NONE);
			}
		}
		else if(current->r == 0 && current->tcv == 1){
			current->tcv = 0;
			mprotect(current->addr, page_size, PROT_NONE); //added
		}
		current = current->next;
	}
}



int addPage(int page, int permission, void *addr) { //returns evicted page number or -1
	struct element *temp = (struct element*) malloc(sizeof(struct element));
	int evicted_page = -1;
	if (checkPageExistence(page) == 0){
		if(getLength() == num_frames){
			if(policy == 1){
				evicted_page = deleteLastPage();
			} 
			else{
				evicted_page = evict();
			}
		}
		else{
			if(policy == 1){
				curr_frame++;
			}
		}

		if(policy==1){    // POLICY 1
			temp->frame = curr_frame;
			temp->page = page;
			temp->permission = permission;
			temp->addr = addr;
			temp->next = head;
			head = temp;

		}
		else{	// POLICY 2
			struct element *current = head;
			for(int i = 0; i < num_frames; i++){
				if(current->page == evicted_page){
					current->page = page;
					current->r = 1;

					mBit = current->m;

					current->m = permission;
					current->permission = permission;
					current->tcv = 0;
					current->addr = addr;
					break;
				}
				current = current->next;
			}
			if(evicted_page == -1 && getLength() == num_frames){
				position = head->page;
			}
		}
		return evicted_page;
	}	
	else{
		struct element *current;
		
		for(current = head; current != NULL; current = current->next){
			if(current->page == page)
				break;
		}
		
		current->permission = permission;
		if(policy == 2){
			current->r = 1;
			if(current->m == 0)
				current->m = permission;
		}
	}
	return -1;
}



void addFrame(int counter){
	struct element *temp = (struct element*) malloc(sizeof(struct element));
	struct element *current = head;
	temp->page = -1;
	temp->permission = 0;
	temp->addr = NULL;
	temp->r = 0;
	temp->m = 0;
	temp->tcv = 0;
	temp->frame = counter;
	temp->next = NULL;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = temp;
}



void createList(int frames){
	struct element *temp = (struct element*) malloc(sizeof(struct element));
	struct element *current;
	temp->page = -1;
	temp->permission = 0;
	temp->addr = NULL;
	temp->r = 0;
	temp->m = 0;
	temp->tcv = 0;
	temp->frame = 0;
	temp->next = NULL;
	head = temp;

	current = head;
	for(int i = 1; i < frames; i++){
		addFrame(i); //made negative 1 each page to signify it is empty
	}

	while(current->next != NULL){
		current->r = 0;
		current->m = 0;
		current->tcv = 0;
		current = current->next;
	}
	current->next = head;
}
