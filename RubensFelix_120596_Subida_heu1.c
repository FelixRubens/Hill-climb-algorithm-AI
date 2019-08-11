
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define TAM 3
#define MAX_FILHOS 4

typedef struct estado
{
    int heuristica;
    int heuristica2;
    int estado[TAM][TAM];
} Estado;


int verifica_pos_0(Estado *estado_inicial)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(estado_inicial->estado[i][j] == 0)
            {
                return count;
            }
            else
            {
                count ++;
            }
        }
    }
}

void calcula_fator_2(Estado* estado_atual){
  int aux;
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        aux = estado_atual->estado[i][j];

        switch (aux){

        case 1:
              estado_atual->heuristica2 += abs(i - 0) + abs(j - 1);
        break;

        case 2:
              estado_atual->heuristica2 += abs(i - 0) + abs(j - 2);
        break;

        case 3:
              estado_atual->heuristica2 += abs(i - 1) + abs(j - 0);
        break;

        case 4:
              estado_atual->heuristica2 += abs(i - 1) + abs(j - 1);
        break;

        case 5:
              estado_atual->heuristica2 += abs(i - 1) + abs(j - 2);
        break;

        case 6:
              estado_atual->heuristica2 += abs(i - 2) + abs(j - 0);
        break;

        case 7:
              estado_atual->heuristica2 += abs(i - 2) + abs(j - 1);
        break;

        case 8:
              estado_atual->heuristica2 += abs(i - 2) + abs(j - 2);
        break;

        default:

        break;
        }
      }
    }
}

void calcula_fator(Estado* estado_atual)
{

    int fator = 0;
    if(estado_atual->estado[0][1] != 1)
        fator++;
    if(estado_atual->estado[0][2] != 2)
        fator++;
    if(estado_atual->estado[1][0] != 3)
        fator++;
    if(estado_atual->estado[1][1] != 4)
        fator++;
    if(estado_atual->estado[1][2] != 5)
        fator++;
    if(estado_atual->estado[2][0] != 6)
        fator++;
    if(estado_atual->estado[2][1] != 7)
        fator++;
    if(estado_atual->estado[2][2] != 8)
        fator++;

    estado_atual->heuristica = fator;
}

bool comparador_matriarcal(Estado* estado_atual, int proximo_estado[3][3])
{
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(estado_atual->estado[i][j] != proximo_estado[i][j])
            {
                flag++;
            }
        }
    }
    if(!flag)
        return true;
    else
        return false;
}

Estado* busca_estado(Estado *estado_inicial)
{

    int estado_final[TAM][TAM];

    estado_final[0][0] = 0;
    estado_final[0][1] = 1;
    estado_final[0][2] = 2;
    estado_final[1][0] = 3;
    estado_final[1][1] = 4;
    estado_final[1][2] = 5;
    estado_final[2][0] = 6;
    estado_final[2][1] = 7;
    estado_final[2][2] = 8;

    if(comparador_matriarcal(estado_inicial, estado_final))
    {
        return estado_inicial;
    }

    int aux = verifica_pos_0(estado_inicial);

    Estado** vet_in = malloc(4*sizeof(Estado));

    Estado *proximo_estado1 = malloc(sizeof(Estado));
    proximo_estado1->heuristica = -1;
    Estado *proximo_estado2 = malloc(sizeof(Estado));
    proximo_estado2->heuristica = -1;
    Estado *proximo_estado3 = malloc(sizeof(Estado));
    proximo_estado3->heuristica = -1;
    Estado *proximo_estado4 = malloc(sizeof(Estado));
    proximo_estado4->heuristica = -1;

    int aux2;
    switch (aux)
    {
    case 0:

        //printf("\n");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
            }
        }

        aux2 = proximo_estado1->estado[0][0];
        proximo_estado1->estado[0][0] = estado_inicial->estado[0][1];
        proximo_estado1->estado[0][1] = aux2;
        calcula_fator(proximo_estado1);

        aux2 = proximo_estado2->estado[0][0];
        proximo_estado2->estado[0][0] = estado_inicial->estado[1][0];
        proximo_estado2->estado[1][0] = aux2;
        calcula_fator(proximo_estado2);

        break;

    case 1:

        //printf("\n");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado3->estado[i][j] = estado_inicial->estado[i][j];
            }
        }


        aux2 = proximo_estado1->estado[0][0];
        proximo_estado1->estado[0][0] = 0;
        proximo_estado1->estado[0][1] = aux2;
        calcula_fator(proximo_estado1);


        aux2 = proximo_estado2->estado[0][2];
        proximo_estado2->estado[0][2] = 0;
        proximo_estado2->estado[0][1] = aux2;
        calcula_fator(proximo_estado2);


        aux2 = proximo_estado3->estado[1][1];
        proximo_estado3->estado[1][1] = 0;
        proximo_estado3->estado[0][1] = aux2;
        calcula_fator(proximo_estado3);

        break;

    case 2:

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
            }
        }

        aux2 = proximo_estado1->estado[0][1];
        proximo_estado1->estado[0][1] = estado_inicial->estado[0][2];
        proximo_estado1->estado[0][2] = aux2;
        calcula_fator(proximo_estado1);


        aux2 = proximo_estado2->estado[1][2];
        proximo_estado2->estado[1][2] = estado_inicial->estado[0][2];
        proximo_estado2->estado[0][2] = aux2;
        calcula_fator(proximo_estado2);


        break;

    case 3:

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado3->estado[i][j] = estado_inicial->estado[i][j];
            }
        }

        aux2 = proximo_estado1->estado[0][0];
        proximo_estado1->estado[0][0] = 0;
        proximo_estado1->estado[1][0] = aux2;
        calcula_fator(proximo_estado1);


        aux2 = proximo_estado2->estado[1][1];
        proximo_estado2->estado[1][1] = 0;
        proximo_estado2->estado[1][0] = aux2;
        calcula_fator(proximo_estado2);

        aux2 = proximo_estado3->estado[2][0];
        proximo_estado3->estado[2][0] = 0;
        proximo_estado3->estado[1][0] = aux2;
        calcula_fator(proximo_estado3);


        break;

    case 4:

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado3->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado4->estado[i][j] = estado_inicial->estado[i][j];
            }
        }

        aux2 = proximo_estado1->estado[0][1];
        proximo_estado1->estado[0][1] = 0;
        proximo_estado1->estado[1][1] = aux2;
        calcula_fator(proximo_estado1);

        aux2 = proximo_estado2->estado[1][0];
        proximo_estado2->estado[1][0] = 0;
        proximo_estado2->estado[1][1] = aux2;
        calcula_fator(proximo_estado2);

        aux2 = proximo_estado3->estado[1][2];
        proximo_estado3->estado[1][2] = 0;
        proximo_estado3->estado[1][1] = aux2;
        calcula_fator(proximo_estado3);


        aux2 = proximo_estado4->estado[2][1];
        proximo_estado4->estado[2][1] = 0;
        proximo_estado4->estado[1][1] = aux2;
        calcula_fator(proximo_estado4);

        break;

    case 5:

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado3->estado[i][j] = estado_inicial->estado[i][j];
            }
        }

        aux2 = proximo_estado1->estado[0][2];
        proximo_estado1->estado[0][2] = 0;
        proximo_estado1->estado[1][2] = aux2;
        calcula_fator(proximo_estado1);


        aux2 = proximo_estado2->estado[1][1];
        proximo_estado2->estado[1][1] = 0;
        proximo_estado2->estado[1][2] = aux2;
        calcula_fator(proximo_estado2);


        aux2 = proximo_estado3->estado[2][2];
        proximo_estado3->estado[2][2] = 0;
        proximo_estado3->estado[1][2] = aux2;
        calcula_fator(proximo_estado3);

        break;

    case 6:

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
            }
        }

        aux2 = proximo_estado1->estado[1][0];
        proximo_estado1->estado[1][0] = 0;
        proximo_estado1->estado[2][0] = aux2;
        calcula_fator(proximo_estado1);

        aux2 = proximo_estado2->estado[2][1];
        proximo_estado2->estado[2][1] = 0;
        proximo_estado2->estado[2][0] = aux2;
        calcula_fator(proximo_estado2);

        break;

    case 7:


        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado3->estado[i][j] = estado_inicial->estado[i][j];
            }
        }


        aux2 = proximo_estado1->estado[1][1];
        proximo_estado1->estado[1][1] = 0;
        proximo_estado1->estado[2][1] = aux2;
        calcula_fator(proximo_estado1);


        aux2 = proximo_estado2->estado[2][0];
        proximo_estado2->estado[2][0] = 0;
        proximo_estado2->estado[2][1] = aux2;
        calcula_fator(proximo_estado2);


        aux2 = proximo_estado3->estado[2][2];
        proximo_estado3->estado[2][2] = 0;
        proximo_estado3->estado[2][1] = aux2;
        calcula_fator(proximo_estado3);



        break;

    case 8:


        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                proximo_estado1->estado[i][j] = estado_inicial->estado[i][j];
                proximo_estado2->estado[i][j] = estado_inicial->estado[i][j];
            }
        }

        aux2 = proximo_estado1->estado[1][2];
        proximo_estado1->estado[1][2] = 0;
        proximo_estado1->estado[2][2] = aux2;
        calcula_fator(proximo_estado1);


        aux2 = proximo_estado2->estado[2][1];
        proximo_estado2->estado[2][1] = 0;
        proximo_estado2->estado[2][2] = aux2;
        calcula_fator(proximo_estado2);


        break;
    }

    vet_in[0] = proximo_estado1;
    vet_in[1] = proximo_estado2;
    vet_in[2] = proximo_estado3;
    vet_in[3] = proximo_estado4;
    int menor = vet_in[0]->heuristica;
    int indice = 0;
    int flag = 0;

    for(int i = 1; i < 4; i++)
    {
        if(menor > vet_in[i]->heuristica && vet_in[i]->heuristica != -1)
        {
            menor = vet_in[i]->heuristica;
            indice = i;
            flag++;
        }
    }

    if(estado_inicial->heuristica > menor)
        return vet_in[indice];
    else
    {
        vet_in[indice]->heuristica = -2;
        return vet_in[indice];
    }
}

int main()
{

    Estado *estado_inicial = malloc(sizeof(Estado));
    Estado *aux;
    int flag = 0;
    int menor,indice;
    int estado_final[TAM][TAM];
    int contador, estado_finais;
    estado_final[0][0] = 0;
    estado_final[0][1] = 1;
    estado_final[0][2] = 2;
    estado_final[1][0] = 3;
    estado_final[1][1] = 4;
    estado_final[1][2] = 5;
    estado_final[2][0] = 6;
    estado_final[2][1] = 7;
    estado_final[2][2] = 8;
    srand((int)time(NULL));

  for(contador = 0; contador < 100000; contador++){
              int vet[9] = {0,1,2,3,4,5,6,7,8};
              int r;
              int k = 0;
              int temp;

              for (int i = 0; i < 9; i++)
          	{
          		r = rand() % 9;
          		temp = vet[i];
          		vet[i] = vet[r];
          		vet[r] = temp;
          	}

              for (int i = 0; i < 3; i++)
              {
                  for (int j = 0; j < 3; j++)
                  {
                      estado_inicial->estado[i][j] = vet[k];
                      k++;
                  }
              }

              estado_inicial->heuristica = 0;
              calcula_fator(estado_inicial);
              do {
                  aux = busca_estado(estado_inicial);
                  if(comparador_matriarcal(aux, estado_final))
                  {
                      estado_finais++;
                      break;
                  }
                  estado_inicial = aux;
              }
              while (aux->heuristica != -2);
  }
  printf("%d\n", estado_finais);
    return 0;
}
