#***********************************************
#		   聊天软件-服务端	       *
#	       by:Sucoder QQ:330729793	       *
#				2013.01.25     *
#Makefile文件..		     		       *
#***********************************************

OBJ = server.o network.o dbinit.o msgdispose.o dbdispose.o
CC = gcc
APP = a
LIBS = -L /usr/lib/mysql -lmysqlclient -lpthread

all:$(OBJ)
	$(CC) -o $(APP) $(OBJ) $(LIBS) 

.PHONY:clean
clean:
	rm -f $(APP) ../*/*.o  ../*/*~ 
