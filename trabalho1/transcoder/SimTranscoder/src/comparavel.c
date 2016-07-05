// comparavel.c
// Created by Micael Levi on 07/05/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.

#include "comparavel.h"

short comparar(void* a, void* b){
	TComparavel* A = a;
	TComparavel* B = b;
	return A->compara(A, B);
}
