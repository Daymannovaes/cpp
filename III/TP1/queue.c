#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * Essa implementação de fila pode ser encontrada
 * nos exemplos de implementação do livro do Nivio Ziviani
 * http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes.php
 *
 * Apenas os nomes das variáveis foram alterados
 * para atender uma melhor semântica do código
 */

void init_queue(Queue *queue) {
  queue->first = (CellPointer) malloc(sizeof(Cell));
  queue->last = queue->first;
  queue->first->next = NULL;
} 

int is_queue_empty(Queue queue) { 
  return (queue.first == queue.last);
} 

void do_queue(CellItem item, Queue *queue) {
  queue->last->next = (CellPointer) malloc(sizeof(Cell));
  queue->last = queue->last->next;
  queue->last->item = item;
  queue->last->next = NULL;
} 

void undo_queue(Queue *queue, CellItem *item) {
  CellPointer pointer;
  if (is_queue_empty(*queue)) { printf("Erro fila esta vazia\n"); return; }
  pointer = queue->first;
  queue->first = queue->first->next;
  *item = queue->first->item;
  free(pointer);
}