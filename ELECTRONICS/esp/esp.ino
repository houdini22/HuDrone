#include <ESP8266WiFi.h>
#include <Arduino.h>

//#define ___DEBUG___ true

#define MESSAGE_DEFINITION "M"

#define MESSAGE_READY_1 "0001"
#define MESSAGE_READY_2 "0002"
#define MESSAGE_CLIENT_CONNECTED "0003"
#define MESSAGE_CLIENT_DISCONNECTED "0004"

#define PING_INTERVAL 200

const int TELNET_BUFFER_SIZE = 20;

//  WIFI SETUP
const char *AP__ssid = "ESP";
const char *AP__password = "ESP1234567890";
const int AP__channel = 5;
const int AP__hidden = 0;
const int AP__maxConnections = 1;

bool AP__started = false;
bool TELNET__started = false;
bool TELNET__connected = false;
const int TELNET__port = 23;

WiFiServer TELNET__server(TELNET__port);
WiFiClient TELNET;

bool SERVICES__started = false;
unsigned long PING__lastSent;
unsigned long PING__telnet__lastSent;
bool PING__telnet__begin = false;

bool started = false;

// helpers
#ifdef ___DEBUG___
void debug(String message) {
  Serial.println(message);
}
#endif

void ARDUINO__send(String msg) {
#ifdef ___DEBUG___
  debug("sending message to arduino:");
#endif
  
  Serial.print(msg);
  Serial1.print(msg);

#ifdef ___DEBUG___
  debug("");
#endif
}

void ARDUINO__sendMessage(String msg) {
  String message = String(MESSAGE_DEFINITION) + " " + String(msg);
  ARDUINO__send(message);
}

void TELNET__run(){
  if (!TELNET__connected) {
    if (TELNET__server.hasClient()) {
      // client is connected
      if (!TELNET || !TELNET.connected()) {
        if (TELNET) {                                   // client disconnected
          TELNET.stop();
        }              
        
        TELNET = TELNET__server.available();              // ready for new client
      } else {
        TELNET__server.available().stop();                // have client, block new conections
      }
      
      if (TELNET.connected()) {
        TELNET__connected = true;
#ifdef ___DEBUG___
        debug("telnet connected");
#endif
        delay(10);
        TELNET.write('C');
        PING__telnet__begin = true;
        PING__telnet__lastSent = millis();
      }
    }
  } else {
    if (!TELNET.connected()) {
      ARDUINO__sendMessage(MESSAGE_CLIENT_DISCONNECTED);
      _stop();
    } else {
      if (TELNET.available()) {
        // client input processing
        String buff = "";
        
        while (TELNET.available()) {
          char ch = TELNET.read();
          buff += String(ch);
          if (ch == 'T') {
            PING__telnet__lastSent = millis();
          }
        }
  
        // pass through
        if (buff.length() > 0) {
          ARDUINO__send(buff);
        }
      }
    }
  }
}

void AP__start() {
  while (!AP__started) {
#ifdef ___DEBUG___
    debug("starting ap");
#endif
    WiFi.mode(WIFI_AP);
    AP__started = WiFi.softAP(AP__ssid, AP__password, AP__channel, AP__hidden, AP__maxConnections);
#ifdef ___DEBUG___
    debug("ap started");
#endif
    delay(1000);
  }
}

void SERIAL__setup() {
  Serial.begin(57600);
  while (!Serial) {
    delay(500);
  };
  delay(500);
  
  Serial1.begin(57600);
  while (!Serial1) {
    delay(500);
  };
  delay(500);
  delay(1000);
  
#ifdef ___DEBUG___
  debug("hello");
#endif
}

void TELNET__start() {
  if (AP__started) {
    while (!TELNET__started) {
      TELNET__server.begin();
      TELNET__started = (bool) TELNET__server.status();
      if (TELNET__started) {
#ifdef ___DEBUG___
        debug("starting telnet server on port: " + (String) TELNET__port);
#endif
      }
    }
  }
}

void _start() {
  if (!started) {
    ARDUINO__sendMessage(MESSAGE_READY_1);
    SERVICES__start();
    ARDUINO__sendMessage(MESSAGE_READY_2);
    PING__lastSent = millis() / PING_INTERVAL;
    started = true;
  }
}

void _stop() {
  if (started) {
    SERVICES__stop();
    started = false;
    delay(1000);
  }
}

void setup() {
  SERIAL__setup();
  delay(1000);
}

void SERVICES__stop() {
  if (!SERVICES__started) return;
  
  if (AP__started) {
    AP__started = false;
    WiFi.softAPdisconnect(true);
  }
  
  if (TELNET__started) {
    TELNET__started = false;
    TELNET__server.close();
  }
  
  if (TELNET || TELNET__connected) {
    TELNET__connected = false;
    TELNET.stop();
  }

  SERVICES__started = false;
}

void SERVICES__start() {
  if (SERVICES__started) return;
  
  AP__start();
  TELNET__start();
  
  SERVICES__started = true;
}

void loop() {
  _start();
  
  bool p = false;

  if (started) {
    if ((millis() / 200) > PING__lastSent) {
      ARDUINO__send("P");
      PING__lastSent = (millis() / 200);
      delay(10);
      p = true;
    }
  }

  if (PING__telnet__begin) {
    if ((millis() - PING__telnet__lastSent) > 1000) {
      ARDUINO__sendMessage(MESSAGE_CLIENT_DISCONNECTED);
      PING__telnet__begin = false;
      _stop();
      return;
    }
  }

  if (!p) {
    delay(10);
    TELNET__run();
  }
}
