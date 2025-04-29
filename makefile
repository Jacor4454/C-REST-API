CPPFLAGS=
#-fsanitize=address -g
COMPILER=g++
OBJDIR=./objects/
TESTDIR=./tests/
SRCDIR=./src/
HTTPDIR=./src/http_server/
LOGDIR=./src/logging/
RESPDIR=./src/http_server/APIresponces/


project: main.o http_server.o responces.o logging.o
	$(COMPILER) $(CPPFLAGS) -o a $(OBJDIR)main.o $(OBJDIR)responces.o $(OBJDIR)logging.o $(OBJDIR)api.o $(OBJDIR)http_server.o
	./a

test: test.o http_server.o responces.o
	$(COMPILER) $(CPPFLAGS) -Wall -g -pthread -o b $(OBJDIR)test.o $(OBJDIR)responces.o $(OBJDIR)http_server.o /usr/lib/libgtest.a
	./b


http_server.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)http_server.o $(HTTPDIR)http_server.cpp

logging.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)logging.o $(LOGDIR)logging.cpp

responces.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)responces.o $(RESPDIR)Base.cpp

main.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)main.o main.cpp

test.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)test.o $(TESTDIR)test.cpp
