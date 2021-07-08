#include <Arduino.h>
// Simple date conversions and calculations
// Date and time functions using just software, based on millis() & timer

//-------------------------------------------------------------------------------------
// RTC clock
#include "RTClib.h"
RTC_DS3231 rtc;
char buf1[] = "hh:mm";
int oldHour = 0;
int oldMinute = 0;
char t_sz[32];
char d_sz[32];
//-------------------------------------------------------------------------------------
#include <rs_common.h>
#include <int.h>
#include <string.h>

//-------------------------------------------------------------------------------------
// I2C
#include <Wire.h>

//-------------------------------------------------------------------------------------
// Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* const unsigned char NaN [] PROGMEM = {
	// 'path1624-6-6, 90x64px
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3f, 
	0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xc0, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 
	0x87, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0x07, 
	0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xc0, 
	0xff, 0xff, 0xf0, 0x00, 0x7f, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xe0, 0x00, 
	0x03, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x1f, 0xfe, 0x00, 
	0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 
	0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3f, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xc0, 
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 
	0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xff, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xff, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 
	0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc0, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x7f, 0xff, 0xc0, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xc0, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3f, 0xc0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1f, 0xc0, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x07, 0xc0, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x03, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
	0xff, 0xf0, 0x01, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0xc0, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0xc0, 0x00, 0x0e, 0x00, 0x00, 
	0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x40, 0x00, 0x09, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xc0, 0x00, 0x40, 0x00, 0x0b, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x80, 0x0b, 0x5a, 0x19, 0xb7, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x80, 0x0b, 0x5b, 0xd6, 
	0x97, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xc0, 0x0b, 0x5b, 0xb7, 0x97, 0xff, 0xff, 0xff, 
	0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xdb, 0x74, 0xb7, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0xe0, 0x00, 0xc7, 0x76, 0xa7, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x40, 0xf0, 0x00, 0x07, 0xf0, 
	0xa7, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x40, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x40, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xff, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0xc0, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 
	0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0xff, 0xff, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xff, 0xc0, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xc0, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xfe, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
	0x0f, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xc0
};
 */

//-------------------------------------------------------------------------------------
// Geodata / Maidenhead
#include <TinyGPS++.h>
// The TinyGPS++ object
TinyGPSPlus gps;
TinyGPSTime t;
TinyGPSDate d;
#include "../lib/maidenhead/maidenhead.h"
char* locator = "AA00";
char* locator_full = "AA00AA";

int resync = 0;
//#include "Adafruit_MCP23017.h"
String oldTime = " ";

String currentBand;

// TIME KEEPING

//RTC_Millis rtc;
//Adafruit_MCP23017
//Adafruit_MCP23017 mcp;
//Adafruit_SSD1306

//-------------------------------------------------------------------------------------
// SI5351 + JTEncode

#include <si5351.h>
#include <JTEncode.h>

//Si5351

Si5351 si5351;
//-------------------------------------------------------------------------------------
//JTEncode
JTEncode jtencode;
enum mode
{
  MODE_WSPR,
  MODE_FT8
};
// Global variables
//#define WSPR_FREQ       14096900UL // 20M, 14.094,60
//#define WSPR_DEFAULT_FREQ   3568800ULL //80m

#define WSPR_DEFAULT_FREQ 3586600ULL //80m

#define WSPR_80m_FREQ 3594000UL //80m 
//old  #define WSPR_80m_FREQ 3592600ULL
#define WSPR_10m_FREQ 28125900UL
// old #define WSPR_10m_FREQ 28125200UL

#define WSPR_2m_FREQ 144504000UL //80m

#define WSPR_DELAY 683        // Delay value for WSPR
#define WSPR_TONE_SPACING 146 // ~1.46 Hz

/* #define FT8_DELAY               159          // Delay value for FT8
#define FT8_DEFAULT_FREQ        14096900UL
#define FT8_TONE_SPACING        625          // ~6.25 Hz
 */
unsigned long freq;
//char message[] = "CQ DO7GN JN48";
char call[] = "N0CALL";

//char loc[] = "JN48";
uint8_t dbm = 27;
uint8_t tx_buffer[255];
uint8_t symbol_count;
uint16_t tone_delay, tone_spacing;
#define DEFAULT_MODE MODE_WSPR //  MODE_WSPR    //   MODE_FT8
enum mode cur_mode = DEFAULT_MODE;

#define LED_PIN 13
#define RELAY_PIN 5


//-------------------------------------------------------------------------------------
// DEBUG

//#define DEBUG

#ifdef DEBUG
#define DEBUG_BEGIN(x) Serial.begin(x);
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_BEGIN(x)
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

//#define DEBUG_GPS
#ifdef DEBUG_GPS
#define DEBUG_GPS_PRINT(x) Serial.print(x)
#define DEBUG_GPS_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_GPS_PRINT(x)
#define DEBUG_GPS_PRINTLN(x)
#endif

// Loop through the string, transmitting one character at a time.
void encode()
{
  uint8_t i;

  // Reset the tone to the base frequency and turn on the output
  si5351.output_enable(SI5351_CLK0, 1);
  digitalWrite(LED_PIN, HIGH);

  for (i = 0; i < symbol_count; i++)
  {
    //si5351.set_pll(SI5351_PLL_FIXED,SI5351_PLLA);
    si5351.set_freq((freq * 100) + (tx_buffer[i] * tone_spacing), SI5351_CLK0);
    delay(tone_delay);
  }

  // Turn off the output
  si5351.output_enable(SI5351_CLK0, 0);
  digitalWrite(LED_PIN, LOW);
}

void set_tx_buffer()
{
  // Clear out the transmit buffer
  memset(tx_buffer, 0, 255);
  // switch (cur_mode)
  //  {

  //  case MODE_WSPR:
  jtencode.wspr_encode(call, locator, dbm, tx_buffer);

  //    break;
  /*     case MODE_FT8:
 jtencode.ft8_encode(message, tx_buffer);
      break; */
  //  }
}

void printGPS(bool GPS)
{
  display.fillRect(0, 0, 24, 8, BLACK);
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner
  if (GPS)
  {
    display.println("GPS");
  }
  else
  {
    display.println("!GPS");
  }
  display.display();
}

void printBand(String band, bool draw)
{
  display.fillRect(44, 0, 24, 8, BLACK);
  if (draw)
  {
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(44, 0);            // Start at top-left corner
    display.println(band);
    display.display();
  }
}

void printTX(bool TX)
{
  display.fillRect(24, 0, 12, 8, BLACK);
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_BLACK); // Draw white text
  display.setCursor(24, 0);
  if (TX)
  {
    display.fillRect(24, 0, 12, 8, WHITE);
    // Start at top-left corner
    display.println("TX");
  }
  display.display();
}

void printTime(String time)
{
  display.fillRect(98, 0, 30, 8, BLACK);
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(98, 0);            // Start at top-left corner
  display.println(time);
  display.display();
}

void printTemp(String temp)
{
  display.fillRect(92, 8, 30, 8, BLACK);
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(92, 8);            // Start at top-left corner
  display.println(temp);
  display.display();
}


void printLocator()
{
  display.fillRect(92, 24, 30, 8, BLACK);
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(92, 24);           // Start at top-left corner
  display.println(locator);
  display.display();
}

void printText(String text, bool draw)
{
  display.fillRect(0, 24, 90, 8, BLACK);
  if (draw)
  {
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 24);            // Start at top-left corner
    display.println(text);
    display.display();
  }
}

void setup()
{
  DEBUG_BEGIN(115200);
  rtc.begin();
  Serial1.begin(9600);
  rtc.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    DEBUG_PRINTLN(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  /*  mcp.begin();      // use default address 0

  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT); */
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  delay(2000);
  printGPS(false);
  //printGPS(" GPS");
  DEBUG_PRINTLN("Wait for GPS");
  while (!gps.location.isValid())
  {
    // DEBUG_GPS_PRINTLN("No GPS");

    if (Serial1.available() > 0)
    {
      if (gps.encode(Serial1.read()))
      {
        DEBUG_GPS_PRINT("Encodeded>> \t");
        String test = String(gps.time.hour());
        d = gps.date;
        t = gps.time;

        if (!d.isValid())
        {
          DEBUG_GPS_PRINT(F("********** "));
        }
        else
        {
          char sz[32];
          sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
          DEBUG_GPS_PRINT(sz);
        }
        DEBUG_GPS_PRINT("\t");
        if (!t.isValid())
        {

          DEBUG_GPS_PRINTLN(F("********s "));
        }
        else
        {
          char sz[32];
          sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
          DEBUG_GPS_PRINT(sz);
          DEBUG_GPS_PRINT("\t");
        }
        //delay(1000);
        //printText(test);
        DEBUG_GPS_PRINT("Lat: ");
        DEBUG_GPS_PRINT(gps.location.lat());
        DEBUG_GPS_PRINT("\tLong: ");
        DEBUG_GPS_PRINTLN(gps.location.lng());
      }
    }
  }
  printGPS(true);
  locator = get_mh(gps.location.lat(), gps.location.lng(), 4);
  locator_full = get_mh(gps.location.lat(), gps.location.lng(), 6);
  DEBUG_PRINTLN(locator);
  printText("Time syncing", true);
  DEBUG_PRINTLN("Time syncing");

  //encode current GPS signal to get latest timestamp for RTC
  gps.encode(Serial1.read());

  d = gps.date;
  t = gps.time;

  //set RTC to date from GPS

  rtc.adjust(DateTime(d.year(), d.month(), d.day(), t.hour(), t.minute(), t.second()));
  DateTime now = rtc.now();

  // TX
  String time = now.toString(buf1);
  printTime(time);
  DEBUG_PRINTLN("Time syncing");
  // Initialize the Si5351
  printText("Start SI5351", true);
  DEBUG_PRINTLN("Start SI5351");
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);

  // Use the Arduino's on-board LED as a keying indicator.
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
    pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  // Set CLK0 output
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA); // Set for max power if desired
  si5351.output_enable(SI5351_CLK0, 0);                 // Disable the clock initially

  // switch (cur_mode)
  //{

  //case MODE_WSPR:
  freq = WSPR_DEFAULT_FREQ;
  symbol_count = WSPR_SYMBOL_COUNT; // From the library defines
  tone_spacing = WSPR_TONE_SPACING;
  tone_delay = WSPR_DELAY;
  // break;
  /*     case MODE_FT8:
      freq = FT8_DEFAULT_FREQ;
      symbol_count = FT8_TONE_SPACING; // From the library defines
      tone_spacing = FT8_TONE_SPACING;
      tone_delay = FT8_DELAY;
      break; */

  //}

  // Encode the message in the transmit buffer
  set_tx_buffer();
  DEBUG_PRINTLN("Starting Transmisson mode...");

  //printText("TX ready");
  printText(call, true);
  printLocator();
  int delaying = 60 - (rtc.now().second());
  delay(delaying * 1000);
  printTemp(String(rtc.getTemperature()));

}

void send_wspr()
{
  printTX(true);
  printBand(currentBand, true);

  digitalWrite(RELAY_PIN, HIGH);

  //printText("TX "+currentBand +" >");
  DEBUG_PRINTLN("Transmisson " + currentBand + " started");
  //printText("TX "+currentBand);
  //mcp.digitalWrite(0, HIGH);
  encode();
  //mcp.digitalWrite(0, LOW);
  digitalWrite(RELAY_PIN, LOW);

  //printText("TX "+currentBand +">|");
  printTX(false);
  printBand("", false);
  DEBUG_PRINTLN("Transmisson  " + currentBand + " ended");
}

void loop()
{

  //DEBUG_PRINTLN(resync);
  /*    if (resync==1){
           DEBUG_PRINTLN("-----------------");
            DEBUG_PRINTLN("RESYNC");
            DEBUG_PRINTLN(Serial1.available() );
            while(Serial1.available() > 0)
            {Serial1.read();
            //serialData =  Serial1.read();
            //DEBUG_PRINTLN(serialData);
            } 
            //DEBUG_PRINTLN(serialData);
            DEBUG_PRINTLN(Serial1.available() );
            while(Serial1.available()){
            gps.encode(Serial1.read());
            }
            gps.encode(Serial1.read());

            d = gps.date;
            t = gps.time;
            //rtc.begin(DateTime(d.year(), d.month(), d.day(), t.hour(), t.minute()+2, t.second()));
            DateTime now = rtc.now();
            String time = now.toString(buf1);
            DEBUG_PRINT("Now: "); DEBUG_PRINTLN(time);
            resync = 0;
            DEBUG_PRINTLN("-----------------");
            
          } */

  DateTime rtc_time = rtc.now();

if(rtc_time.minute() != oldMinute)
{
oldMinute = rtc_time.minute();
  String myTime = String(rtc_time.hour()) + ":"+String(rtc_time.minute());
  printTime(myTime);
}
  // TX
  // DEBUG_PRINT(rtc_time.hour());
  // DEBUG_PRINT(":");
  // DEBUG_PRINT(rtc_time.minute());
  // DEBUG_PRINT(":");
  // DEBUG_PRINTLN(rtc_time.second());
  //oldTime=time;


  //}
  if (rtc_time.second() == 0)
  {
    if (rtc_time.minute() == 02 || rtc_time.minute() == 12 || rtc_time.minute() == 22 || rtc_time.minute() == 32 || rtc_time.minute() == 42 || rtc_time.minute() == 52)
    {
      DEBUG_PRINTLN("Send 80m");
      currentBand = "80m";
      freq = WSPR_80m_FREQ;
      send_wspr();
      DEBUG_PRINTLN("Finished 80m");
      resync = 0;
      printTemp(String(rtc.getTemperature()));
      DEBUG_PRINT(rtc.getTemperature());
      DEBUG_PRINTLN("°C");
    }

    if (rtc_time.minute() == 06 || rtc_time.minute() == 16 || rtc_time.minute() == 26 || rtc_time.minute() == 36 || rtc_time.minute() == 46 || rtc_time.minute() == 56)
    {
      DEBUG_PRINTLN("Send 10m");
      currentBand = "10m";
      freq = WSPR_10m_FREQ;
      send_wspr();
      DEBUG_PRINTLN("Finished 10m");
      resync = 0;
      printTemp(String(rtc.getTemperature()));
      DEBUG_PRINT(rtc.getTemperature());
      DEBUG_PRINTLN("°C");
    }
  }
  // Sleep until next TX
  delay(500);
}