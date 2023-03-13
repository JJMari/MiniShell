
// Llibreries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "my_lib.h"

// Constants
#define NUM_THREADS 10
#define NUM_ITERATIONS 1000000

// Variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static struct my_stack *stack;

// Funcions
struct my_stack *init_stack(char *file);
void *worker(void *ptr);
void my_stack_content(struct my_stack *stack);

