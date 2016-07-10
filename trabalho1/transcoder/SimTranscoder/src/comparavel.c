#include "comparavel.h"

short comparar(void* a, void* b){
	TComparavel* A = a;
	TComparavel* B = b;
	return A->compara(A, B);
}
