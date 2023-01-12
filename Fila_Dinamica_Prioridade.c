/*
  autor: Benjamim Rees Pereira do Nascimento
  problem: Fila Dinâmica com prioridade
*/

/*
  Retira primeiro os com prioridade pra depois seguir retirando os sem prioridade
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int senha;
  int prioridade;
  char nome[30];
} TipoItem;

typedef struct tipoNoh{
  TipoItem item;
  struct tipoNoh *prox;
} TipoNoh;

typedef TipoNoh *PNoh;

typedef struct {
  PNoh inicio, fim;
} TipoFilaD;

void inicializaFila(TipoFilaD *fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
}

void imprimeMenu() {
  printf("\nMenu");
  printf("\n1 - Gerar senha normal");
  printf("\n2 - Retira da fila");
  printf("\n3 - Imprime fila");
  printf("\n4 - Gerar senha prioritaria");
  printf("\n5 - Sair");
}

void leDadosItem(TipoItem *item, int *senha) {
  getchar();
  printf("\nNome: ");
  fgets(item->nome, sizeof(item->nome), stdin);
  item->nome[strlen(item->nome) - 1] = '\0';
  
  item->senha = *senha;

  (*senha)++;
}

int filaVazia(TipoFilaD *fila){
  return fila->inicio==NULL;
}

int buscarNaFila(PNoh aux, PNoh* aux2){
  int ver = 0;
 
  while(ver == 0 && aux != NULL)
  {
    if(aux->item.prioridade == 0)
       ver = 1;
    else
    {
      if(aux->prox == NULL)
        ver = 2;
      else
      {
        *aux2 = aux;
        aux = aux->prox;      
      }
    } 
  }

  if(ver == 1 && aux == *aux2)
  {
    return 1;
  }

  if(ver == 2)
  {
    return 2;
  }
  else{ 
    return 3;
  }
}

void imprimeItem(TipoItem item){
  printf("senha:%i cliente:%s\n",item.senha,item.nome);
}

int imprimeFila(TipoFilaD *fila){
  TipoNoh *ptrAux;

  if(!filaVazia(fila))
  {
    ptrAux = fila->inicio;

    while(ptrAux!=NULL)
    {
      imprimeItem(ptrAux->item);
      ptrAux = ptrAux->prox;
    }

    return 1;
  }
  return 0;
}

int insereNaFila(TipoFilaD *fila, TipoItem item) {
  PNoh novo, aux, aux2;
  int verifica;

  novo = (PNoh)malloc(sizeof(TipoNoh));

  if (novo != NULL) 
  {
    novo->item = item;
    novo->prox = NULL;

    if(filaVazia(fila))
    {
      fila->inicio = novo;
      fila->fim = novo;
    }else
    {
      if(item.prioridade == 1)
      {       
        aux = fila->inicio;
        aux2 = fila->inicio;

        verifica = buscarNaFila(aux, &aux2);

        switch(verifica)
        {
          case 1:
            novo->prox = fila->inicio; 
            fila->inicio = novo;
            break;
          case 2:
            fila->fim->prox = novo; 
            fila->fim = novo;
            break;
          case 3:
            novo->prox = aux2->prox;
            aux2->prox = novo;
            break;
        }        
      }
      else
      {
        fila->fim->prox = novo; 
        fila->fim = novo;
      }
    }
    return 1;
  }else
    return 0;
}

int retiraDaFila(TipoFilaD *fila,TipoItem *item){
  TipoNoh *ptrAux;

  if(!filaVazia(fila))
  {
    ptrAux = fila->inicio;
    *item = ptrAux->item;

    if(fila->inicio==fila->fim)
    {
      fila->inicio = NULL;
      fila->fim = NULL;
    }
    else
    {
      fila->inicio = ptrAux->prox;
    }
    free(ptrAux);

    return 1;
  }
  return 0;
}

int main() {
  TipoFilaD fila;
  TipoItem item;
  int op = 0, i, senha=1;

  inicializaFila(&fila);

  do {
    imprimeMenu();

    printf("\nOpção: ");
    scanf("%i", &op);

    switch (op) {
    case 1:
      leDadosItem(&item, &senha);

      item.prioridade = 0;

      if (insereNaFila(&fila, item))
        printf("\nSenha gerada com sucesso!\n");
      else
        printf("\nErro! Não foi possível gerar a senha!\n");

      break;
    case 2:
      if (retiraDaFila(&fila, &item)) 
      {
        printf("\nCliente atendido com sucesso!");
        printf("\nCliente: %s Senha: %d\n",item.nome, item.senha );
      } 
      else{
        printf("\nErro! Não foi possível atender o cliente!\n");
      }
      break;
    case 3:
      if (!filaVazia(&fila)) 
      {
        printf("\nFila:\n");
        imprimeFila(&fila);
      } 
      else{
        printf("\nFila Vazia!\n");
      }
      break;
    
    case 4:
      leDadosItem(&item, &senha);

      item.prioridade = 1;

      if (insereNaFila(&fila, item))
        printf("\nSenha gerada com sucesso!\n");
      else
        printf("\nErro! Não foi possível gerar a senha!\n");

      break;
    }
  }while (op != 5);

  return 0;
}