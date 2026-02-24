CXX = g++
CXXFLAGS = -Wall -Werror

all: loadbalancer

loadbalancer: main.o Request.o RequestQueue.o WebServer.o IpRange.o Config.o LogFile.o LoadBalancer.o
	$(CXX) $(CXXFLAGS) -o loadbalancer main.o Request.o RequestQueue.o WebServer.o IpRange.o Config.o LogFile.o LoadBalancer.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Request.o: Request.cpp
	$(CXX) $(CXXFLAGS) -c Request.cpp

RequestQueue.o: RequestQueue.cpp
	$(CXX) $(CXXFLAGS) -c RequestQueue.cpp

WebServer.o: WebServer.cpp
	$(CXX) $(CXXFLAGS) -c WebServer.cpp

IpRange.o: IpRange.cpp
	$(CXX) $(CXXFLAGS) -c IpRange.cpp

Config.o: Config.cpp
	$(CXX) $(CXXFLAGS) -c Config.cpp

LogFile.o: LogFile.cpp
	$(CXX) $(CXXFLAGS) -c LogFile.cpp

LoadBalancer.o: LoadBalancer.cpp
	$(CXX) $(CXXFLAGS) -c LoadBalancer.cpp

clean:
	rm -f loadbalancer *.o log.txt