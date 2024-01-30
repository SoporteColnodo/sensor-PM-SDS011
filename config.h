const char* ssid = "Colnodo_ETB";     // Nombre de la red WiFi
const char* password = "Colnodo-1700.";  
const char* hostname = "ESP32AIRE_04"; // nombre del dispositivo

extern String User = "esp32airecolnodo_004@colnodo.apc.org";//nombre del dispositivo en AA
extern String Password = "V4X2PbA3xG7.";//contraseña del dispositivo en AA

extern const long minutos = 2;  // tiempo en milisegundos
extern const long intervalSD = minutos * 60000;// 2 minutos tiempo en milisegundos
extern const long hora = 3600000; // tiempo en milisegundos

extern unsigned long previousMillisSD = 0; //tiempo inicial de envio a SD
extern int maxAttempts = 15; //intentos antes de finalizar proceso
extern int currentAttempts = 0;
extern uint32_t maxciclos = 0;
extern int tmg = 100; //valores delay inicio

IPAddress ip(192, 168, 7, 9); //IP del dispositivo
IPAddress gateway(192, 168, 7, 1); //IP-gateway del dispositivo
IPAddress subnet(255, 255, 255, 0); //IP-subnet del dispositivo