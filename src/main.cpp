#include <Seeed_Arduino_SSCMA.h>
#include <WiFi.h>
#include <HTTPClient.h>

SSCMA AI;

const char* ssid = "nombre_red"; 
const char* password = "pw_red"; 
const char* wled_ip = "ip_wled"; 
int preset=0;

void sendWledPreset(int preset); 

void setup() {
    AI.begin();
    Serial.begin(9600);


    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a la red WiFi...");
    }
    Serial.println("Conectado");
}

void loop() {
    if (!AI.invoke()) {
        Serial.println("invoke success");
        Serial.print("perf: preprocess=");
        Serial.print(AI.perf().prepocess);
        Serial.print(", inference=");
        Serial.print(AI.perf().inference);
        Serial.print(", postprocess=");
        Serial.println(AI.perf().postprocess);

        for (int i = 0; i < AI.boxes().size(); i++) {
            Serial.print("Box[");
            Serial.print(i);
            Serial.print("] target=");
            Serial.print(AI.boxes()[i].target);
            Serial.print(", score=");
            Serial.print(AI.boxes()[i].score);
            Serial.print(", x=");
            Serial.print(AI.boxes()[i].x);
            Serial.print(", y=");
            Serial.print(AI.boxes()[i].y);
            Serial.print(", w=");
            Serial.print(AI.boxes()[i].w);
            Serial.print(", h=");
            Serial.println(AI.boxes()[i].h);
            if (AI.boxes()[0].score > 0.2){
                preset = AI.boxes()[0].target;
                break;
                }
        }
        for (int i = 0; i < AI.classes().size(); i++) {
            Serial.print("Class[");
            Serial.print(i);
            Serial.print("] target=");
            Serial.print(AI.classes()[i].target);
            Serial.print(", score=");
            Serial.println(AI.classes()[i].score);
        }
        for (int i = 0; i < AI.points().size(); i++) {
            Serial.print("Point[");
            Serial.print(i);
            Serial.print("] target=");
            Serial.print(AI.points()[i].target);
            Serial.print(", score=");
            Serial.print(AI.points()[i].score);
            Serial.print(", x=");
            Serial.print(AI.points()[i].x);
            Serial.print(", y=");
            Serial.println(AI.points()[i].y);
        }


        sendWledPreset(preset+1); 
    }
}

void sendWledPreset(int preset) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "http://" + String(wled_ip) + "/win&PL=" + String(preset);
        http.begin(url);
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
            String response = http.getString();
            //Serial.println(httpResponseCode);
            //Serial.println(response);
        } else {
            Serial.print("Error al enviar GET: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    } else {
        Serial.println("No WiFi");
    }
}
