#ifndef __NETWORK__
#define __NETWORK__
#include <WiFi.h>
#include <LoRa.h>
#include <HTTPClient.h>
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

    public:
        Network();
        ~Network();
        void buildClient(const char* host);
        int doPostDataPacket(String dst,String src, String type,String sizExtra,String address,String metric);
        int doPostRoutingTable(String address,String metric,String lastSeqNo,String timeout,String via);
        void setHost(char* host);

    
};
    

#endif