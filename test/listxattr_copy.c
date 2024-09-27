#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <unistd.h>

int main(int ac, char **av) {
    const char *filename = av[1]; // İncelenecek dosya adı
    char list[1024]; // Nitelik adlarını tutacak dizi
    ssize_t len;

    // Genişletilmiş nitelikleri listele
    len = listxattr(filename, list, sizeof(list));

    if (len < 0) {
        perror("listxattr hatası");
        return EXIT_FAILURE;
    }

    if (len == 0) {
        printf("Herhangi bir genişletilmiş nitelik yok.\n");
        return EXIT_SUCCESS;
    }

    // Nitelik adlarını yazdır
    printf("Genişletilmiş Nitelikler:\n");
    for (ssize_t i = 0; i < len; ) {
        printf(" - %s\n", list + i);
        // Nitelik adının uzunluğu
        i += strlen(list + i) + 1; // Sonraki nitelik için atla
    }

    char value[1024];
    ssize_t ret = getxattr(filename, av[2], value, sizeof(value));
    if (ret < 0) {
        perror("getxattr hatası");
        return EXIT_FAILURE;
    }

    value[ret] = '\0'; // Sonlandırıcı ekle
    printf("Genişletilmiş Niteliğin Değeri: %s\n", value);

    return EXIT_SUCCESS;
}