/***********************************************************************
 * 
 * struct.h | "Alguns typedefs utilizados em algumas func. derivadas.
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

#ifndef STRUCT_H
#define STRUCT_H

#define MAX_CHAR 2048

typedef enum {false, true} bool;
typedef enum {im_bd, ex_bd} bd_type;
typedef enum {pt_cst, pt_fnc, pt_opr, pt_par, pt_sig, pt_var} ch_type;
typedef enum {cnst, expo, hypl, loga, poly, powr, trig} fn_type;

typedef struct list {
    char *entry;
    struct list *next;
} list;

typedef struct comp {
    struct list *elem;
} comp;

typedef struct term {
    struct list *segm;
} term;

typedef struct block {
    struct list *mult;
    struct list *divi;
} block;

list *init_list();
term *init_term();
comp *init_comp();
block *init_block();

#endif
