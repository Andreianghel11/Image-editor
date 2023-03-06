/*Anghel Andrei - Stelian, 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LMAX 256
#include "header.h"

void rotate_matrix_gray(image *picture, coordinates coord)
{
	/*Diferenta coordonatelor pe oricare axa este
	dimensiunea zonei patratice de pixeli.*/
	int n = coord.x2 - coord.x1;
	unsigned char **aux;
	aux = malloc(n * sizeof(char *));
	if (!aux) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < n; i++) {
		aux[i] = malloc(n * sizeof(char));
		if (!aux[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}
	/*Rotirea matricei la 90
	de grade in sens orar.*/
	for (int i = coord.y1; i < coord.y2; i++)
		for (int j = coord.x1; j < coord.x2; j++)
			aux[j - coord.x1][n - 1 - i + coord.y1] =
				picture->pixel_matrix[i][j];

	for (int i = coord.y1; i < coord.y2; i++)
		for (int j = coord.x1; j < coord.x2; j++)
			picture->pixel_matrix[i][j] = aux[i - coord.y1][j - coord.x1];

	for (int i = 0; i < n; i++)
		free(aux[i]);
	free(aux);
}

void rotate_matrix_rgb(image *picture, coordinates coord)
{
	/*Diferenta coordonatelor pe oricare axa este
	dimensiunea zonei patratice de pixeli.*/
	int n = coord.x2 - coord.x1;
	color_pixel **aux;
	aux = malloc(n * sizeof(color_pixel *));
	if (!aux) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < n; i++) {
		aux[i] = malloc(n * sizeof(color_pixel));
		if (!aux[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}
	/*Rotirea matricei la 90
	de grade in sens orar.*/
	for (int i = coord.y1; i < coord.y2; i++)
		for (int j = coord.x1; j < coord.x2; j++)
			aux[j - coord.x1][n - 1 - i + coord.y1] = picture->cp_matrix[i][j];

	for (int i = coord.y1; i < coord.y2; i++)
		for (int j = coord.x1; j < coord.x2; j++)
			picture->cp_matrix[i][j] = aux[i - coord.y1][j - coord.x1];

	for (int i = 0; i < n; i++)
		free(aux[i]);
	free(aux);
}

void rotate_matrix_rect_gray(image *picture, coordinates *coord)
{
	/*Folosesc matricea de tip UNSIGNED CHAR.*/
	unsigned char **aux;
	aux = malloc(picture->width * sizeof(char *));
	if (!aux) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < picture->width; i++) {
		aux[i] = malloc(picture->height * sizeof(char));
		if (!aux[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}
	for (int i = 0; i < picture->height; i++)
		for (int j = 0; j < picture->width; j++)
			aux[j][picture->height - 1 - i] = picture->pixel_matrix[i][j];

	for (int i = 0; i < picture->height; i++)
		free(picture->pixel_matrix[i]);
	free(picture->pixel_matrix);

	/*Interschimb dimensiunile matricei.*/
	int aux1;
	aux1 = picture->height;
	picture->height = picture->width;
	picture->width = aux1;

	picture->pixel_matrix = malloc(picture->height * sizeof(char *));
	if (!picture->pixel_matrix) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < picture->height; i++) {
		picture->pixel_matrix[i] = malloc(picture->width * sizeof(char));
		if (!picture->pixel_matrix[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}

	for (int i = 0; i < picture->height; i++)
		for (int j = 0; j < picture->width; j++)
			picture->pixel_matrix[i][j] = aux[i][j];

	for (int i = 0; i < picture->height; i++)
		free(aux[i]);
	free(aux);

	select_all_basic(picture, coord, 1);
}

void rotate_matrix_rect_rgb(image *picture, coordinates *coord)
{
	/*Folosesc matricea de tip COLOR_PIXEL.*/
	color_pixel **aux;
	aux = malloc(picture->width * sizeof(color_pixel *));
	if (!aux) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < picture->width; i++) {
		aux[i] = malloc(picture->height * sizeof(color_pixel));
		if (!aux[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}
	for (int i = 0; i < picture->height; i++)
		for (int j = 0; j < picture->width; j++)
			aux[j][picture->height - 1 - i] = picture->cp_matrix[i][j];

	for (int i = 0; i < picture->height; i++)
		free(picture->cp_matrix[i]);
	free(picture->cp_matrix);

	/*Interschimb dimensiunile matricei.*/
	int aux1;
	aux1 = picture->height;
	picture->height = picture->width;
	picture->width = aux1;

	picture->cp_matrix = malloc(picture->height * sizeof(color_pixel *));
	if (!picture->cp_matrix) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < picture->height; i++) {
		picture->cp_matrix[i] = malloc(picture->width * sizeof(color_pixel));
		if (!picture->cp_matrix[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}

	for (int i = 0; i < picture->height; i++)
		for (int j = 0; j < picture->width; j++)
			picture->cp_matrix[i][j] = aux[i][j];

	for (int i = 0; i < picture->height; i++)
		free(aux[i]);
	free(aux);

	select_all_basic(picture, coord, 1);
}
