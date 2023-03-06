/*Anghel Andrei - Stelian, 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LMAX 256
#include "header.h"

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int f_min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int aprox(double n)
{
	double p_fractionara;
	int p_intreaga;

	p_intreaga = (int)n;
	p_fractionara = (double)(n - p_intreaga);
	if (p_fractionara < 0.5)
		return p_intreaga;
	else
		return p_intreaga + 1;
}

void select_all_basic(image *picture, coordinates *coord, int loaded)
{
	if (loaded == 1) {
		coord->x1 = 0;
		coord->y1 = 0;
		coord->x2 = picture->width;
		coord->y2 = picture->height;
	}
}
