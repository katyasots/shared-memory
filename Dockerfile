FROM gcc:11.3.0
COPY src /app

WORKDIR /app

RUN gcc -o writer writer.c
RUN gcc -o reader reader.c

CMD ["bash"]