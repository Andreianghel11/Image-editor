/*Anghel Andrei - Stelian, 312CA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LMAX 256
#include "header.h"

void exit_image(image picture, int *loaded)
{
	/*Cazul cand vrem sa inchidem programul
	fara sa fi incarcat o imagine.*/
	if (*loaded == 0) {
		printf("No image loaded\n");
	} else if (*loaded == 1) {
		if (picture.type == 2 || picture.type == 5) {
			for (int i = 0; i < picture.height; i++)
				free(picture.pixel_matrix[i]);

			free(picture.pixel_matrix);
		} else if (picture.type == 3 || picture.type == 6) {
			for (int i = 0; i < picture.height; i++)
				free(picture.cp_matrix[i]);

			free(picture.cp_matrix);
		}
		*loaded = 0;
	}
}

void load(image *picture, char *line, int *loaded)
{
	/*Temp este o variabila temporara,
	utilizata la parsarea string-ului line.*/
	char temp, temp1[LMAX], file_name[LMAX], file_line[LMAX];
	int nr_arg;
	nr_arg = sscanf(line, "%s %s", temp1, file_name);
	if (nr_arg == 1) {
		printf("Invalid command\n");
		return;
	}
	/*Inainte de a incarca o imagine noua dealocam
	resursele utilizate pentru imaginea anterioara.*/
	if (*loaded == 1)
		exit_image(*picture, loaded);
	FILE *f = fopen(file_name, "r");
	if (!f) {
		printf("Failed to load %s\n", file_name);
		*loaded = 0;
	} else {
		/*Verific existenta comentariilor in fisierul imagine.
		Liniile care incep cu caracterul '#' sunt ignorate.*/
		fgets(file_line, LMAX, f);
		while (file_line[0] == '#')
			fgets(file_line, LMAX, f);
		nr_arg = sscanf(file_line, "%c %d", &temp, &picture->type);
		fgets(file_line, LMAX, f);
		while (file_line[0] == '#')
			fgets(file_line, LMAX, f);
		nr_arg = sscanf(file_line, "%d %d", &picture->width, &picture->height);
		fgets(file_line, LMAX, f);
		while (file_line[0] == '#')
			fgets(file_line, LMAX, f);
		nr_arg = sscanf(file_line, "%d", &picture->max_val);

		/*Apelez functia corespunzatoare
		tipului imaginii.*/
		if (picture->type == 2)
			load_P2(file_name, f, picture);
		else if (picture->type == 3)
			load_P3(file_name, f, picture);
		else if (picture->type == 5)
			load_P5(file_name, f, picture);
		else if (picture->type == 6)
			load_P6(file_name, f, picture);

		*loaded = 1;
		fclose(f);
		printf("Loaded %s\n", file_name);
	}
}

void save(image picture, char *line, int loaded)
{
	/*Cazul cand vrem sa salvam o imagine
	fara sa fi incarcat un fisier.*/
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	/*Valoarea parametrului ascii determina daca imaginea
	trebuie salvata in format ascii sau in format binar.*/
	int nr_arg, ascii;
	char new_file_name[LMAX], ascii_param[LMAX], temp[LMAX];
	/*Folosesc faptul ca sscanf() returneaza
	numarul de variabile citite cu succes.*/
	nr_arg = sscanf(line, "%s %s %s", temp, new_file_name, ascii_param);
	if (nr_arg == 1) {
		printf("Invalid command\n");
		return;
	} else if (nr_arg == 2) {
		ascii = 0;
	} else if (nr_arg == 3 && strcmp(ascii_param, "ascii") == 0) {
		ascii = 1;
	}

	if (loaded == 1) {
		if (ascii == 1) {
			FILE *f = fopen(new_file_name, "w");
			if (picture.type == 2 || picture.type == 5) {
				int pw = picture.width;
				int ph = picture.height;
				int mv = picture.max_val;
				fprintf(f, "P2\n%d %d\n%d\n", pw, ph, mv);
				for (int i = 0; i < picture.height; i++) {
					for (int j = 0; j < picture.width; j++)
						fprintf(f, "%d ", picture.pixel_matrix[i][j]);
					fprintf(f, "\n");
				}
			} else if (picture.type == 3 || picture.type == 6) {
				int pw = picture.width;
				int ph = picture.height;
				int mv = picture.max_val;
				fprintf(f, "P3\n%d %d\n%d\n", pw, ph, mv);
				for (int i = 0; i < picture.height; i++) {
					for (int j = 0; j < picture.width; j++) {
						fprintf(f, "%d ", picture.cp_matrix[i][j].r);
						fprintf(f, "%d ", picture.cp_matrix[i][j].g);
						fprintf(f, "%d ", picture.cp_matrix[i][j].b);
					}
					fprintf(f, "\n");
				}
			}
			fclose(f);
		} else if (ascii == 0) {
			FILE *f = fopen(new_file_name, "wb");
			if (picture.type == 5 || picture.type == 2) {
				int pw = picture.width;
				int ph = picture.height;
				int mv = picture.max_val;
				fprintf(f, "P5\n%d %d\n%d\n", pw, ph, mv);
				for (int i = 0; i < picture.height; i++) {
					for (int j = 0; j < picture.width; j++)
						fwrite(&picture.pixel_matrix[i][j], sizeof(char), 1, f);
				}
			} else if (picture.type == 6 || picture.type == 3) {
				int pw = picture.width;
				int ph = picture.height;
				int mv = picture.max_val;
				fprintf(f, "P6\n%d %d\n%d\n", pw, ph, mv);
				for (int i = 0; i < picture.height; i++) {
					for (int j = 0; j < picture.width; j++) {
						fwrite(&picture.cp_matrix[i][j].r, sizeof(char), 1, f);
						fwrite(&picture.cp_matrix[i][j].g, sizeof(char), 1, f);
						fwrite(&picture.cp_matrix[i][j].b, sizeof(char), 1, f);
					}
				}
			}
			fclose(f);
		}
		printf("Saved %s\n", new_file_name);
	}
}

void fselect(image *picture, coordinates *coord, char *line, int loaded)
{
	/*Cazul cand vrem sa selectam o zona
	fara sa fi incarcat o imagine.*/
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	}
	char temp[LMAX];
	int x1, x2, y1, y2, nr;
	/*Cazul cand comanda nu a primit suficienti
	parametrii sau parametrii nu sunt numere intregi.*/
	nr = sscanf(line, "%s %d %d %d %d", temp, &x1, &y1, &x2, &y2);
	if (nr != 5) {
		printf("Invalid command\n");
		return;
	}
	if (x1 < 0 || x1 > picture->width) {
		printf("Invalid set of coordinates\n");
	} else if (x2 < 0 || x2 > picture->width) {
		printf("Invalid set of coordinates\n");
	} else if (y1 < 0 || y1 > picture->height) {
		printf("Invalid set of coordinates\n");
	} else if (y2 < 0 || y2 > picture->height) {
		printf("Invalid set of coordinates\n");
	} else if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
	} else if (x1 > x2 && y1 > y2) {
		swap(&x1, &x2);
		swap(&y1, &y2);
		coord->x1 = x1;
		coord->x2 = x2;
		coord->y1 = y1;
		coord->y2 = y2;
		printf("Selected %d %d %d %d\n",
			   coord->x1, coord->y1, coord->x2, coord->y2);
	} else if (x1 > x2) {
		swap(&x1, &x2);
		coord->x1 = x1;
		coord->x2 = x2;
		coord->y1 = y1;
		coord->y2 = y2;
		printf("Selected %d %d %d %d\n",
			   coord->x1, coord->y1, coord->x2, coord->y2);
	} else if (y1 > y2) {
		swap(&y1, &y2);
		coord->x1 = x1;
		coord->x2 = x2;
		coord->y1 = y1;
		coord->y2 = y2;
		printf("Selected %d %d %d %d\n",
			   coord->x1, coord->y1, coord->x2, coord->y2);
	} else {
		coord->x1 = x1;
		coord->x2 = x2;
		coord->y1 = y1;
		coord->y2 = y2;
		printf("Selected %d %d %d %d\n",
		       coord->x1, coord->y1, coord->x2, coord->y2);
	}
}

void select_all(image *picture, coordinates *coord, int loaded)
{
	/*Cazul cand vrem sa selectam intreaga
	zona fara sa fi incarcat o imagine.*/
	if (loaded == 0) {
		printf("No image loaded\n");
	} else if (loaded == 1) {
		coord->x1 = 0;
		coord->y1 = 0;
		coord->x2 = picture->width;
		coord->y2 = picture->height;
		printf("Selected ALL\n");
	}
}

void rotate(image *picture, coordinates *coord, char *line, int loaded)
{
	int angle, nr_arg;
	char temp[LMAX];
	nr_arg = sscanf(line, "%s %d", temp, &angle);
	if (nr_arg != 2) {
		printf("Invalid command\n");
		return;
	}
	/*Cazul cand vrem sa rotim o zona
	fara sa fi incarcat o imagine.*/
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	}
	/*Rotirea la 180 sau -180 de grade
	este trata ca o rotire la 90 de grade
	realizata de 2 ori. Asemanator pentru
	-90 si 270 de grade.*/
	if (angle % 90 != 0) {
		printf("Unsupported rotation angle\n");
	/*Rotirea unei imagini intregi.*/
	} else if (coord->x2 - coord->x1 == picture->width &&
						 coord->y2 - coord->y1 == picture->height) {
		if (picture->type == 2 || picture->type == 5) {
			if (angle == 90 || angle == -270) {
				rotate_matrix_rect_gray(picture, coord);
			} else if (angle == 180 || angle == -180) {
				for (int i = 0; i < 2; i++)
					rotate_matrix_rect_gray(picture, coord);
			} else if (angle == 270 || angle == -90) {
				for (int i = 0; i < 3; i++)
					rotate_matrix_rect_gray(picture, coord);
			}
		} else if (picture->type == 3 || picture->type == 6) {
			if (angle == 90 || angle == -270) {
				rotate_matrix_rect_rgb(picture, coord);
			} else if (angle == 180 || angle == -180) {
				for (int i = 0; i < 2; i++)
					rotate_matrix_rect_rgb(picture, coord);
			} else if (angle == 270 || angle == -90) {
				for (int i = 0; i < 3; i++)
					rotate_matrix_rect_rgb(picture, coord);
			}
		}
		printf("Rotated %d\n", angle);
	/*Rotirea unei zone patrate din imagine.*/
	} else if (coord->x2 - coord->x1 != coord->y2 - coord->y1) {
		printf("The selection must be square\n");

	} else {
		if (picture->type == 2 || picture->type == 5) {
			if (angle == 90 || angle == -270) {
				rotate_matrix_gray(picture, *coord);
			} else if (angle == 180 || angle == -180) {
				for (int i = 0; i < 2; i++)
					rotate_matrix_gray(picture, *coord);
			} else if (angle == 270 || angle == -90) {
				for (int i = 0; i < 3; i++)
					rotate_matrix_gray(picture, *coord);
			}
		} else if (picture->type == 3 || picture->type == 6) {
			if (angle == 90 || angle == -270) {
				rotate_matrix_rgb(picture, *coord);
			} else if (angle == 180 || angle == -180) {
				for (int i = 0; i < 2; i++)
					rotate_matrix_rgb(picture, *coord);
			} else if (angle == 270 || angle == -90) {
				for (int i = 0; i < 3; i++)
					rotate_matrix_rgb(picture, *coord);
			}
		}
		printf("Rotated %d\n", angle);
	}
}

void crop(image *picture, coordinates *coord, int loaded)
{
	/*Cazul cand vrem sa decupam o
	zona fara sa fi incarcat o imagine.*/
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	}
	if (picture->type == 2 || picture->type == 5) {
		crop_gray(picture, coord);
		printf("Image cropped\n");
	} else if (picture->type == 3 || picture->type == 6) {
		crop_rgb(picture, coord);
		printf("Image cropped\n");
	}
}

void grayscale(image *picture, coordinates *coord, int loaded)
{
	/*Cazul cand vrem sa prelucram o zona
	fara sa fi incarcat o imagine.*/
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	} else if (picture->type == 2 || picture->type == 5) {
		printf("Grayscale filter not available\n");
	} else {
		/*Variabila auxiliara de tip double
		pentru calcule precise.*/
		double aux;
		for (int i = coord->y1; i < coord->y2; i++) {
			for (int j = coord->x1; j < coord->x2; j++) {
				aux = (double)(picture->cp_matrix[i][j].r +
				      picture->cp_matrix[i][j].g + picture->cp_matrix[i][j].b);
				aux = aux / 3;
				picture->cp_matrix[i][j].r = (char)aprox(aux);
				picture->cp_matrix[i][j].g = (char)aprox(aux);
				picture->cp_matrix[i][j].b = (char)aprox(aux);
			}
		}
		printf("Grayscale filter applied\n");
	}
}

void sepia(image *picture, coordinates *coord, int loaded)
{
	/*Cazul cand vrem sa prelucram o zona
	fara sa fi incarcat o imagine.*/
	if (loaded == 0) {
		printf("No image loaded\n");
	} else if (picture->type == 2 || picture->type == 5) {
		printf("Sepia filter not available\n");
	} else {
		/*Variabile auxiliare de tip double
		pentru calcule precise.*/
		double nr, ng, nb;
		for (int i = coord->y1; i < coord->y2; i++) {
			for (int j = coord->x1; j < coord->x2; j++) {
				nr = 0.393 * (double)picture->cp_matrix[i][j].r +
						0.769 * (double)picture->cp_matrix[i][j].g +
						0.189 * (double)picture->cp_matrix[i][j].b;
				ng = 0.349 * (double)picture->cp_matrix[i][j].r +
						0.686 * (double)picture->cp_matrix[i][j].g +
						0.168 * (double)picture->cp_matrix[i][j].b;
				nb = 0.272 * (double)picture->cp_matrix[i][j].r +
						0.534 * (double)picture->cp_matrix[i][j].g +
						0.131 * (double)picture->cp_matrix[i][j].b;
				int mv = picture->max_val;
				picture->cp_matrix[i][j].r = (char)f_min(mv, aprox(nr));
				picture->cp_matrix[i][j].g = (char)f_min(mv, aprox(ng));
				picture->cp_matrix[i][j].b = (char)f_min(mv, aprox(nb));
			}
		}
		printf("Sepia filter applied\n");
	}
}

int main(void)
{
	image picture;
	coordinates coord;
	char line[LMAX], cmd[LMAX], cmd2[LMAX];
	int end = 0, loaded = 0, nr_arg = 0;

	/*valoarea variabilei end
	determina incheierea programului.*/
	while (!end) {
		/*Elimin caracterul '\n' din string atunci
		cand acesta este citit de functia fgets.*/
		fgets(line, LMAX, stdin);
		char *s = strchr(line, '\n');
		if (s)
			*s = '\0';

		/*Parsarea input-ului de la tastatura si stocarea
		in variabila cmd a comenzii ce va fi executata.*/
		nr_arg = sscanf(line, "%s %s", cmd, cmd2);
		if (!nr_arg)
			printf("Invalid command\n");

		if (!strcmp(cmd, "LOAD")) {
			load(&picture, line, &loaded);
			select_all_basic(&picture, &coord, loaded);
		} else if (!strcmp(cmd, "EXIT")) {
			exit_image(picture, &loaded);
			end = 1;
		} else if (!strcmp(cmd, "SAVE")) {
			save(picture, line, loaded);
		} else if (!strcmp(cmd, "SELECT") && !strcmp(cmd2, "ALL")) {
			select_all(&picture, &coord, loaded);
		} else if (!strcmp(cmd, "SELECT")) {
			fselect(&picture, &coord, line, loaded);
		} else if (!strcmp(cmd, "ROTATE")) {
			rotate(&picture, &coord, line, loaded);
		} else if (!strcmp(cmd, "CROP")) {
			crop(&picture, &coord, loaded);
		} else if (!strcmp(cmd, "GRAYSCALE")) {
			grayscale(&picture, &coord, loaded);
		} else if (!strcmp(cmd, "SEPIA")) {
			sepia(&picture, &coord, loaded);
		} else {
			/*Output-ul pentru un input ce nu reprezinta
			o comanda acceptata de catre program.*/
			printf("Invalid command\n");
		}
	}

	return 0;
}
