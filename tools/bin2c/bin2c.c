/*
 * bin2c — simple converter of binary files to C-style arrays.
 * This version generates a single .h file with static unsigned char array and length.
 * Suitable for SFML's loadFromMemory and similar APIs.
 * Public domain.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s input_file output_header_file array_name\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *header_file = argv[2];
    const char *name = argv[3];

    FILE *f_input = fopen(input_file, "rb");
    if (!f_input) {
        fprintf(stderr, "Error: Cannot open %s for reading\n", input_file);
        return 2;
    }

    fseek(f_input, 0, SEEK_END);
    long size = ftell(f_input);
    rewind(f_input);

    if (size <= 0) {
        fprintf(stderr, "Error: File is empty or error reading size\n");
        fclose(f_input);
        return 3;
    }

    unsigned char *data = (unsigned char *)malloc(size);
    assert(data);
    fread(data, 1, size, f_input);
    fclose(f_input);

    FILE *f_header = fopen(header_file, "w");
    if (!f_header) {
        fprintf(stderr, "Error: Cannot open %s for writing\n", header_file);
        free(data);
        return 4;
    }

    fprintf(f_header, "#pragma once\n\n");
    fprintf(f_header, "static const unsigned char %s[%ld] = {\n", name, size);
    for (long i = 0; i < size; ++i) {
        fprintf(f_header, "0x%02X", data[i]);
        if (i != size - 1) fprintf(f_header, ",");
        if ((i + 1) % 12 == 0) fprintf(f_header, "\n");
    }
    fprintf(f_header, "\n};\n");
    fprintf(f_header, "static const int %s_len = %ld;\n", name, size);

    fclose(f_header);
    free(data);
    return 0;
}
