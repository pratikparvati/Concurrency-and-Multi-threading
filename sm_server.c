#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    int id, err;
    int* mem;
    if (argc <= 1) {
        printf("Need shared memory id.\n");
        exit(1);
    }
    sscanf(argv[1], "%d", &id); /* Get id from command line . */
    printf("Id is %d\n", id);
    mem = (int*)shmat(id, (void*)0, 0); /* Attach the segment */
    if ((int)mem == -1)
        perror("shmat");
    else
        printf("Attached--> Mem contents %d\n", *mem);
    *mem = 200; /* Give it a different value */
    printf("Changed mem is now %d\n", *mem);
    err = shmdt((void*)mem); /* Detach segment */
    if (err == -1)
        perror("shmdt");
    else
        printf("Detachment %d\n", err);
    return 0;
}