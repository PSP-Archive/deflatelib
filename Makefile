BINARY = out

OBJECTS = startup.o main.o pg.o

LIBRARY = deflatelib.a unziplib.a

all: $(BINARY)

$(BINARY): $(OBJECTS)
	ee-ld -O0 $(OBJECTS) $(LIBRARY) -M -Ttext 8900000 -q -o $@ > deflate.map
	outpatch deflateSample
	elf2pbp outp "deflateSample"

%.o : %.c
	ee-gcc -march=r4000 -O3 -fomit-frame-pointer -g -mgp32 -mlong32 -c $< -o $@

%.o : %.s
	ee-gcc -march=r4000 -g -mgp32 -c -xassembler -O -o $@ $<

clean:
	del /s /f *.o *.map
	rm *.o gbcore/*.o
