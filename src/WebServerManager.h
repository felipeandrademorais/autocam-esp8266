#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <StoreManager.h>

class WebServerManager {
private:
    ESP8266WebServer server;
    StoreManager storeManager;

public:
    WebServerManager() : server(80) {
        server.on("/", [this]() { this->handleRoot(); });
        server.on("/connect", [this]() { this->handleConnect(); });
        server.begin();
        Serial.println("Servidor iniciado");
    }

    void handleClient() {
        server.handleClient();
    }

private:
    void handleRoot() {
        String page = "<!DOCTYPE html><html lang=\"pt-br\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Configuração Wi-Fi</title></head><body><h1>Selecione uma rede Wi-Fi</h1>";
        int n = WiFi.scanNetworks();
        if (n == 0) {
            page += "<p>Nenhuma rede encontrada. Tente novamente.</p>";
        } else {
            for (int i = 0; i < n; ++i) {
                page += "<form action=\"/connect\" method=\"post\">";
                page += "<input type=\"hidden\" name=\"ssid\" value=\"" + WiFi.SSID(i) + "\">";
                page += "<button type=\"submit\">" + WiFi.SSID(i) + "</button>";
                page += "</form>";
            }
        }
        page += "</body></html>";
        server.send(200, "text/html", page);
    }

    void handleConnect() {
        String ssid = server.arg("ssid");
        String page = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Conectar à Rede</title></head><body>";
        page += "<h1>Conectar à rede: " + ssid + "</h1>";
        page += "<form action=\"/save\" method=\"post\">";
        page += "<input type=\"hidden\" name=\"ssid\" value=\"" + ssid + "\">";
        page += "<label for=\"pass\">Senha:</label><input type=\"password\" id=\"pass\" name=\"pass\">";
        page += "<input type=\"submit\" value=\"Salvar e Conectar\">";
        page += "</form></body></html>";
        server.send(200, "text/html", page);
        server.on("/save", [this]() { this->handleSave(); });
    }

    void handleSave() {
        String ssid = server.arg("ssid");
        String pass = server.arg("pass");
        WiFi.begin(ssid.c_str(), pass.c_str());

        delay(5000);

        if (WiFi.status() == WL_CONNECTED) {
            server.send(200, "text/html", "<p>Conectado com sucesso a " + ssid + ". IP: " + WiFi.localIP().toString() + "</p>");
            storeManager.saveCredentials(ssid, pass);
            delay(1000);
            ESP.restart();
        } else {
            server.send(200, "text/html", "<p>Falha ao conectar a " + ssid + ". <a href=\"/\">Tente novamente</a></p>");
        }
    }
};
