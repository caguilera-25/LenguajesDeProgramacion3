#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

char* read_whole_file(const char* filename) {
    int fd;
    struct stat st;
    char* buffer;
    ssize_t bytes_read;

    // Obtener tamaño del archivo
    if (stat(filename, &st) == -1) {
        perror("stat fallo");
        return NULL;
    }

    // Abrir archivo
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open fallo");
        return NULL;
    }

    // Reservar memoria +1 para '\0'
    buffer = (char*) malloc(st.st_size + 1);
    if (!buffer) {
        perror("malloc fallo");
        close(fd);
        return NULL;
    }

    // Leer todo el archivo
    bytes_read = read(fd, buffer, st.st_size);
    if (bytes_read == -1) {
        perror("read fallo");
        free(buffer);
        close(fd);
        return NULL;
    }

    buffer[bytes_read] = '\0'; // asegurar fin de string
    close(fd);
    return buffer;
}

int main() {
    char* buffer;

    buffer = read_whole_file("archivo.txt");  // ruta según donde esté el archivo

    if (!buffer) {
        fprintf(stderr, "No se pudo leer el archivo\n");
        return 1;
    }

    printf("Contenido del archivo:\n%s\n", buffer);

    free(buffer);
    return 0;
}
