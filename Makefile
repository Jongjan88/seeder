CXXFLAGS = -O3 -g0
LDFLAGS = $(CXXFLAGS)

dnsseed: dns.o bitcoin.o netbase.o protocol.o db.o main.o util.o jj_http_message.o jj_http_server.o
	g++ -pthread $(LDFLAGS) -o dnsseed dns.o bitcoin.o netbase.o protocol.o db.o main.o util.o jj_http_message.o jj_http_server.o -lcrypto

%.o: %.cpp *.h
	g++ -std=c++11 -pthread $(CXXFLAGS) -Wall -Wno-unused -Wno-sign-compare -Wno-reorder -Wno-comment -c -o $@ $<
