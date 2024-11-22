CC = clang
FLAGS = -O0
SFLAGS = -O3 -S
TARGET = build/EchoRenderer
SRCS = main.c
HEADERS = vec3.h color.h ray.h

OBJS = $(patsubst %.c, build/%.o, $(SRCS))
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC)  -o $@ $^
build/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run:
	make && ./build/EchoRenderer > a.ppm && open a.ppm
