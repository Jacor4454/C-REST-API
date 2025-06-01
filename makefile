CPPFLAGS=
#-fsanitize=address -g
COMPILER=g++
OBJDIR=./objects/
TESTDIR=./tests/
SRCDIR=./src/
HTTPDIR=./src/http_server/
LOGDIR=./src/logging/
RESPDIR=./src/http_server/APIresponces/
SVGDIR=./src/svg/


project: main.o object
	$(COMPILER) $(CPPFLAGS) -o a $(OBJDIR)main.o rest.o
	./a

test: test.o object
	$(COMPILER) $(CPPFLAGS) -Wall -g -pthread -o b $(OBJDIR)test.o rest.o /usr/lib/libgtest.a
	./b

clean:
	rm ./objects/*
	make clean -C $(SVGDIR)

svg.o:
	make object -C $(SVGDIR)

object: http_server.o responces.o logging.o svg.o
	ld -r -o rest.o $(OBJDIR)responces.o $(SVGDIR)svg.o $(OBJDIR)logging.o $(OBJDIR)http_server.o

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
