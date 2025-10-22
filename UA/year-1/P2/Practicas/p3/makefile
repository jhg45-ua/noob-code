OPTS=-g -Wall -std=c++11
OBJS=prac3.o Util.o SNData.o SNFollowers.o Agency.o Influencer.o
CC=clang++

prac3: $(OBJS)
	$(CC) $(OPTS) $(OBJS) -o prac3

prac3.o: prac3.cc  Util.h Agency.h Influencer.h SNFollowers.h
	$(CC) $(OPTS) -c prac3.cc

Agency.o: Agency.cc Agency.h Influencer.h SNFollowers.h Util.h
	$(CC) $(OPTS) -c Agency.cc

Influencer.o: Influencer.cc Influencer.h SNFollowers.h Util.h
	$(CC) $(OPTS) -c Influencer.cc

SNData.o: SNData.cc SNData.h
	$(CC) $(OPTS) -c SNData.cc

SNFollowers.o: SNFollowers.cc SNFollowers.h Util.h
	$(CC) $(OPTS) -c SNFollowers.cc

Util.o: Util.cc Util.h
	$(CC) $(OPTS) -c Util.cc

clean:
	rm $(OBJS)