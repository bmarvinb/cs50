#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *input_file_name = argv[1];
    FILE *raw_file = fopen(input_file_name, "r");
    if (raw_file == NULL)
    {
        printf("Error: cannot open %s\n", input_file_name);
        return 2;
    }

    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    FILE *jpg = NULL;
    char filename[4];
    int count = 0;

    while (fread(&buffer, BLOCK_SIZE, 1, raw_file) == 1)
    {
        bool is_jpg_header = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
        if (is_jpg_header)
        {
            if (count != 0)
            {
                fclose(jpg);
            }
            sprintf(filename, "%03i.jpg", count);
            jpg = fopen(filename, "w");
            count++;
        }
        if (count != 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, jpg);
        }
    }
    fclose(raw_file);
    fclose(jpg);

    return 0;
}
