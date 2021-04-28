CC=g++
exe=main
obj=S.o tool.o

all: $(obj) 
	$(CC) -static -o $(exe) $(obj)
%.o:%.cpp %.h
	$(CC) -c $<  -o $@

.PHONY:clean
clean:
	rm *.o
