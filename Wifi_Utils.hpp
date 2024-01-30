#include <WiFi.h>

bool ConnectWiFi_STA(bool useStaticIP = false)
{
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   if(useStaticIP) WiFi.config(ip, gateway, subnet);
   unsigned long start_time = millis();
   while (WiFi.status() != WL_CONNECTED) 
   {
     Serial.print(".");
     delay(100);
     if (millis() - start_time >= 4500) { //desconectar a los 30 segundos
      Serial.println("");
      Serial.println("Error al conectar a WiFi");
      errApi();
      WiFi.disconnect(true);
      return false;
      //while(1);
      //WiFi.disconnect(true);
    }
   }
 
   Serial.println("");
   Serial.print("Proceso iniciado de:\t");
   Serial.println(hostname);
   Serial.print("Dirección IP:\t");
   Serial.println(WiFi.localIP());
   return true;
}
