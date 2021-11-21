#include "network.h"
#include <functional>

Network::Network()
{
    initNetwork();
}

void Network::initNetwork(){
    delay(5000);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
}
Network::~Network(){

}

 void Network::buildClient(const char* host){
     micliente.begin(host);
    micliente.addHeader("User-Agent", "DataServer/1.0", true, true);
    micliente.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);
     

}
int Network::doPostDataPacket(String dst,String src, String type,String sizExtra,String address,String metric){
  int res = 0;
  micliente.POST("dst="+dst+"&src="+src+"&type="+type+"&payload"+sizExtra+"&address"+address+"&metric"+metric);
  micliente.addHeader("Content-Type", "application/json");
  return res;
}

int Network::doPostRoutingTable(String address,String metric,String lastSeqNo,String timeout,String via){
    

}



