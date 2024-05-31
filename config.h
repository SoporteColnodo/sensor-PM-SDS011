//const char* ssid = "Colnodo";     // Nombre de la red WiFi
//const char* password = "%Colnodo-/830-/00/2017.X";  
const char* hostname = "ESP32AIRE_02"; // nombre del dispositivo

extern String User = "esp32airecolnodo_002@colnodo.apc.org";//nombre del dispositivo en AA
extern String Password = "V4X12PbA13xG17.";//contraseña del dispositivo en AA
extern String idDispositivo = "dd20844abe8020aec75fc1dcdf26c09a";//id del dispositivo

extern const long minutos = 2;  // tiempo en milisegundos
extern const long intervalSD = minutos * 60000;// 2 minutos tiempo en milisegundos - 60000 tiempo 2 minutos
extern const long hora = 3600000; // tiempo en milisegundos - 3600000 tiempo 1 hora

extern unsigned long previousMillisSD = 0; //tiempo inicial de envio a SD
extern int maxAttempts = 15; //intentos antes de finalizar proceso
extern int currentAttempts = 0;
extern uint32_t maxciclos = 0;
extern int tmg = 100; //valores delay inicio

IPAddress ip(192, 168, 7, 303); //IP del dispositivo
IPAddress gateway(192, 168, 7, 1); //IP-gateway del dispositivo
IPAddress subnet(255, 255, 255, 0); //IP-subnet del dispositivo