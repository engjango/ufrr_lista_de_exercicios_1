/***********************************************************************
 * 
 * utils.h
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
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* número de linhas de referência do tela. */
#define SCREEN_HEIGHT 	24

/* número de colunas de referência do tela. */
#define SCREEN_WIDTH 	80

/* atributos do texto */
#define RESETATTR    0
#define BRIGHT       1
#define DIM          2
#define UNDERSCORE   4
#define BLINK        5   /* pode não funcionar em todos os monitores. */
#define REVERSE      7
#define HIDDEN       8

/* cor dos caracteres ou plano de fundo destes */
#define BLACK        0x0
#define RED          0x1
#define GREEN        0x2
#define BROWN        0x3
#define BLUE         0x4
#define MAGENTA      0x5
#define CYAN         0x6
#define LIGHTGREY    0x7
#define DARKGREY     0x10
#define LIGHTRED     0x11
#define LIGHTGREEN   0x12
#define YELLOW       0x13
#define LIGHTBLUE    0x14
#define LIGHTMAGENTA 0x15
#define LIGHTCYAN    0x16
#define WHITE        0x17

/* Esc[2JEsc[1;1H - Limpa tela do console e move o cursor para 
 * posição [1,1] no canto superio esquerdo. */
#define clrscr()              puts ("\e[2J\e[1;1H")

/* Esc[K - Apaga o conteúdo da linha atual a partir da posição 
 * corrente do cursor até o final da linha. */
#define clreol()              puts ("\e[K")

/* Esc[2K - Remove todo o conteúdo da linha atual. */
#define delline()             puts ("\e[2K")

/* Esc[Line;ColumnH Move o cursor para posição na tela especifiada 
 * pelas coordenadas (x, y). */
#define gotoxy(x,y)           printf("\e[%d;%dH", y, x)

/* Esc[?25l (Caixa-Baixa L) - Oculta o cursor. */
#define hidecursor()          puts ("\e[?25l")

/* Esc[?25h (Caixa-Baixa H) - Exibe o cursor. */
#define showcursor()          puts ("\e[?25h")

/* Esc[Value;...;Valuem - Configura para o modo de gráficos. */
#define __set_gm(attr,color,val)                                        \
        if (!color)                                                     \
                printf("\e[%dm", attr);                                 \
        else                                                            \
                printf("\e[%d;%dm", color & 0x10 ? 1 : 0, (color & 0xF) + val)
                
/* altera os atributos do texto a ser impresso na tela. */                
#define textattr(attr)        __set_gm(attr, 0, 0)

/* altera a cor do texto a ser impresso na tela. */
#define textcolor(color)      __set_gm(RESETATTR, color, 30)

/* altera a cor do plano de fundo do texto a ser impresso. */
#define textbackground(color) __set_gm(RESETATTR, color, 40)

//#define _CRTIMP void __cdecl	_sleep (unsigned long);

/* efeito rolagem horizontal a partir de uma arte ASCII contida em
 * um ficheiro. Recebe um array de strings com "l" linhas e cria um
 * efeito de rolagem horiontal do texto de comprimento igual ao 
 * fornecido através da variável de entrada "janela". */
void textscrolling(char *_str[], const int l, int _length)	{
	int i,j;
	int head;
	int n = strlen(_str[0]);
	char *str[l];
	
	// +3 espaço inicial, final '\0'
	for(i = 0; i < l; i++)
		str[i] = (char *) malloc((_length+n+3)*sizeof(char));

	// adicionar espaços nas strings
	for(i = 0; i < l; i++)	{
		for(j = 0; j <=_length; j++)
			str[i][j] = ' ';
		for(j = 0; j < n; j++)
			str[i][_length+1+j] = _str[i][j];
		str[i][_length + 1 + n] = ' ';
		str[i][_length + 2 + n] = '\0';
	}

	// imprimir fazendo rolagem
	n = strlen(str[0]);
	// não imprimir os primeiros caracteres (head)
	for(head = 0; head < n; head++)	{ 
		// limpa definições anteriores e reposiciona cursor
		printf("\x1b[0m\x1b[2J"); 
		for(i=0; i<l; i++)	{
			// muda cor do texto → VERMELHO
			textcolor(LIGHTRED);
			// imprime caracteres
			printf("%.*s",_length,str[i]+head);
			// reposiciona cursor
			printf("\x1b[0m\n");
		}
		usleep(40000);
	}

	for(i=0; i<l; i++)
		free(str[i]);
}
 
/* Lê-se a partir do ficheiro localizado em "path" uma sequência de
 * linhas contendo o mesmo número de caracteres e retorna-se um
 * array de strings de dimensão igual ao número de linhas lidas "n". 
 * 
 * Note que são lidas apenas as primeiras 100 linhas do ficheiro,
 * caso existam. */
char **converttexttoarray(char *path, int *n)
{
	FILE *f = fopen(path,"r");
	char *line=NULL;
	int i;
	size_t len,plen=0;
	ssize_t read;
	char *linhas[100];

	// erro ao tentar abrir ficheiro para posterior leitura?
	if(!f)
	{
		textcolor(RED);
		printf("\n[ERRO] Impossivel abrir o ficheiro %s para leitura.\n", path);
		return(NULL);
	}

	// lê o conteúdo de cada linha e os copia para o array de strings.
	for(i = 0; ((read = getline(&line, &len, f)) != -1 ) && i < 100; i++)	
	{		
		if(strlen(line)==1)	
		{
			free(line);
			break;
		// verifica se cada uma das linhas possuem o mesmo comprimento,
		// isto é, o mesmo número de caracteres.
		} else if(plen!=0 && len!=plen)	{ 
			textcolor(RED);
			printf("[ERRO] As linhas %d and %d do ficheiro %s diferem quanto ao compriento (%zu and %zu)\n.", i, i - 1, path, len, plen);
			return NULL;
		}

		// Remove o "\n" do final da linha
		int j;
		for(j = 0; j < (int)len; j++)
			if(line[j]=='\n') 
			{
				line[j]='\0';
			}

		linhas[i] = line;	
		
		plen=len;
		line = NULL;
	}
	
	*n=i;
	char **dest = (char **) malloc(*n * sizeof(void *));
	for(i = 0; i < *n; i++)
		dest[i] = linhas[i];

	return dest;
}
