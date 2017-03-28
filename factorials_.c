#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

// - (this version calculated up to 15, doesn't find 8 steps for 9, 24th Jan)

#define MAX_SEQ 24

struct OP
{
    union
    {
        int raw;
        char o[4];
    };
};

long long int factorial, c;
int max, meta;
int rec( long long int last, int profundidad, long long int m, int mul, int suma, int resta1, int resta2);
int imprimir(long long int n[MAX_SEQ], int profundidad, int mul, int suma, int resta1, int resta2);
clock_t inicio;
long long int lista[MAX_SEQ];
float sq[MAX_SEQ], sq_tmp[MAX_SEQ];
int existe(int long long value, int profundidad);
int long long mayor( int profundidad );
int imp(int profundidad);
int main()
{
    //printf("sizeof(int): %d", sizeof(int));
    //return 0;
    int i;
    printf("\nNumero factorial meta: ");
    scanf("%d", &meta);
    max = meta+1;
    //max=meta;
    if (max>60) max=60;
    
    for(i=1, factorial=1; i<=meta; i++)
    {
        factorial=factorial*i;
    }
    printf("%d! = %I64d", meta, factorial);
    for(i=0;i<MAX_SEQ;i++)
    {
        lista[i]=0;
        sq[i]=0;
    }
    for(i=1, sq[0]=sqrt(factorial); ; i++)
    {
        sq[i]=sqrt(sq[i-1]);
        if(sq[i]<2)
        {
            sq[i]=0;
            break;
        }
        printf("\n%d: The truncated sqrt of %f is: %f", i, sq[i-1], sq[i]);
    }
    printf("\n");
    c=0;
    int res;
    clock_t ini;    
    for(res=0, max=meta-2;res==0;max++)
    {
        inicio = clock();
        ini=clock();
        srand(ini);
        printf("\nCiclo #%d (max:%d)\n", max-1, max-1);
        for (c=0;c<(max-1);c++)
            printf("%.2f, ", sq[max-c-3]);
        c=0;
        res=rec(1, 1, 0, 0, 0, 0, 0);
        float seconds = (float)((float)clock() - (float)ini) / CLOCKS_PER_SEC;
        if (seconds<0.1) continue;
        printf(" res=%d", res);
        if(res==0)
            printf("\nNodos computados: %.2f (Millones), en %.2f segundos... (%.2f Mn/s)", ((float)c)/1000000.0, seconds, (((float)c)/1000000.0)/seconds);
    }
    //rec(1, 1, 0);    
    return 0;
}
//12! = 479001600
int rec( long long int last, int profundidad, long long int m, int mul, int suma, int resta1, int resta2)
{
    int long long m2;
    c++;
    m2=m;
    if(profundidad>=max)
        return 0;
    int mul2, suma2, resta12, resta22;
    if(last>m2)
        m2=fabs(last);
    lista[profundidad-1]=last;
    int long long tmp;
    tmp=0;
    int i, j, k, res;
    res=0;
    //if(profundidad==(max-1))
    //    imp(profundidad);
    if(last==factorial)
        return imprimir(lista, profundidad, mul, suma, resta1, resta2);
    for(i=0;i<profundidad && res==0;i++)
    {
        for(k=0;k<4 && res==0;k++)
        {
            mul2=mul;
            suma2=suma;
            resta12=resta1;
            resta22=resta2;
            if(k==0)
            {
                tmp = lista[i]*last;
                mul2=mul+1;
                if(profundidad==(max-1))
                    break;
            }
            else if (k==1)
            {
                tmp = lista[i]+last;
                suma2=suma+1;
            }/*
            else if (k==2)
            {
                tmp = lista[i]-last;
                resta12=resta1+1;
            }*/
            else if (k==3)
            {
                tmp = last-lista[i];
                resta22=resta2+1;
            }
            for(j=0;j<profundidad; j++)
            {
                if(lista[j]==tmp)
                    break;
            }
            if(j==profundidad && tmp>m2 && suma2<4 && resta22<3)
            {
                //printf("\nComparing %I64d with %.2f (%d)... profundidad: %d, max: %d", m2, sq[max-profundidad-2], max-profundidad, profundidad, max);
                if(m2<sq[max-profundidad-2])
                {
                    return 0;
                }
                //if((1<<profundidad)<sq[max-profundidad-1])
                /*
                if(mul2<(profundidad-8))
                {
                    return 0;
                    int h;
                    printf("\n");
                    for(h=0;h<profundidad;h++)
                        printf("%I64d, ", lista[h]);
                    printf("\nMul: %d", mul2);
                    //printf("\nProfundidad: %d, sq[%d]=%.2f, ((1<<profundidad)<sq[max-profundidad-1]) == %d", profundidad, profundidad, sq[max-profundidad-1], ((1<<profundidad)<sq[max-profundidad-1]));
                }*/
                if((profundidad+1)<max)
                    res=rec(tmp, profundidad+1, m2, mul2, suma2, resta12, resta22);
                else
                    c++;
            }
        }
    }
    return res;
}

int imprimir(long long int n[MAX_SEQ], int profundidad, int mul, int suma, int resta1, int resta2)
{
    float seconds = (float)((float)clock() - (float)inicio) / CLOCKS_PER_SEC;
    if (seconds<0.1) seconds=0.01;
    printf("\nNodos computados: %.2f (Millones), en %.2f segundos... (%.2f Mn/s)", ((float)c)/1000000.0, seconds, (((float)c)/1000000.0)/seconds);
    c=0;
    int i;
    printf("\n%d: ", profundidad);
    for(i=0;i<profundidad;i++)
    {
        printf("%I64d, ", n[i]);
    }
    printf("  mul: %d, suma: %d, resta1: %d, resta2: %d", mul, suma, resta1, resta2);
    //printf(", %ld", last);
    max=profundidad;
    return 1;
}

int imp(int profundidad)
{
    int i;
    printf("\n%d: ", profundidad);
    for(i=0;i<profundidad;i++)
    {
        printf("%I64d, ", lista[i]);
    }
    return 1;
}


/*
    el numero actual de elementos en la secuencia es mayor o igual al maximo actual?
        si: regresar
        no: continuar
    el ultimo numero de la lista es igual a la meta?
        si: guardar la secuencia, guardar el numero de pasos, salir
        no: continuar
    tomo el ultimo numero de la lista = u
    para cada numero n en la lista:
        si n+u no existe en la lista, añadirlo a la lista y llamar recursion
        si n-u no existe en la lista, añadirlo a la lista y llamar recursion
        si u-n no existe en la lista, añadirlo a la lista y llamar recursion
        si n*u no existe en la lista, añadirlo a la lista y llamar recursion
    salir

*/
int existe(int long long value, int profundidad)
{
    int i;
    for(i=0;i<profundidad;i++)
    {
        if(value==lista[i])
            return 1;
    }
    return 0;
}

int long long mayor( int profundidad )
{
    int long long m;
    int i;
    for(i=0, m=0;i<MAX_SEQ;i++)
    {
        if(fabs(lista[i])>m)
            m=fabs(lista[i]);
    }
    return m;
}

/*
    hacer tabla de n valores
    float sq[MAX_SEQ];
    for(c=n-1, sq[n]=sqrt(factorial);; c!=0; c--)
    {
        sq[c]=sqrt(sq[c+1]);
    }
    si en la profundidad n-1 el mayor numero actual es M, y M<sqrt(n!), entonces este nodo no sirve
    if(M<sq[profundidad])
        salir;
    de lo contrario, 


*/



