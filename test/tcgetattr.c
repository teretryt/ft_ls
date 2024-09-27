#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios term;

    // Terminalin ayarlarını al
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr hatası");
        return EXIT_FAILURE;
    }

    // Terminal ayarlarını yazdır
    printf("Baud Hızı: %d\n", cfgetispeed(&term));
    printf("Parite: %s\n", (term.c_cflag & PARENB) ? "Açık" : "Kapalı");
    printf("Veri Bitleri: %d\n", (term.c_cflag & CSIZE) >> 4);
    printf("Dur Bitleri: %d\n", (term.c_cflag & CSTOPB) ? 2 : 1);
    printf("Akış Kontrolü: %s\n", (term.c_cflag & CRTSCTS) ? "Açık" : "Kapalı");

    return EXIT_SUCCESS;
}

/* LC_ALL=C */