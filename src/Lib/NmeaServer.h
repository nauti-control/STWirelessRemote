#ifndef NMEASERVER_H
#define NMEASERVER_H
#include <Arduino.h>
#include <AsyncTCP.h>
#include <vector>
class NmeaServer {

 public:
    NmeaServer();
    void addClient(AsyncClient *client);
    void removeClient(AsyncClient *client);
    void sendMessageToClients(const String &message);
 private:
   std::vector<AsyncClient*> _clients;
	AsyncServer *_server; // start listening on tcp port 9081
   static void handleNewClient(void* arg, AsyncClient* client);
   static void handleError(void* arg, AsyncClient* client, int8_t error);
   static void handleData(void* arg, AsyncClient* client, void *data, size_t len);
   static void handleDisconnect(void* arg, AsyncClient* client);
   static void handleTimeOut(void* arg, AsyncClient* client, uint32_t time);
   


   
};
#endif
