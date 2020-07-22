cmake_minimum_required(VERSION 3.16)
project(arm11_10 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(src/assembler/headers)
include_directories(src/emulator/headers)

add_executable(arm11_10
        src/assembler/headers/assembler_utils.h
        src/assembler/headers/branch.h
        src/assembler/headers/data_processing.h
        src/assembler/headers/file_utils.h
        src/assembler/headers/hashmap.h
        src/assembler/headers/symbol_table.h
        src/assembler/headers/multiply.h
        src/assembler/headers/single_data_transfer_assembler.h
        src/assembler/assembler_utils.c
        src/assembler/branch.c
        src/assembler/data_processing.c
        src/assembler/file_utils.c
        src/assembler/hashmap.c
        src/assembler/symbol_table.c
        src/assembler/multiply.c
        src/assembler/single_data_transfer_assembler.c
        src/emulator/headers/branch.h
        src/emulator/headers/data_processing.h
        src/emulator/headers/decoder.h
        src/emulator/headers/instructions_utils.h
        src/emulator/headers/multiply.h
        src/emulator/headers/operations.h
        src/emulator/headers/processes.h
        src/emulator/headers/single_data_transfer.h
        src/emulator/headers/utils.h
        src/emulator/branch.c
        src/emulator/data_processing.c
        src/emulator/decoder.c
        src/emulator/instructions_utils.c
        src/emulator/multiply.c
        src/emulator/operations.c
        src/emulator/processes.c
        src/emulator/single_data_transfer.c
        src/emulator/utils.c
        src/assemble.c
        src/emulate.c
        src/structures.h)
