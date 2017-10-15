/*
 * Processo responsável por tirar screenshots da tela do estado atual do 
 * da tabela pcb do process manager 
 */

#ifndef reporter_H
#define reporter_H

#include "pm.h"

/* Recebe Processos e seu respectivo estado.
 * estado == 0, em execução.
 * estado == 1, processo pronto para execução.
 * estado == 2, processo bloqueado.
 * legenda0 flag para indicar se precisa imprimir os cabeçaalhos da tabela.
 * legenda1 flag para indicar se precisa imprimer O tipo de estado.
*/

void showTable(Processo *p, int tempoAtual, sint legenda0, sint legenda1, sint legenda2);
#endif