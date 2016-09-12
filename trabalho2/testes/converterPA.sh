#!/bin/bash

##
##	[converterPA.sh]
##	Created by Micael Levi on 09/11/2016
##	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
##


gawk '
{ a[i++] = $0 }
END {
	pag=1
	for(j=0; j < i; ){
		if( gsub(/^PA/, "PAGINA:"pag"\n", a[j]) == 1) pag++
		print a[j++]
	}
}' "$1"
