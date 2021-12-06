#ifndef __NETWORK__
#define __NETWORK__
#include <WiFi.h>
#include <LoRa.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <inttypes.h>


class Network{
    private:
        //const char* ssid  = "IoT";
        //const char* password = "Cucamonga";
        const char* ssid = "MOVISTAR_44B6";
        const char* password = "E2zeYs8s4t6uZJ86z2C9";
        const int httpport = 80;
        char* Server;
        void initNetwork();
        void initHttpConnection();
        HTTPClient  micliente;
        WiFiClient client;
        HTTPClient micliente2;
        HTTPClient micliente3;

    public:
        Network();
        ~Network();
        void buildClient(String host,String host2);
        int doPostDataPacket(uint8_t dst,uint8_t src, uint8_t type,uint32_t payload ,uint8_t sizExtra,uint8_t* address,int32_t* metric);
        int doPostRoutingTable(byte address,int metric,int lastSeqNo,unsigned long timeout, byte via);
        int doGetTest();
        void setHost(char* host);

    
};
    

#endif