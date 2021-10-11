#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 4

void *f(void *arg) {
  	long id = (long)arg;
	for (int i = 0; i < 100; i++)
	{
  		printf("Hello World din thread-ul %ld!\n", id);
	}
	pthread_exit(NULL);
}

void *f1() {
	printf("Salut din functia f1!\n");
}

void *f2() {
	printf("Salut din functia f2!\n");
}

int main(int argc, char *argv[]) {
	long cores = sysconf(_SC_NPROCESSORS_CONF);
	pthread_t threads[cores];
  	int r;
  	long id;
  	void *status;

  	for (id = 0; id < cores; id++) {
		r = pthread_create(&threads[id], NULL, f, (void *)id);

		if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	for (id = 0; id < cores; id++) {
		r = pthread_join(threads[id], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}
	printf("\n");

	sleep(5);


	pthread_t thread1, thread2;

	r = pthread_create(&thread1, NULL, f1, (void *)id);
	if (r) {
	  	printf("Eroare la crearea thread-ului thread1\n");
	  	exit(-1);
	}

	r = pthread_create(&thread2, NULL, f2, (void *)id);
	if (r) {
	  	printf("Eroare la crearea thread-ului thread2\n");
	  	exit(-1);
	}

	r = pthread_join(thread1, &status);
	if (r) {
	  	printf("Eroare la asteptarea thread-ului thread1\n");
	  	exit(-1);
	}

	r = pthread_join(thread2, &status);
	if (r) {
	  	printf("Eroare la asteptarea thread-ului thread2\n");
	  	exit(-1);
	}

  	pthread_exit(NULL);


}
