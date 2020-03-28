#include <stdio.h>
#include <pthread.h>

/*
 * thread application code, the multi-thread application start code of Linux application
 * compile :
 *          $/usr/local/arm/2.95.3/bin/arm-linux-gcc -o thread -lpthread thread.c
 *          $cp thread /tftpboot/examples
 * run in target:
 *          #mount 192.168.1.180:/tftpboot/ /mnt/nfs
 *          #cd /mnt/nfs/examples
 *          #./thread
 */

void thread(void)
{
    int i;
    for(i=0;i<3;i++)
    printf("This is a pthread.\n");
}

int main(int argc, char **argv)
{
    pthread_t id;
    int i,ret;
    ret=pthread_create(&id,NULL,(void *) thread,NULL);
    if(ret!=0){
    printf ("Create pthread error!\n");
    exit (1);
    }
    for(i=0;i<3;i++)
    printf("This is the main process.\n");
    pthread_join(id,NULL);
    return (0);
}

