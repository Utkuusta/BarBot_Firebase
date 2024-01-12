
/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 *
 * Copyright (c) 2023 mobizt
 *
 */

#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#elif __has_include(<WiFiNINA.h>)
#include <WiFiNINA.h>
#elif __has_include(<WiFi101.h>)
#include <WiFi101.h>
#elif __has_include(<WiFiS3.h>)
#include <WiFiS3.h>
#endif

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "ENTER SSID"
#define WIFI_PASSWORD "ENTER PWD"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyDx6QhWFEczA6yJyr-h9gFOfQ4Ko9tk68E"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://onlinefialkol-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "aeyetisken@gmail.com"
#define USER_PASSWORD "ENTER PWD"

// Define Firebase Data object
FirebaseData fbdo;
  
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
const unsigned long MINUTE = 60000UL;
unsigned long count = 0;

const int PUMP_1 = D0;
const int PUMP_2 = D1;
const int PUMP_3 = D2;
const int PUMP_4 = D3;
const int PUMP_5 = D4;
const int PUMP_6 = D5;
const int PUMP_7 = D6;
const int PUMP_8 = D7;



enum class State {
  WORKING,
  IDLE,
};


State state = State::IDLE;
int seconds = 0;
String ResultString = "0";
int selectedDrink = 0;

int PourDrink(int val) {
  switch (val) {
    case 1:
      digitalWrite(PUMP_1, LOW);
      delay(1500);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      digitalWrite(PUMP_2, LOW);
      delay(1250);
      digitalWrite(PUMP_2, HIGH);
      delay(300);
      digitalWrite(PUMP_3, LOW);
      delay(1250);
      digitalWrite(PUMP_3, HIGH);
      delay(300);
      digitalWrite(PUMP_4, LOW);
      delay(2500);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      digitalWrite(PUMP_6, LOW);
      delay(1000);
      digitalWrite(PUMP_6, HIGH);
      delay(300);
      digitalWrite(PUMP_8, LOW);
      delay(1750);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

       case 12:
      digitalWrite(PUMP_1, LOW);
      delay(1500);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      digitalWrite(PUMP_2, LOW);
      delay(1250);
      digitalWrite(PUMP_2, HIGH);
      delay(300);
      digitalWrite(PUMP_3, LOW);
      delay(1250);
      digitalWrite(PUMP_3, HIGH);
      delay(300);
      digitalWrite(PUMP_6, LOW);
      delay(1000);
      digitalWrite(PUMP_6, HIGH);
      delay(300);
      digitalWrite(PUMP_8, LOW);
      delay(1750);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

    case 2:
      digitalWrite(PUMP_5, LOW);
      delay(2000);
      digitalWrite(PUMP_5, HIGH);
      delay(300);
      digitalWrite(PUMP_4, LOW);
      delay(2750);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      digitalWrite(PUMP_8, LOW);
      delay(2250);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

     case 13:
      digitalWrite(PUMP_5, LOW);
      delay(2000);
      digitalWrite(PUMP_5, HIGH);
      delay(300);
     
      digitalWrite(PUMP_8, LOW);
      delay(2250);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

    case 3:
      digitalWrite(PUMP_4, LOW);
      delay(1750);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      digitalWrite(PUMP_3, LOW);
      delay(2000);
      digitalWrite(PUMP_3, HIGH);
      delay(300);
      digitalWrite(PUMP_8, LOW);
      delay(1250);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

    case 14:
      digitalWrite(PUMP_3, LOW);
      delay(2000);
      digitalWrite(PUMP_3, HIGH);
      delay(300);
      digitalWrite(PUMP_8, LOW);
      delay(1250);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

      case 4:
      digitalWrite(PUMP_3, LOW);
      delay(2000);
      digitalWrite(PUMP_3, HIGH);
      delay(300);
      digitalWrite(PUMP_8, LOW);
      delay(1250);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

      case 5:
      digitalWrite(PUMP_6, LOW);
      delay(2250);
      digitalWrite(PUMP_6, HIGH);
      delay(300);
      digitalWrite(PUMP_7, LOW);
      delay(1750);
      digitalWrite(PUMP_7, HIGH);
      delay(300);
      
      break;

      case 6:
      digitalWrite(PUMP_2, LOW);
      delay(3000);
      digitalWrite(PUMP_2, HIGH);
      delay(300);
      digitalWrite(PUMP_7, LOW);
      delay(1500);
      digitalWrite(PUMP_7, HIGH);
      delay(300);
      break;

      case 7:
      digitalWrite(PUMP_5, LOW);
      delay(2750);
      digitalWrite(PUMP_5, HIGH);
      delay(300);
      digitalWrite(PUMP_4, LOW);
      delay(2500);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      break;

      case 15:
      digitalWrite(PUMP_5, LOW);
      delay(2750);
      digitalWrite(PUMP_5, HIGH);
      delay(300);
      break;

      case 8:
      digitalWrite(PUMP_5, LOW);
      delay(3000);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      break;

      case 9:
      digitalWrite(PUMP_1, LOW);
      delay(3000);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      digitalWrite(PUMP_4, LOW);
      delay(2500);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      break;

      case 16:
      digitalWrite(PUMP_1, LOW);
      delay(3000);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      break;

      case 10:
      digitalWrite(PUMP_1, LOW);
      delay(2500);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      digitalWrite(PUMP_6, LOW);
      delay(1500);
      digitalWrite(PUMP_6, HIGH);
      delay(300);
      digitalWrite(PUMP_4, LOW);
      delay(1500);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      break;

      case 17:
      digitalWrite(PUMP_1, LOW);
      delay(2500);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      digitalWrite(PUMP_6, LOW);
      delay(1500);
      digitalWrite(PUMP_6, HIGH);
      delay(300);
      break;

      case 11:
      digitalWrite(PUMP_2, LOW);
      delay(2500);
      digitalWrite(PUMP_2, HIGH);
      delay(300);
      digitalWrite(PUMP_4, LOW);
      delay(750);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      break;

      case 18:
      digitalWrite(PUMP_2, LOW);
      delay(2500);
      digitalWrite(PUMP_2, HIGH);
      delay(300);
      break;

      

      case 20:
      digitalWrite(PUMP_1, LOW);
      delay(2000);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      break;


      case 21:
      digitalWrite(PUMP_2, LOW);
      delay(2000);
      digitalWrite(PUMP_2, HIGH);
      delay(300);
      break;


      case 22:
      digitalWrite(PUMP_3, LOW);
      delay(2000);
      digitalWrite(PUMP_3, HIGH);
      delay(300);
      break;


      case 23:
      digitalWrite(PUMP_5, LOW);
      delay(2000);
      digitalWrite(PUMP_5, HIGH);
      delay(300);
      break;


      case 24:
      digitalWrite(PUMP_6, LOW);
      delay(1750);
      digitalWrite(PUMP_6, HIGH);
      delay(300);
      break;

      case 31:
      digitalWrite(PUMP_1, LOW);
      delay(5000);
      digitalWrite(PUMP_1, HIGH);
      delay(300);
      digitalWrite(PUMP_2, LOW);
      delay(5000);
      digitalWrite(PUMP_2, HIGH);
      delay(300);
      digitalWrite(PUMP_3, LOW);
      delay(5000);
      digitalWrite(PUMP_3, HIGH);
      delay(300);
      digitalWrite(PUMP_4, LOW);
      delay(5000);
      digitalWrite(PUMP_4, HIGH);
      delay(300);
      digitalWrite(PUMP_5, LOW);
      delay(5000);
      digitalWrite(PUMP_5, HIGH);
      delay(300);
      digitalWrite(PUMP_6, LOW);
      delay(5000);
      digitalWrite(PUMP_6, HIGH);
      delay(300);
      digitalWrite(PUMP_7, LOW);
      delay(5000);
      digitalWrite(PUMP_7, HIGH);
      delay(300);
      digitalWrite(PUMP_8, LOW);
      delay(5000);
      digitalWrite(PUMP_8, HIGH);
      delay(300);
      
      break;
     default:
      delay(300);
      break;
  }
  return 0;
}

void turnOff() {
  digitalWrite(PUMP_1, HIGH);
  digitalWrite(PUMP_2, HIGH);
  digitalWrite(PUMP_3, HIGH);
  digitalWrite(PUMP_4, HIGH);
  digitalWrite(PUMP_5, HIGH);
  digitalWrite(PUMP_6, HIGH);
  digitalWrite(PUMP_7, HIGH);
  digitalWrite(PUMP_8, HIGH);
}

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

void setup()
{

  Serial.begin(115200);

  pinMode(PUMP_1, OUTPUT);
  pinMode(PUMP_2, OUTPUT);
  pinMode(PUMP_3, OUTPUT);
  pinMode(PUMP_4, OUTPUT);
  pinMode(PUMP_5, OUTPUT);
  pinMode(PUMP_6, OUTPUT);
  pinMode(PUMP_7, OUTPUT);
  pinMode(PUMP_8, OUTPUT);
  turnOff();
  
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  multi.addAP(WIFI_SSID, WIFI_PASSWORD);
  multi.run();
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    if (millis() - ms > 10000)
      break;
#endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

  //////////////////////////////////////////////////////////////////////////////////////////////
  // Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  // otherwise the SSL connection will fail.
  //////////////////////////////////////////////////////////////////////////////////////////////

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  // The WiFi credentials are required for Pico W
  // due to it does not have reconnect feature.
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  config.wifi.clearAP();
  config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;

  // You can use TCP KeepAlive in FirebaseData object and tracking the server connection status, please read this for detail.
  // https://github.com/mobizt/Firebase-ESP-Client#about-firebasedata-object
  // fbdo.keepAlive(5, 5, 1);

  /** Timeout options.

  //Network reconnect timeout (interval) in ms (10 sec - 5 min) when network or WiFi disconnected.
  config.timeout.networkReconnect = 10 * 1000;

  //Socket connection and SSL handshake timeout in ms (1 sec - 1 min).
  config.timeout.socketConnection = 10 * 1000;

  //Server response read timeout in ms (1 sec - 1 min).
  config.timeout.serverResponse = 10 * 1000;

  //RTDB Stream keep-alive timeout in ms (20 sec - 2 min) when no server's keep-alive event data received.
  config.timeout.rtdbKeepAlive = 45 * 1000;

  //RTDB Stream reconnect timeout (interval) in ms (1 sec - 1 min) when RTDB Stream closed and want to resume.
  config.timeout.rtdbStreamReconnect = 1 * 1000;

  //RTDB Stream error notification timeout (interval) in ms (3 sec - 30 sec). It determines how often the readStream
  //will return false (error) when it called repeatedly in loop.
  config.timeout.rtdbStreamError = 3 * 1000;

  Note:
  The function that starting the new TCP session i.e. first time server connection or previous session was closed, the function won't exit until the
  time of config.timeout.socketConnection.

  You can also set the TCP data sending retry with
  config.tcp_data_sending_retry = 1;

  */
}

void loop()
{
   switch (state) {
    case State::IDLE:
      if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    
    ResultString = Firebase.RTDB.getString(&fbdo, F("/kokteyl")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
    //Serial.printf("Get string... %s\n", ResultString.c_str());

    //if error handling
    int parsedInt = atoi(ResultString.c_str());
    selectedDrink = parsedInt;
    Serial.print("Selected Drink: ");
    Serial.println(selectedDrink);

    if (selectedDrink != 0){
      state = State::WORKING;
    }
    Serial.println();

    
  }
      break;

    case State::WORKING:
      PourDrink(selectedDrink);
      delay(100); // Adjust this delay as needed
      turnOff();
      Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/kokteyl"), F("0")) ? "ok" : fbdo.errorReason().c_str());

      state = State::IDLE; // Assuming you want to go back to idle after working
      break;
  }
  
  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  
}

/** NOTE:
 * When you trying to get boolean, integer and floating point number using getXXX from string, json
 * and array that stored on the database, the value will not set (unchanged) in the
 * FirebaseData object because of the request and data response type are mismatched.
 *
 * There is no error reported in this case, until you set this option to true
 * config.rtdb.data_type_stricted = true;
 *
 * In the case of unknown type of data to be retrieved, please use generic get function and cast its value to desired type like this
 *
 * Firebase.RTDB.get(&fbdo, "/path/to/node");
 *
 * float value = fbdo.to<float>();
 * String str = fbdo.to<String>();
 *
 */

/// PLEASE AVOID THIS ////

// Please avoid the following inappropriate and inefficient use cases
/**
 *
 * 1. Call get repeatedly inside the loop without the appropriate timing for execution provided e.g. millis() or conditional checking,
 * where delay should be avoided.
 *
 * Everytime get was called, the request header need to be sent to server which its size depends on the authentication method used,
 * and costs your data usage.
 *
 * Please use stream function instead for this use case.
 *
 * 2. Using the single FirebaseData object to call different type functions as above example without the appropriate
 * timing for execution provided in the loop i.e., repeatedly switching call between get and set functions.
 *
 * In addition to costs the data usage, the delay will be involved as the session needs to be closed and opened too often
 * due to the HTTP method (GET, PUT, POST, PATCH and DELETE) was changed in the incoming request.
 *
 *
 * Please reduce the use of swithing calls by store the multiple values to the JSON object and store it once on the database.
 *
 * Or calling continuously "set" or "setAsync" functions without "get" called in between, and calling get continuously without set
 * called in between.
 *
 * If you needed to call arbitrary "get" and "set" based on condition or event, use another FirebaseData object to avoid the session
 * closing and reopening.
 *
 * 3. Use of delay or hidden delay or blocking operation to wait for hardware ready in the third party sensor libraries, together with stream functions e.g. Firebase.RTDB.readStream and fbdo.streamAvailable in the loop.
 *
 * Please use non-blocking mode of sensor libraries (if available) or use millis instead of delay in your code.
 *
 * 4. Blocking the token generation process.
 *
 * Let the authentication token generation to run without blocking, the following code MUST BE AVOIDED.
 *
 * while (!Firebase.ready()) <---- Don't do this in while loop
 * {
 *     delay(1000);
 * }
 *
 */
