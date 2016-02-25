#include <pthread.h>
#include <unistd.h>
#include "primary.h"


int main()
{
	pthread_t t1;
	pthread_create(&t1, NULL, Primary, NULL);

	sleep(15);

	return 0;
}
