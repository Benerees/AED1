/*
    autor: Benjamim Rees Pereira do Nascimento
    problem: Torre de Hanoi
*/

/*
Enunciado:

Torre de Hanói é um quebra-cabeça que consiste em uma base de três pinos, em um dos quais
são dispostos alguns discos uns sobre os outros, em ordem crescente de diâmetro, de cima para baixo.
O problema consiste em passar todos os discos do primeiro pino para o último pino, usando
o pino do meio como auxiliar, de maneira que um disco maior nunca fique sobre outro menor 
em nenhuma situação. A cada jogada, é possível passar apenas um disco do topo de um 
pino para outro pino. A sua tarefa é implementar um programa que avalia os resultados de 
sequências de jogadas nessa torre de hanói. Você deve implementar tipos e funções específicas
 de algum Tipo Abstrato de Dados (TAD) que pode ser utilizado para resolver o problema de forma eficiente.
Entrada: A entrada para cada teste se inicia com uma linha contendo os números inteiros N (0 ≤ N ≤ 10) 
de discos e M (0 ≤ M ≤ 2.000) de movimentos. Nas próximas M linhas são apresentados os números 
dos pinos po e pd ( 1 ≤ po , pd ≤ 3 )) de origem e de destino, respectivamente, de cada movimento.
Saída: Para cada caso de teste, imprima uma linha com um dos seguintes resultados: a) “Wrong move”, 
se houve algum movimento inválido; b) “Unfinished”, se o problema não foi resolvido por completo; e c) 
“Solved” se após todos os movimentos o problema foi resolvido, ou seja, todos os pinos foram movidos 
corretamente para o pino 3.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
  int Valor;
}TipoItem;

typedef  struct Noh{
  TipoItem item;
  struct Noh *prox;
}TipoNoh;

typedef TipoNoh *PNoh;

typedef struct{
  PNoh topo;
}PilhaDinamica;

void inicializaPilhas(PilhaDinamica *pilha){
  int cont;

  for(cont = 0; cont < 3; cont++)
    pilha[cont].topo = NULL;
}

int pilhaVazia(PilhaDinamica pilha){
  return pilha.topo == NULL;
}

void empilha(PilhaDinamica *Pilha, int Valor){
  PNoh novo;
  
  novo = (PNoh) malloc(sizeof(TipoNoh));
  if(novo != NULL)
  {
    novo->item.Valor = Valor; 

    if(pilhaVazia(*Pilha))
    {
      novo->prox = NULL;
      Pilha->topo = novo;
    }
    else
    {
      novo->prox = Pilha->topo;
      Pilha->topo = novo;
    }
  }
}

int desempilha(PilhaDinamica *Pilha){
  PNoh Aux = Pilha->topo;
  int Valor = Aux->item.Valor;

  Pilha->topo = Pilha->topo->prox;

  free(Aux);

  return Valor;
}

void montaTorre(int N, PilhaDinamica *Pilha){
  int cont;

  for(cont = N; cont > 0; cont--)
  {
    empilha(&Pilha[0], cont);
  }
}

int verificaValor(PNoh Topo){  
  return Topo->item.Valor;
}

int resolveProblema(PilhaDinamica *Pilha, int M){
  int cont, pilha1, pilha2, verifica = 0, numDesempilha, numTopo;

  for(cont = 0; cont < M; cont++)
  {
    scanf("%d %d", &pilha1, &pilha2);

    if(verifica == 0)
    {
      numDesempilha = desempilha(&Pilha[pilha1-1]);

      if(Pilha[pilha2-1].topo == NULL)
      {
         empilha(&Pilha[pilha2-1], numDesempilha);
      }
      else
      {
        numTopo = verificaValor(Pilha[pilha2-1].topo);

        if(numDesempilha > numTopo)
        {
          verifica = 1;
        }else
          empilha(&Pilha[pilha2-1], numDesempilha);
      }
    }
  }
  return verifica;
}

int main(void) {
  PilhaDinamica Pilha[3];
  int N, M, result;
  TipoItem item;
  int Resultado;


  scanf("%d %d", &N, &M);

  inicializaPilhas(Pilha);

  montaTorre(N, Pilha);

  result = resolveProblema(Pilha, M);

  if(result == 1)
  {
    printf("Wrong Move");
  }else
  {
    if(Pilha[0].topo != NULL || Pilha[1].topo != NULL)
    {
      printf("Unfinished");
    }
    else
    {
      printf("Solved");
    }
  }
  
  return 0;
}
