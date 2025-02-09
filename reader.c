#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Ошибка! не передан ключ разделяемой памяти\n");
        return EXIT_FAILURE;
    }

    int shmid = atoi(argv[1]);

    //подключение к разделяемой памяти
    void *shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void *)-1) {
        fprintf(stderr, "Ошибка shmat: %d - %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%s\n", (char *)shmaddr);

    //отключение
    if (shmdt(shmaddr) == -1) {
        fprintf(stderr, "Ошибка shmdt: %d - %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    //удаление разделяемой памяти
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        fprintf(stderr, "Ошибка shmctl: %d - %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
