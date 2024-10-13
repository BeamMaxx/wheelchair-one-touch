#include <SPI.h>

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#include <WiFi.h>

const char* ssid = "Nongmon";///////wifiname/////
const char* password = "123456@0";////////password//////
WiFiServer server(80);
String header;
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

const int trig = 25;
const int echo = 26;

#define DL1  2  

#define DL2  15  

#define PWML 13 


/////////////////////////////////

#define DR1  17  

#define DR2  16 

#define PWMR 4  



#define A0 1034  
#define A1 1249    

#define A2 1507     
#define A3 1251  
int s0,s1,s2,s3;
int button =  34;
int snd = 12 ;

void analogs() 
{
  s0 = analogRead(32);
  s1 = analogRead(36);
  s2 = analogRead(39);
  s3 = analogRead(33);
}


//////////////////////////////////////////////


void setup() {
  Serial.begin(9600);
  // Initialize the output variables as outputs
  digitalWrite(DL1, LOW);
  digitalWrite(DL2, LOW);
  digitalWrite(DR1, LOW);
  digitalWrite(DR2, LOW);

  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(34, INPUT);
  

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();///////////
  pinMode(s0, INPUT); //
  pinMode(s1, INPUT); //
  pinMode(s2, INPUT); //
  pinMode(s3, INPUT); // 

  pinMode(DL1, OUTPUT);

  pinMode(DL2, OUTPUT);

  pinMode(PWML, OUTPUT);

  pinMode(DR1, OUTPUT);

  pinMode(DR2, OUTPUT);

  pinMode(PWMR, OUTPUT);  


}

void run(int spl, int spr) 

{

  if (spl > 0)

  {
    analogWrite(PWML, spl);
    digitalWrite(DL1, LOW);

    digitalWrite(DL2, HIGH);

    

  }

  else if (spl < 0)

  {
    analogWrite(PWML, -spl);
    digitalWrite(DL1, HIGH);

    digitalWrite(DL2, LOW);


  }

  else

  {

    digitalWrite(DL1, LOW);

    digitalWrite(DL2, LOW);
    //analogWrite(PWML, 0);
  }

  

  //////////////////////////////////////

  

  if (spr > 0)

  {
    analogWrite(PWMR, spr);
    digitalWrite(DR1, LOW);

    digitalWrite(DR2, HIGH);

  }

  else if (spr < 0)

  {
    analogWrite(PWMR, -spr);
    digitalWrite(DR1, HIGH);

    digitalWrite(DR2, LOW);

  }

  else

  {

    digitalWrite(DR1, LOW);

    digitalWrite(DR2, LOW);
    //analogWrite(PWMR, 0);
  }

}


void loop() {
  WiFiClient client = server.available();
  int sw = digitalRead(button);
  if (sw == 1){run(0,0);delay(3000);tone(snd, 660, 10000);}
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on button press on web page
            if (header.indexOf("GET /forword") >= 0) {
              Serial.println("forword");
              {For();}
            }
            if(header.indexOf("GET /backword") >= 0) {
              Serial.println("backword");
              {Back();}
            }
            if(header.indexOf("GET /stop") >= 0) {
              Serial.println("stop");
              {STOP();}
            }
            if (header.indexOf("GET /TURN.L") >= 0) {
              Serial.println("TURN.L");
              {left();}
            }
            if (header.indexOf("GET /TURN.R") >= 0) {
              Serial.println("TURN.R");
              {right();}
            }
            if (header.indexOf("GET /TURN.R") >= 0) {
              Serial.println("TURN.R");
              {right();}
            }
            ///////////////////////////////////////////////////Exr1
            if (header.indexOf("GET /Eoxr") >= 0) {
              Serial.println("Eoxr");
              {Eoxr();}
            }
            if (header.indexOf("GET /ExrToOpr") >= 0) {
              Serial.println("ExrToOpr");
              {ExrToOpr();}
            }
            if (header.indexOf("GET /ExrToPrr") >= 0) {
              Serial.println("ExrToPrr");
              {ExrToPrr();}
            }
            if (header.indexOf("GET /ExrToPtr") >= 0) {
              Serial.println("ExrToPtr");
              {ExrToPtr();}
            }
            if (header.indexOf("GET /ExrToA1") >= 0) {
              Serial.println("ExrToA1");
              {ExrToA1();}
            }
            if (header.indexOf("GET /ExrToA2") >= 0) {
              Serial.println("ExrToA2");
              {ExrToA2();}
            }
            if (header.indexOf("GET /ExrToA3") >= 0) {
              Serial.println("ExrToA3");
              {ExrToA3();}
            }
            if (header.indexOf("GET /ExrToA4") >= 0) {
              Serial.println("ExrToA4");
              {ExrToA4();}
            }
            ////////////////////////////////////////////////Opr2
            if (header.indexOf("GET /Oopr") >= 0) {
              Serial.println("Oopr");
              {Oopr();}
            }
            if (header.indexOf("GET /OprToExr") >= 0) {
              Serial.println("OprToExr");
              {OprToExr();}
            }
            if (header.indexOf("GET /OprToPrr") >= 0) {
              Serial.println("OprToPrr");
              {OprToPrr();}
            }
            if (header.indexOf("GET /OprToPtr") >= 0) {
              Serial.println("OprToPtr");
              {OprToPtr();}
            }
            if (header.indexOf("GET /OprToA1") >= 0) {
              Serial.println("OprToA1");
              {OprToA1();}
            }
            if (header.indexOf("GET /OprToA2") >= 0) {
              Serial.println("OprToA2");
              {OprToA2();}
            }
            if (header.indexOf("GET /OprToA3") >= 0) {
              Serial.println("OprToA3");
              {OprToA3();}
            }
            if (header.indexOf("GET /OprToA4") >= 0) {
              Serial.println("OprToA4");
              {OprToA4();}
            }
            ////////////////////////////////////////////////Prr03 pink
            if (header.indexOf("GET /Porr") >= 0) {
              Serial.println("Porr");
              {Porr();}
            }
            if (header.indexOf("GET /PrrToExr") >= 0) {
              Serial.println("PrrToExr");
              {PrrToExr();}
            }
            if (header.indexOf("GET /PrrToOpr") >= 0) {
              Serial.println("PrrToOpr");
              {PrrToOpr();}
            }
            if (header.indexOf("GET /PrrToPtr") >= 0) {
              Serial.println("PrrToPtr");
              {PrrToPtr();}
            }
            if (header.indexOf("GET /PrrToA1") >= 0) {
              Serial.println("PPrrToA1");
              {PrrToA1();}
            }
            if (header.indexOf("GET /PrrToA2") >= 0) {
              Serial.println("PrrToA2");
              {PrrToA2();}
            }
            if (header.indexOf("GET /PrrToA3") >= 0) {
              Serial.println("PrrToA3");
              {PrrToA3();}
            }
            if (header.indexOf("GET /PrrToA4") >= 0) {
              Serial.println("PrrToA4");
              {PrrToA4();}
            }
            ////////////////////////////////////////////////Ptr04
            if (header.indexOf("GET /Potr") >= 0) {
              Serial.println("Potr");
              {Potr();}
            }
            if (header.indexOf("GET /PtrToExr") >= 0) {
              Serial.println("PtrToExr");
              {PtrToExr();}
            }
            if (header.indexOf("GET /PtrToOpr") >= 0) {
              Serial.println("PtrToOpr");
              {PtrToOpr();}
            }
            if (header.indexOf("GET /PtrToPrr") >= 0) {
              Serial.println("PtrToPrr");
              {PtrToPrr();}
            }
            if (header.indexOf("GET /PtrToA1") >= 0) {
              Serial.println("PtrToA1");
              {PtrToA1();}
            }
            if (header.indexOf("GET /PtrToA2") >= 0) {
              Serial.println("PtrToA2");
              {PtrToA2();}
            }
            if (header.indexOf("GET /PtrToA3") >= 0) {
              Serial.println("PtrToA3");
              {PtrToA3();}
            }
            if (header.indexOf("GET /PtrToA4") >= 0) {
              Serial.println("PtrToA4");
              {PtrToA4();}
            }
            ////////////////////////////////////////////////A1
            if (header.indexOf("GET /A1ToExr") >= 0) {
              Serial.println("A1ToExr");
              {A1ToExr();}
            }
            if (header.indexOf("GET /A1ToOpr") >= 0) {
              Serial.println("A1ToOpr");
              {A1ToOpr();}
            }
            if (header.indexOf("GET /A1ToPrr") >= 0) {
              Serial.println("A1ToPrr");
              {A1ToPrr();}
            }
            if (header.indexOf("GET /A1ToPtr") >= 0) {
              Serial.println("A1ToPtr");
              {A1ToPtr();}
            }
            ////////////////////////////////////////////////A2
            if (header.indexOf("GET /A2ToExr") >= 0) {
              Serial.println("A2ToExr");
              {A2ToExr();}
            }
            if (header.indexOf("GET /A2ToOpr") >= 0) {
              Serial.println("A2ToOpr");
              {A2ToOpr();}
            }
            if (header.indexOf("GET /A2ToPrr") >= 0) {
              Serial.println("A2ToPrr");
              {A2ToPrr();}
            }
            if (header.indexOf("GET /A2ToPtr") >= 0) {
              Serial.println("A2ToPtr");
              {A2ToPtr();}
            }
            ////////////////////////////////////////////////A3
            if (header.indexOf("GET /A3ToExr") >= 0) {
              Serial.println("A3ToExr");
              {A3ToExr();}
            }
            if (header.indexOf("GET /A3ToOpr") >= 0) {
              Serial.println("A3ToOpr");
              {A3ToOpr();}
            }
            if (header.indexOf("GET /A3ToPrr") >= 0) {
              Serial.println("A3ToPrr");
              {A3ToPrr();}
            }
            if (header.indexOf("GET /A3ToPtr") >= 0) {
              Serial.println("A3ToPtr");
              {A3ToPtr();}
            }
            ////////////////////////////////////////////////A4
            if (header.indexOf("GET /A4ToExr") >= 0) {
              Serial.println("A4ToExr");
              {A4ToExr();}
            }
            if (header.indexOf("GET /A4ToOpr") >= 0) {
              Serial.println("A4ToOpr");
              {A4ToOpr();}
            }
            if (header.indexOf("GET /A4ToPrr") >= 0) {
              Serial.println("A4ToPrr");
              {A4ToPrr();}
            }
            if (header.indexOf("GET /A4ToPtr") >= 0) {
              Serial.println("A4ToPtr");
              {A4ToPtr();}
            }
            if (header.indexOf("GET /Show") >= 0) {
              Serial.println("Show");
              {Show();}
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the button
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { background-color:#f2fafa; font-family: Helvetica; display: inline-block; text-align: center;}");
            client.println(".button { background-color: #006400; color: white; padding: 20px 40px;");
            client.println(" font-size: 20px; cursor: pointer;}");
            client.println(".button2 {background-color:#ed111c; color: black; padding: 20px 40px;}");
            client.println(".button7 {background-color:#f2fafa; color: black; padding: 0px 0px;}");
            /////////////////////////////////////////////////////////////////////////////A1
            client.println(".button10 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button11 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button12 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button13 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            ///////////////////////////////////////////////////////////////////////////A2
            client.println(".button20 {background-color:#b0e8b7; color: black; padding: 10px 20px;}");
            client.println(".button21 {background-color:#b0e8b7; color: black; padding: 10px 20px;}");
            client.println(".button22 {background-color:#b0e8b7; color: black; padding: 10px 20px;}");
            client.println(".button23 {background-color:#b0e8b7; color: black; padding: 10px 20px;}");
            ///////////////////////////////////////////////////////////////////////////A3
            client.println(".button30 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button31 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button32 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button33 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            ///////////////////////////////////////////////////////////////////////////A4
            client.println(".button40 {background-color:#f5ce9f; color: black; padding: 10px 20px;}");
            client.println(".button41 {background-color:#f5ce9f; color: black; padding: 10px 20px;}");
            client.println(".button42 {background-color:#f5ce9f; color: black; padding: 10px 20px;}");
            client.println(".button43 {background-color:#f5ce9f; color: black; padding: 10px 20px;}");
            ///////////////////////////////////////////////////////////////////////////Erx1
            client.println(".button50 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            client.println(".button51 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            client.println(".button52 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            client.println(".button53 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            client.println(".button54 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            client.println(".button55 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            client.println(".button56 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            client.println(".button57 {background-color:#f5e49f; color: black; padding: 10px 20px;}");
            ///////////////////////////////////////////////////////////////////////////Opr2
            client.println(".button60 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            client.println(".button61 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            client.println(".button62 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            client.println(".button63 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            client.println(".button64 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            client.println(".button65 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            client.println(".button66 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            client.println(".button67 {background-color:#aee8f5; color: black; padding: 10px 20px;}");
            ///////////////////////////////////////////////////////////////////////////Prr03 pink
            client.println(".button70 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button71 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button72 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button73 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button74 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button75 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            client.println(".button76 {background-color:#eda8eb; color: black; padding: 10px 2px;}");
            client.println(".button77 {background-color:#eda8eb; color: black; padding: 10px 20px;}");
            ///////////////////////////////////////////////////////////////////////////Ptr04
            client.println(".button80 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button81 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button82 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button83 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button84 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button85 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button86 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button87 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button88 {background-color:#b781e3; color: black; padding: 10px 20px;}");
            client.println(".button3 {background-color:#006400; }</style></head>");
            // Web Page Heading
            client.println("<body><h1>WHEELCHAIR ONE TOUCH</h1>");
            
      
         
            client.println("<p><a href=\"/forword\"><button class=\"button\">^</button></a></p>");
            client.println("<p><a href=\"/TURN.L\"><button class=\"button button4\"><</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/stop\"><button class=\"button button2\">STOP</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/TURN.R\"><button class=\"button button5\">></button>");
            client.println("<p><a href=\"/backword\"><button class=\"button button3\">v</button></a></p>");
            //////////////////////////////////////////////////////////////////////////////////////////////////////A1
            client.println("<p><a href=\"/A1ToExr\"><button class=\"button button10\">A1ToExr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A1ToOpr\"><button class=\"button button11\">A1ToOpr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A1ToPrr\"><button class=\"button button12\">A1ToPrr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A1ToPtr\"><button class=\"button button13\">A1ToPtr</button>");
            ///////////////////////////////////////////////////////////////////////////A2
            client.println("<p><a href=\"/A2ToExr\"><button class=\"button button20\">A2ToExr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A2ToOpr\"><button class=\"button button21\">A2ToOpr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A2ToPrr\"><button class=\"button button22\">A2ToPrr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A2ToPtr\"><button class=\"button button23\">A2ToPtr</button>");
            ///////////////////////////////////////////////////////////////////////////A3
            client.println("<p><a href=\"/A3ToExr\"><button class=\"button button30\">A3ToExr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A3ToOpr\"><button class=\"button button31\">A3ToOpr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A3ToPrr\"><button class=\"button button32\">A3ToPrr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A3ToPtr\"><button class=\"button button33\">A3ToPtr</button>");
             ///////////////////////////////////////////////////////////////////////////A4
            client.println("<p><a href=\"/A4ToExr\"><button class=\"button button40\">A4ToExr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A4ToOpr\"><button class=\"button button41\">A4ToOpr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A4ToPrr\"><button class=\"button button42\">A4ToPrr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/A4ToPtr\"><button class=\"button button43\">A4ToPtr</button>");
            ///////////////////////////////////////////////////////////////////////////Erx1
            client.println("<p><a href=\"/Eoxr\"><button class=\"button button50\">Exr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/ExrToOpr\"><button class=\"button button51\">ExrToOpr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/ExrToPrr\"><button class=\"button button52\">ExrToPrr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/ExrToPtr\"><button class=\"button button53\">ExrToPtr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/ExrToA1\"><button class=\"button button54\">ExrToA1</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/ExrToA2\"><button class=\"button button55\">ExrToA2</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/ExrToA3\"><button class=\"button button56\">ExrToA3</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/ExrToA4\"><button class=\"button button57\">ExrToA4</button>");
            ///////////////////////////////////////////////////////////////////////////Opr2
            client.println("<p><a href=\"/Oopr\"><button class=\"button button60\">Opr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/OprToExr\"><button class=\"button button61\">OprToExr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/OprToPrr\"><button class=\"button button62\">OprToPrr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/OprToPtr\"><button class=\"button button63\">OprToPtr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/OprToA1\"><button class=\"button button64\">OprToA1</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/OprToA2\"><button class=\"button button65\">OprToA2</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/OprToA3\"><button class=\"button button66\">OprToA3</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/OprToA4\"><button class=\"button button67\">OprToA4</button>");
            ///////////////////////////////////////////////////////////////////////////Prr03 pink
            client.println("<p><a href=\"/Porr\"><button class=\"button button70\">Prr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PrrToExr\"><button class=\"button button71\">PrrToExr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PrrToOpr\"><button class=\"button button72\">PrrToOpr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PrrToPtr\"><button class=\"button button73\">PrrToPtr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PrrToA1\"><button class=\"button button74\">PrrToA1</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PrrToA2\"><button class=\"button button75\">PrrToA2</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PrrToA3\"><button class=\"button button76\">PrrToA3</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PrrToA4\"><button class=\"button button77\">PrrToA4</button>");
            ///////////////////////////////////////////////////////////////////////////Ptr04
            client.println("<p><a href=\"/Potr\"><button class=\"button button80\">Ptr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PtrToExr\"><button class=\"button button81\">PtrToExr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PtrToOpr\"><button class=\"button button82\">PtrToOpr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PtrToPrr\"><button class=\"button button83\">PtrToPrr</button>");
            client.println("<button class=\"button button7\" <p><a href=\"PtrToA1\"><button class=\"button button84\">PtrToA1</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PtrToA2\"><button class=\"button button85\">PtrToA2</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PtrToA3\"><button class=\"button button86\">PtrToA3</button>");
            client.println("<button class=\"button button7\" <p><a href=\"/PtrToA4\"><button class=\"button button87\">PtrToA4</button>");
            client.println("<p><a href=\"/Show\"><button class=\"button button2\">Show</button></a></p>");

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
void P()     


{while (1){ 


  analogs();


if ((s0 > A0) and (s3 > A3)){run(60, 56.4);}


if (s1 < A1){run(-30, 30);}


if (s2 < A2){run(30, -30);}



if (s0 < A0){run(-70, 70);}


if (s3 < A3){run(70, -70);}


if ((s1 < A1) and (s3 < A3))


    {run(50, 42);delay(270);run(0, 0);delay(100);break;}
  }
}


void P1()     


{run(10, 10);delay(800);run(0, 0);delay(100);
  while (1){ 


  analogs();


if ((s0 > A0) and (s3 > A3)){run(60, 50);}


if (s1 < A1){run(-17, 30);}


if (s2 < A2){run(30, -17);}


//if (s0 < A0){run(-100, 100);}


//if (s3 < A3){run(100, -100);}

else {run(60,56.4);}


if ((s1 < A1) and (s3 < A3))


    {run(50, 42);delay(650);run(0, 0);delay(100);break;}
  }
}
void PLeft()


{while (1){ 


  analogs();


if ((s0 > A0) and (s3 > A3)){run(50, 45);}


if (s1 < A1){run(-30, 30);}


if (s2 < A2){run(30, -30);}


//if (s0 < A0){run(-100, 100);}


//if (s3 < A3){run(100, -100);}

else {run(50,47);}


if ((s0 < A0) and (s1 < A1))


    {run(50, 42);delay(350);run(0, 0);delay(100);break;}
  }
}
void PRight()

{while (1){ 


  analogs();


if ((s0 > A0) and (s3 > A3)){run(50, 45);}


if (s1 < A1){run(-30, 30);}


if (s2 < A2){run(30, -100);}


//if (s0 < A0){run(-100, 100);}


//if (s3 < A3){run(100, -100);}

else {run(50,47);}


if ((s2 < A2) and (s3 < A3))


    {run(50, 42);delay(350);run(0, 0);delay(100);break;}
  }
}




void L(){L0();L2();} 

void L0(){while (1){analogs();run(-30,30);if(s0<A0){run(0,0);break;}}} //S0

void L1(){while (1){analogs();run(-20,20);if(s1<A1){run(0,0);break;}}} //S1

void L2(){while (1){analogs();run(-15,15);if(s2<A2){run(0,0);break;}}} //S2
//////////////////////////////
void R(){R0();R2();}

void R0(){while (1){analogs();run(30,-30);if(s3<A3){run(0,0);break;}}} //S0

void R1(){while (1){analogs();run(20,-20);if(s2<A2){run(0,0);break;}}} //S1

void R2(){while (1){analogs();run(15,-15);if(s1<A1){run(0,0);break;}}} //S2

////////////////////////////////////

void b() 
{while (1){ 


  analogs();
run(-50,-47);delay(300); 
if ((s0 < A0) and (s2 < A2))
    {run(50, 47);delay(650);run(0, 0);delay(100);break;}
    else {run(-50,-47);}
  }
}                                                                //{run(-100,-100);delay(1000);run(0,0);delay(600);}
//////////////////////////////////////////////////////
void STOP(){run(0,0);}
void For(){run(100, 94);}
void Back(){run(-100, -94);}
void left(){run(-50, 47);}//run(-50, 47);
void right(){run(50, -47);}
////////////////////////////////////////////////////////////////////////////////////////
void Eoxr(){P1();L();P();P();L();}//Exr1
void ExrToOpr(){R();P();P();L();}
void ExrToPrr(){R();P();P();R();}
void ExrToPtr(){L();P();L();P();P();L();}
void ExrToA1(){L();L();P();PRight();}
void ExrToA2(){L();L();P();PRight();R();PLeft();L();}
void ExrToA3(){L();L();P();PRight();R();PLeft();PLeft();P();L();}
void ExrToA4(){L();P();P();L();P();P();P();P();}//Exr1
///////////////////////////////////////////////////////////////////////
void Oopr(){P1();L();P();P();R();P();P();L();}//Opr2
void OprToExr(){L();P();PLeft();}
void OprToPrr(){L();L();}
void OprToPtr(){L();P();PLeft();L();P();P();L();P();P();L();}
void OprToA1(){R();P();PRight();}
void OprToA2(){R();P();PRight();R();PLeft();L();}
void OprToA3(){R();P();PRight();R();PLeft();PLeft();L();}
void OprToA4(){R();P();PRight();R();PLeft();PLeft();P();L();}//Opr2
//////////////////////////////////////////////////////////////////////
void Porr(){P1();L();P();P();R();P();P();R();}//Prr03 pink
void PrrToExr(){R();P();PLeft();}
void PrrToOpr(){R();R();}
void PrrToPtr(){R();P();PLeft();L();P();P();L();P();P();L();}
void PrrToA1(){L();P();PRight();}
void PrrToA2(){L();P();PRight();R();PLeft();L();}
void PrrToA3(){L();P();PRight();R();PLeft();PLeft();L();}
void PrrToA4(){L();P();PRight();R();PLeft();PLeft();PLeft();L();}//Prr03 pink
//////////////////////////////////////////////////////////////////////////
void Potr(){P1();P();P();L();}//Ptr04
void PtrToExr(){L();P();P();R();P();P();L();}
void PtrToOpr(){L();P();P();R();P();P();R();P();P();L();}
void PtrToPrr(){L();P();P();R();P();P();R();P();P();R();}
void PtrToA1(){R();P();P();L();PLeft();PLeft();P();R();}
void PtrToA2(){R();P();P();L();PLeft();PLeft();R();}
void PtrToA3(){R();P();P();L();PLeft();R();}
void PtrToA4(){R();P();P();}//Ptr04
//////////////////////////////////////////////////////////////////////////
void A1ToExr(){R();R();P();P();P();PLeft();}//A1
void A1ToOpr(){R();R();P();P();R();}
void A1ToPrr(){R();R();P();P();L();}
void A1ToPtr(){R();PLeft();PLeft();P();R();P();P();R();}//A1
//////////////////////////////////////////////////////////
void A2ToExr(){L();P();L();P();P();P();PLeft();}//A2
void A2ToOpr(){L();P();L();P();P();R();}
void A2ToPrr(){L();P();L();P();P();L();}
void A2ToPtr(){R();PLeft();P();R();P();P();R();}//A2
//////////////////////////////////////////////////////////
void A3ToExr(){R();P();R();P();P();P();P();R();P();P();L();}//A3
void A3ToOpr(){L();PLeft();P();L();P();P();R();}
void A3ToPrr(){L();PLeft();P();L();P();P();L();}
void A3ToPtr(){R();P();R();P();P();R();}//A3
//////////////////////////////////////////////////////////
void A4ToExr(){L();L();P();P();P();P();R();P();P();L();}//A4
void A4ToOpr(){L();P();L();P();P();R();}
void A4ToPrr(){L();PLeft();PLeft();P();L();P();P();L();}
void A4ToPtr(){L();L();P();P();R();}//A4
/////////////////////////////////////////////////////
void Show(){P1();L();P();P();L();delay(10000);L();P();P();L();P();P();P();P();delay(10000);L();L();P();P();R();delay(10000);L();P();P();R();P();P();R();P();P();R();delay(10000);L();P();PRight();R();PLeft();PLeft();P();L();}