#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void list_files_recursive(const char *path) 
{
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Dizini açarken hata");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char new_path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            printf("Dizin: %s\n", new_path);
            list_files_recursive(new_path);
        } else {
            printf("Dosya: %s/%s\n", path, entry->d_name);
        }
    }
    closedir(dir);
}

int main() {
    DIR *dir;
    struct dirent *entry;

    // Dizini aç
    dir = opendir(".");

    if (dir == NULL) {
        perror("Dizini açarken hata");
        return EXIT_FAILURE;
    }

    

    list_files_recursive(".");

    // Dizin akışını kapat
    closedir(dir);
    return EXIT_SUCCESS;
}