#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_to_bits(const char *str, char *bits) {
    int i = 0;
    while (str[i] != '\0') {
        char ch = str[i];
        int j = 7;
        while (j >= 0) {
            if ((ch >> j) & 1) {
                bits[i * 8 + (7 - j)] = '1';
            } else {
                bits[i * 8 + (7 - j)] = '0';
            }
            j--;
        }
        i++;
    }
    bits[i * 8] = '\0'; // Adiciona o terminador nulo
}


int main() {
    char str[] = "Davi";
    char bits[8 * strlen(str) + 1];

    string_to_bits(str, bits);

    printf("String: %s\n", str);
    printf("Bits:   %s\n", bits);

    return 0;
}
