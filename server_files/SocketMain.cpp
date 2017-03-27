#include "GarbageCollector.h"
#include "TCPServerSocket.h"

int main(){
	// INstantiate a new TCPSocketServer Object that listens on all interfaces on port 9999
	TCPServerSocket * tcpServerSocket = new TCPServerSocket("0.0.0.0",9999,100);
	// Instantiate a connection garbage collector
	GarbageCollector * garbageCollector = new GarbageCollector();
	// initialize the server socket
	tcpServerSocket->initializeSocket();
	for(;;)// loop server
	{
		// Wait for connection and return a TCPSocket Object upon one.
		TCPSocket * tcpSocket = tcpServerSocket->getConnection();
		if(tcpSocket == NULL) break;
		garbageCollector->cleanup();
		Connection * c = new Connection(tcpSocket);
		c->start();
		garbageCollector->addConnection(c);
	}
	delete(garbageCollector);
	delete(tcpServerSocket);
	return 0;
}

