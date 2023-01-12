/*
  autor: Benjamim Rees Pereira do Nascimento
  problem: Sintaxe
*/

/*
Enunciado:

Em sintaxes de linguagens de programação são utilizados caracteres como parênteses, chaves
e colchetes para definição de expressões, contexto, etc, sendo que cada par desses caracteres
são utilizados seguindo uma ordem esperada, por exemplo, '(' utilizado antes de algum ')'. 
Podemos definir que para cada par de símbolos correspondentes, o símbolo que deve aparecer 
primeiro é um “símbolo esquerdo” e o símbolo que deve aparecer depois como um “símbolo direito”. 
Como em uma sequência de símbolos os pares correspondentes podem apresentar uma estrutura 
aninhada, então temos que, em uma sequência correta: i) o número de símbolos da esquerda deve
ser igual ao número de símbolos da direita; ii) todo símbolo da direita é precedido por um 
símbolo da esquerda correspondente, e iii) um símbolo da direita só pode fechar um símbolo 
da esquerda correspondente se este foi o último símbolo da esquerda aberto e que ainda 
não foi fechado. Para auxiliar no processo de desenvolvimento de compiladores de novas linguagens
de programação, você deve escrever um programa que, dada uma sequência de pares de símbolos
ordenados (esquerdo e direito), você deve avaliar se uma sequência de caracteres contendo apenas
esses símbolos, representa uma sequência aninhada correta desses símbolos. Você deve implementar
tipos e funções específicas de algum Tipo Abstrato de Dados (TAD) que pode ser utilizado para 
resolver o problema de forma eficiente. Entrada: A entrada para cada teste se inicia com uma 
linha contendo os números inteiros M (1 ≤ M ≤ 50) de pares de símbolos e N (1 ≤ N ≤ 100.000) de 
caracteres de uma sequência a ser avaliada. Nas próximas M linhas são apresentados os pares de 
símbolos a serem considerados, sendo um par de símbolos por linha na ordem símbolo esquerdo e 
símbolo direito, separados por um espaço em branco. Nas N linhas seguintes, é fornecida a sequência
de símbolos a ser avaliada, sendo um caractere por linha. Saída: Se a sequência de caracteres 
apresentada estiver correta, você deve imprimir “Correto”. Caso contrário, avaliando a sequência
do início ao fim, você deve imprimir uma mensagem informando a o tipo de erro da primeira posição
errada encontrada: i) “Simbolo direito nao esperado”, se algum símbolo direito foi encontrado 
sem que o símbolo esquerdo correspondente tenha sido o último símbolo esquerdo aberto anteriormente
e ainda não fechado; ii) “Simbolo esquerdo nao fechado”, se após todos os caracteres terem sido 
processados, não for encontrado um símbolo direito correspondente ao último símbolo esquerdo 
que foi aberto anteriormente e ainda não fechado.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
  char Valor[1];
  char Esquerda[1];
  char Direita[1];
}TipoItem;

typedef  struct Noh{
  TipoItem item;
  struct Noh *prox;
}TipoNoh;

typedef TipoNoh *PNoh;

typedef struct{
  PNoh topo;
}PilhaDinamica;

void inicializaPilha(PilhaDinamica *pilha){
  pilha->topo = NULL;
}

int pilhaVazia(PilhaDinamica pilha){
  return pilha.topo == NULL;
}

void empilha(PilhaDinamica *Pilha, TipoItem item, int tipo){
  PNoh novo;
  
  novo = (PNoh) malloc(sizeof(TipoNoh));

  if(novo != NULL)
  {
    novo->item = item;

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

TipoItem desempilha(PilhaDinamica *Pilha){
  PNoh Aux = Pilha->topo;
  TipoItem Retorno = Pilha->topo->item;

  Pilha->topo = Pilha->topo->prox;

  free(Aux);

  return Retorno;
}

TipoItem buscaItem(PilhaDinamica *Sintaxe, TipoItem item){
  PNoh Aux = Sintaxe->topo;
  
  while (Aux!=NULL)
  {
    if(Aux->item.Esquerda[0]==item.Valor[0])
      return Aux->item;

    Aux = Aux->prox;
  }
}

int buscaTipo(PilhaDinamica *Sintaxe, TipoItem item){
  PNoh Aux = Sintaxe->topo;

  while (Aux!=NULL)
  {
    if(Aux->item.Esquerda[0]==item.Valor[0])
      return 1;

    if(Aux->item.Direita[0] == item.Valor[0])
      return 2;

    Aux = Aux->prox;
  }
  return 3;
}

int recursiva(PilhaDinamica *Sintaxe,PNoh Expressao, PilhaDinamica *Verifica, int *num){
  TipoItem ItemDesempilha, ItemAux;

  if(Expressao->prox!=NULL)
    recursiva(Sintaxe, Expressao->prox, Verifica, num);
  
  switch(*num){
    case 0:
    switch (buscaTipo(Sintaxe, Expressao->item)){
      case 1:
        empilha(Verifica, Expressao->item, 2);
        break;
      case 2:
        if(pilhaVazia(*Verifica)!= 1)
        {
          ItemDesempilha = desempilha(Verifica);

          ItemAux = buscaItem(Sintaxe, ItemDesempilha);

          if(ItemAux.Direita[0] != Expressao->item.Valor[0])
          {
            printf("\n\n%c %c\n",ItemAux.Direita[0],Expressao->item.Valor[0]);
            
            *num = 1;
          }
        }
        else
        {
          *num = 1;
        }
        break;
      case 3:
          *num = 3;
        break;
    }
    return 0;

    case 1:
      return 1;

    case 2:
      break;

    case 3:
      return 3;
    
  }
    return -1;
  
}

int resolveProblema(PilhaDinamica *Sintaxe,PilhaDinamica *Expressao, PilhaDinamica *Verifica){
  int num=0, result;
  
  result = recursiva(Sintaxe,Expressao->topo, Verifica, &num);

  if(result == 0)
  {
    if(Verifica->topo != NULL)
      printf("Simbolo esquerdo nao fechado");
    else
      printf("Correto");
    return 0;
  }
  if(result == 1)
  {
    printf("Simbolo direito nao esperado");
    return 0;
  }
  if(result == 3){
    printf("Simbolo não esperado");
    return 0;
  }
  
  return 0;
}

void entradas(int M, int N, PilhaDinamica *Sintaxe, PilhaDinamica *Expressao){
  int cont;
  TipoItem item;

  for(cont = 0; cont < M; cont++)
  {
    getchar();
    scanf("%c %c", &item.Esquerda[0],&item.Direita[0]);

    empilha(Sintaxe, item, 1);
  }
  for(cont = 0; cont < N; cont++)
  {
    getchar();
    scanf("%c",&item.Valor[0]);

    empilha(Expressao, item, 2);
  }
}

int main(void) {
  int M,N, result;
  PilhaDinamica PilhaSintaxe, PilhaExpressao, PilhaVerifica;
  TipoItem item;

  scanf("%d %d", &M, &N);

  inicializaPilha(&PilhaSintaxe);
  inicializaPilha(&PilhaExpressao);
  inicializaPilha(&PilhaVerifica);

  entradas(M,N, &PilhaSintaxe, &PilhaExpressao);

  result = resolveProblema(&PilhaSintaxe, &PilhaExpressao, &PilhaVerifica);
  
  return 0;
}