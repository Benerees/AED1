/*
  autor: Benjamim Rees Pereira do Nascimento
  problem: Pilha Pós Fixa
*/

/*
Enunciado:

Diremos que uma expressão posfixa simples é uma cadeia de caracteres (= string) de 
comprimento ≤ 99 cujos caracteres pertencem ao conjunto  '+', '*', '0', '1', . . . , '9'
(o caracter ' ' não faz parte do conjunto). Uma expressão posfixa simples representa
 uma expressão aritmética da maneira usual. Por exemplo,  "123*+"  representa a expressão
1 + (2*3) ,  cujo valor é  7.  Note que cada caracter numérico representa um número
entre 0 e 9;  assim, a sequência "23" representa o número 2 seguido do número 3,
e não o número 23.  Escreva uma função que receba uma expressão posfixa simples e 
devolva o valor da correspondente expressão aritmética.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
  float Valor;
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

int imprimePilha(PilhaDinamica Pilha){
  PNoh ptrAux = Pilha.topo;

  while(ptrAux!=NULL)
  {
    printf("%.2f",ptrAux->item.Valor);

    ptrAux = ptrAux->prox;
  }
}

void empilha(PilhaDinamica *Pilha, float Valor){
  PNoh novo;
  
  novo = (PNoh) malloc(sizeof(TipoNoh));

  if(novo != NULL)
  {
    novo->item.Valor = Valor; 
    
    if(pilhaVazia(*Pilha))
    {
      novo->prox = NULL;
      Pilha->topo = novo;
    }else{
      novo->prox = Pilha->topo;
      Pilha->topo = novo;
    }
  }
}

float desempilha(PilhaDinamica *Pilha){
  PNoh Aux = Pilha->topo;
  float Valor = Aux->item.Valor;

  Pilha->topo = Pilha->topo->prox;
  
  free(Aux);
  
  return Valor;
}

float resolveProblema(char *Expressao, PilhaDinamica *Pilha){
  int cont, Valor, n1, n2;

  for(cont = 0; cont < strlen(Expressao); cont++)
  {
    switch (Expressao[cont])
    {
      case '+': 
        n1 = desempilha(Pilha);
        n2 = desempilha(Pilha);

        empilha(Pilha, n1+n2);

        break;
      case '-':
        n1 = desempilha(Pilha);
        n2 = desempilha(Pilha);

        empilha(Pilha, n1-n2);

        break;
      case'*':
        n1 = desempilha(Pilha);
        n2 = desempilha(Pilha);

        empilha(Pilha, n1*n2);

        break;
      case'/':
        n1 = desempilha(Pilha);
        n2 = desempilha(Pilha);

        empilha(Pilha, n1/n2);

        break;
      default:
        Valor = (int)Expressao[cont]-'0';
        empilha(Pilha, (float)Valor);
    }
  }
  return 0;
}

void entrada(char *Expressao){
  char copia[100];

  printf("Escreva a expressão\n");
  
  fgets(Expressao, sizeof(copia), stdin);
  Expressao[strlen(Expressao) - 1] = '\0';
}

int main(void) {
  PilhaDinamica Pilha;
  TipoItem item;
  float Resultado;
  char Expressao[100];

  entrada(&Expressao);

  inicializaPilha(&Pilha);

  Resultado = resolveProblema(Expressao, &Pilha);
  
  imprimePilha(Pilha);
  
  return 0;
}
