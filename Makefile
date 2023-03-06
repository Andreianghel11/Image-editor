#Anghel Andrei - Stelian, 312CA

build: image_editor.c auxiliary_functions.c load_functions.c rotate_functions.c crop_functions.c
	gcc -Wall -Wextra image_editor.c load_functions.c rotate_functions.c crop_functions.c auxiliary_functions.c -o image_editor

clean:
	rm -f image_editor
