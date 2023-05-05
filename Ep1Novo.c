#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>


//============================== METODOS DE AUXILIO =================================

 typedef struct {
    int tam;
    double** matriz;
} MatrizSistemaLinear;

double** .alocarMatriz(int l, int c){
    int i, j;
    double **m;
    m = malloc(sizeof(double*) * l);
    if(m == NULL)
        return NULL;
    for(i=0;i<l;i++){
        m[i] = malloc(sizeof(double)*c);
        if(m[i] == NULL){
            for (j = 0; j < i; j++)
                free(m[j]);
            free(m);
            return NULL;
        }
    }
    return m;
}

double* alocarVetor(int c){
    double *m;
    m = malloc(sizeof(double) * c);
    if(m == NULL)
        return NULL;
    return m;
}

void mostrarMatriz(double **m, int l, int c){
    int i;
    int j;
    for(i=0; i < l; i++){
        for (j = 0; j < c; j++){
            printf("%9.3lf \n", m[i][j]);
        }
        printf("\n");
    }
}

void RecebeLagrange(double **m, int l, int c){
    int i = 0, j;
    do {
        printf("Digite A%d : ", c-i-1);
        scanf(" %lf", &m[0][0]);
        if(m[0][0] <= 0)
            printf("Valor deve ser positivo e nao-nulo.\n", c-i-1);
    } while(m[0][0] <= 0);

    for (i = 1; i < c-1; i++){
        printf("Digite A%d: ", c-i-1);
        scanf(" %lf", &m[0][i]);
    }

    do {
        printf("Digite A%d : ", 0);
        scanf(" %lf", &m[0][c-1]);
        if(m[0][c-1] == 0)
            printf("Valor deve ser diferente de 0.\n");
    } while(m[0][c-1] == 0);

    m[0][c] = 0; m[0][c+1] = 0;

    for(i=1; i < l; i++){
        for(j=0; j<c+2; j++) {
            m[i][j] = 0;
        }
    }
    mostrarMatriz(m,l,c);
}

MatrizSistemaLinear* lerArquivo(){
    int  n, i, j;
    double **matrix;
    char Arquivo[20];
    FILE *fp;

    printf("Digite o nome do arquivo: ");
    scanf(" %s", Arquivo);
    fp = fopen(Arquivo, "r");

    if(fp == NULL){
        printf("O arquivo nao existe.\n");
        return NULL;
    }
    fscanf(fp, " %d", &n);

    matrix = .alocarMatriz(n, n+1);

    for (i = 0; i < n; i++){
        for (j = 0; j < n + 1; j++){
            fscanf(fp, " %lf", &matrix[i][j]);
        }
    }
    fclose(fp);
    MatrizSistemaLinear* mSL = (MatrizSistemaLinear*)malloc(sizeof(MatrizSistemaLinear));;

    if(mSL == NULL)
        return NULL;
    mSL->matriz = matrix;
    mSL->tam = n;

    return mSL;
}
//============================== METODOS DE AUXILIO =================================




//============================ CONFIGURACAO DO MENU ============================


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

//============================ CONFIGURACAO DO MENU ============================//


//============================ METODO DE LAGRANGE ============================//
int perguntaGrauEquacao() {
    int grauEq;
    do {
        printf("Digite grau da equação: ");
        scanf(" %d", &grauEq);
        printf("\n");
    } while(grauEq < 0);
    return grauEq;
}

void metodoLagrange() {
    int i, j;
    int mTam  = perguntaGrauEquacao() + 1;
    double** ml = .alocarMatriz(4, mTam + 2);
    double* limites = alocarVetor(4);

    RecebeLagrange(ml, 1, mTam);

    for(i=0; i<mTam; i++) {
        ml[1][mTam-1-i] = ml[0][i];
        ml[2][i] = i%2==0 ? ml[0][i] : -1*ml[0][i];
        ml[3][mTam-1-i] = i%2==0 ? ml[0][i] : -1*ml[0][i];
    }

    mostrarMatriz(ml, 4, mTam);

    //calculando o k e b respectivamente
    for(j=0; j<4; j++) {
        for(i=0; i<mTam; i++) {
            ml[j][mTam] = ((ml[j][i] < 0) && ((mTam-i-1) > ml[j][mTam])) ? (mTam-i-1) : ml[j][mTam];
            ml[j][mTam+1] = (ml[j][i] < ml[j][mTam+1]) ? ml[j][i] : ml[j][mTam+1];
        }

        ml[j][mTam+1] = fabs(ml[j][mTam+1]);
    }

    //calculando os limites
    for(i=0; i<4; i++) {
        limites[i] = (1.0 + pow(ml[i][mTam+1]/ml[i][0], 1.0/(mTam-1-ml[i][mTam]))) * (i<2 ? 1 : -1);
    }

    printf("Os limites para a equacao sao:\n");
    printf("Superiores: %.4f  <= x <=  %.4f\n", 1.0/limites[1], limites[0]);
    printf("Inferiores: %.4f <= x <= %.4f\n", limites[2], 1.0/limites[3]);
}
//============================ METODO DE LAGRANGE ============================//




//============================ METODO DE GAUSS-SEIDEL ============================//


//retorna 1 para bem condicionada. -1 para mal condicionada
int CriterioLinhasEColunas(double** m) {
    int nVariaveis = 3, i, j;
    double pivo, somaLinha, somaColuna;

    for (i = 0; i < nVariaveis; i++){
        somaLinha = 0.0;
        somaColuna = 0.0;
        pivo = fabs(m[i][i]);

        for (j = 0; j < nVariaveis; j++){
            if (i != j){
                somaLinha = somaLinha + fabs(m[i][j]);
                somaColuna = somaColuna + fabs(m[j][i]);
            }

            if (somaLinha > pivo || somaColuna > pivo)
                return -1;
        }
    }
    return 1;
}
/*
*   @brief
*   @params
*/
void GaussSeidel() {
    MatrizSistemaLinear* mSL = lerArquivo();

    if(mSL == NULL) {
        printf("Houve um erro ao ler a matriz ou o arquivo.\n");
        return;
    }

    double** m = mSL->matriz;

    if (CriterioLinhasEColunas(m) == -1) {
        printf("\nMatriz não satisfaz criterio das linhas e colunas\n");
        return;
    }
    //verificar condicionamento
    double divisor, valorLinha;
    int i, j, h = 0;
    int nVariaveis = mSL->tam;
    double valores[nVariaveis];
    double valoresAnteriores[nVariaveis];

    for(i=0;i<nVariaveis;i++){
        valores[i] = 0.0;
        valoresAnteriores[i] = 0.0;
    }

    int DifMinima = 0;
    while (h<1000 && DifMinima == 0){
        for(i=0; i<nVariaveis; i++) {
              = 0.0;
            divisor = m[i][i];
            for(j=0; j<nVariaveis; j++){
                if(i!=j) {
                    valorLinha = valorLinha - (valores[j] * m[i][j]);
                }
            }

            valores[i] = (valorLinha + m[i][nVariaveis])/divisor;
        }
        printf("%d\n", h);
        DifMinima = 1;

        for(i=0; i<nVariaveis; i++) {
            DifMinima = (fabs(valoresAnteriores[i]-valores[i]) < 0.00000001) && (DifMinima == 1) ? 1 : 0;
            valoresAnteriores[i] = valores[i];
        }
        h++;
    }

    printf("Quantidade de iteracoes: %d\n", h);
    printf("Solucao:\n");
    for(i=0;i<nVariaveis;i++){
        printf("x%d: %f\n", i+1, valores[i]);
    }

    printf("\n");
}




//============================== METODOS DE CONVERSAO =================================

/*
*   @brief  método para checar os valores quando for imprimir
*           na base hexxadecimal.
*   @params value, valor a ser verificado. Se for entre 10 - 15,imprime
*           a respectiva letra, caso nao, imprime o proprio valor.*/
void checkValue(int value){
  switch (value){
    case 10: printf("A");
      break;
    case 11: printf("B");
      break;
    case 12: printf("C");
      break;
    case 13: printf("D");
      break;
    case 14: printf("E");
      break;
    case 15: printf("F");
      break;
    default: printf("%d", value);
      break;
  }
}

/*
*   @brief  converte de decimal para binário
*   @params i, valor da parte inteira do decimal.
*           f, valor da parte fracionária do decimal.
*/
void convertBin(int i, double f){
    int res_int[10], index_int = 0, index_frac = 0;
    double f_aux = f,  res_fra[20];

    while(i >= 2){
      res_int[index_int] = i%2;
      i = (i - i%2)/2;
      index_int++;
    }
    res_int[index_int] = i;

    while(f_aux > 0 && index_frac < 20){
      double k;
      f_aux = modf(f_aux * 2, &k);
      res_fra[index_frac] = k;
      index_frac++;
    }
    // Mostrar valores convertidos
    printf("Binário: ");
    for(i=index_int; i>=0; i--)
      printf("%d", res_int[i]);
    if(f > 0){
      printf(".");
      for(i=0; i<index_frac; i++)
        printf("%d", (int)res_fra[i]);
    }
    printf("\n");
}

/*
*   @brief  converte de decimal para hexadecimal.
*   @params i, valor da parte inteira do decimal.
*           f, valor da parte fracionária do decimal.
*/
void convertHex(int i, double f){
  int res_int[10], index_int = 0, index_frac = 0;
  double f_aux = f,res_fra[20];

  while(i >= 16){
    res_int[index_int] = i%16;
    i = (i - i%16)/16;
    index_int++;
  }
  res_int[index_int] = i;

  while(f_aux > 0 && index_frac < 20){
    double k;
    f_aux = modf(f_aux * 16, &k);
    res_fra[index_frac] = k;
    index_frac++;
  }
  // Mostrar valores convertidos
  printf("Hexadecimal: ");
  for(i=index_int; i>=0; i--)
    checkValue(res_int[i]);
  if(f > 0){
    printf(".");
    for(i=0; i<index_frac; i++)
      checkValue((int)res_fra[i]);
  }
  printf("\n");
}

/*
*   @brief  converte de decimal para octadecimal.
*   @params i, valor da parte inteira do decimal.
*           f, valor da parte fracionária do decimal.
*/
void convertOct(int i, double f){
  int res_int[10], index_int = 0, index_frac = 0;
  double f_aux = f, res_fra[20];

  while(i >= 8){
    res_int[index_int] = i%8;
    i = (i - i%8)/8;
    index_int++;
  }
  res_int[index_int] = i;

  while(f_aux > 0 && index_frac < 20){
    double k;
    f_aux = modf(f_aux * 8, &k);
    res_fra[index_frac] = k;
    index_frac++;
  }
  // Mostrar valores convertidos
  printf("Octadecimal: ");
  for(i=index_int; i>=0; i--)
    printf("%d", res_int[i]);
  if(f > 0){
    printf(".");
    for(i=0; i<index_frac; i++)
      printf("%d",(int)res_fra[i]);
  }
  printf("\n");
}

//============================== METODOS DE CONVERSAO =================================




int main()
{
    setlocale(LC_ALL, "");
    char op1, op2;
    double value, intpart, fracpart;

    do
    {
        menu_principal();
        fflush(stdin);
        op1 = getchar();
        system("cls || clear");

        if (op1 == 'f' || op1 == 'F')
        {
            printf("\n  ** Fim **");
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

                scanf(" %lf", &value);
                fracpart = modf(value, &intpart);
                convertBin(intpart, fracpart);
                convertOct(intpart, fracpart);
                convertHex(intpart, fracpart);

                printf("\n\n");
                //sleep(5);
            break;
            case 'S':
                printf("\n%s", lin_sim);
                printc("Sistema Linear", 66);
                printf("\n%s\n", lin_sim);
                GaussSeidel();
                break;

            case 'E':
                printf("\n%s", lin_sim);
                printc("Equação Algébrica", 66);
                printf("\n%s\n", lin_sim);
                metodoLagrange();
                break;
            default:
                printf("Digite uma opção valida\n");
        }
    } while(op1);
}
