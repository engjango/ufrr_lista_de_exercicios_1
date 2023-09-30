/***********************************************************************
 * 
 * simplify.c | "Funções pertencentes às simplificações matemáticas."
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
#include "parse.h"
#include "struct.h"
#include "simplify.h"
#include "utility.h"

char *simp_input(char *str) {
    char *str_cpy = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
    strcpy(str_cpy, str);

    /* inicia removendo os parênteses fechados */
    while (par_enclosed(str_cpy)) {
        str_cpy = rm_par(str_cpy);
    }

    fn_type fn_tp = id_fn_tp(str_cpy);
    int num_tm = n_term(str_cpy), num_bl = n_block(str_cpy);
    char *rt_str = (char *) malloc(sizeof(char) * MAX_CHAR);

    if ((num_tm == 1) && (num_bl == 1)) {
        if (is_composite(str_cpy)) {
            comp *cp = into_comp(str_cpy);
            list *rev = rev_list(cp->elem);

            size_t len;
            char *pt;
            char *temp_1 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            char *temp_2 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            char *temp_3 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            strcpy(temp_1, rev->entry);

            if ((n_term(rev->entry) != 1) || (n_block(rev->entry) != 1)) {
                temp_1 = simp_input(rev->entry);
            } else {
                pt = strpbrk(temp_1, "^");
                while (!par_paired(temp_1, pt - temp_1)) {
                    pt = strpbrk(pt + 1, "^");
                }

                if (pt != NULL) {
                    char *bef = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
                    char *aft = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
                
                    *(pt++) = 0;
                    strcpy(bef, temp_1);
                    strcpy(aft, pt);

                    bef = simp_input(bef);
                    aft = simp_input(aft);

                    strcpy(temp_1, "");
                    if ((n_term(bef) != 1) || (n_block(bef) != 1)) {
                        strcat(temp_1, "(");
                        strcat(temp_1, bef);
                        strcat(temp_1, ")");
                    } else {
                        strcat(temp_1, bef);
                    }
                    strcat(temp_1, "^");
                    if ((n_term(aft) != 1) || (n_block(aft) != 1)) {
                        strcat(temp_1, "(");
                        strcat(temp_1, aft);
                        strcat(temp_1, ")");
                    } else {
                        strcat(temp_1, aft);
                    }
                } else {
                    pt = strpbrk(temp_1, "x");
                    while (((*(pt - 1) == '(') && (*(pt + 1) == ')')) &&
                           ((*(pt - 2) == '(') && (*(pt + 2) == ')'))) {
                        strcpy(pt - 1, pt);
                        strcpy(pt + 1, pt + 2);

                        pt = strpbrk(temp_1, "x");
                    }
                }
            }

            while (rev->next != NULL) {
                while (par_enclosed(rev->entry)) {
                    rev->entry = rm_par(rev->entry);
                }

                len = strlen(rev->entry);
                pt = strstr(rev->next->entry, rev->entry);

                strncpy(temp_2, rev->next->entry, pt - rev->next->entry);
                temp_2[pt - rev->next->entry] = 0;

                strcpy(temp_3, pt + len);
                strcat(temp_2, temp_1);
                strcat(temp_2, temp_3);

                len = strlen(temp_1);
                pt = strstr(temp_2, temp_1);
                while (((*(pt - 1) == '(') && (*(pt + len) == ')')) &&
                       ((*(pt - 2) == '(') && (*(pt + len + 1) == ')'))) {
                    strcpy(pt - 1, pt);
                    strcpy(pt + len, pt + len + 1);

                    pt = strstr(temp_2, temp_1);
                }

                bool exp_bef = false, exp_aft = false;
                if (*(pt - 1) == '(') {
                    if (*(pt - 2) == '^') {
                        exp_bef = true;
                    } else if (*(pt + len + 1) == '^') {
                        exp_aft = true;
                    }
                } else if (*(pt - 1) == '^') {
                    exp_bef = true;
                } else if (*(pt + len) == '^') {
                    exp_aft = true;
                }

                if (exp_bef) {
                    char *temp_4 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
                    if (*(pt - 1) == '(') {
                        pt -= 3; // antes de '^'
                    } else {
                        pt -= 2;
                    }
                    strcpy(temp_4, pt + 1);

                    int ind = 0;
                    while (!par_paired(pt - ind, ind + 1)) {
                        ind++;
                    }
                    len = ind + 1;
                    pt -= ind;

                    strncpy(temp_3, pt, len);
                    while (par_enclosed(temp_3)) {
                        temp_3 = rm_par(temp_3);
                    }
                    temp_3 = simp_input(temp_3);

                    strcpy(temp_2, "");
                    if ((n_term(temp_3) != 1) || (n_block(temp_3) != 1)) {
                        strcat(temp_2, "(");
                        strcat(temp_2, temp_3);
                        strcat(temp_2, ")");
                    } else {
                        strcat(temp_2, temp_3);
                    }
                    strcat(temp_2, temp_4);
                } else if (exp_aft) {
                    char *temp_4 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
                    if (*(pt - 1) == '(') {
                        pt += len + 2; // depois de '^'
                    } else {
                        pt += len + 1;
                    }
                    strncpy(temp_4, temp_2, pt - temp_2);

                    while (par_enclosed(pt)) {
                        pt = rm_par(pt);
                    }
                    pt = simp_input(pt);

                    strcpy(temp_2, temp_4);
                    if ((n_term(pt) != 1) || (n_block(pt) != 1)) {
                        strcat(temp_2, "(");
                        strcat(temp_2, pt);
                        strcat(temp_2, ")");
                    } else {
                        strcat(temp_2, pt);
                    }
                }

                strcpy(temp_1, temp_2);

                rev = rev->next;
            }
            strcpy(rt_str, temp_1);

            return rt_str;
        } else if ((fn_tp == expo) || (fn_tp == powr) ||
                   ((fn_tp == poly) && (strcmp(str_cpy, "x") != 0))) {
            char *pt = strpbrk(str_cpy, "^");
            while (!par_paired(str_cpy, pt - str_cpy)) {
                pt = strpbrk(pt + 1, "^");
            }
            *pt = 0;

            char *bef = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            char *aft = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            strcpy(bef, str_cpy);
            strcpy(aft, pt + 1);

            bef = simp_input(bef);
            aft = simp_input(aft);

            strcpy(rt_str, "");
            if ((n_term(bef) != 1) || (n_block(bef) != 1)) {
                strcat(rt_str, "(");
                strcat(rt_str, bef);
                strcat(rt_str, ")");
            } else {
                strcat(rt_str, bef);
            }
            strcat(rt_str, "^");
            if ((n_term(aft) != 1) || (n_block(aft) != 1)) {
                strcat(rt_str, "(");
                strcat(rt_str, aft);
                strcat(rt_str, ")");
            } else {
                strcat(rt_str, aft);
            }

            return rt_str;            
        } else {
            return str_cpy;
        }
    } else if (num_tm != 1) {
        term *tm = into_term(str_cpy);
        bool op = false;

        strcpy(rt_str, "");
        while (tm->segm != NULL) {
            if (!op) {
                tm->segm->entry = simp_input(tm->segm->entry);
                
                if (n_term(tm->segm->entry) == 1) {
                    strcat(rt_str, tm->segm->entry);
                } else {
                    strcat(rt_str, "(");
                    strcat(rt_str, tm->segm->entry);
                    strcat(rt_str, ")");
                }

                op = true;
            } else {
                strcat(rt_str, tm->segm->entry);

                op = false;
            }
            tm->segm = tm->segm->next;
        }

        return rt_str;
    } else if (num_bl != 1) {
        block *bl = into_block(str_cpy);
        list *mult_head = bl->mult;
        list *mult_curr = mult_head;
        list *divi_head = bl->divi;
        list *divi_curr = divi_head;

        int n_divi, n_mult = n_list(mult_curr);
        if (strlen(divi_curr->entry) == 0) {
            n_divi = 0;
            mult_curr = mult_head;
        } else {
            n_divi = n_list(divi_curr);
            mult_curr = mult_head;
            divi_curr = divi_head;
        }

        while (mult_curr != NULL) {
            while (par_enclosed(mult_curr->entry)) {
                mult_curr->entry = rm_par(mult_curr->entry);
            }
            mult_curr = mult_curr->next;
        }
        mult_curr = mult_head;
        while (divi_curr != NULL) {
            while (par_enclosed(divi_curr->entry)) {
                divi_curr->entry = rm_par(divi_curr->entry);
            }
            divi_curr = divi_curr->next;
        }
        divi_curr = divi_head;

        strcpy(rt_str, "");
        while (mult_curr != NULL) {
            mult_curr->entry = simp_input(mult_curr->entry);
            if (n_term(mult_curr->entry) == 1) {
                strcat(rt_str, mult_curr->entry);
            } else {
                strcat(rt_str, "(");
                strcat(rt_str, mult_curr->entry);
                strcat(rt_str, ")");
            }

            if (mult_curr->next != NULL) {
                strcat(rt_str, "*");
            }
            mult_curr = mult_curr->next;
        }
        if (n_divi != 0) {
            while (divi_curr != NULL) {
                strcat(rt_str, "/");
                divi_curr->entry = simp_input(divi_curr->entry);
                if ((n_term(divi_curr->entry) == 1) && (n_block(divi_curr->entry) == 1)) {
                    strcat(rt_str, divi_curr->entry);
                } else {
                    strcat(rt_str, "(");
                    strcat(rt_str, divi_curr->entry);
                    strcat(rt_str, ")");
                }

                divi_curr = divi_curr->next;
            }
        }

        return rt_str;
    }
}

char *simp_output(char *str) {
    char *str_cpy = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
    strcpy(str_cpy, str);

    while (par_enclosed(str_cpy)) {
        str_cpy = rm_par(str_cpy);
    }

    int num_tm = n_term(str_cpy), num_bl = n_block(str_cpy);
    char *rt_str = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
    
    if ((num_tm == 1) && (num_bl == 1)) {
        if (is_composite(str_cpy)) {
            comp *cp = into_comp(str_cpy);
            list *rev = rev_list(cp->elem);

            size_t len;
            char *pt;
            char *temp_1 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            char *temp_2 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            char *temp_3 = (char *) malloc(sizeof(char) * MAX_CHAR / 8);

            strcpy(temp_1, rev->entry);
            while (rev->next != NULL) {
                while (par_enclosed(rev->entry)) {
                    rev->entry = rm_par(rev->entry);
                }

                len = strlen(rev->entry);
                pt = strstr(rev->next->entry, rev->entry);
                temp_1 = simp_output(temp_1);

                strncpy(temp_2, rev->next->entry, pt - rev->next->entry);
                temp_2[pt - rev->next->entry] = 0;

                strcpy(temp_3, pt + len);
                strcat(temp_2, temp_1);
                strcat(temp_2, temp_3);

                strcpy(temp_1, temp_2);
                rev = rev->next;
            }
            strcpy(rt_str, temp_1);

            return rt_str;
        } else {
            return str_cpy;
        }
    } else if (num_tm != 1) {
        term *tm = into_term(str_cpy);
        bool op = false;

        char *prev_sig = (char *) malloc(sizeof(char) * 4);
        strcpy(rt_str, "");
        while (tm->segm != NULL) {
            if (!op) {
                while (par_enclosed(tm->segm->entry)) {
                    tm->segm->entry = rm_par(tm->segm->entry);
                }
                tm->segm->entry = simp_output(tm->segm->entry);

                if ((strcmp(tm->segm->entry, "0") != 0) && (strcmp(tm->segm->entry, "(0)") != 0) &&
                    (strcmp(tm->segm->entry, "") != 0)) {
                    strcat(rt_str, prev_sig);

                    ch_type ch_tp = id_ch_tp(*tm->segm->entry);
                    if (ch_tp == pt_sig) {
                        strcat(rt_str, "(");
                        strcat(rt_str, tm->segm->entry);
                        strcat(rt_str, ")");
                    } else {
                        strcat(rt_str, tm->segm->entry);
                    }
                }

                op = true;
            } else {
                strcpy(prev_sig, tm->segm->entry);

                op = false;
            }
            tm->segm = tm->segm->next;
        }

        ch_type ch_tp = id_ch_tp(*(rt_str + strlen(rt_str) - 1));
        if (ch_tp == pt_sig) {
            *(rt_str + strlen(rt_str) - 1) = 0;
        }

        if (strcmp(rt_str, "") == 0) {
            return "0";
        }
        
        return rt_str;
    } else if (num_bl != 1) {
        block *bl = into_block(str_cpy);
        list *mult_head = bl->mult;
        list *mult_curr = mult_head;
        list *divi_head = bl->divi;
        list *divi_curr = divi_head;

        int n_divi, n_mult = n_list(mult_curr);
        if (strlen(divi_curr->entry) == 0) {
            n_divi = 0;
            mult_curr = mult_head;
        } else {
            n_divi = n_list(divi_curr);
            mult_curr = mult_head;
            divi_curr = divi_head;
        }

        strcpy(rt_str, "");
        while (mult_curr != NULL) {
            mult_curr->entry = simp_output(mult_curr->entry);

            if (strcmp(mult_curr->entry, "0") == 0) {
                return "";
            }

            if (strcmp(mult_curr->entry, "1") != 0) {
                if ((n_term(mult_curr->entry) != 1) || (n_block(mult_curr->entry) != 1)) {
                    strcat(rt_str, "(");
                    strcat(rt_str, mult_curr->entry);
                    strcat(rt_str, ")");
                } else {
                    ch_type ch_tp = id_ch_tp(*mult_curr->entry);
                    fn_type fn_tp = id_fn_tp(mult_curr->entry);
                    if ((fn_tp == expo) || (fn_tp == powr) || 
                        ((fn_tp == poly) && (strcmp(mult_curr->entry, "x") != 0))) {
                        strcat(rt_str, "(");
                        strcat(rt_str, mult_curr->entry);
                        strcat(rt_str, ")");
                    } else if (ch_tp == pt_sig) {
                        strcat(rt_str, "(");
                        strcat(rt_str, mult_curr->entry);
                        strcat(rt_str, ")");
                    } else {
                        strcat(rt_str, mult_curr->entry);
                    }
                }
            } else if (n_mult == 1) {
                strcat(rt_str, mult_curr->entry);
            }
            mult_curr = mult_curr->next;
        }

        if (n_divi != 0) {
            char *divi_str = (char *) malloc(sizeof(char) * MAX_CHAR / 8);
            strcpy(divi_str, "");

            while (divi_curr != NULL) {
                divi_curr->entry = simp_output(divi_curr->entry);

                if (strcmp(divi_curr->entry, "0") == 0) {
                    return "";
                }

                if (strcmp(divi_curr->entry, "1") != 0) {
                    if ((n_term(divi_curr->entry) != 1) || (n_block(divi_curr->entry) != 1)) {
                        strcat(divi_str, "(");
                        strcat(divi_str, divi_curr->entry);
                        strcat(divi_str, ")");
                    } else {
                        ch_type ch_tp = id_ch_tp(*divi_curr->entry);
                        fn_type fn_tp = id_fn_tp(divi_curr->entry);
                        if ((fn_tp == expo) || (fn_tp == powr) || 
                            ((fn_tp == poly) && (strcmp(divi_curr->entry, "x") != 0))) {
                            strcat(divi_str, "(");
                            strcat(divi_str, divi_curr->entry);
                            strcat(divi_str, ")");
                        } else if (ch_tp == pt_sig) {
                            strcat(divi_str, "(");
                            strcat(divi_str, divi_curr->entry);
                            strcat(divi_str, ")");
                        } else {
                            strcat(divi_str, divi_curr->entry);
                        }
                    }
                } else if (n_divi == 1) {
                    strcat(divi_str, divi_curr->entry);
                }
                divi_curr = divi_curr->next;
            }

            if (strcmp(divi_str, "") != 0) {
                strcat(rt_str, "/");
                if ((n_term(divi_str) != 1) || (n_block(divi_str) != 1)) {
                    strcat(rt_str, "(");
                    strcat(rt_str, divi_str);
                    strcat(rt_str, ")");
                } else {
                    strcat(rt_str, divi_str);
                }
            }
        }

        return rt_str;
    }
}
