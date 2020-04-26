# ESP32 MQTT LAMP CONTROL
This project using ESP32 to control LED ON and OFF, MQTT protocol for communication protocol and Node-RED as MQTT client for GUI in smartphone browser. MQTT broker and Node-RED server installed in Raspberry Pi. For further explanation, please visit my blog in Medium [here](https://medium.com/@elvandry13/hack-fitting-lampu-sensor-cahaya-tutorial-esp32-mqtt-dan-node-red-368d43e71c70).

## 1. Wifi Configuration
Setup your SSID and password Wifi here :
```cpp
// Enter SSID and Password
const char *ssid = "WIFI_SSID";
const char *password = "WIFI_PASSWD";
```

## 2. MQTT Configuration
Setup your MQTT Broker IP Address, username and password here :
```cpp
/ Enter MQTT Broker IP address
const char *mqtt_server = "MQTT_IP_ADDR";

// Enter MQTT security
const char *mqtt_user = "MQTT_USER";
const char *mqtt_pass = "MQTT_PASSWD";
```

## 3. Subscribe Topic
Subscribe to the topic and receive the message. The received message will control the LED.
```cpp
if (String(topic) == "esp32/output")
{
    Serial.print("Changing output to ");
    if (messageTemp == "on")
    {
        Serial.println("on");
        digitalWrite(ledPin, HIGH);
    }
    else if (messageTemp == "off")
    {
        Serial.println("off");
        digitalWrite(ledPin, LOW);
    }
}
```