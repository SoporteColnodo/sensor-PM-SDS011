/*
El proceso de toma de datos en la siguiente aplicación consta de las siguiente etapas:
1.Cargue de dispositivos en serial2 de ESP32 (respuesta correcta de GPS,  sds011 aire Y SD)
2.Cada ciclo de toma de información de los dispositivos se evalua para que sean diferentes a O (cero)
3.Se genera un ciclo especial de 5 segundos 5000 ms para enviar información a la SD
4.Si la información enviada a SD es correcta se guarda en un archivo distinto cada hora (ver nota)
5. Si hay un error en la conexión a wifi, se crea un archivo de respaldo para subir la información manualmente

La hora se estima a partir de los ciclos que se programaron de 2 minutos restandolos de la hora actual generada
por el RTC
*/

#include "RTC_Utils.hpp"
#include <TinyGPSPlus.h>
#include "config.h"
#include "indicador.h"
#include "Wifi_Utils.hpp"
#include "SD_Utils.hpp"
#include "API.hpp"
#include <SoftwareSerial.h>

//variables inicializar librerias y seriales
HardwareSerial gpsSerial(2);
SoftwareSerial sdsSerial(25, 26);
TinyGPSPlus gps;

// variables muestra en pantalla -PMS -SD nombre
bool mostrarIndicador = true;

double pm25 = 0.0;      // PM25  
double pm10 = 0.0;      // PM10  
double latitud = 0.0;   // latitud
double longitud = 0.0;  // longitud

DateTime fecha;
  
void setup() {
RTCSet();
SDSet();
InicioLCD();
lcd.init();
Serial.begin(9600);
gpsSerial.begin(9600);
sdsSerial.begin(9600);
delay(2000);
fecha = DS1307_RTC.now();
uint32_t milisegundosEnHora = fecha.minute() * 60000 + fecha.second() * 1000;
maxciclos = (hora - milisegundosEnHora) / intervalSD;
}

void loop() {
unsigned long currentMillis = millis();
generarPM(); // muestra PMS
generarLatLng(); // muestra latitud longitud
if (mostrarIndicador) {
IndicadorGeneral(latitud, longitud, pm25, pm10); 
}
mostrarIndicador = true;
Serial.println(maxciclos);
if (currentMillis - previousMillisSD >= intervalSD) {
static int contador = 0; 
static double promedioPM25 = 0.0;
static double promedioPM10 = 0.0;
static String nombreArchivo;

previousMillisSD = currentMillis;
DateTime fecha = DS1307_RTC.now();
Serial.println(maxciclos);
if (latitud != 0.0 && longitud != 0.0 && pm25 != 0.0 && pm10 != 0.0) {
nombreArchivo = String(fecha.day()) + "-" + String(fecha.month()) + "-" + String(fecha.year()) +  "-" + String(fecha.hour()) + ".csv";
crearArchivo(nombreArchivo);
okcreacionSD();
guardaInformacionCSV(latitud, longitud, pm25, pm10, fecha, nombreArchivo);
mostrarIndicador = false;
okguardarSD();
contador++;
if (contador >= maxciclos) {
promedioPM25 = calcularPromedioPM(nombreArchivo,maxciclos,"pm25");// se lee archivo y calculan promedios
promedioPM10 = calcularPromedioPM(nombreArchivo,maxciclos,"pm10");// se lee archivo y calculan promedios
if(ConnectWiFi_STA()){
CrearRegistro(latitud, longitud, promedioPM25, promedioPM10, LoginUser(User, Password));
WiFi.disconnect(true);
delay(tmg);
mostrarIndicador = false;
okApi();//indicador
sdsSerial.end();
}else{
crearArchivo("informacion_manual_aa.csv");
guardaInformacionCSV(latitud, longitud, promedioPM25, promedioPM10, fecha, "informacion_manual_aa.csv");
delay(tmg);
mostrarIndicador = false;
errApi();
sdsSerial.end();
}
contador = 0;
}
} else {
Serial.println("Error: GPS no proporciona valores válidos para la API.");
mostrarIndicador = false;
errGPS();
currentAttempts++;
if (currentAttempts >= maxAttempts) {
Serial.println("Se superó el número máximo de intentos. Reiniciando.");
reinicioESP();
while (true) {
ESP.restart();
}
}
}
}
}

void generarLatLng() {
while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      latitud = gps.location.lat();
      longitud = gps.location.lng();
      Serial.println(latitud);
      Serial.println(longitud);
    }
  }
}

void generarPM() {
static byte buffer[10];
Serial.print("valor available pm25: ");
Serial.println(sdsSerial.available());
while (sdsSerial.available() >= 10) {
sdsSerial.readBytes(buffer, 10);
pm25 = ((buffer[3] << 8) | buffer[2]) / 10.0;
Serial.println(pm25);
pm10 = ((buffer[5] << 8) | buffer[4]) / 10.0;
Serial.println(pm10);
}
}