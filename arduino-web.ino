#include <WiFi101.h>

char ssid[] = "The_One";       // Nom du réseau WiFi
char pass[] = "0506200120060230"; // Mot de passe du réseau WiFi

WiFiServer server(80); // Création d'un serveur web sur le port 80

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Connexion au réseau WiFi
  if (WiFi.begin(ssid, pass) == WL_CONNECTED) {
    Serial.println("Connecté au réseau WiFi");
    server.begin(); // Démarrage du serveur web
  } else {
    Serial.println("Erreur de connexion au réseau WiFi");
    while (1);
  }
}

void loop() {
  WiFiClient client = server.available(); // Vérification de la connexion client

  if (client) {
    Serial.println("Nouvelle connexion");

    // Lecture de la requête HTTP
    String request = client.readStringUntil('\r');
    Serial.println(request);

    // Vérification de la carte RFID lue
    if (request.indexOf("GET /?carte=carte_bonne") != -1) 
    {
      client.println("HTTP/1.1 301 Moved Permanently");
      client.println("Location: /page_coordonnees_humidite.html");
      client.println("Connection: close");
      client.println();
    } 
    else 
    {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();
      client.println("<html><body>");
      client.println("<h1>Carte incorrecte, veuillez réessayer.</h1>");
      client.println("</body></html>");
    }

    client.stop(); // Fermeture de la connexion client
  }
}
