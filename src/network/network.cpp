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
  micliente.end();
  micliente2.end();

}

 void Network::buildClient(const String host,const String host2){
     String host3 = "http://192.168.1.160:8080/get_test";
     micliente.begin(host.c_str());
     micliente.addHeader("User-Agent", "DataServer/1.0", true, true);
     micliente.addHeader("Content-Type", "application/json", false, true);
     micliente2.begin(host2.c_str());
     micliente.addHeader("User-Agent", "DataServer/1.0", true, true);
     micliente.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);
     
     micliente3.begin(host3.c_str());

}
int Network::doPostDataPacket(uint8_t dst,uint8_t src, uint8_t type,uint32_t payload,uint8_t sizExtra,uint8_t* address,int32_t* metric){
  int res = 0;
  char buffer[80] ;
   
   StaticJsonDocument<500> doc;
   JsonArray addressValues = doc.createNestedArray("address");
   JsonArray metricValues = doc.createNestedArray("metric");
   for(int i =0;i < sizeof(address)/sizeof(address[0]);i++){
        addressValues.add(address[i]);
        
   }
   for(int i = 0;i < sizeof(metric)/sizeof(metric[0]);i++){
      metricValues.add(metric[i]);
   }
  
   doc["dst"] = dst;
   doc["src"] = src;
   doc["type"]= type;
   doc["payload"]= sizExtra;

  JsonObject obj = doc.to<JsonObject>();
  serializeJson(obj,buffer);
  
  //sprintf(buffer,"dst=%02X&src=%02X&type=%02X&payload=%lu&sizExtra=%02X&address=%s&metric%s",dst,src,type,payload,sizExtra,*address,*metric);
  res = micliente.POST(buffer);
  
  if (res == -1) Serial.println("He intentado enviar el mensaje al servidor, pero he recibido error -1. Parece que el servidor está desconectado o no responde");
    else {
      Serial.print("He enviado el mensaje al servidor, y me ha devuelto un código HTTP ");
      Serial.println(res);
    }
  micliente.end();
  return res;
}

int Network::doPostRoutingTable(byte address,int metric,int lastSeqNo,unsigned long timeout,byte via){
    int res = 0;
    char buffer[80];
    sprintf(buffer,"address=%hhx&metric=%d&lastSeqNo=%d&timeout=%lu&via=%hhx",address,metric,lastSeqNo,timeout,via);
  
    res = micliente2.POST(buffer);
    if (res == -1) Serial.println("He intentado enviar el mensaje al servidor, pero he recibido error -1. Parece que el servidor está desconectado o no responde");
    else {
      Serial.print("He enviado el mensaje al servidor, y me ha devuelto un código HTTP ");
      Serial.println(res);
    }
    micliente2.end();
    return res;
}

    int Network::doGetTest(){
      int res = 0;
      res = micliente3.GET();
      if(res >=0){
        // Serial.println(micliente3.getString());

      }
      else {
         Serial.print("Error code: ");
        //Serial.println(res);
      }
      micliente3.end();
     
      return res;
    }




