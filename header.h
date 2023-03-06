/*Anghel Andrei - Stelian, 312CA*/

typedef struct {
	unsigned char r, g, b;
} color_pixel;

typedef struct {
	int type, width, height, max_val;
	unsigned char **pixel_matrix;
	color_pixel **cp_matrix;
} image;

typedef struct{
	int x1, x2, y1, y2;
} coordinates;

void swap(int *a, int *b);

int f_min(int a, int b);

int aprox(double n);

void load_P2(char *file_name, FILE *f, image *picture);

void load_P3(char *file_name, FILE *f, image *picture);

void load_P5(char *file_name, FILE *f, image *picture);

void load_P6(char *file_name, FILE *f, image *picture);

void exit_image(image picture, int *loaded);

void load(image *picture, char *line, int *loaded);

void save(image picture, char *line, int loaded);

void fselect(image *picture, coordinates *coord, char *line, int loaded);

void select_all(image *picture, coordinates *coord, int loaded);

void select_all_basic(image *picture, coordinates *coord, int loaded);

void rotate_matrix_gray(image *picture, coordinates coord);

void rotate_matrix_rgb(image *picture, coordinates coord);

void rotate_matrix_rect_gray(image *picture, coordinates *coord);

void rotate_matrix_rect_rgb(image *picture, coordinates *coord);

void rotate(image *picture, coordinates *coord, char *line, int loaded);

void crop_gray(image *picture, coordinates *coord);

void crop_rgb(image *picture, coordinates *coord);

void crop(image *picture, coordinates *coord, int loaded);

void grayscale(image *picture, coordinates *coord, int loaded);

void sepia(image *picture, coordinates *coord, int loaded);
