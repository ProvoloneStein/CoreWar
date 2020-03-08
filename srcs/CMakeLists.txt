cmake_minimum_required(VERSION 3.14)
project(srcs C)

set(CMAKE_C_STANDARD 11)

add_executable(srcs
        checks.c
        checks2.c
        code_generator.c
        create_list.c
        edgar_func.c
        edgar_func1.c
        errors.c
        funct1.c
        funct2.c
        funct3.c
        funct4.c
        functions.c
        functions2.c
        main.c
        operations.c
        read_commands.c
        read_struct.c
        variables.c)
