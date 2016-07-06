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


short comparar(void*, void*); // compara as prioridades.
