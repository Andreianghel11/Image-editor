/*Anghel Andrei - Stelian, 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LMAX 256
#include "header.h"

void load_P2(char *file_name, FILE *f, image *picture)
{
	/*Incarcarea imaginii ascii grayscale.
	Utilizez matricea de tip UNSIGNED CHAR din structura.*/
	picture->pixel_matrix = malloc(picture->height * sizeof(char *));
	if (!picture->pixel_matrix)
		printf("Failed to load %s\n", file_name);
	for (int i = 0; i < picture->height; i++) {
		picture->pixel_matrix[i] = malloc(picture->width * sizeof(char));
		if (!picture->pixel_matrix[i]) {
			printf("Failed to load %s\n", file_name);
		} else {
			for (int j = 0; j < picture->width; j++) {
				int aux;
				fscanf(f, "%d", &aux);
				picture->pixel_matrix[i][j] = aux;
			}
		}
	}
}

void load_P3(char *file_name, FILE *f, image *picture)
{
	/*Incarcarea imaginii ascii color.
	Utilizez matricea de tip COLOR_PIXEL din structura.*/
	picture->cp_matrix = malloc(picture->height * sizeof(color_pixel *));
	if (!picture->cp_matrix)
		printf("Failed to load %s\n", file_name);
	for (int i = 0; i < picture->height; i++) {
		picture->cp_matrix[i] = malloc(picture->width * sizeof(color_pixel));
		if (!picture->cp_matrix[i]) {
			printf("Failed to load %s\n", file_name);
		} else {
			for (int j = 0; j < picture->width; j++) {
				int aux1;
				int aux2;
				int aux3;
				fscanf(f, "%d %d %d", &aux1, &aux2, &aux3);
				picture->cp_matrix[i][j].r = aux1;
				picture->cp_matrix[i][j].g = aux2;
				picture->cp_matrix[i][j].b = aux3;
			}
		}
	}
}

void load_P5(char *file_name, FILE *f, image *picture)
{
	/*Incarcarea imaginii binare grayscale.
	Utilizez matricea de tip UNSIGNED CHAR din structura.*/
	picture->pixel_matrix = malloc(picture->height * sizeof(char *));
	if (!picture->pixel_matrix)
		printf("Failed to load %s\n", file_name);
	for (int i = 0; i < picture->height; i++) {
		picture->pixel_matrix[i] = malloc(picture->width * sizeof(char));
		if (!picture->pixel_matrix[i])
			printf("Failed to load %s\n", file_name);
		else
			fread(picture->pixel_matrix[i], sizeof(char), picture->width, f);
	}
}

void load_P6(char *file_name, FILE *f, image *picture)
{
	/*Incarcarea imaginii binare color.
	Utilizez matricea de tip COLOR_PIXEL din structura.*/
	picture->cp_matrix = malloc(picture->height * sizeof(color_pixel *));
	if (!picture->cp_matrix)
		printf("Failed to load %s\n", file_name);
	for (int i = 0; i < picture->height; i++) {
		picture->cp_matrix[i] = malloc(picture->width * sizeof(color_pixel));
		if (!picture->cp_matrix[i]) {
			printf("Failed to load %s\n", file_name);
		} else {
			for (int j = 0; j < picture->width; j++) {
				fread(&picture->cp_matrix[i][j].r, sizeof(char), 1, f);
				fread(&picture->cp_matrix[i][j].g, sizeof(char), 1, f);
				fread(&picture->cp_matrix[i][j].b, sizeof(char), 1, f);
			}
		}
	}
}
