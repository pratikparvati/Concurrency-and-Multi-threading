#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    int id = 0, err = 0;
    int *mem;

    id = shmget(IPC_PRIVATE, 10, 0666); /* Make shared memory segment */
    if (id == -1)
        perror("shmget");
    else
        printf("Allocated with shm id %d\n", (int)id);

    mem = (int *)shmat(id, (void *)0, 0); /* Attach the segment */
    if ((int)mem == -1)
        perror("shmat");
    else
        printf("Attached --> Mem contents %d\n", *mem);

    *mem = 100; /* Give it initial value */
    printf("mem updated to 100\n");
    printf("Start other process-->");
    getchar();
    printf("mem is now %d\n", *mem); /* Print out new value */

    err = shmctl(id, IPC_RMID, 0); /* Remove segment */
    if (err == -1)
        perror("shmctl");
    else
        printf("Removed %d\n", (int)(err));

    return 0;
}