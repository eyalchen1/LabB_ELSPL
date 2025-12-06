#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main() {
    FILE *f = fopen("signatures-L", "wb");
    if (!f) return 1;

    // Write magic number (LITTLE endian)
    fwrite("VIRL", 1, 4, f);

    // -------- Virus #1 --------
    uint16_t size1 = 4;   // signature length
    char name1[16] = "AAA";     // padded with zeros
    unsigned char sig1[4] = {0x11, 0x22, 0x33, 0x44};
    fwrite(&size1, 1, 2, f); // LITTLE ENDIAN OK
    fwrite(name1, 1, 16, f);
    fwrite(sig1, 1, size1, f);

    // -------- Virus #2 --------
    uint16_t size2 = 3;
    char name2[16] = "BBB";
    unsigned char sig2[3] = {0xAA, 0xBB, 0xCC};

    fwrite(&size2, 1, 2, f);
    fwrite(name2, 1, 16, f);
    fwrite(sig2, 1, size2, f);

    fclose(f);
    return 0;
}
