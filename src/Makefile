OUT	= emulator
CC	 = gcc
CFLAGS	 = -g -c -Wall -D_DEFAULT_SOURCE  -std=c99 -pedantic -O3 -DNDEBUG

.SUFFIXES: .c .o

.PHONY: clean

all: emulate assemble

# Build rule for the final executable
emulate: emulate.o emulator/utils.o emulator/processes.o emulator/data_processing.o emulator/single_data_transfer.o emulator/instructions_utils.o emulator/operations.o emulator/decoder.o emulator/multiply.o emulator/branch.o

# Build rules for the .o files
emulate.o: emulate.c
	$(CC) $(CFLAGS) emulate.c -o emulate.o

emulator/utils.o: emulator/utils.c
	$(CC) $(CFLAGS) emulator/utils.c -o emulator/utils.o

emulator/processes.o: emulator/processes.c
	$(CC) $(CFLAGS) emulator/processes.c -o emulator/processes.o

emulator/data_processing.o: emulator/data_processing.c
	$(CC) $(CFLAGS) emulator/data_processing.c -o emulator/data_processing.o

emulator/single_data_transfer.o: emulator/single_data_transfer.c
	$(CC) $(CFLAGS) emulator/single_data_transfer.c -o emulator/single_data_transfer.o

emulator/instructions_utils.o: emulator/instructions_utils.c
	$(CC) $(CFLAGS) emulator/instructions_utils.c -o	emulator/instructions_utils.o

emulator/operations.o: emulator/operations.c
	$(CC) $(CFLAGS) emulator/operations.c -o emulator/operations.o

emulator/decoder.o: emulator/decoder.c
	$(CC) $(CFLAGS) emulator/decoder.c -o emulator/decoder.o

emulator/multiply.o: emulator/multiply.c
	$(CC) $(CFLAGS) emulator/multiply.c -o emulator/multiply.o

emulator/branch.o: emulator/branch.c
	$(CC) $(CFLAGS) emulator/branch.c -o emulator/branch.o

# Build rule for the final executable
assemble: assemble.o assembler/file_utils.o assembler/symbol_table.o assembler/hashmap.o assembler/branch.o assembler/multiply.o assembler/data_processing.o assembler/single_data_transfer_assembler.o assembler/assembler_utils.o

# Build rules for the .o files
assemble.o: assemble.c
	$(CC) $(CFLAGS) -c assemble.c -o assemble.o

assembler/file_utils.o: assembler/file_utils.c
	$(CC) $(CFLAGS) assembler/file_utils.c -o assembler/file_utils.o

assembler/symbol_table.o: assembler/symbol_table.c
	$(CC) $(CFLAGS) assembler/symbol_table.c -o assembler/symbol_table.o

assembler/hashmap.o: assembler/hashmap.c
	$(CC) $(CFLAGS) assembler/hashmap.c -o assembler/hashmap.o

assembler/branch.o: assembler/branch.c
	$(CC) $(CFLAGS) assembler/branch.c -o assembler/branch.o

assembler/multiply.o: assembler/multiply.c
	$(CC) $(CFLAGS) assembler/multiply.c -o assembler/multiply.o

assembler/data_processing.o: assembler/data_processing.c
	$(CC) $(CFLAGS) assembler/data_processing.c -o assembler/data_processing.o

assembler/single_data_transfer_assembler.o: assembler/single_data_transfer_assembler.c
	$(CC) $(CFLAGS) assembler/single_data_transfer_assembler.c -o assembler/single_data_transfer_assembler.o

assembler/assembler_utils.o: assembler/assembler_utils.c
	$(CC) $(CFLAGS) assembler/assembler_utils.c -o assembler/assembler_utils.o

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate