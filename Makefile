
root_include_dir := include
root_source_dir  := src
compile_flags    := -Wall 
libs             := -lncurses
CC               := gcc

build:
	mkdir bin
	$(CC) -o bin/snake ${compile_flags} ${libs} ${root_source_dir}/*.c
clean:
	rm -rf bin
