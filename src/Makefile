.DEFAULT_GOAL := default

CC?=clang
SOURCES=mmProgram.c matrixMultiply.c readWriteMatrices.c threads.c userInput.c 

BINARIES=mmProgram

%: %.c
	$(CC) $(CFLAGS) $(LIBRARIES) -o $@ $^

clean:
	rm -f $(BINARIES)

executable:
	$(CC) $(SOURCES) -o $(BINARIES)

default: executable