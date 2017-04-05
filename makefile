objects = Initsocket.o pthread-look.o split_merge.o\
pthread-download.o pthread-upload.o server.o

server : $(objects)
	gcc -g -o server $(objects) -pthread -L /usr/include/mysql/ -lmysqlclient
	
server.o : server.c hdsokt.h func.h
	gcc -g -c server.c -L /usr/include/mysql/ -lmysqlclient
Initsocket.o : Initsocket.c hdsokt.h
	gcc -g  -c Initsocket.c
pthread-download.o : pthread-download.c hdsokt.h
	gcc -g -c pthread-download.c -pthread
pthread-look.o : pthread-look.c hdsokt.h
	gcc -g -c pthread-look.c -pthread
pthread-upload.o : pthread-upload.c hdsokt.h
	gcc -g -c pthread-upload.c -pthread
split_merge.o : split_merge.c hdsokt.h
	gcc -g -c split_merge.c
.PHONY : clean
clean :
	rm $(objects)
