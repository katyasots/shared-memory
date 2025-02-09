#!/bin/bash

KEY=$(docker run --rm --ipc=host shm-example ./writer)

echo "Ключ разделяемой памяти: $KEY"

docker run --rm --ipc=host shm-example ./reader "$KEY"
