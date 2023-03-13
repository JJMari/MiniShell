#include "stack_counters.h"
/********************************
 * Juan José Marí Enseñat
 * Harpo Joan Alberola
 * Daniel Giralt Pascual
*********************************/

/**
 * Mètode main principal del programa
 */
int main(int args, char *argv[])
{
    if (argv[1])
    {

        stack = my_stack_read(argv[1]);

        printf("Fils: %i, Iteracions: %i\n", NUM_THREADS, NUM_ITERATIONS);
        // Si la pila existeix
        if (stack)
        {
            if (my_stack_len(stack) > NUM_THREADS)
            {
                printf("Contingut inicial de la pila:\n");
                my_stack_content(stack);
                printf("longitud inicial de la pila: %d \n", my_stack_len(stack));
            }
            else
            { // si no significa que no està completa

                printf("contingut inicial de la pila:\n");
                my_stack_content(stack);
                printf("longitud inicial de la pila: %d \n", my_stack_len(stack));
                int length = my_stack_len(stack);
                length = NUM_THREADS - length;
                for (int i = 0; i < length; i++)
                {
                    int *data = malloc(sizeof(int));
                    *data = 0;
                    my_stack_push(stack, data);
                }
                printf("\nNombre d'elements afegits a la pila inicial: %d\n", length);

                printf("Contingut de la pila pel tractament: \n");
                my_stack_content(stack);
                printf("longitud: %d \n", my_stack_len(stack));
            }
        }
        else
        {
            stack = my_stack_init(sizeof(int));
            printf("stack->size: %d \n", stack->size);
            printf("longitud inicial de la pila: %d", my_stack_len(stack));
            printf("Contingut inicial de la pila: \n");

            for (int i = 0; i < NUM_THREADS; i++)
            {
                int *data = malloc(sizeof(int));
                *data = 0;
                my_stack_push(stack, data);
            }
            printf("Contingut de la pila pel tractament: \n");
            my_stack_content(stack);
            printf("nova longitud: %d \n", my_stack_len(stack));
        }

        // Cream els fils
        pthread_t threads[NUM_THREADS];

        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&threads[i], NULL, worker, NULL);
            printf("%d) Fil %ld creat\n", i, threads[i]);
        }
        printf("\n");

        // Esperam a que acabin els fils
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }

        printf("Contingut de la pila despres del tractament:\n");
        my_stack_content(stack);
        printf("longitud de la pila: %d\n", my_stack_len(stack));

        // Guardam a la pila
        my_stack_write(stack, argv[1]);
        printf("Elements escrits de la pila al fitxer: %d\n", my_stack_len(stack));
        printf("Bytes eliminats: %d\n", my_stack_purge(stack));
        printf("Bye desde main\n\n");
        pthread_exit(0);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "\x1b[31mUSAGE: ./stack_counters stack_file\x1b[0m\n");
        return EXIT_FAILURE;
    }
}

/**
 * Mètode que regula l'activitat dels fils mitjançant un semàfor
 */
void *worker(void *ptr)
{
    int *data;

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        // Secció crítica nº1
        pthread_mutex_lock(&mutex);
#if DEBUG
        printf("\nSóc el fil %ld executant 'pop'", pthread_self());
#endif
        data = my_stack_pop(stack);
        pthread_mutex_unlock(&mutex);

        (*data)++;

        // Secció crítica nº2
        pthread_mutex_lock(&mutex);
#if DEBUG
        printf("\nSóc el fils %ld executant 'push'", pthread_self());
#endif
        my_stack_push(stack, data);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

/**
 * Mètode per mostrar el contingut de la pila
 */
void my_stack_content(struct my_stack *stack)
{
    if (stack->top && stack && stack->size)
    {
        int *data;
        struct my_stack_node *node = stack->top;

        while (node != NULL)
        {
            data = node->data;
            printf("%d\n", *data);
            node = node->next;
        }
    }
}