#include "websocket.h"
char ssid[] = "tufts_eecs";
char pass[] = "foundedin1883";

char serverAddress[] = "35.239.140.61"; // server address
int port = 8080;
WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
String clientID = "8050D1451904"; //Insert your Server ID Here!
String clientID_RIDGE = "89C87865077A"; //Insert your Server ID Here!
int status = WL_IDLE_STATUS;
int count = 0;

void setupSocket(){
    
    while ( status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Network named: ");
        Serial.println(ssid); // print the network name (SSID);

        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);
    }
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    //connect to server
    Serial.println("starting WebSocket client");
    client.begin();
    client.beginMessage(TYPE_TEXT);
    client.print(clientID);
    client.endMessage();

    Serial.println("Done starting websocket");
}

void writeMessage(String message){
    if(client.connected()){
        client.beginMessage(TYPE_TEXT);
        client.print(message);
        client.endMessage();
    }
    //Serial.println(message);
}

String readMessage(){
    String response;
    if(client.connected()){
        client.parseMessage();
        response = client.readString();
    }
    return response;
}

String parseID(String message) {
    int underscoreIndex = message.indexOf('_');   // Find "_"
    if (underscoreIndex == -1) {
        // No underscore found → return empty or entire string (your choice)
        return message;
    }
    return message.substring(0, underscoreIndex);  // Everything before "_"
}

String getMessage(String message){
    while(message[0] != '.')
        message.remove(0,1);
    message.remove(0,1);
    return message;
}

int parseMessage(){
    return client.parseMessage();
}