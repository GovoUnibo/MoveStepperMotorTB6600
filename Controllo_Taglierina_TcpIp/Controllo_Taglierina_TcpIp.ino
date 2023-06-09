#include <SPI.h>
#include <Ethernet.h>
#include "Stepper_taglierina.hpp"


byte mac[] = { 0x84, 0x42, 0x8B, 0xBA, 0xB2, 0x31 };
IPAddress ip(192, 168, 1, 100);
IPAddress gateway(192,168,1,2);
IPAddress DNSserver(192,168,5,200);
IPAddress subnet(255,255,255,0);
EthernetServer server(80); 
EthernetClient client;

#define STEPPER_ENABLE_PIN 8
#define STEPPER_DIR_PIN 9
#define STEPPER_STEP_PIN 10

using namespace taglierina;
Stepper Blade(1,STEPPER_ENABLE_PIN,STEPPER_DIR_PIN,STEPPER_STEP_PIN);

enum eStateMachine {INIT, HOME, HOME_DONE, CUT_BIG, CUT_SMALL, MOTOR_STOP, OPERATE_GRIPPER};
eStateMachine State; // Overall state machine


void setup() {
  Ethernet.begin(mac, ip, DNSserver, gateway, subnet);
  Serial.begin(9600);

  Serial.print("Indirizzo ip del server: ");
  Serial.println(Ethernet.localIP());

  server.begin();
  
  State = INIT;


}

void loop() {
      Blade.setHomeDone();
      Serial.println(Blade.getCurrentPositionDistance());
      Blade.moveToDistance(100,78,200);
      Serial.println(Blade.getCurrentPositionDistance());
      Blade.setHomeDone();
      Serial.println(Blade.getCurrentPositionDistance());
      delay(1000);

}

String waitCommand(){
   
  client = server.available();  
  if (client) {
    Serial.println("Connection With Client Estabilished");
    // if (client.available() > 0) {
    if (client.connected() > 0) {
        String message = client.readStringUntil('\n');
        Serial.println("Received message: " + message);
        client.println("Received message: " + message);  // Send response back to client
        return message;
    }
  }

  return "";

}
