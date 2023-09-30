/***********************************************************************
 * 
 * struct.c | "Inicialização de algumas variáveis structs."
 * 
 * Copyright 2015 J. G. Silva (django) <dparicarana@Gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 ***********************************************************************
 *  
 * UNIVERSIDADE FEDERAL DE RORAIMA
 * CENTRO DE CIÊNCIAS E TECNOLOGIA - CCT
 * DEPARTAMENTO DE CIÊNCIAS DA COMPUTAÇÃO - DCC
 * PROGRAMAÇÃO ESTRUTURADA
 * 
 * LISTA DE EXERCÍCIOS I
 * 
 * DOSCENTE:	Dion Ribeiro
 * DISCENTE: 	Janderson Gomes da Silva
 * MATRÍCULA: 	2201514716
 * DATA: 		10/12/2015
 * 
 **********************************************************************/

#include <stdlib.h>
#include "struct.h"

list *init_list() {
    list *ls = (list *) malloc(sizeof(list));
    ls->entry = (char *) malloc(sizeof(char) * (MAX_CHAR / 8));
    ls->next = NULL;

    return ls;
}

comp *init_comp() {
    comp *cp = (comp *) malloc(sizeof(comp));
    cp->elem = init_list();
    
    return cp;
}

term *init_term() {
    term *tm = (term *) malloc(sizeof(term));
    tm->segm = init_list();

    return tm;
}

block *init_block() {
    block *bl = (block *) malloc(sizeof(block));
    bl->mult = init_list();
    bl->divi = init_list();

    return bl;
}
