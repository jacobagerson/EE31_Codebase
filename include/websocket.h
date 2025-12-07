/*
    Simple WebSocket client for ArduinoHttpClient library
    created 9/18/25
    by Cooper Bailey
    Based on the example provided to us in class 
*/

#include "WebSocketClient.h"
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <Arduino.h>

void writeMessage(String message);
String readMessage();
void setupSocket();
String parseID(String message);
String getMessage(String message);
int parseMessage();

