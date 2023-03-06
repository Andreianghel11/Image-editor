/*Anghel Andrei - Stelian, 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LMAX 256
#include "header.h"

void crop_gray(image *picture, coordinates *coord)
{
	/*Noile dimensiuni ale imaginii.*/
	int new_width = coord->x2 - coord->x1;
	int new_height = coord->y2 - coord->y1;
	unsigned char **aux;
	aux = malloc(new_height * sizeof(char *));
	if (!aux) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < new_height; i++) {
		aux[i] = malloc(new_width * sizeof(char));
		if (!aux[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}
	for (int i = coord->y1; i < coord->y2; i++)
		for (int j = coord->x1; j < coord->x2; j++)
			aux[i - coord->y1][j - coord->x1] = picture->pixel_matrix[i][j];

	/*Realocarea matricei.*/
	for (int i = 0; i < picture->height; i++)
		free(picture->pixel_matrix[i]);
	free(picture->pixel_matrix);

	picture->height = new_height;
	picture->width = new_width;

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

void crop_rgb(image *picture, coordinates *coord)
{
	/*Noile dimensiuni ale imaginii.*/
	int new_width = coord->x2 - coord->x1;
	int new_height = coord->y2 - coord->y1;
	color_pixel **aux;
	aux = malloc(new_height * sizeof(color_pixel *));
	if (!aux) {
		printf("Eroare\n");
		exit(-1);
	}
	for (int i = 0; i < new_height; i++) {
		aux[i] = malloc(new_width * sizeof(color_pixel));
		if (!aux[i]) {
			printf("Eroare\n");
			exit(-1);
		}
	}
	for (int i = coord->y1; i < coord->y2; i++)
		for (int j = coord->x1; j < coord->x2; j++)
			aux[i - coord->y1][j - coord->x1] = picture->cp_matrix[i][j];

	/*Realocarea matricei.*/
	for (int i = 0; i < picture->height; i++)
		free(picture->cp_matrix[i]);
	free(picture->cp_matrix);

	picture->height = new_height;
	picture->width = new_width;

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
