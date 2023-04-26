#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>


char lin_dup[70] = "==================================================================\n";
char lin_sim[70] = "------------------------------------------------------------------\n";


void printc(char *s, int tam)
{
    int ne = (tam - strlen(s)) / 2;
    while (ne > 0)
    {
        printf(" ");
        ne--;
    }
    printf(s);
}

void sleep(time_t delay)
{
    time_t timer0, timer1;
    time(&timer0);
    do
    {
        time(&timer1);
    } while ((timer1 - timer0) < delay);
}

int menu_principal()
{
    printf("\n%s", lin_dup);
    printc("Exercício Programa - Cálculo Numérico", 66);
    printf("\n%s\n", lin_dup);
    printf("  C - Conversão\n");
    printf("  S - Sistema Linear\n");
    printf("  E - Equação Algébrica\n");
    printf("  F - Finalizar\n");
    printf("  ----------------------\n");
    printf("\n  Escolha uma opção: ");
}

/*
void convert (int num, int base)
{
        int rem = num%base;

        if(num==0)
                return;
        convert(num/base, base);

        if(rem < 10)
                printf("%d", rem);
        else
                printf("%c", rem-10+'A' );
}*/

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char op1, op2;
    long double n1;

    do
    {
        menu_principal();
        fflush(stdin);
        op1 = getchar();

        system("cls || clear");

        if (op1 == 'f' || op1 == 'F')
        {
            printf("\n  ** Fim do aplicativo **");
            sleep(1);
            break;
        }
        switch(toupper(op1))
        {
            case 'C':
                printf("\n%s", lin_sim);
                printc("Conversão de número decimal", 66);
                printf("\n%s\n", lin_sim);

                printf("Digite um número decimal: ");
                scanf("%Lf",&n1);

                printf("Binário: ");
                conversor(n1, 2);

                printf("\nOctal: ");
                conversor(n1, 8);

                printf("\nHexadecimal: ");
                //conversorHexa(n1, 16);

                printf("\n\n");
                //sleep(5);
            break;
            case 'S':
                printf("\n%s", lin_sim);
                printc("Sistema Linear", 66);
                printf("\n%s\n", lin_sim);
                break;

            case 'E':
                printf("\n%s", lin_sim);
                printc("Equação Algébrica", 66);
                printf("\n%s\n", lin_sim);
                break;
            default:
                printf("Digite uma opção valida\n");
        }
    } while(op1);
}

int conversor(long double fraDecimal, int base)
{
	long double fraBinary,bFractional = 0.0,dFractional,fraFactor=0.1;
    long int dIntegral,bIntegral=0;
    long int intFactor=1,resto,temp,i;

    dIntegral = fraDecimal;
    dFractional =  fraDecimal - dIntegral;

    while(dIntegral!=0)
	{
         resto=dIntegral%base;
         bIntegral=bIntegral+resto*intFactor;
         dIntegral=dIntegral/base;
         intFactor=intFactor*10;
    }

   for(i=1;i<=2;i++)
   {
       dFractional = dFractional * base; 			// multiplica o valor fracionario pela base
       temp =  dFractional;							// armazena o numero inteiro da parte fracionária
       bFractional = bFractional + fraFactor* temp; //armazena os valores de temp
       if(temp ==1)
             dFractional = dFractional - temp;		// aumenta uma casa decimal a cada ciclo para armazenar os valores de temp
       fraFactor=fraFactor/10;
   }

   fraBinary =  bIntegral +  bFractional;
  printf("%Lf", fraBinary);
   return 0;
}
/*
int conversorHexa(long double fraDecimal, int base)
{
	long double fraBinary,bFractional = 0.0,dFractional,fraFactor=0.1;
    long int dIntegral,bIntegral=0;
    long int intFactor=1,resto,temp,i;

    dIntegral = fraDecimal;
    dFractional =  fraDecimal - dIntegral;

    while(dIntegral!=0)
	{
         resto=dIntegral%base;
         bIntegral=bIntegral+resto*intFactor;
         dIntegral=dIntegral/base;
         intFactor=intFactor*10;
    }

   for(i=1;i<=2;i++)
   {
       dFractional = dFractional * base; 			// multiplica o valor fracionario pela base
       temp =  dFractional;							// armazena o numero inteiro da parte fracionária
       bFractional = bFractional + fraFactor* temp; //armazena os valores de temp
       if(temp ==1)
             dFractional = dFractional - temp;		// aumenta uma casa decimal a cada ciclo para armazenar os valores de temp
       fraFactor=fraFactor/10;
   }

   fraBinary =  bIntegral +  bFractional;
   if(fraBinary > 10)
     printf("%x", fraBinary);
}
*/
