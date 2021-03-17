BINARY = out

OBJECTS = adler32.o compress.o crc32.o deflate.o deflateInterface.o \
          inffast.o inflate.o inftrees.o trees.o zutil.o

all: $(BINARY)

$(BINARY): $(OBJECTS)
	ee-ar rcs deflatelib.a $(OBJECTS)


%.o : %.c
	ee-gcc -march=r4000 -O3 -fomit-frame-pointer -g -mgp32 -mlong32 -c $< -o $@

clean:
	del /s /f *.o *.map
