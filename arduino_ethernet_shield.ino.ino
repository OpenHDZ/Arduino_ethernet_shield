/*
 Created by Areour Mohamed Cherif
 Visit: https://www.facebook.com/openhardwareDZ/

 Arduino with Ethernet Shield
 */

#include <SPI.h>
#include <Ethernet.h>


int led = 4;
 
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1C, 0x9D };   // physical mac address
byte ip[] = { 192, 168, 1, 10 };                       // ip address
byte gateway[] = { 192, 168, 1, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  // subnet mask

EthernetServer server(80);                             // server port     

String readString;

void setup() 
{
  // Open serial communications 
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() 
{
  // Create a client connection
  EthernetClient client = server.available();
  if (client) 
  {
    while (client.connected()) 
    {   
      if (client.available()) 
      {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) 
        {
          //store characters to string
          readString += c;
          //Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') 
        {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<TITLE>Open Hardware Algerie </TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Introduction to Ethernet shield</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Arduino with Ethernet Shield</H2>");
           client.println("<br />");  
           client.println("<p style='text-align:center'> <a href=\"/?ledon\"\">Turn On LED</a></p>");
           client.println("<p style='text-align:center'> <a href=\"/?ledoff\"\">Turn Off LED</a></p><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<p style='text-align:center'><img src='https://lh5.googleusercontent.com/-QGTwKI5cUuU/AAAAAAAAAAI/AAAAAAAAAIg/L_FAH-Njxgk/photo.jpg' alt='test' /></p>");
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           
           //controls the Arduino if you press the buttons
           if (readString.indexOf("?ledon") >0)
           {
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?ledoff") >0)
           {
               digitalWrite(led, LOW);
           }
           
           //clearing string for next read
           readString="";  
           
         }
       }
    }
}
}

