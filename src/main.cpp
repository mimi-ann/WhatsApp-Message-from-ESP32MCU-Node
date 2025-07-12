#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const int LED_PIN = 34;

//const int button = D1;
//const int LED = D34;
String sendData; 

void sendDataToWhatsApp ()
{
  delay(10); // this speeds up the simulation

  Serial.print("Connecting to");
  Serial.print("WhatsApp");

//https://api.callmebot.com/whatsapp.php?phone=27622646159&text=Welcome+Mimi,%20+I+am+activated&apikey=2672715

  WiFiClientSecure client;
  client.setInsecure(); //skips certificate verification

  HTTPClient http; 
  sendData = "https://api.callmebot.com/whatsapp.php?";
  sendData += "phone=27622646159";
  sendData += "&text=Welcome+Mimi,%20+I+am+activated";
  sendData += "&apikey=2672715";

  http.begin(client, sendData);
  //int httpCode = http.POST(sendData);
  int httpCode = http.GET();

  Serial.print("HTTP Response code: ");
  Serial.println(httpCode);

  if(httpCode > 0)
  {
    String payload = http.getString();
    Serial.println("Response: "+ payload);
    for(int i = 0; i < 5; i++) // Visual feedback for API call
    {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  }
  else 
  {
    Serial.println("Error on HTTP request");
    // Error - long blink
    digitalWrite(LED_PIN, HIGH);
    delay(2000);
    digitalWrite(LED_PIN, LOW);
  }

  http.end();
}
void setup() 
{
  // put your setup code here, to run once:
  pinMode(1, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println();
  Serial.println("Connecting To ");
  Serial.println(ssid);
  
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected!");

  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  sendDataToWhatsApp();

}

void loop ()
{
  //setup();
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

