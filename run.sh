#!/bin/bash

#запуск контейнера с флагом --ipc=host для использования общей памяти хоста
docker run --rm --ipc=host shm-example /bin/bash -c \
    "./writer | ./reader"
