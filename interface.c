#include "interface.h"
#include "vmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <ucontext.h>
#include <math.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

void *vm_ptr;
int vmSize;
int numFrames;
int pageSize;
int p;


static void handler(int sig, siginfo_t *si, void *ucontext)
{	
	//siginfo_t has the address where fault occurred
	//ucontext has the read or write permission that I need to get
	ucontext_t* context = (ucontext_t*)ucontext;
	int op = (context->uc_mcontext.gregs[REG_ERR] >> 1) & 1;
	void *fault_addr = si->si_addr;
	//Get starting address of page
	void *page_addr = (void *)((long)fault_addr - (long)vm_ptr); //4128
	long start = 0;
	
	for(int x = 0; x < vmSize; x += pageSize){
		if(x <= (long)page_addr && (long)page_addr < (x + pageSize)){
			start = x;
			break;
		}
	}

	int virt_page = start / pageSize;
	long offset = ((long)page_addr - start); //32
	page_addr = (void *)(start + (long)vm_ptr); //4096 plus start of mem
	
	//Set necessary protection on page to allow for operation
	if(op == 0){
		if(mprotect(page_addr, pageSize, PROT_READ) == -1){
			handle_error("mprotect");
		}
	}
	else{
		if(mprotect(page_addr, pageSize, PROT_WRITE) == -1){
			handle_error("mprotect");
		}
	}
	
	
	int pageExist = checkPageExistence(virt_page); //Check if page exists in page table
	int currentPermission = -1; //Stores current permission if it does exist in page table
	if(p == 2)
		currentPermission = getPermission(virt_page);
	int evicted_page = addPage(virt_page, op, page_addr); //AddPage() adds page to table and returns a page evicted, or -1

	
	
	//MM_LOGGER Checker
	if(evicted_page == -1){
		if(pageExist == 0){
			if(p == 1)
				mm_logger(virt_page, op, evicted_page, 0, (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));
			else
				mm_logger(virt_page, op, evicted_page, getModifiedBit(), (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));
		}
		else{
			if(p == 1)
				mm_logger(virt_page, 2, evicted_page, 0, (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));
			else{
				if(op < currentPermission || (op == 0 && currentPermission == 0)){
					mm_logger(virt_page, 3, evicted_page, 0, (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));	
				} 
				else if(op > currentPermission){
					mm_logger(virt_page, 2, evicted_page, 0, (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));
				} 
				else{
					mm_logger(virt_page, 4, evicted_page, 0, (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));
				}
			}
			
		}
	}
	else{
		void *evicted_page_addr = (void *)(long)((evicted_page * pageSize)+(long)vm_ptr);
		if(mprotect(evicted_page_addr, pageSize, PROT_NONE) == -1){
			handle_error("mprotect");
		}
		if(p == 1)
			mm_logger(virt_page, op, evicted_page, getWriteBack(), (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));
		else
			mm_logger(virt_page, op, evicted_page, getModifiedBit(), (unsigned int)(long)(void *)((getFrame(virt_page) * pageSize) + offset));
		
	}
}


void mm_init(enum policy_type policy, void *vm, int vm_size, int num_frames, int page_size) {
	vm_ptr = vm;
	vmSize = vm_size;
	numFrames = num_frames;
	pageSize = page_size;
	p = policy;
	
	struct sigaction sa;
  	sa.sa_flags = SA_SIGINFO;
  	sigemptyset(&sa.sa_mask);
  	sa.sa_sigaction = handler;
  
	//Sets handler() as default handler
	if(sigaction(SIGSEGV, &sa, NULL) == -1){
		handle_error("sigaction");
	}
	//Prevents access to Virutal memory with mprotect()
	if(mprotect(vm, vm_size, PROT_NONE) == -1){
	  	handle_error("mprotect");
	}
	
	//Passes parameters to vmm.c file for ease of use
  	getData(p, vm, vm_size, num_frames, page_size);
  	if(p == 2)
		createList(num_frames);
}









