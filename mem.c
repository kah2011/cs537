#include "mem.h"
#include "header.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <sys/mman.h>

//typedef struct __node_t{
//    int size;
//    struct node_t *next;
//} node_t;

int m_error;
struct node_t *headnode = NULL;

int Mem_Init(int sizeOfRegion, int debug)
{
    if(sizeOfRegion <= 0 || debug == 1) {
        m_error = E_BAD_ARGS;
        return -1;
    }

    // open the /dev/zero device
    int fd = open("/dev/zero", O_RDWR);

    // sizeOfRegion (in bytes) needs to be evenly divisible by the page size
    int sz = getpagesize();

    int pages = sizeOfRegion / sz;
    if(sizeOfRegion % sz != 0) {
        pages += 1;
    }
    sizeOfRegion = pages * sz;

    printf("page size:%d\n", sz);
    printf("total region size :%d\n", sizeOfRegion);

    void *ptr = mmap(NULL, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (ptr == MAP_FAILED) 
    { 
        perror("mmap");
        exit(1);
    }
    
    //close the device (don't worry, mapping should be unaffected)
    close(fd);
    //printf("ptr address: %p \n ", ptr);
    ptr = ptr + (sizeOfRegion - 8);
    //printf("ptr address: %p \n ", ptr);
    //*ptr = (int *) ptr;
    //printf("ptr address: %d \n ", (int) (*ptr));
    
    //headnode = (struct node_t) (&ptr);
    headnode = ptr;
    headnode->size = sizeOfRegion - sizeof(node_t);
    headnode->next = NULL;
    return 0;
}

void *Mem_Alloc(int size) 
{

    void *ptr = malloc(sizeof(void*));
    return ptr;
}

int Mem_Free(void *ptr, int coalesce) 
{
    return 0;

}

void Mem_Dump() 
{


}

int main(int argc, char * argv[]) {

    int init = Mem_Init(5120, 0);
    printf("init value is %d\n", init);
    int init1 = Mem_Init(-1, 0);
    printf("init1 value is %d\n", init1);

    return 0;
}
