CPPFLAGS=
#-fsanitize=address -g
COMPILER=g++
OBJDIR=./objects/
TESTDIR=./tests/
SRCDIR=./src/
HTTPDIR=./src/http_server/


project: api.o main.o
	$(COMPILER) $(CPPFLAGS) -o a $(OBJDIR)main.o $(OBJDIR)api.o

test: test.o api.o http_server.o
	$(COMPILER) $(CPPFLAGS) -Wall -g -pthread -o b $(OBJDIR)test.o $(OBJDIR)api.o $(OBJDIR)http_server.o /usr/lib/libgtest.a
	./b

api.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)api.o $(SRCDIR)api.cpp

http_server.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)http_server.o $(HTTPDIR)http_server.cpp

main.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)main.o main.cpp

test.o:
	$(COMPILER) $(CPPFLAGS) -c -o $(OBJDIR)test.o $(TESTDIR)test.cpp
