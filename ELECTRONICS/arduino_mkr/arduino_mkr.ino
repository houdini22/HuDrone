#include <WiFi101.h>
#include <Wire.h>
#include <LIS3MDL.h>
#include <LSM6.h>

#define ___DEBUG___

//LIS3MDL mag;
LSM6 imu;

char WIFI__SSID[] = "ESP";
char WIFI__password[] = "ESP1234567890";
int WIFI__status = WL_IDLE_STATUS;

WiFiClient TELNET;
IPAddress TELNET__IP = {192, 168, 4, 1};
int TELNET__port = 23;
bool TELNET__connected = false;
unsigned int TELNET__ping = 0;

unsigned int TEST__time = 0;
bool TEST1__sent = false;
bool TEST2__sent = false;
bool TEST3__sent = false;
bool TEST4__sent = false;
bool TEST5__sent = false;

float __imu_roll;
float __imu_pitch;

#ifdef ___DEBUG___
void debug(String message) {
  Serial.println(message);
}
#endif

void IMU__setup() {
  Wire.begin();
  //if (!mag.init()) {
//#ifdef ___DEBUG___
    //debug("Failed to detect and initialize magnetometer!");
//#endif
    //while (1);
  //}
  //mag.enableDefault();

  if (!imu.init()) {
#ifdef ___DEBUG___
    debug("Failed to detect and initialize IMU!");
#endif
    while (1);
  }
  imu.enableDefault();
}

void IMU__read() {
  //mag.read();
  imu.read();

  float accelX = imu.a.x;
  float accelY = imu.a.y;
  float accelZ = imu.a.z;
  //float gyroX = imu.g.x / 57.3;
  //float gyroY = imu.g.y / 57.3;
  //float gyroZ = imu.g.z / 57.3;
  //float magX = mag.m.x;
  //float magY = mag.m.y;
  //float magZ = mag.m.z;

  __imu_pitch = atan2(accelY, (sqrt((accelX * accelX) + (accelZ * accelZ))));
  __imu_roll = atan2(-accelX, (sqrt((accelY * accelY) + (accelZ * accelZ))));

   // yaw from mag
  //float Yh = (magY * cos(roll)) - (magZ * sin(roll));
  //float Xh = (magX * cos(pitch)) + (magY * sin(roll) * sin(pitch)) + (magZ * cos(roll) * sin(pitch));

  //float yaw =  atan2(Yh, Xh);
  
  __imu_roll = __imu_roll * 57.3;
  __imu_pitch = __imu_pitch * 57.3;
  //yaw = yaw * 57.3;
}

void WIFI__connect() {
  WIFI__status = WiFi.status();
  while (WIFI__status != WL_CONNECTED) {
    TELNET__connected = false;
#ifdef ___DEBUG___
    debug("Attempting to connect to network...");
#endif
    WIFI__status = WiFi.begin(WIFI__SSID, WIFI__password);
    for (int i = 5; i >= 0; i -= 1) {
      delay(1000);
      WIFI__status = WiFi.status();
      if (WIFI__status == WL_CONNECTED) {
#ifdef ___DEBUG___
        debug("Connected.");
        WIFI__printStatus();
#endif
        return;
      }
#ifdef ___DEBUG___
      debug(String(i) + " -> 0");
      debug("Status: " + String(WiFi.status()));
#endif
    }
  }
}

#ifdef ___DEBUG___
void WIFI__printStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());// print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);// print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
#endif

void setup() {
  IMU__setup();
#ifdef  ___DEBUG___
  Serial.begin(115200);
  while (!Serial) {
    delay(20);
  }
#endif
}

void TELNET__connect() {
  if (WIFI__status == WL_CONNECTED) {
    if (!TELNET__connected) {
      if (TELNET.connect(TELNET__IP, TELNET__port)) {
        while (!TELNET.available()) {
#ifdef ___DEBUG___
          debug("Waiting...");
#endif
          delay(5);
        }
        while (TELNET.available()) {
          char ch = TELNET.read();
          if (ch == 'C') {
            TELNET__connected = true;
            break;
          }
        }
        if (TELNET__connected) {
          delay(5);
          TELNET__send("M 0003");
          TELNET__ping = millis() / 200;
          TEST__time = millis();
#ifdef ___DEBUG___
          debug("Telnet connected.");
#endif
        }
      } else {
#ifdef ___DEBUG___
        debug("Telnet cannot connect.");
#endif
        delay(100);
      }
    }
  }
}

void TELNET__send(char message[]) {
#ifdef ___DEBUG___
  debug("TELNET__send: " + String(message));
#endif
  TELNET.write(message);
}

void TELNET__send(const char message[]) {
#ifdef ___DEBUG___
  debug("TELNET__send: " + String(message));
#endif
  TELNET.write(message);
}

void IMU__send() {
  if (TELNET__connected) {
    IMU__read();
    String send_imu = "I ";
    send_imu += String(__imu_pitch);
    send_imu += "$";
    TELNET__send(send_imu.c_str());
  
    send_imu = "R ";
    send_imu += String(__imu_roll);
    send_imu += "$";
    TELNET__send(send_imu.c_str());
  }
}

void loop() {
  IMU__send();
  
  if (TELNET__connected) {
    if ((millis() / 200) > TELNET__ping) {
      TELNET__ping = millis() / 200;
      TELNET__send("T");
    }
  }
  
  WIFI__connect();
  TELNET__connect();
  
  if (TEST__time > 0) {
    if (millis() - TEST__time > 8000 && !TEST1__sent) {
      TELNET__send("B 01");
      TEST1__sent = true;
    }
    if (millis() - TEST__time > 16000 && !TEST2__sent) {
      TELNET__send("B 02");
      TEST2__sent = true;
    }
    if (millis() - TEST__time > 24000 && !TEST3__sent) {
      TELNET__send("B 03");
      TEST3__sent = true;
    }
    if (millis() - TEST__time > 32000 && !TEST4__sent) {
      TELNET__send("B 04");
      TEST4__sent = true;
    }
    if (millis() - TEST__time > 40000 && !TEST5__sent) {
      TELNET__send("B 05");
      TEST5__sent = true;
    }
  }
  
  delay(20);
}
