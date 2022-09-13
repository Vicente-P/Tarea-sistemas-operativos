GCC= gcc

compile: tarea.c 
	gcc tarea.c -o tarea

clean:
	rm tarea.c