#ifndef VMM_H
#define VMM_H

#include "interface.h"

void getData(int p, void *vm, int size, int frames, int p_size);
//void printList();
int getLength();
int deleteLastPage();
int getFrame(int virt_page);
int getWriteBack();
int getModifiedBit();
int getPermission(int page);
int evict();
int addPage(int page, int permission, void *addr);
int checkPageExistence(int page);
void addFrame(int counter);
void createList(int frames);


#endif
