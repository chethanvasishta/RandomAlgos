CC = g++

all: compile
	$(CC) obj/*.o -o algo 

compile:
	find -name '*.cpp' -print0 | xargs -0 $(CC) -c $(CPPFLAGS) && mkdir -p obj && mv *.o ./obj/
#clean
clean:
	rm -rf obj 
