TARGET=taskTest
OBJS=main.o TaskThread.o TaskTool.o

CC=g++
$(TARGET):$(OBJS)
	$(CC) $^ -o $@ -lpthread
