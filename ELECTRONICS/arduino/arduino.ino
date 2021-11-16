#include <EZPROM.h>

////////////////////// PPM CONFIGURATION ///////////////////////////////
#define CHANNELS_NUMBER       8           // set the number of chanels
#define DEFAULT_SERVO_VALUE   1500        // set the default servo value
#define PPM_FRAME_LENGTH      22500       // set the PPM frame length in microseconds (1ms = 1000µs) (2.5ms * (NUM_CHANNELS + 1)
#define PPM_PULSE_LENGTH      300         // set the pulse length
#define POLARITY              1           // set polarity of the pulses: 1 is positive, 0 is negative
#define SIGNAL_PIN            2           // set PPM signal output pin on the arduino
///////////////////////////////////////////////////////////////////////

////////////////////// LED CONFIGURATION ///////////////////////////////
#define LED_R_PIN 8
#define LED_G_PIN 9
#define LED_B_PIN 10

#define LED_R_HIGH 102
#define LED_G_HIGH 127
#define LED_B_HIGH 168
///////////////////////////////////////////////////////////////////////

//
int defaultPpmValues[CHANNELS_NUMBER] = {1500, 1500, 1100, 1500, 1100, 1100, 1100, 1100};
int ppm[CHANNELS_NUMBER] = {1500, 1500, 1100, 1500, 1100, 1100, 1100, 1100};

#define ___DEBUG___ true

#define RUN_MODE_ZERO '\0'
#define RUN_MODE_ESP_ERROR '0'
#define RUN_MODE_INIT1 '1'
#define RUN_MODE_READY 'R'
#define RUN_MODE_TESTING 'T'
#define RUN_MODE_SENDING 'S'
#define RUN_MODE_TESTING_IMU 'I'

#define MESSAGE__TYPE_MESSAGE 'M'
#define MESSAGE__TYPE_BUTTON 'B'
#define MESSAGE__TYPE_BUTTON_RELEASE 'N'
#define MESSAGE__TYPE_IMU__PITCH 'I'
#define MESSAGE__TYPE_IMU__ROLL 'R'

#define COMMAND_LED_PURPLE 0
#define COMMAND_LED_RED 1
#define COMMAND_LED_GREEN 2
#define COMMAND_LED_BLUE 3
#define COMMAND_LED_OFF 4
#define COMMAND_RUN_MODE_TESTING 5
#define COMMAND_RUN_MODE_INIT1 6
#define COMMAND_RUN_MODE_READY 7
#define COMMAND_RUN_MODE_ESP_ERROR 8
#define COMMAND_RUN_MODE_TESTING_NEXT 9
#define COMMAND_RUN_MODE_TESTING_INC 10
#define COMMAND_RUN_MODE_TESTING_IMU 11
#define COMMAND_RUN_MODE_SENDING 12

#define QUEUE__ITEMS_SIZE 20

struct QUEUE__ITEM {
  unsigned long when;
  int command;
  char runMode;
};
QUEUE__ITEM _queue__container[QUEUE__ITEMS_SIZE];
int _queue__containerSize = -1;
unsigned long _esp__lastPingReceived = 0;
unsigned long _esp__lastTelnetPingReceived = 0;
unsigned long _esp__lastPingSent = 0;
bool _message__started = false;
char _message__type = '\0';
int _message__type_length = 0;
char _run_mode__current = RUN_MODE_ZERO;
int _run_mode__testing__currentButton = 0;
bool _run_mode__testing__waiting = false;
bool _radio__sending = false;

String _pitch_str;
String _roll_str;
float _pitch = 0;
float _roll = 0;

bool _run_mode__testing_imu__x1 = false;
bool _run_mode__testing_imu__x2 = false;
bool _run_mode__testing_imu__y1 = false;
bool _run_mode__testing_imu__y2 = false;

bool _run_mode__preparing__espError = false;
bool _run_mode__preparing__send = false;

bool _button_1_pressed = false;
bool _button_2_pressed = false;
bool _button_3_pressed = false;
bool _button_4_pressed = false;
bool _button_5_pressed = false;

void startTimer() {
  cli();
  TCCR1A = 0;                             // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;                            // compare match register, change this
  TCCR1B |= (1 << WGM12);                 // turn on CTC mode
  TCCR1B |= (1 << CS11);                  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A);                // enable timer compare interrupt
  sei();
}

void stopTimer() {
  TCCR1B = 0;
  TIMSK1 |= (0 << OCIE1A);
}

// helpers
void debug(String message) {
  if (___DEBUG___) {
    Serial.println(message);
  }
}

void debug(char ch) {
  if (___DEBUG___) {
    Serial.println(ch);
  }
}

void SERIAL__setup() {
  Serial.begin(115200);
  while(!Serial) {};
  debug("");
  debug("hello");
}

void LED__setup() {
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

void ESP__serial__start() {
  Serial1.begin(57600);
  debug("ESP Serial Communication started.");
}

void LED__off() {
  analogWrite(LED_R_PIN, 0);
  analogWrite(LED_G_PIN, 0);
  analogWrite(LED_B_PIN, 0);
  //debug("led is off");
}

void LED__red() {
  LED__off();
  analogWrite(LED_R_PIN, LED_R_HIGH);
  //debug("led is red");
}

void LED__green() {
  LED__off();
  analogWrite(LED_G_PIN, LED_G_HIGH);
  //debug("led is green");
}

void LED__blue() {
  LED__off();
  analogWrite(LED_B_PIN, LED_B_HIGH);
  //debug("led is blue");
}

void LED__yellow() {
  LED__off();
  analogWrite(LED_R_PIN, LED_R_HIGH);
  analogWrite(LED_G_PIN, LED_G_HIGH - 90);
  //debug("led is yellow");
}

void LED__purple() {
  LED__off();
  analogWrite(LED_R_PIN, LED_R_HIGH);
  analogWrite(LED_B_PIN, LED_B_HIGH);
  //debug("led is purple");
}

void LED__lightBlue() {
  LED__off();
  analogWrite(LED_G_PIN, LED_G_HIGH);
  analogWrite(LED_B_PIN, LED_B_HIGH);
  //debug("led is lightblue");
}

void LED__white() {
  LED__off();
  analogWrite(LED_R_PIN, LED_R_HIGH);
  analogWrite(LED_G_PIN, LED_G_HIGH);
  analogWrite(LED_B_PIN, LED_B_HIGH);
  //debug("led is white");
}

float averageColor(float v1, float v2, float _max) {
  return round(min(((v1 + v2) / (float) 2), _max));
}

void LED__rgb__pitch_roll() {
  float pitch = _pitch / (float) 90;
  float roll = _roll / (float) 90;

  float r1_r;
  float r1_g;
  float r1_b;

  float r2_r;
  float r2_g;
  float r2_b;
  
  if (pitch > 0) {
    // red
    r1_r = LED_R_HIGH * pitch;
    r1_g = 0;
    r1_b = 0;
      
    if (roll > 0) {
      // purple
      r2_r = LED_R_HIGH * roll;
      r2_g = 0;
      r2_b = LED_B_HIGH * roll;
      
    } else {
      // lightblue
      r2_r = 0;
      r2_g = LED_G_HIGH * abs(roll);
      r2_b = LED_B_HIGH * abs(roll);
    }
  } else {
    // green
    r1_r = 0;
    r1_g = LED_G_HIGH * abs(pitch);
    r1_b = 0;

    if (roll > 0) {
      // purple
      r2_r = LED_R_HIGH * roll;
      r2_g = 0;
      r2_b = LED_B_HIGH * roll;
      
    } else {
      // lightblue
      r2_r = 0;
      r2_g = LED_G_HIGH * abs(roll);
      r2_b = LED_B_HIGH * abs(roll);
    }
  }
  
  analogWrite(LED_R_PIN, (int) averageColor(r1_r, r2_r, (float) LED_R_HIGH));
  analogWrite(LED_G_PIN, (int) averageColor(r1_g, r2_g, (float) LED_G_HIGH));
  analogWrite(LED_B_PIN, (int) averageColor(r1_b, r2_b, (float) LED_B_HIGH));
}

void resetInCommand() {
  _message__started = false;
  _message__type = '\0';
  _message__type_length = 0;
}

void RUN_MODE__prepare__espError() {
  stopTimer();
  
  QUEUE_clear('D');
  QUEUE_clear(RUN_MODE_INIT1);
  QUEUE_clear(RUN_MODE_READY);
  QUEUE_clear(RUN_MODE_TESTING);
  QUEUE_clear(RUN_MODE_TESTING_IMU);
  QUEUE_clear(RUN_MODE_SENDING);
  QUEUE_clear(RUN_MODE_ESP_ERROR);
  QUEUE_add(40, COMMAND_RUN_MODE_ESP_ERROR, 'D');
}

// this is start mode
void RUN_MODE__start__espError() {
  _run_mode__current = RUN_MODE_ESP_ERROR;
  _run_mode__preparing__espError = false;
  
  LED__off();

  QUEUE_add(50, COMMAND_LED_RED, RUN_MODE_ESP_ERROR);
  QUEUE_add(150, COMMAND_LED_OFF, RUN_MODE_ESP_ERROR);
  QUEUE_add(250, COMMAND_LED_RED, RUN_MODE_ESP_ERROR);
  QUEUE_add(350, COMMAND_LED_OFF, RUN_MODE_ESP_ERROR);
  QUEUE_add(450, COMMAND_LED_RED, RUN_MODE_ESP_ERROR);
  QUEUE_add(550, COMMAND_LED_OFF, RUN_MODE_ESP_ERROR);
}

void RUN_MODE__prepare__init1() {
  LED__red();
  QUEUE_clear(RUN_MODE_ESP_ERROR);
  _run_mode__current = RUN_MODE_INIT1;
  //QUEUE_add(40, COMMAND_RUN_MODE_INIT1, 'D');
}

// from ESP_ERROR mode
void RUN_MODE__start__init1() {
}

void RUN_MODE__prepare__ready() {
  LED__yellow();
  _esp__lastPingReceived = millis();
  _run_mode__current = RUN_MODE_READY;
  _esp__lastPingReceived = millis();
  //QUEUE_add(40, COMMAND_RUN_MODE_READY, 'D');
}

// from INIT1 mode
void RUN_MODE__start__ready() {
}

// from READY mode
void RUN_MODE__prepare__testing() {
  QUEUE_add(50, COMMAND_LED_GREEN, RUN_MODE_READY);
  QUEUE_add(1050, COMMAND_LED_BLUE, RUN_MODE_READY);
  QUEUE_add(2050, COMMAND_LED_OFF, RUN_MODE_READY);
  QUEUE_add(3050, COMMAND_RUN_MODE_TESTING, 'D');
}

void RUN_MODE__start__testing() {
  _button_1_pressed = false;
  _button_2_pressed = false;
  _button_3_pressed = false;
  _button_4_pressed = false;
  _button_5_pressed = false;
  _run_mode__current = RUN_MODE_TESTING;
  _run_mode__testing__waiting = false;
  _run_mode__testing__currentButton = 0; // test mode
}

// in / from: TESTING mode
void RUN_MODE__testing__prepare__next_button() {
  resetButtons();
  QUEUE_clear(RUN_MODE_TESTING);
  QUEUE_add(40, COMMAND_LED_GREEN, 'D');
  QUEUE_add(1040, COMMAND_LED_OFF, 'D');
  QUEUE_add(1050, COMMAND_RUN_MODE_TESTING_INC, 'D');
}

void resetButtons() {
  _button_1_pressed = false;
  _button_2_pressed = false;
  _button_3_pressed = false;
  _button_4_pressed = false;
  _button_5_pressed = false;
}

void RUN_MODE__testing__incButton() {
  resetButtons();
  _run_mode__testing__waiting = false;
  _run_mode__testing__currentButton += 1;
}

void RUN_MODE__prepare__testing_imu() {
  resetButtons();
  QUEUE_clear(RUN_MODE_TESTING);
  QUEUE_add(50, COMMAND_LED_BLUE, RUN_MODE_TESTING_IMU);
  QUEUE_add(550, COMMAND_LED_OFF, RUN_MODE_TESTING_IMU);
  QUEUE_add(1050, COMMAND_LED_BLUE, RUN_MODE_TESTING_IMU);
  QUEUE_add(1550, COMMAND_LED_OFF, RUN_MODE_TESTING_IMU);
  QUEUE_add(1650, COMMAND_RUN_MODE_TESTING_IMU, RUN_MODE_TESTING_IMU);
}

void RUN_MODE__start__testing_imu() {
  _run_mode__testing_imu__x1 = false;
  _run_mode__testing_imu__x2 = false;
  _run_mode__testing_imu__y1 = false;
  _run_mode__testing_imu__y2 = false;
  _run_mode__preparing__send = false;
  _run_mode__current = RUN_MODE_TESTING_IMU;
}

void ESP__processIncomingChar(const char inByte) {
  if (inByte == 'P') {
    _esp__lastPingReceived = millis();
    return;
  } else if (inByte == 'T') {
    _esp__lastTelnetPingReceived = millis();
    return;
  } else if (!_message__started) {
    switch (inByte) {
      case MESSAGE__TYPE_MESSAGE: // type message (M 000x) started
        _message__started = true;
        _message__type = MESSAGE__TYPE_MESSAGE;
        _message__type_length = 0;
        break;

      case MESSAGE__TYPE_BUTTON: // type button (B 0x) started
        _message__started = true;
        _message__type = MESSAGE__TYPE_BUTTON;
        _message__type_length = 0;
        break;

      case MESSAGE__TYPE_BUTTON_RELEASE: // type button released (N 0x) started
        _message__started = true;
        _message__type = MESSAGE__TYPE_BUTTON_RELEASE;
        _message__type_length = 0;
        break;

      case MESSAGE__TYPE_IMU__PITCH:
        _message__started = true;
        _message__type = MESSAGE__TYPE_IMU__PITCH;
        _message__type_length = 0;
        _pitch_str = "";
        break;

      case MESSAGE__TYPE_IMU__ROLL:
        _message__started = true;
        _message__type = MESSAGE__TYPE_IMU__ROLL;
        _message__type_length = 0;
        _roll_str = "";
        break;
    }
  } else { // messsageStarted
    if (_message__type == MESSAGE__TYPE_MESSAGE) { // type message
      if (_message__type_length >= 0 && _message__type_length < 3) {
        if (inByte == '0') {
          _message__type_length += 1;
        } else if (inByte == ' ') { // separator
          // do nothing
        } else {
          resetInCommand();
        }
      } else if (_message__type_length == 3) {
        switch (inByte) { // parse message
          case '1': // ESP ready for connections
            if (RUN_MODE__is(RUN_MODE_ESP_ERROR)) {
              RUN_MODE__prepare__init1();
            }
            resetInCommand();
            break;
            
          case '2': // ESP services ready
            if (RUN_MODE__is(RUN_MODE_INIT1)) {
              RUN_MODE__prepare__ready();
            }
            resetInCommand();
            break;

          case '3': // ESP client connected
            //if (RUN_MODE__is(RUN_MODE_READY)) {
            //  RUN_MODE__prepare__testing();
            //}
            resetInCommand();
            break;

          case '4': // ESP client disconnected
            if (RUN_MODE__is(RUN_MODE_READY) || RUN_MODE__is(RUN_MODE_TESTING) || RUN_MODE__is(RUN_MODE_SENDING)) {
              RUN_MODE__prepare__espError();
            }
            resetInCommand();
            break;

          default:
            resetInCommand();
            break;
        }
      }
    } else if (_message__type == MESSAGE__TYPE_BUTTON || _message__type == MESSAGE__TYPE_BUTTON_RELEASE) { // type button
      if (RUN_MODE__is(RUN_MODE_TESTING)) {
        if (_message__type_length >= 0 && _message__type_length <= 1) {
          if (inByte == '0') {
            _message__type_length += 1;
          } else if (inByte == ' ') { // separator
            _message__type_length += 1;
          } else {
            resetInCommand();
          }
        } else if (_message__type_length == 2) {
          switch (inByte) {
            case '1':
              _button_1_pressed = _message__type == MESSAGE__TYPE_BUTTON;
              break;

            case '2':
              _button_2_pressed = _message__type == MESSAGE__TYPE_BUTTON;
              break;

            case '3':
              _button_3_pressed = _message__type == MESSAGE__TYPE_BUTTON;
              break;

            case '4':
              _button_4_pressed = _message__type == MESSAGE__TYPE_BUTTON;
              break;

            case '5':
              _button_5_pressed = _message__type == MESSAGE__TYPE_BUTTON;
              break;
          }

          resetInCommand();
        }
      }
    } else if (_message__type == MESSAGE__TYPE_IMU__PITCH || _message__type == MESSAGE__TYPE_IMU__ROLL) {
      if (inByte == ' ') {
        _message__type_length += 1;
      } else if (_message__type_length == 1) {
        if (inByte == '$') {
          if (_message__type == MESSAGE__TYPE_IMU__PITCH) {
            _pitch = _pitch_str.toFloat();

            if (RUN_MODE__is(RUN_MODE_TESTING_IMU)) {
              if (_pitch > ((float) 45) && !_run_mode__testing_imu__x1) {
                _run_mode__testing_imu__x1 = true;
              } else if (_pitch < ((float) -45) && !_run_mode__testing_imu__x2) {
                _run_mode__testing_imu__x2 = true;
              }
            }
            
          } else {
            _roll = _roll_str.toFloat();

            if (RUN_MODE__is(RUN_MODE_TESTING_IMU)) {
              if (_roll > ((float) 45) && !_run_mode__testing_imu__y1) {
                _run_mode__testing_imu__y1 = true;
              } else if (_roll < ((float) -45) && !_run_mode__testing_imu__y2) {
                _run_mode__testing_imu__y2 = true;
              }
            }
          }
          
          resetInCommand();
        } else {
          if (_message__type == MESSAGE__TYPE_IMU__PITCH) {
            _pitch_str += String(inByte);
          } else {
            _roll_str += String(inByte);
          }
        }
      }
    }
  }
}

void QUEUE__processCommand(int command) {
  switch(command) {
    case COMMAND_LED_PURPLE:
      LED__purple();
      break;

    case COMMAND_LED_OFF:
      LED__off();
      break;

    case COMMAND_LED_BLUE:
      LED__blue();
      break;

    case COMMAND_LED_RED:
      LED__red();
      break;

    case COMMAND_LED_GREEN:
      LED__green();
      break;

    case COMMAND_RUN_MODE_TESTING:
      RUN_MODE__start__testing();
      break;

    case COMMAND_RUN_MODE_INIT1:
      RUN_MODE__start__init1();
      break;

    case COMMAND_RUN_MODE_READY:
      RUN_MODE__start__ready();
      break;
  
    case COMMAND_RUN_MODE_ESP_ERROR:
      RUN_MODE__start__espError();
      break;
  
    case COMMAND_RUN_MODE_TESTING_INC:
      RUN_MODE__testing__incButton();
      break;

    case COMMAND_RUN_MODE_TESTING_IMU:
      RUN_MODE__start__testing_imu();
      break;

    case COMMAND_RUN_MODE_SENDING:
      RUN_MODE__start__sending();
      break;

    default:
      return;
  }
}

void QUEUE_clear(const char runMode) {
  QUEUE__ITEM newQueueItems[QUEUE__ITEMS_SIZE];
  int newQueueSize = -1;

  for (int i = 0; i < _queue__containerSize + 1; i += 1) {
    if (_queue__container[i].runMode != runMode) {
      newQueueItems[++newQueueSize] = _queue__container[i];
    }
  }

   memcpy(_queue__container, newQueueItems, sizeof newQueueItems);
    _queue__containerSize = newQueueSize;
}

bool QUEUE__process() {
  QUEUE__ITEM newQueueItems[QUEUE__ITEMS_SIZE];
  int newQueueSize = -1;
  bool result = false;
  
  for (int i = 0; i < _queue__containerSize + 1; i += 1) {
    if (millis() >= _queue__container[i].when) {
      if (_queue__container[i].runMode == RUN_MODE_TESTING) {
        
        _queue__container[i].when += 1500;
        
        newQueueItems[++newQueueSize] = _queue__container[i];
        
        QUEUE__processCommand(_queue__container[i].command);
        debug("executing: " + String(_queue__container[i].command));
        
        result = true;
      } else if (_queue__container[i].runMode == RUN_MODE_ESP_ERROR) {
        
        _queue__container[i].when += 1000;
   
        newQueueItems[++newQueueSize] = _queue__container[i];
        
        QUEUE__processCommand(_queue__container[i].command);
        debug("executing: " + String(_queue__container[i].command));
        
        result = true;
      } else {
        
        QUEUE__processCommand(_queue__container[i].command);
        debug("executing: " + String(_queue__container[i].command));
        
        result = true;
      }
    } else {
      newQueueItems[++newQueueSize] = _queue__container[i];
    }
  }

  memcpy(_queue__container, newQueueItems, sizeof newQueueItems);
  _queue__containerSize = newQueueSize;

  return result;
}

void QUEUE_add(unsigned long when, int command, char runMode) {
  QUEUE__ITEM item;
  item.when = millis() + when;
  item.command = command;
  item.runMode = runMode;
  _queue__container[++_queue__containerSize] = item;
}

bool RUN_MODE__is(char mode) {
  return _run_mode__current == mode;
}

bool ESP__timeout() {
  return (millis() - _esp__lastPingReceived > (unsigned long) 1000);
}

bool ESP__telnet__timeout() {
  return (millis() - _esp__lastTelnetPingReceived > (unsigned long) 1000);
}

bool RUN_MODE_TESTING__isWaiting() {
  return _run_mode__testing__waiting;
}

void RUN_MODE__prepare__send() {
  QUEUE_clear('D');
  QUEUE_clear(RUN_MODE_INIT1);
  QUEUE_clear(RUN_MODE_READY);
  QUEUE_clear(RUN_MODE_TESTING);
  QUEUE_clear(RUN_MODE_TESTING_IMU);
  QUEUE_clear(RUN_MODE_ESP_ERROR);
  
  QUEUE_add(50, COMMAND_LED_BLUE, RUN_MODE_SENDING);
  QUEUE_add(550, COMMAND_LED_GREEN, RUN_MODE_SENDING);
  QUEUE_add(1050, COMMAND_LED_BLUE, RUN_MODE_SENDING);
  QUEUE_add(1550, COMMAND_LED_GREEN, RUN_MODE_SENDING);
  QUEUE_add(2050, COMMAND_LED_OFF, RUN_MODE_SENDING);
  QUEUE_add(3050, COMMAND_LED_GREEN, RUN_MODE_SENDING);
  QUEUE_add(3060, COMMAND_RUN_MODE_SENDING, RUN_MODE_SENDING);
}

void RUN_MODE__start__sending() {
  _run_mode__current = RUN_MODE_SENDING;
  startTimer();
}

bool _run() {
  bool result = QUEUE__process();

  if (!result) {
    if (RUN_MODE__is(RUN_MODE_TESTING) || RUN_MODE__is(RUN_MODE_TESTING_IMU) || RUN_MODE__is(RUN_MODE_SENDING)) {
      if (!_run_mode__preparing__espError) {
        if (ESP__timeout() || ESP__telnet__timeout()) {
          _run_mode__preparing__espError = true;
          RUN_MODE__prepare__espError();
          return true;
        }
      }
    }
        
    if (RUN_MODE__is(RUN_MODE_TESTING)) {
      if (RUN_MODE_TESTING__isWaiting()) {
        if (_button_1_pressed && _run_mode__testing__currentButton == 0) {
          RUN_MODE__testing__prepare__next_button();
          return true;
        } else if (_button_2_pressed && _run_mode__testing__currentButton == 1) {
          RUN_MODE__testing__prepare__next_button();
          return true;
        } else if (_button_3_pressed && _run_mode__testing__currentButton == 2) {
          RUN_MODE__testing__prepare__next_button();
          return true;
        } else if (_button_4_pressed && _run_mode__testing__currentButton == 3) {
          RUN_MODE__testing__prepare__next_button();
          return true;
        } else if (_button_5_pressed && _run_mode__testing__currentButton == 4) {
          RUN_MODE__prepare__testing_imu();
          return true;
        }
      } else {
        int blinkCount = _run_mode__testing__currentButton + 1;
        unsigned int when = 10;
        
        for (int i = 0; i < blinkCount; i += 1) {
          QUEUE_add(when, COMMAND_LED_PURPLE, RUN_MODE_TESTING);
          QUEUE_add(when + 100, COMMAND_LED_OFF, RUN_MODE_TESTING);
          when += 200;
        }
        
        _run_mode__testing__waiting = true;
        
        return true;
      }
    } else if (RUN_MODE__is(RUN_MODE_TESTING_IMU)) {
      if (_run_mode__testing_imu__x1 && _run_mode__testing_imu__x2 && _run_mode__testing_imu__y1 && _run_mode__testing_imu__y2) {
        if (!_run_mode__preparing__send) {
          _run_mode__preparing__send = true;
          RUN_MODE__prepare__send();
          return true;
        }
      } else {
        LED__rgb__pitch_roll();
      }
    } else if (RUN_MODE__is(RUN_MODE_SENDING)) {
      float axis0 = (float) defaultPpmValues[0];  // left right -> 1500
      float axis1 = (float) defaultPpmValues[1];  // forward backward -> 1500
      float multiplier = 0.3;

      if (_roll >= 0) {
        axis0 += (((float) 500) * ((_roll / ((float) 90)))) * multiplier; // right
      } else {
        axis0 -= (((float) 500) * ((abs(_roll) / ((float) 90)))) * multiplier; // left
      }

      if (_pitch >= 0) {
        axis1 -= (((float) 500) * ((_pitch / ((float) 90)))) * multiplier; // backward
      } else {
        axis1 += (((float) 500) * ((abs(_pitch) / ((float) 90)))) * multiplier; // forward
      }

      ppm[0] = (int) axis0;
      ppm[1] = (int) axis1;
    }
  }

  return result;
}

void EEPROM__setup() {
  // warning.
  //ezprom.reset();
}

void setup() {
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, !POLARITY);
  
  LED__setup();
  EEPROM__setup();
  SERIAL__setup();
  ESP__serial__start();
  RUN_MODE__prepare__espError();
}

void loop() {
  bool tasksProcessed = _run();
  
  if (!tasksProcessed) {
    if (Serial1.available()) {
      String str = "received message: ";
      while (Serial1.available()) {
        char ch = Serial1.read();
        ESP__processIncomingChar(ch);
        str += ch;
      }
      str.toLowerCase();
      debug(str);
    }
  }
  delay(10);
}

ISR(TIMER1_COMPA_vect) {
  static boolean state = true;
  static byte current_channel_number;
  static unsigned int calc_rest;
  
  TCNT1 = 0;

  if (state) {                                        // start pulse
    digitalWrite(SIGNAL_PIN, POLARITY);
    OCR1A = PPM_PULSE_LENGTH * 2;
    state = false;
  } else {                                            // end pulse and calculate when to start the next pulse
    digitalWrite(SIGNAL_PIN, !POLARITY);
    state = true;

    if (current_channel_number >= CHANNELS_NUMBER) {
      current_channel_number = 0;
      calc_rest = calc_rest + PPM_PULSE_LENGTH;
      OCR1A = (PPM_FRAME_LENGTH - calc_rest) * 2;
      calc_rest = 0;
    } else {
      OCR1A = (ppm[current_channel_number] - PPM_PULSE_LENGTH) * 2;
      calc_rest = calc_rest + ppm[current_channel_number];
      current_channel_number++;
    }
  }
}
