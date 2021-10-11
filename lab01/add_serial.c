#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    schelet pentru exercitiul 5
*/

int* arr;
int array_size;

typedef struct {
    int start;
    int end;
    int* arr;
} thread_args;

void *f (void* args) {

    thread_args *one_t_arg = (thread_args *)args;
    for (int i = one_t_arg->start; i < one_t_arg->end; i++) {
        one_t_arg->arr[i] += 100;
    }

    for (int i = one_t_arg->start; i < one_t_arg->end; i++) {
        printf("%d", one_t_arg->arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
}

int min(int a1, int a2) {
    if (a1 > a2) return a2;
    else return a1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Specificati dimensiunea array-ului\n");
        exit(-1);
    }

    long cores = sysconf(_SC_NPROCESSORS_CONF);

    array_size = atoi(argv[1]);

    arr = malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    // TODO: aceasta operatie va fi paralelizata
    pthread_t threads[cores];
  	int r;
  	long id;
  	void *status;

    thread_args t_args[cores];
    for (id = 0; id < cores; id++)
    {
        int start = id * (double)array_size / cores;
        int end = min((id + 1) * (double)array_size / cores, array_size);
        t_args[id].start = start;
        t_args[id].end = end;
        t_args[id].arr = arr;
        r = pthread_create(&threads[id], NULL, f, (void *)&t_args[id]);

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
    

  	pthread_exit(NULL);
}
