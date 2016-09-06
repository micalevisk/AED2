//
//	[wordToInt.c]
//	Created by Micael Levi on 08/05/2016
//	Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "wordToInt.h"

/*
// ideal caso existam palavras com as mesmas letras
unsigned long converterParaNumero(void* str){
	TElemento* _str = str;
	if(!_str) return 0;
	char* STR = _str->palavra;
	if(!STR) return 0;

	unsigned long h = STR[0];
	int i;
	for(i=1; STR[i]!='\0'; ++i) h = (h * 251 + STR[i]);
	return h;
}
*/

unsigned long converterParaNumero(void *elemento){
	TElemento* E = elemento;
	if(!E) return 0;
	char* str = E->palavra;
	unsigned long hash = 5381;
	int c;
	while(c = *str++)
		hash = ((hash << 5) + hash) + c; // = hash * 33 + c
	return hash;
}
