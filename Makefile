#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}.; \
#echo $(LD_LIBRARY_PATH); 

mem: mem.c
	gcc -lmem -L. -o mem mem.c -Wall -Werror

libmem.o: mem.o
	gcc -shared -o libmem.so mem.o

mem.o: mem.c
	gcc -c -fpic mem.c -Wall -Werror

clean:
	rm -f mem.o mem.c libmem.so mem

