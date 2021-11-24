#ifndef __NETWORK__
#define __NETWORK__
#include <WiFi.h>
#include <LoRa.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
class Network{
    private:
        const char* ssid  = "IoT";
        const char* password = "Cucamonga";
        const int httpport = 80;
        char* Server;
        void initNetwork();
        void initHttpConnection();
        HTTPClient  micliente;
        WiFiClient client;
        HTTPClient micliente2;

    public:
        Network();
        ~Network();
        void buildClient(const char* host,const char* host2);
        int doPostDataPacket(String dst,String src, String type,String payload ,String sizExtra,String* address,String* metric);
        int doPostRoutingTable(String address,String metric,String lastSeqNo,String timeout,String via);
        void setHost(char* host);

    
};
    

#endif