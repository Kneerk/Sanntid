#include <pthread.h>
#include <unistd.h>
#include "primary.h"

int main()
{
	pthread_t t1;
	pthread_create(&t1, NULL, Primary, NULL);

	sleep(5);

	return 0;
}
