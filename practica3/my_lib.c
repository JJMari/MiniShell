/*_____________________________________________________________________________
PRACTICA 1
SQUAD: HDJ 
NOMS: 
        Giralt Pascual, Daniel
        Joan Alberola, Harpo
        Marí Enseñat, Juan José       
_____________________________________________________________________________*/

#include <stdio.h>     /* para printf en depurarión */
#include <string.h>    /* para funciones de strings  */
#include <stdlib.h>    /* Funciones malloc(), free(), y valor NULL */
#include <fcntl.h>     /* Modos de apertura de función open()*/
#include <sys/stat.h>  /* Permisos función open() */
#include <sys/types.h> /* Definiciones de tipos de datos como size_t*/
#include <unistd.h>    /* Funciones read(), write(), close()*/
#include <errno.h>     /* COntrol de errores (errno) */

/*_____________________________________________________________________________

                FUNCIONS PER A STRINGS                    
_____________________________________________________________________________*/

/*
-------------------------------------------------------------------------------
Funció: my_strlen()

Acció: Funció que retorna la longitud de array.

Paràmetre 1: str es un punter d'un array.

Sortida: Retorna la longitud del array.
-------------------------------------------------------------------------------
*/
size_t my_strlen(const char *str){
    //Declaram la variable que retornarem y la deixam a 0
    size_t len=0;

    //En un bucle recorrem tot l'array i, per cada element que trobi,
    //suma 1 a la variable "len"
    while(*str++){
        len++;
    }return len;
}

/*
-------------------------------------------------------------------------------
Funció: my_strcmp()

Acció: Funció que retorna si dos arrays son iguals o no.

Paràmetre 1: str1 es el punter del primer array a comparar.

Paràmetre 2: str2 es el punter del segon array a comparar.

Sortida: Retorna 0 si els arrays son iguals. Si és menor a 0 significa que el
        codi ascii de str1 és menor que str2. Si s'ha retornat un nombre 
        major a 0 significa que str1 és major que str2.
-------------------------------------------------------------------------------
*/
int my_strcmp(const char *str1, const char *str2){  

    //En un bucle, recorrem els dos arrays fins el final d'ambdos
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

/*
-------------------------------------------------------------------------------
Funció: my_strcpy()

Acció: Funció que copía el contingut de l'array font a un array destí.

Parèmetre 1: dest és el punter de l'array de destí.

Parèmetre 2: src és el punter de l'array a copiar

Sortida: Retorna el punter de l'array de destí on s'ha realitzat la còpia
-------------------------------------------------------------------------------
*/
char *my_strcpy(char *dest, const char *src){
    //Declaram un index 
    int aux= 0;

    //buidam dest
    while(dest[aux] != '\0'){
        dest[aux++] = '\0';
    }

    aux = 0;

    //pasams tots els caracters de src a dest
    while (src[aux] != '\0')
    {
        dest[aux] = src[aux];
        aux++;
    }

    return dest;    
}        
/*
-------------------------------------------------------------------------------
Funció: my_strcpy()

Acció: Funció que copía el contingut de l'array font a un array destí.

Parèmetre 1: dest és el punter de l'array de destí.

Parèmetre 2: src és el punter de l'array a copiar

Paràmetre 3: n es la quantitat d'elements que es volen copiar.

Sortida: Retorna el punter de l'array de destí on s'ha realitzat la còpia
-------------------------------------------------------------------------------
*/
char *my_strncpy(char *dest, const char *src, size_t n){

    //obtenim la longitud de src
    int len = my_strlen(src);
    
    //separam el problema en els dos posibles casos
    if (len < n)
    {
        //per a un tamany major que el de *src:

        //posam el contingut de *src en *dest y omplim
        //la resta de 0's
        for (int i = 0; i < len; i++)
        {
            dest[i] = src[i];
        }
        for (int i = len; i < n; i++)
        {
            dest[i] = '\0';
        }
    }
    else
    {
        //para un tamaño menor o igual que el de *src

        //añadimos los n primeros caracteres de *src en *dest
        for (int i = 0; i < n; i++)
        {
            dest[i] = src[i];
        }
    }
    return dest;
}
/*
-------------------------------------------------------------------------------
Funció: my_strcat()

Acció: Funció que copía el contingut de l'array font a un array destí, però
        el copía a partir del valor nul.

Paràmetre 1: dest es el punter de l'array destí

Paràmetre 2; src es el punter de l'array a copiar

Sortida: Retorna el punter de l'array de destí on s'ha realitzat la còpia
-------------------------------------------------------------------------------
*/
char *my_strcat(char *dest, const char *src){
    //Declaram un punter de l'array on farem la copia
    char *inici = dest;
    //Declaram una variable amb el tamany de l'array destí
    size_t n = my_strlen(dest);
    
    //Recorrem fins arribar al final de l'array destí
    while(n>0){
        dest++;
        n--;
    }

    //Copiam a la font la part del destí al final
    dest = my_strcpy(dest,src);


    return inici;
    
}
/*
-------------------------------------------------------------------------------
Funció: my_strchr()

Acció: Funció que se que encarga de buscar una letra en el array.

Paràmetre 1: s és el punter de l'array en el que hem de cercar.

Paràmetre 2: c és el caràcter a cercar.

Sortida: Retorna el punter de l'array on es troba la letra.
-------------------------------------------------------------------------------
*/
char *my_strchr(const char *str, int c){
    //recorrem el string amb el punter
    while (*str != '\0'){

        //si trobam el caracter retornam el que falta de string
        if (*str == c){
            return (char *)str;
        }
        str++;
    }

    return NULL;
}

//char *my_strncat(char *dest, const char *src, size_t n);

//structuras para gestor de pila
struct my_stack_node {      // nodo de la pila (elemento)
    void *data;
    struct my_stack_node *next;
};

struct my_stack {   // pila
    int size;       // tamaño de data, nos lo pasarán por parámetro
    struct my_stack_node *top;  // apunta al nodo de la parte superior
};  

/*_____________________________________________________________________________

               FUNCIONS PER AL TRACTAMENT DEL GESTOR DE PILES                    
_____________________________________________________________________________*/

/*
-------------------------------------------------------------------------------
Funció: my_stack_init()

Acció: Funció que s'encarrega d'inicializar la pila, reservant espai en 
        memoria (la quantitat d'espai a reservar es pasa per paràmetre)

Paràmetre 1: size es la quantitat de memoria a reservar, ha de ser 
             obligatoriament size>=1.

Sortida: Retorna la pila ja inicialitzada.
-------------------------------------------------------------------------------
*/
struct my_stack *my_stack_init(int size){
    // ACCIONS DE LA FUNCIÓ
    //inicialitzam la pila reservant l'espai que s'ha pasat por paràmetre
    struct my_stack *stack = malloc(size);
    
    //definim el tamany de la pila
    stack->size = size;
    
    //establim que el top de la pila (valor que sortirà primer) sigui null
    stack->top = NULL;
    
    //retornam la pila ja inicialitzada
    return stack;

}
/*
-------------------------------------------------------------------------------
Funció: my_stack_push()

Acció: Funció que s'encarrega d'introduïr elements a la pila (dinàmica). 
        Per a realizar aquest procés inicializam un node on guardarà la 
        informació que es introduïda por paràmetro (data) y apuntarà al 
        següent node.

Paràmetre 1: stack es la pila que contendrà la direcció del primer node.

Paràmetre 2: data es la dada que hem de guardar.

Sortida: Si el procediment és correcte es retornarà 0 però si s'ha produït qualque
         error es retornarà -1.
-------------------------------------------------------------------------------
*/
int my_stack_push(struct my_stack *stack, void *data){
    //inicialitzam una estructura que anomenam node
    struct my_stack_node *node;
    
    //reservam tant espai com requereixi el tamano de la pila
    node = malloc(sizeof(struct my_stack));
    
    if (node) {
        //el node guarda la informació pasada per paràmetre que és data
        node -> data = data;
        
        //posteriorment s'apunta al seguent node
        node -> next = stack -> top;
        stack -> top = node;
        return 1;
    }else return 0;
}
/*
-------------------------------------------------------------------------------
Funció: my_stack_pop()

Acció: Funció que s'encarrega d'extreure elements de la pila (dinàmica). Per a
        dur a terme aquest procés inicializam un void de data que enmagatzema la 
        informació extreta. Después ens dirigim al node que hi ha al punter
        top de stack on s'extreurà la informació de data i posicionarà la 
        del punter de la pila a l'element inferior. Finalment, alliberam la
        posició del node al que hem realitzat un pop.

Paràmetre 1: stack es la pila que contendrà la direcció del primer node.

Sortida: Retorna la dada del node eliminat
-------------------------------------------------------------------------------
*/
void *my_stack_pop(struct my_stack *stack){
    //comprovam que la pila no estigui buida
    if (stack->top!=NULL) {
        //enmagatzemam la informació corresponent al top de la pila
        void *data = stack->top->data;
        
        //posicionam el punter top al següent element de la pila
        stack->top = stack->top->next;
        
        //retornam la informació que hem extret del top de la pila
        return data;     

    }else return NULL;
}
/*
-------------------------------------------------------------------------------
Funció: my_stack_len()

Acció: Funció que s'encarrega de recorrer la pila per a comptar la quantitat  
       d'elements que conté.

Parèmetro 1: stack es la pila que contendrá la dirección del primer nodo.

Sortida: Retorna la quantitat d'elements que hi ha a la pila.
-------------------------------------------------------------------------------
*/
int my_stack_len(struct my_stack *stack){
    //cream una variable per guardar el top de la pila pasada por paràmetre
    struct my_stack_node *aux = stack->top; 
    
    //definim una variable que serveixi d'índex al recorrer la pila
    int i=0;
    
    //entram en un bucle tipus while en el que la condició és que la pila
    //no estigui buida
    while (aux!=NULL) {    
        //augmentam l'índex    
        i++;
        
        //apuntamo al següent element
        aux = aux -> next;        
    } return i;
}
/*
-------------------------------------------------------------------------------
Funció: my_stack_purge()

Acció: Funció que s'encarrega de alliurar els espais reservats en memoria
        (la pila, els nodes y els elements).

Paràmetre 1: stack es la pila que contendrè la direcció del primer node.

Salida: Retorna la quantitat de bytes eliminats.
-------------------------------------------------------------------------------
*/
int my_stack_purge(struct my_stack *stack){

    //Declaració de variables
    int i = my_stack_len(stack);
    int j = 0;
    //Bucle per a tota la longitud de la pila
    while(i>0){
        //Swap i suma de bytes alliberats a j
        struct my_stack_node *aux = stack->top;
        j += sizeof(struct my_stack_node );
        j += stack->size;
        stack -> top = aux -> next;
        //Alliberament de l'element
        free(aux);
        //decrementam l'iterador
        i--;
    }
    //sumam els bytes de la pila i la alliberam   
    j += sizeof(struct my_stack);
    free(stack);
    //retornam els bytes buids
    return j;
} 

/*
-------------------------------------------------------------------------------
Funció: my_stack_write()

Acció: Enmagatzema les dades de la pila en el fitxer indicat per filename 
        empleant una pila auxiliar que contendrà les dades enmagatzemades 
        inversament per a la grabació i la lectura dels nodes amb l'ordre 
        inicial correcte.

Paràmetre 1: stack es la pila que volem grabar en el fitxer pasat per 
             paràmetre

Paràmetre 2: filename es el punter que conté el nom del fitxer a llegir.

Sortida: si els nodes de la pila no es graven de forma correcta retorna -1 i
         0 en cas contrari.
-------------------------------------------------------------------------------
*/
int my_stack_write(struct my_stack *stack, char *filename)
{
    //DECLARACIONS DE LA FUNCIÓ
    int fd;
    int cont = 0;
    void *data;
    struct my_stack *aux;
    struct my_stack_node *nod;
    int bytesDatos;
    const int BYTES_INT = 4;

    //ACCIONS DE LA FUNCIÓ
    //si la pila no es null, podem tratar...
    if ( stack!=NULL )
    {
        //inicialitzam algunes declaracions per a que la pila no estigui buida
        bytesDatos = stack->size;
        aux = my_stack_init(stack->size);
        nod = stack->top;
        /*copiam els nodes a la pila auxiliar (aux) per a tenir els nodes
        invertits*/
        while (nod != NULL)
        {
            my_stack_push(aux, nod->data);
            nod = nod->next;
        }
        //establim enllaç lògic amb el fitxer;
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        /*si l'enllaç lògic amb el fitxer s'ha establert de forma correcta, 
        podem copiar els nodes al fitxer*/
        if (fd != -1)
        {
            //escribim primer l'enter de la pila que indica el tamany de "data". 
            //Si es fa de forma correcta, podem copiar els nodes al fitxer
            if ( write(fd, &bytesDatos, BYTES_INT) != -1 )
            {
                //copiam la informació dels nodes al fitxer
                data = my_stack_pop(aux);
                while (data != NULL)
                {
                    //si a l'escriure al fitxer NO es pordueix error, contabilizam el node
                    if ( write(fd, data, bytesDatos) != -1 )
                    {
                        cont++;
                    }
                    //actualizam data per el següent node a escriure
                    data = my_stack_pop(aux);
                }
            }
            //si al'escriure l'enter de la pila que indica el tamano de data es produeix un error
            //nodes pasa a valer -1 perque no podem escriure ningún node a la pila
            else
            {
                cont = -1;
            }
            //establim tancament d'enllaç lògic amb el fitxer
            close(fd);
        }
        /*Si l'enllaç lògic amb el fitxer NO s'ha establert de forma correcta
        retornam -1 porque hi ha hagut un error*/
        else
        {
            cont = -1;
        }
    }
    //retornam el nombre d'elements que s'han introduït
    return cont;
}


/*
-------------------------------------------------------------------------------
Funció: my_stack_read()

Acció: Llegiex les dades de la pila enmagatzemats al fitxer.

Paràmetre 1: filename és el punter que conté el nom del fitxer a llegir.

Sortida: Retorna el punter a la pila.
-------------------------------------------------------------------------------
*/
struct my_stack *my_stack_read(char *filename)
{
    //DECLARACIONS DE LA FUNCIÓ
    int fd;
    int lect;
    int size;
    const int BYTES_INT = 4;
    struct my_stack *aux;
    void *data;

    //ACCIONES DE LA FUNCION
    //establim l'enllaç lògic amb el fitxer
    fd = open(filename, O_RDONLY);
    //si l'enllaç lògic s'ha establert de forma correcta podem continuar
    if( fd != -1)
    {
        //lectura dels 4 primers bytes del tamany de les dades
        lect = read(fd, &size, BYTES_INT);
        //si s'ha llegit de forma correcta i el fitxer no està buid, tractarem
        if( lect > 0 )
        {
            //inicializació de la pila
            aux = my_stack_init(size);
            //mentre que no arribem al final del fitxer, lletgirem y crearem
            //nodes afegintlos a la pila
            while ( lect > 0 )
            {
                //reservamos memoria para el nodo
                data = malloc(size);
                //si no s'ha pogut reservar memoria de forma correcta,
                //sortirem del bucle amb lect=-1
                if ( data == NULL)
                {
                    lect = -1;
                }
                //si es reserva memòria de forma correcta, podem llegir i
                //guardar a la pila
                else
                {
                    //lectura de la data del node
                    lect = read(fd, data, size);
                    //si es llegiex de forma correcta podem afegir el node a la
                    //pila
                    if( lect > 0 )
                    {
                        //actualització de la pila amb el nou node
                        my_stack_push(aux, data);
                    }
                    //si no es llegeix de forma correcta alliberam la memoria que
                    //haviem reservat per la dada
                    else
                    {
                        free(data);
                    }
                }
            }
            //si sortim del bucle per algún error purgarem la pila
            if( lect == -1)
            {
                my_stack_purge(aux);
            }
            //establim el tancament de lenllaç lògic amb el fitxer
            close(fd);
        }
        //si no s'ha llegit bé els 4 primers bytes del tamany de data
        //tancam el fitxer
        else
        {
            close(fd);
        }
        
    }
    //si l'enllaç lògic no s'ha establert amb èxit retornam NULL
    else
    {
        aux = NULL;
    }
    //retornam la pila ja sigui amb nodes o buida (NULL)
    return aux;
}