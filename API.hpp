#include <HTTPClient.h>
#include <ArduinoJson.h>

String ApiHost = "https://api.rds.org.co";
String previousID = "";

bool isNewRecord(String currentID) {
  // Compara el registro actual con el registro anterior
  if (currentID != previousID) {
    // Si son diferentes, actualiza el registro anterior y devuelve true
    previousID = currentID;
    return true;
  } else {
    // Si son iguales, devuelve false
    return false;
  }
}

//Autenticación de usuario
String LoginUser(String User, String Password)
{
  HTTPClient http;
  http.begin(ApiHost + "/usuarios/login");
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<256> authRequest;
  String requestBody;

  authRequest["email"] = User;
  authRequest["password"] = Password;
 
  serializeJson(authRequest, requestBody);
  int httpResponseCode = http.POST(requestBody);
  
  if (httpResponseCode == 201) { 
    //Serial.println("Autenticación exitosa");
    String token = http.getString();
    //Serial.println(token);
    return token;
    http.end();
  } else {
    Serial.print("Error de Autenticación, error:");
    Serial.println(httpResponseCode);
    http.end();
  }
   http.end();
}

//Generación de token y envio de información
String CrearRegistro(double lat, double lng, double pm25, double pm10,String Token)
{
  HTTPClient http;
  http.begin(ApiHost + "/alertas/registro");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + Token); 

  StaticJsonDocument<512> authRequest;
  String requestBody;

  authRequest["categoria"] = "aire";
  authRequest["tiempo"] = "";
  authRequest["pm25m"] = pm25;
  authRequest["pm100m"] = pm10;
  authRequest["latitud"] = lat;
  authRequest["longitud"] = lng;
 
  serializeJson(authRequest, requestBody);
  int httpResponseCode = http.POST(requestBody);
  
  if (httpResponseCode == 201) {
  String ingreso_ok = http.getString();
  //Serial.println(ingreso_ok);
  http.end();
  if(isNewRecord(ingreso_ok)){
  Serial.print("Dato registrado con el ID:");  
  Serial.println(ingreso_ok);
  }
  return ingreso_ok;
  } else {
    Serial.print("Error de Autenticación, error:");
    Serial.println(httpResponseCode);
    http.end();
  }
   http.end();
}