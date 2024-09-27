#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char **av) {
    const char *link_name = av[1];
    const char *target_name = av[2];

    // Sembolik bağlantı oluştur
    if (symlink(target_name, link_name) != 0) {
        perror("Sembolik bağlantı oluşturulurken hata");
        return EXIT_FAILURE;
    }

    char buffer[1024]; // Hedef yolu tutacak buffer
    ssize_t len = readlink(link_name, buffer, sizeof(buffer) - 1); // -1: Sonlandırıcı için yer bırak

    if (len < 0) {
        perror("readlink hatası");
        return EXIT_FAILURE;
    }

    buffer[len] = '\0'; // Sonlandırıcı ekle
    printf("Sembolik bağlantının hedefi: %s\n", buffer);

    return EXIT_SUCCESS;
}