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

 void Network::buildClient(const char* host,const char*host2){
     micliente.begin(host);
     micliente.addHeader("User-Agent", "DataServer/1.0", true, true);
     micliente.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);
     micliente2.begin(host2);
     micliente.addHeader("User-Agent", "DataServer/1.0", true, true);
     micliente.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);

}
int Network::doPostDataPacket(String dst,String src, String type,String payload,String sizExtra,String* address,String* metric){
  int res = 0;
   /*
   StaticJsonDocument<500> doc;
   JsonArray addressValues = doc.createNestedArray("address");
   JsonArray metricValues = doc.createNestedArray("metric");
   for(int i =0;i < size;i++){
        addressValues.add(address[i]);
        metricValues.add(metric[i]);
   }
   doc["dst"] = dst;
   doc["src"] = src;
   doc["type"]= type;
   doc["payload"]= sizExtra;

  JsonObject obj = doc.to<JsonObject>();
  */
  res = micliente.POST("dst="+dst+"&src="+src+"&type="+type+"&payload="+payload+"&sizExtra="+sizExtra+"&address"+*address+"&metric"+*metric);
  
  if (res == -1) Serial.println("He intentado enviar el mensaje al servidor, pero he recibido error -1. Parece que el servidor está desconectado o no responde");
    else {
      Serial.print("He enviado el mensaje al servidor, y me ha devuelto un código HTTP ");
      Serial.println(res);
    }
  return res;
}

int Network::doPostRoutingTable(String address,String metric,String lastSeqNo,String timeout,String via){
    int res = 0;
    res = micliente.POST("address="+address+"&metric="+metric+"&lastSeqNo="+lastSeqNo+"&timeout"+timeout+"&via=");
    if (res == -1) Serial.println("He intentado enviar el mensaje al servidor, pero he recibido error -1. Parece que el servidor está desconectado o no responde");
    else {
      Serial.print("He enviado el mensaje al servidor, y me ha devuelto un código HTTP ");
      Serial.println(res);
    }
    return res;
}



