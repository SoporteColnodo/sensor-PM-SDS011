#ifndef INDICADOR_H
#define INDICADOR_H


#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
int tm = 1000;

void InicioLCD(){
  lcd.clear();
  //lcd.noBacklight();
  lcd.setCursor(0, 0);
  lcd.print("AIR Data: ");
  lcd.setCursor(0, 1);
  lcd.print("iniciando... ");
}

void IndicadorGeneral(double latitud, double longitud,double pm25, double pm10) {
  lcd.clear();
  //lcd.noBacklight();
  lcd.setCursor(0, 0);
  lcd.print("PM2.5: ");
  lcd.print(pm25);
  lcd.setCursor(0, 1);
  lcd.print("PM10: ");
  lcd.print(pm10);
  lcd.setCursor(0, 2);
  lcd.print("Lat: ");
  lcd.print(latitud,6);
  lcd.setCursor(0, 3);
  lcd.print("Lon: ");
  lcd.print(longitud,6);

  delay(tm);
}

void okguardarSD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("La  informacion se  ");
  lcd.setCursor(0, 1);
  lcd.print("guardo correctamente");

  delay(tm);
}

void okcreacionSD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Los archivos csv se ");
  lcd.setCursor(0, 1);
  lcd.print("crearon corrctamente");

  delay(tm);
}

void errSD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error al inicializar");
  lcd.setCursor(0, 1);
  lcd.print("la tarjeta SD      ");

  delay(tm);
}

void okApi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enviando Información");
  lcd.setCursor(0, 1);
  lcd.print("al API..............");

  delay(tm);
}

void errApi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error en la conexión");
  lcd.setCursor(0, 1);
  lcd.print("a internet (4g)    ");

  delay(tm);
}

void okGPS() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Señal GPS correcta");

  delay(tm);
}

void errGPS() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Los disp. Aire o GPS");
  lcd.setCursor(0, 1);
  lcd.print("arrojan valores NULL");

  delay(tm);
}

void reinicioESP() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Se superó el máximo ");
  lcd.setCursor(0, 1);
  lcd.print("de intentos.Reinicio");

  delay(tm);
}

void errRTC() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error, RTC no proporciona valores validos");

  delay(tm);
}

#endif // INDICADOR_H