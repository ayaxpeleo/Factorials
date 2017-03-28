#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SEQ 13

long long int factorial, c;
int max, meta, flag;
int rec( long long int ultimo_valor, int profundidad, long long int m, int mul, int suma, int resta1, int resta2);
#define MUL 100
#define SUM 100
#define RE1 100
#define RE2 100
int imprimir(long long int n[MAX_SEQ], int profundidad, int mul, int suma, int resta1, int resta2);
clock_t inicio;
long long int lista[MAX_SEQ];
char lista_operadores[MAX_SEQ];
char lista_niveles[MAX_SEQ][2];
float sq[MAX_SEQ], sq_tmp[MAX_SEQ];
long long int mayor( int profundidad );
int imprimir_operadores(long long int n[MAX_SEQ], int profundidad, int mul, int suma, int resta1, int resta2);
long long int tmp;
int main()
{
	
	
    //printf("sizeof(int): %d", sizeof(int));
    //return 0;
    int i;
    printf("\nNumero factorial meta: ");
    scanf("%d", &meta);
    
    for(i=1, factorial=1; i<=meta; i++)
    {
        factorial=factorial*i;
    }
	//factorial=212520;
    for(i=0;i<MAX_SEQ;i++)
    {
        lista[i]=0;
		lista_operadores[i]=0;
		lista_niveles[i][0]=0;
		lista_niveles[i][1]=0;
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
        printf("\n%d: The sqrt of %f is: %f", i, sq[i-1], sq[i]);
    }
    printf("\n");
    c=0;
    int res;
    clock_t ini;
    
    for(res=0, max=3;res==0 && max<=MAX_SEQ && flag==0;max++)
    {
        //printf("\nmax: %d", max);
        inicio = clock();
        ini=clock();
        c=0;
		flag=0;
        res=rec(1, 1, 0, 0, 0, 0, 0);
        float seconds = (float)((float)clock() - (float)ini) / CLOCKS_PER_SEC;
        if (seconds<0.01) continue;
        //printf(" res=%d", res);
    }
    return 0;
}

int rec( long long int ultimo_valor, int profundidad, long long int m, int mul, int suma, int resta1, int resta2)
{
    c++;
    if(ultimo_valor==factorial)
	{
		lista[profundidad-1]=(ultimo_valor);
		imprimir_operadores(lista, profundidad, mul, suma, resta1, resta2);
		imprimir(lista, profundidad, mul, suma, resta1, resta2);
		printf("\n");
		flag=1;
		return 1;
	}
    if(profundidad==(max-1))
        return 0;
    long long int m2;
    m2=m;
    if(ultimo_valor>m2)
        m2=ultimo_valor;
    if(m2<(sq[max-profundidad-1]))
    {
        return 0;
    }
    lista[profundidad-1]=(ultimo_valor);
    tmp=0;
    int i, j, k;
    for(i=0;i<profundidad;i++)
    {
		for(k=i;k<profundidad;k++)
		{
			lista_niveles[profundidad-1][0]='a'+i;
			lista_niveles[profundidad-1][1]='a'+k;
			//k=profundidad-1;
			if(i>0 && k>0)
			{
				tmp = lista[i]*lista[k];
				for(j=0;j<profundidad; j++)
					if(lista[j]==tmp)
						break;
				if(j==profundidad)
				{
					lista_operadores[profundidad-1]='*';
					rec(tmp, profundidad+1, m2, mul+1, suma, resta1, resta2);
				}
			}
			//**********
			tmp = lista[i]+lista[k];
			for(j=0;j<profundidad; j++)
				if(lista[j]==tmp)
					break;
			if(j==profundidad)
			{
				lista_operadores[profundidad-1]='+';
				rec(tmp, profundidad+1, m2, mul, suma+1, resta1, resta2);
			}
			//**********
			//if((i!=0 && k!=(profundidad-1)) && (k!=0 && i!=(profundidad-1)))
			{
				tmp = lista[i]-lista[k];
				for(j=0;j<profundidad; j++)
					if(lista[j]==tmp)
						break;
				if(j==profundidad)
				{
					lista_operadores[profundidad-1]='_';
					rec(tmp, profundidad+1, m2, mul, suma, resta1+1, resta2);
				}
			//**********
				tmp = lista[k]-lista[i];
				for(j=0;j<profundidad; j++)
					if(lista[j]==tmp)
						break;
				if(j==profundidad)
				{
					lista_operadores[profundidad-1]='-';
					rec(tmp, profundidad+1, m2, mul, suma, resta1, resta2+1);
				}
			}
		}
    }
    return 0;
}

int imprimir(long long int n[MAX_SEQ], int profundidad, int mul, int suma, int resta1, int resta2)
{
    c=0;
    int i;
    printf("\n%d: ", profundidad);
    for(i=0;i<profundidad;i++)
    {
        printf("%I64d, ", n[i]);
    }
    printf(" m:%d,s:%d,r1:%d,r2:%d", mul, suma, resta1, resta2);
    return 1;
}
int imprimir_operadores(long long int n[MAX_SEQ], int profundidad, int mul, int suma, int resta1, int resta2)
{
    c=0;
    int i;
    printf("\n%d: ", profundidad);
    for(i=0;i<profundidad;i++)
    {
		if(lista_operadores[i]=='_')
		{
			lista_operadores[i]='-';
			printf("%c%c%c, ", lista_niveles[i][0], lista_operadores[i], lista_niveles[i][1]);
		}
		else
			printf("%c%c%c, ", lista_niveles[i][1], lista_operadores[i], lista_niveles[i][0]);
    }
    //printf(" m:%d,s:%d,r1:%d,r2:%d", mul, suma, resta1, resta2);
    return 1;
}