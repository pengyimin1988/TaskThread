TARGET=taskTest
OBJS=main.o TaskThread.o TaskMutex.o TaskTool.o

CC=g++
$(TARGET):$(OBJS)
	$(CC) $^ -o $@ -lpthread

.PHONY:clean
clean:
	rm -rf *.o $(TARGET)
