/*
 * comparavel.c
 *
 *  Created on: 27/06/2016
 *      Author: cesar
 */

typedef short(*TCompara)(void*, void*);
typedef struct {
	void *dado;
	TCompara compara;
}TComparavel;

// COMPARA AS PRIORIDADES:
// retorna 
// 	> 0 se 'a' tiver prioridade maior que 'b'
// 	< 0 se 'b' tiver prioridade maior que 'a'
// 	= 0 se 'a' e 'b' tiverem a mesma prioridade.
short comparar(void* a, void* b); 
