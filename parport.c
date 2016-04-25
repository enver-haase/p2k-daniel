
#include <asm/io.h>
#include <rtai.h>
#include <rtai_sem.h>
#include "parport.h"
#define LPTPORT     0x378
#define DATAPORT    LPTPORT + 0x0
#define STATUSPORT  LPTPORT + 0x1
#define CTRLPORT    LPTPORT + 0x2
#define ECP_ECR     LPTPORT + 0x402


static SEM ppsem;


BYTE receive_data(BYTE dest)
{
	BYTE data;
	rt_sem_wait(&ppsem);
	outb(0x0a, CTRLPORT);
	outb(dest, DATAPORT);
	outb(0x0e, CTRLPORT);
	outb(0x2b, CTRLPORT);
	data = inb(DATAPORT);
	outb(0x2a, CTRLPORT);
	rt_sem_signal(&ppsem);
	return data;
}


void send_data(BYTE dest, BYTE data)
{
	rt_sem_wait(&ppsem);
	outb(0x02, CTRLPORT);
	outb(dest, DATAPORT);
	outb(0x06, CTRLPORT);
	outb(data, DATAPORT);
	outb(0x03, CTRLPORT);
	outb(0x02, CTRLPORT);
	outb(0x2a, CTRLPORT);
	rt_sem_signal(&ppsem);
}


void init_parport(void)
{
	rt_sem_init(&ppsem, 1);
	outb(0x2a,CTRLPORT);
	outb(0x3f, ECP_ECR);
}


void cleanup_parport(void)
{
}

