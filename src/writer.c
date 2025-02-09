#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define SHM_SIZE 1000
#define MESSAGE "Hello world!"

int main() {
    //создание разделяемой памяти
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        fprintf(stderr, "Ошибка shmget: %d - %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    //подключение к разделяемой памяти
    void *shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void *)-1) {
        fprintf(stderr, "Ошибка shmat: %d - %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    //запись сообщения
    strncpy((char *)shmaddr, MESSAGE, SHM_SIZE);
    //вывод ключа 
    printf("%d\n", shmid);

    //отключение
    if (shmdt(shmaddr) == -1) {
        fprintf(stderr, "Ошибка shmdt: %d - %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
