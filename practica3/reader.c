#include <stdio.h>
#include <limits.h>
#include "my_lib.h"
/********************************
 * Juan José Marí Enseñat
 * Harpo Joan Alberola
 * Daniel Giralt Pascual
*********************************/

#define NUM_THREADS 10

int main(int argc, char *argv[])
{
    if (argv[1])
    {
        struct my_stack *stack;
        stack = my_stack_read(argv[1]);

        if (stack)
        {
            int sum, average, length, min, max;
            sum = 0;
            length = my_stack_len(stack);
            min = INT_MAX;
            max = -1;

            printf("Longitud de la pila: %d\n", length);

            if (length > NUM_THREADS)
            {
                length = NUM_THREADS;
            }

            // Mentre la pila no estigui buida
            for (int i = 0; i < length && i<NUM_THREADS ; i++)
            {
                int data =*((int*) my_stack_pop(stack));

                if (data > max)
                {
                    max = data;
                }
                else if (data < min)
                {
                    min = data;
                }
                sum += data;
                printf("%d\n", data);
            }

            average = sum / length;

            printf("Elements: %d \x1b[30mSuma:\x1b[36m %d \x1b[0mMínim: %d, Màxim: %d, \x1b[30mMitjana:\x1b[36m %d\x1b[0m\n\n", length, sum, min, max, average);
        }
        else
        {
            printf("\x1b[31mCouldn't open stack file s\x1b[0m\n");
            return EXIT_FAILURE;
        }

        // Alliberam la memoria que correspon a la pila
        my_stack_purge(stack);

        return EXIT_SUCCESS;
    }
    else
    {
        printf("\x1b[31mUSAGE: ./reader  stack_file\x1b[0m\n");
        return EXIT_FAILURE;
    }
}