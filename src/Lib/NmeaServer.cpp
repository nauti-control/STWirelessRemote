#include "NmeaServer.h"

NmeaServer::NmeaServer()
{
    _server = new AsyncServer(8091); // start listening on tcp port 8091
    _server->onClient(&handleNewClient, this);
    _server->begin();
}

void NmeaServer::sendMessageToClients(const String &message)
{

    for (AsyncClient *client : _clients)
    {
        if (client->connected() && client->canSend())
        {
            client->write(message.c_str(), message.length());
        }
    }
}

void NmeaServer::addClient(AsyncClient *client)
{
    // add to list
    _clients.push_back(client);

    // register events
    client->onData(&handleData, this);
    client->onError(&handleError, this);
    client->onDisconnect(&handleDisconnect, this);
    client->onTimeout(&handleTimeOut, this);
}

void NmeaServer::removeClient(AsyncClient *client)
{
    _clients.erase(std::remove(_clients.begin(), _clients.end(), client), _clients.end());
}

void NmeaServer::handleError(void *arg, AsyncClient *client, int8_t error)
{
    NmeaServer *server = static_cast<NmeaServer *>(arg);
    Serial.printf("\n connection error %s from client %s \n", client->errorToString(error), client->remoteIP().toString().c_str());
}

void NmeaServer::handleData(void *arg, AsyncClient *client, void *data, size_t len)
{
    NmeaServer *server = static_cast<NmeaServer *>(arg);
}

void NmeaServer::handleDisconnect(void *arg, AsyncClient *client)
{
    NmeaServer *server = static_cast<NmeaServer *>(arg);
    Serial.printf("\n client %s disconnected \n", client->remoteIP().toString().c_str());
    server->removeClient(client);
}

void NmeaServer::handleTimeOut(void *arg, AsyncClient *client, uint32_t time)
{
    NmeaServer *server = static_cast<NmeaServer *>(arg);
    Serial.printf("\n client ACK timeout ip: %s \n", client->remoteIP().toString().c_str());
}

/* server events */
void NmeaServer::handleNewClient(void *arg, AsyncClient *client)
{
    NmeaServer *server = static_cast<NmeaServer *>(arg);
    Serial.printf("\n new client has been connected to server, ip: %s", client->remoteIP().toString().c_str());
    server->addClient(client);
}
