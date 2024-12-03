
CFLAGS= -O2 -lOpenCL

.PHONY:all
all:diffusion

diffusion:opencl.c
	gcc $(CFLAGS) -o diffusion opencl.c

.PHONY:clean
clean:
	rm -rf extracted diffusion
