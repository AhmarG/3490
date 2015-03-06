/*
 * Queues.c
 *
 * Created: 3/3/2015 11:29:35 AM
 *  Author: gordona
 */ 
#include "Queues.h";
#include "System.h";


char arr1[64];
char arr2[64];
struct QCB queueArray[QCB_MAX_COUNT];
int queueCheck[QCB_MAX_COUNT];

//Attempts to write 1 byte to specified queue. returns 1 if successful,
//0 if queue is full
byte Q_putc(byte qid, char data)
{
	struct QCB que;
	que = queueArray[qid];
	
	if(que.flags == Q_EMPTY)
	{
		*(que.pQ + que.in) = data;
		que.in = (que.in + 1) & que.smask;
	}
	else
	{
		return 0;
	}
	
	//check if empty
	if(que.in == 0)
	{
		que.flags = Q_FULL;
	}
	que.available++;
}

//Attempts to read 1 byte from specified queue to *pdata.
//Returns 1 if successful, 0 of queue empty
byte Q_getc(byte qid, char *pdata )
{
	struct QCB que;
	que = queueArray[qid];
	
	if(que.flags == Q_EMPTY)
	{
		return 0;
	}
	else
	{
		*pdata = *(que.pQ + que.out);
		que.out = *(que.out + 1) & que.smask;
	}
	
	if(que.out == 0)
	{
		que.flags = Q_EMPTY;
	}
	que.available--;
}

//Create a queue of specified size.
//Returns id of next available queue, -1 if error (no more queues, invalid size)
int8_t Q_create(int qsize, char * pbuffer)
{
	int i = 0;
	for(; i < QCB_MAX_COUNT; i++)
	{
		if (queueCheck[i] == 0)
		{
			break;
		}
	}
	
	if(i == QCB_MAX_COUNT)
	{
		i = 0;
		return -1;
	}
	
	if (qsize != 8 || qsize != 16 || qsize != 32 || qsize != 64)
	{
		return -1;
	}
	
	QCB newQ = {0, 0, qsize, Q_EMPTY, 0, pbuffer};
	queueArray[i] = newQ;
	queueCheck[i] = 1;
	
	int j = 0;
	for(; j < QCB_MAX_COUNT; j++)
	{
		if (queueCheck[j] == 0)
		{
			return j;
		}
	}
	if (j == QCB_MAX_COUNT)
	{
		return -1;
	}
}

//Remove specified queue and reset it to be reused (by Q_create)
void Q_delete(byte qid)
{
	queueCheck[qid] = 0;
}

//Returns number of bytes used in the queue (available for reading)
//Returns -1 if error (invalid queue)
int Q_used(byte qid)
{
	if (queueArray[qid].pQ == NULL)
	{
		return -1;
	}
	return queueArray[qid].available;
	
}

//Returns number of unused bytes in the queue (available for writing)
//Returns -1 if error (invalid queue).
int Q_unused(byte qid)
{
	if (queueArray[qid].pQ == NULL)
	{
		return -1;
	}
	return ((queueArray[qid].smask + 1) - queueArray[qid].available);
}
