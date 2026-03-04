#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    unsigned char rgb[3] = {204, 0, 0};  // R=204, G=0, B=0
    write(fd, rgb, 3);
    close(fd);
    
    printf("Wrote rgb=[%d][%d][%d]\n", rgb[0], rgb[1], rgb[2]);
    
    // Leer de vuelta
    fd = open("test.bin", O_RDONLY);
    unsigned char read_rgb[3];
    read(fd, read_rgb, 3);
    close(fd);
    
    printf("Read back=[%d][%d][%d]\n", read_rgb[0], read_rgb[1], read_rgb[2]);
    return 0;
}
