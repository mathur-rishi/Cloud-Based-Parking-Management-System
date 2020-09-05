// Include Libraries
#include "Arduino.h"
#include "ESP8266.h"
#include "RFID.h"


// Pin Definitions
#define WIFI_PIN_TX	3
#define WIFI_PIN_RX	10
#define RFID_1_PIN_RST	2
#define RFID_1_PIN_SDA	4
#define RFID_2_PIN_RST	5
#define RFID_2_PIN_SDA	6
#define RFID_3_PIN_RST	7
#define RFID_3_PIN_SDA	8
#define RFID_4_PIN_RST	9
#define RFID_4_PIN_SDA	A3



// Global variables and defines
// ====================================================================
// vvvvvvvvvvvvvvvvvvvv ENTER YOUR WI-FI SETTINGS  vvvvvvvvvvvvvvvvvvvv
//
const char *SSID     = "WIFI-SSID"; // Enter your Wi-Fi name 
const char *PASSWORD = "PASSWORD" ; // Enter your Wi-Fi password
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ====================================================================
char* const host = "www.google.com";
int hostPort = 80;
// object initialization
ESP8266 wifi(WIFI_PIN_RX,WIFI_PIN_TX);
RFID rfid_1(RFID_1_PIN_SDA,RFID_1_PIN_RST);
RFID rfid_2(RFID_2_PIN_SDA,RFID_2_PIN_RST);
RFID rfid_3(RFID_3_PIN_SDA,RFID_3_PIN_RST);
RFID rfid_4(RFID_4_PIN_SDA,RFID_4_PIN_RST);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    wifi.init(SSID, PASSWORD);
    //initialize RFID module
    rfid_1.init();
    //initialize RFID module
    rfid_2.init();
    //initialize RFID module
    rfid_3.init();
    //initialize RFID module
    rfid_4.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // ESP8266-01 - Wifi Module - Test Code
    //Send request for www.google.com at port 80
    wifi.httpGet(host, hostPort);
    // get response buffer. Note that it is set to 250 bytes due to the Arduino low memory
    char* wifiBuf = wifi.getBuffer();
    //Comment out to print the buffer to Serial Monitor
    //for(int i=0; i< MAX_BUFFER_SIZE ; i++)
    //  Serial.print(wifiBuf[i]);
    //search buffer for the date and time and print it to the serial monitor. This is GMT time!
    char *wifiDateIdx = strstr (wifiBuf, "Date");
    for (int i = 0; wifiDateIdx[i] != '\n' ; i++)
    Serial.print(wifiDateIdx[i]);

    }
    else if(menuOption == '2') {
    // RFID Card Reader - RC522 #1 - Test Code
    //Read RFID tag if present
    String rfid_1tag = rfid_1.readTag();
    //print the tag to serial monitor if one was discovered
    rfid_1.printTag(rfid_1tag);

    }
    else if(menuOption == '3') {
    // RFID Card Reader - RC522 #2 - Test Code
    //Read RFID tag if present
    String rfid_2tag = rfid_2.readTag();
    //print the tag to serial monitor if one was discovered
    rfid_2.printTag(rfid_2tag);

    }
    else if(menuOption == '4') {
    // RFID Card Reader - RC522 #3 - Test Code
    //Read RFID tag if present
    String rfid_3tag = rfid_3.readTag();
    //print the tag to serial monitor if one was discovered
    rfid_3.printTag(rfid_3tag);

    }
    else if(menuOption == '5') {
    // RFID Card Reader - RC522 #4 - Test Code
    //Read RFID tag if present
    String rfid_4tag = rfid_4.readTag();
    //print the tag to serial monitor if one was discovered
    rfid_4.printTag(rfid_4tag);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) ESP8266-01 - Wifi Module"));
    Serial.println(F("(2) RFID Card Reader - RC522 #1"));
    Serial.println(F("(3) RFID Card Reader - RC522 #2"));
    Serial.println(F("(4) RFID Card Reader - RC522 #3"));
    Serial.println(F("(5) RFID Card Reader - RC522 #4"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing ESP8266-01 - Wifi Module"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing RFID Card Reader - RC522 #1"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing RFID Card Reader - RC522 #2"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing RFID Card Reader - RC522 #3"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing RFID Card Reader - RC522 #4"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
