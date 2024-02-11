#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

const int size = 32; 

int main(int argc, char* argv[]){
    //проверка аргументов
    if (argc != 3)
    {
        std::cout<<"Неверное количество аргументов!" << std::endl;
        return 0;
    }
    ssize_t writted_size;
    //храним идентификаторы потоков в этих переменных
    int fd_read;
    int fd_write;
    //буфер, в котором будем хранить прочитанное и записывать в другой файл
    char buffer[size];
    //сколько прочлось и записалось байт на данной итерации будет храниться в этих переменных
    ssize_t read_bytes;
    ssize_t write_bytes;

    (void)umask(0);

    //пробуем открыть первый файл для чтения
    if((fd_read = open(argv[1], O_RDONLY,0555)) < 0){
      printf("Can\'t open read file\n");
      exit(0);
    }
    
    // пробуем открыть второй файл для записи
    if((fd_write = open(argv[2], O_WRONLY | O_CREAT, 0333)) < 0){
      printf("Can\'t open write file\n");
      exit(0);
    }

    do {
    read_bytes = read(fd_read, buffer, size);
    // если не удалось чтение
    if(read_bytes == -1) {
      printf("Can\'t read this file\n");
      exit(0);
    }
    //иначе записываем в файл буфер отрезок массива, который успел перезаписаться
    write_bytes = write(fd_write, buffer, read_bytes);

   if(write_bytes != read_bytes) {
     printf("Can\'t write all string\n");
     exit(0);
   }
   //итерируемся до тех пор, пока есть, что читать из файла
    } while(read_bytes != 0);

    if(close(fd_read) < 0) {
        printf("Can\'t close read file\n");
    }
    
    if(close(fd_write) < 0) {
        printf("Can\'t close write file\n");
    }

    return 0;
}