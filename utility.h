/***********************************************************************
 * 
 * utility.h | "Arquétipo de algumas funçoẽs úteis."
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


#ifndef UTILITY_H
#define UTILITY_H

bool has_dec(char *str);
bool has_func(char *str);
bool has_var(list *ls);
bd_type id_bd_tp(char ch);
ch_type id_ch_tp(char ch);
fn_type id_fn_tp(char *str);
char *int_str(int n);
int n_list(list *ls);
bool par_enclosed(char *str);
bool par_paired(char *str, int i);
list *rev_list(list *ls);
char *rm_par(char *str);
int str_int(char *str);
char *wo_space(char *str);

#endif
