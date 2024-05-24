cmake_minimum_required(VERSION 3.10)
project(TextGenerator)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add executable
add_executable(TextGenerator
        src/main.c
        src/frequency_table.c
        src/text_generator.c
        src/single_threaded.c
        src/multi_process.c
)


# Add compile options if needed
# target_compile_options(SO2_project PRIVATE -Wall -Wextra -pedantic)