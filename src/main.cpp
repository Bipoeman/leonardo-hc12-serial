#include <Arduino.h>
#define CONFIG_PIN 2

void processCommand(String command);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  pinMode(CONFIG_PIN,OUTPUT);
  digitalWrite(CONFIG_PIN,HIGH);
}
enum RECEIVE_STATE{
  DATA_STATE,
  PROCESSING_STATE,
  COMMAND_STATE
};
int receiveState = DATA_STATE;
String command;
void loop() {
  if(Serial1.available()){
    Serial.write(Serial1.read());
  }
  if(Serial.available()){
    char c = Serial.read();
    if (c == '/' && command.length() == 0){
      receiveState = PROCESSING_STATE;
      
    }
    else if (c == '\r' || c == '\n'){
      processCommand(command);
      command = "";
      receiveState = DATA_STATE;
    }
    if (receiveState == PROCESSING_STATE){
      command += c;
    }
    else {
      Serial1.write(c);
    }
  }
}

void processCommand(String command){
  command.trim();
  if (command.compareTo("/command") == 0){
     digitalWrite(CONFIG_PIN,!digitalRead(CONFIG_PIN));
     Serial.println("-----------------------------------------------------------------------");
     Serial.println(digitalRead(CONFIG_PIN) == 1 ? "DATA Mode" : "COMMAND Mode");
  }
}

