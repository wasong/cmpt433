#include "server.h"
#include "sorter.h"

int main()
{
	pthread_t sorterThread;
	pthread_t serverThread;

	pthread_attr_t attributes;
	pthread_attr_init(&attributes);

	pthread_create(&sorterThread, &attributes, sorter_startSorting, NULL);
	pthread_create(&serverThread, &attributes, listen_for_command, NULL);
	
	pthread_join(sorterThread, NULL);
	pthread_join(serverThread, NULL);

	return 0;
}
