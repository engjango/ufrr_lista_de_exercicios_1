/***********************************************************************
 * 
 * utility.c | "Funções utilizadas no cálc. da derivada de uma função."
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
#include <string.h>
#include "struct.h"
#include "utility.h"

/* Determina se o parâmetro constante tem decimais à direita. */
bool has_dec(char *str) {
    if ((strpbrk(str, ".") != NULL) || (strpbrk(str, "/") != NULL) ||
        (strpbrk(str, "*") != NULL) || (strpbrk(str, "+") != NULL) ||
        (strpbrk(str, "-") != NULL) || (has_func(str))) {
        return true;
    } else {
        return false;
    }   
}

/* Determina se o parâmetro str contêm um função. */
bool has_func(char *str) {
    if ((strstr(str, "^") != NULL) || (strstr(str, "ln") != NULL) ||
        (strstr(str, "log") != NULL) || (strstr(str, "sen") != NULL) || 
        (strstr(str, "cos") != NULL) || (strstr(str, "tan") != NULL) || 
        (strstr(str, "csc") != NULL) || (strstr(str, "sec") != NULL) || 
        (strstr(str, "cot") != NULL) || (strstr(str, "senh") != NULL) || 
        (strstr(str, "cosh") != NULL) || (strstr(str, "tanh") != NULL) || 
        (strstr(str, "csch") != NULL) || (strstr(str, "sech") != NULL) || 
        (strstr(str, "coth") != NULL)) {
        return true;
    } else {
        return false;
    }
}

/* Determina se qualquer nó de uma lista contêm a variável x. */
bool has_var(list *ls) {
    list *ls_curr = ls; // não modificar lista original...
    while (ls_curr != NULL) {
        if (strpbrk(ls_curr->entry, "x") != NULL) {
            return true;
        }
        ls_curr = ls_curr->next;
    }
    return false;
}

/* Identifica o tipo de limite: implícito ou explícito. */
bd_type id_bd_tp(char ch) {
    if ((ch == '*') || (ch == '/')) {
        return ex_bd;
    } else {
        return im_bd;
    }
}

/* Identifica o tipo de caractere. */
ch_type id_ch_tp(char ch) {
    if ((ch >= '0') && (ch <= '9') || (ch == 'e')) {
        return pt_cst;
    } else if ((ch == '*') || (ch == '/')) {
        return pt_opr;
    } else if ((ch == '(') || (ch == ')')) {
        return pt_par;
    } else if ((ch == '+') || (ch == '-')) {
        return pt_sig;
    } else if (ch == 'x') {
        return pt_var;
    } else {
        return pt_fnc;
    }
}

/* Identifica o tipo da função mais externa. */
fn_type id_fn_tp(char *str) {
    char *str_cpy = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
    strcpy(str_cpy, str); // proíbe modificação da string original...

    while (par_enclosed(str_cpy)) {
        str_cpy = rm_par(str_cpy);
    }

    char *pt = strpbrk(str_cpy, "x");
    if (pt == NULL) {
        return cnst;
    }

    pt = strpbrk(str_cpy, "^");
    while (pt != NULL) {
        if (!par_paired(str_cpy, pt - str_cpy)) {
            pt = strpbrk(pt + 1, "^");
        } else {
            break;
        }
    }

    if (pt != NULL) {// há '^'
        if (strpbrk(pt, "x") != NULL) {// x aparece depois de '^'
            return expo;
        } else {// x aparece antes de '^'
            *pt = 0;

            if (id_ch_tp(str_cpy[0]) == pt_sig) {
                str_cpy++;
            }
            while (par_enclosed(str_cpy)) {// str truncada
                str_cpy = rm_par(str_cpy);
            }

            if (strpbrk(str_cpy, "x") == NULL) {// x não encontrado
                return cnst;
            } else if (((strcmp(str_cpy, "x") == 0) || (strcmp(str_cpy, "-x") == 0)) && 
                       ((strstr(pt + 1, "pi") == NULL) && (strpbrk(pt + 1, "e") == NULL)) &&
                       (strpbrk(pt + 1, ".*/+-") == NULL)) {
                return poly;
            } else {
                return powr;
            }
        }
    } else {// não há '^'
        while (par_enclosed(str_cpy)) {
            str_cpy = rm_par(str_cpy);
        }

        pt = strpbrk(str_cpy, "lsct");
        while (!par_paired(str_cpy, pt - str_cpy)) {
            pt = strpbrk(pt + 1, "lsct");
        }

        if (pt != NULL) {
            if ((strncmp(pt, "ln", 2) == 0) || (strncmp(pt, "log", 3) == 0)) {
                return loga;
            } else if ((strncmp(pt, "senh", 4) == 0) || (strncmp(pt, "cosh", 4) == 0) ||
                       (strncmp(pt, "tanh", 4) == 0) || (strncmp(pt, "csch", 4) == 0) ||
                       (strncmp(pt, "sech", 4) == 0) || (strncmp(pt, "coth", 4) == 0)) {
                return hypl;
            } else if ((strncmp(pt, "sen", 3) == 0) || (strncmp(pt, "cos", 3) == 0) ||
                       (strncmp(pt, "tan", 3) == 0) || (strncmp(pt, "csc", 3) == 0) ||
                       (strncmp(pt, "sec", 3) == 0) || (strncmp(pt, "cot", 3) == 0)) {
                return trig;
            }
        } else {
            return poly;
        }
    }
}

/* Converte um inteiro em uma string */
char *int_str(int n) {
    bool neg;
    if (n < 0) {
        neg = true;
        n *= -1;
    } else {
        neg = false;
    }

    char *pt;
    char *str = (char *) malloc(sizeof(char) * 128);
    if (neg) {
        strcpy(str, "-");
        pt = str + 1;
    } else {
        pt = str;
    }
    
    int fct = 0, val = 1;
    while (n >= val) {
        fct++;
        val *= 10;
    }
    fct--;
    val /= 10;

    char ch;
    while (fct >= 0) {
        ch = (n / val) + 48;
        n %= val;
        *pt = ch;
        pt++;
        fct--;
        val /= 10;
    }
    *pt = 0;

    return str;
}

/* Retorna o número de nós em uma lista conectada. */
int n_list(list* ls) {
    int n = 0;
    while (ls != NULL) {
        n++;
        ls = ls->next;
    }
    return n;
}

/* Examina se o str está fechado redundantemente por parênteses. */
bool par_enclosed(char *str) {
    if (str[0] == '(') {
        int len = strlen(str);
        if (str[len - 1] == ')') {
            int ind = 1, par = 1;
            while (ind < len) {
                if (str[ind] == '(') {
                    par++;
                } else if (str[ind] == ')') {
                    par--;
                }

                if ((par == 0) && (ind != (len - 1))) {
                    return false;
                }
                
                ind++;
            }
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/* Examina todos se todos os parênteses que aparecem até o índice 
 * estão emparelhados. */
bool par_paired(char *str, int i) {
    int par = 0;

    while (--i >= 0) {
        if (str[i] == '(') {
            par++;
        } else if (str[i] == ')') {
            par--;
        }
    }
    
    if (par == 0) {
        return true;
    } else {
        return false;
    }    
}

/* Cria uma nova lista que é o inverso do parâmetro. */
list *rev_list(list *ls) {
    list *rev_curr = NULL;

    while (ls != NULL) {
        list *rev = init_list();
        strcpy(rev->entry, ls->entry);

        if (rev_curr != NULL) {
            rev->next = rev_curr;
        }
        rev_curr = rev;

        ls = ls->next;
    }

    return rev_curr;
}

/* Remove um par de parênteses redundantes fechando a str. */
char *rm_par(char *str) {
    char *str_cpy = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
    strcpy(str_cpy, str);

    str_cpy[strlen(str_cpy) - 1] = 0;
    return str_cpy + 1;
}

/* Converte uma string em um inteiro. */
int str_int(char *str) {
    char *str_cpy = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
    strcpy(str_cpy, str);

    bool neg = false;
    if (str_cpy[0] == '-') {
        neg = true;
        str_cpy++;
    }

    int ind, fct = 1, n = 0, len = strlen(str_cpy);
    for (ind = (len - 1); ind >= 0; ind--) {
        n += ((str_cpy[ind] - 48) * fct);
        fct *= 10;
    }
    
    if (neg) {
        return (-1 * n);
    } else {
        return n;
    }
}

/* Remove todos os espaços em branco na str. */
char *wo_space(char *str) {
    int ind = 0, fill = 0, len = strlen(str);
    char *rt_str = (char *) malloc(sizeof(char) * MAX_CHAR);

    while (ind < len) {
        char ch;
        if ((ch = str[ind++]) != ' ') {
            rt_str[fill++] = ch;
        }
    }
    rt_str[fill] = 0;

    return rt_str;
}
