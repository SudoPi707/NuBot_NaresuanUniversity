/*
 * rosserial Publisher Example
 * Prints "hello world!"
 * This intend to connect to a Wifi Access Point
 * and a rosserial socket server.
 * You can launch the rosserial socket server with
 * roslaunch rosserial_server socket.launch
 * The default port is 11411
 *
 * or use this -->  rosrun rosserial_python serial_node.py tcp 11411
 */


#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <ESP8266WiFi.h>

int Input0 = D0;
int Input1 = D1;
int Input2 = D2;
int Input3 = D5;
int Input4 = D6;
int Input5 = D7;
int Input6 = D8;

int inputList[] = {Input0, Input1, Input2, Input3, Input4, Input5, Input6};

const char* ssid     = "Mi_LAB";
const char* password = "milab603";
// Set the rosserial socket server IP address
IPAddress server(192,168,0,101);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;

std_msgs::Int16 int16;
ros::Publisher index_key("location_index", &int16);

// Be polite and say hello
char hello[13] = "hello world!";

void setup()
{
    for (int i=0; i < 7; i++){
        pinMode(inputList[i], INPUT);
    }

  // Use ESP8266 serial to monitor the process
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect the ESP8266 the the wifi AP
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Another way to get IP
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());

  // Start to be polite
  nh.advertise(index_key);
}

void loop()
{

  if (nh.connected()) {
    // Serial.println(digitalRead(Input));
    // Serial.println("Connected");
    // str_msg.data = hello;
    // chatter.publish( &str_msg );

    byte inputByte = 0b00000000;

    for (int i=0; i < 7; i++){

        if (digitalRead(inputList[i]) == 1 ){
            bitSet(inputByte, i);
        }
    }

    Serial.println(inputByte);
    Serial.println(inputByte, BIN);
    
    switch (inputByte)
    {
    case 1:
        int16.data = 0;
        Serial.println("Publish: 0");
        index_key.publish( &int16 );
        break;
    
    case 2:
        int16.data = 1;
        Serial.println("Publish: 1");
        index_key.publish( &int16 );
        break;
    
    case 4:
        int16.data = 2;
        Serial.println("Publish: 2");
        index_key.publish( &int16 );
        break;

    case 8:
        int16.data = 3;
        Serial.println("Publish: 3");
        index_key.publish( &int16 );
        break;

    case 16:
        int16.data = 4;
        Serial.println("Publish: 4");
        index_key.publish( &int16 );
        break;

    case 32:
        int16.data = 5;
        Serial.println("Publish: 5");
        index_key.publish( &int16 );
        break;

    case 64:
        int16.data = 6;
        Serial.println("Publish: 6");
        index_key.publish( &int16 );
        break;

    case 128:
        int16.data = 7;
        Serial.println("Publish: 7");
        index_key.publish( &int16 );
        break;
    
    default:
        break;
    }
  } else {
    Serial.println("Not Connected");
  }
  nh.spinOnce();
  // Loop exproximativly at 1Hz
  delay(1000);
}
