# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Node_MCU_Code\\Node_MCU_Code.ino"
# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Node_MCU_Code\\Node_MCU_Code.ino"
# 2 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Node_MCU_Code\\Node_MCU_Code.ino" 2
# 3 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Node_MCU_Code\\Node_MCU_Code.ino" 2

void setup()
{
    InitSerialCommunication();
    InitWiFi();
    InitClient();
}

void loop()
{
    ReadSerial();
    UpdateBuffer();
    if (!client.connected())
    {
        ReconnectSilent();
    }
    client.loop();
    if (client.publish("pollutector/outgoing", JSONmessageBuffer) == true)
    {
        Serial.println("Success sending message");
    }
    else
    {
        Serial.println("Error sending message");
    }
    //delay(1000);
}
# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Node_MCU_Code\\MQTT.ino"
// Basic mqtt protocol setup
void InitClient()
{
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), 16);
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      client.publish("ENTC/Wifi_Outgoing", "Welcome to ENTC WiFi Analyzer | Portal");
      client.subscribe("ENTC/Wifi_incoming");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      delay(1000);
    }
  }
}

void ReconnectSilent()
{
  while (!client.connected())
  {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), 16);
    if (client.connect(clientId.c_str()))
    {
      // Serial.println("connected");
      // client.publish("ENTC/Wifi_Outgoing", "Welcome to ENTC WiFi Analyzer | Portal");
      // client.subscribe("ENTC/Wifi_incoming");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      delay(1000);
    }
  }
}
# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Node_MCU_Code\\Serial_Com.ino"
void InitSerialCommunication()
{
    Serial.begin(9600);
    SUART.begin(9600);
}

void ReadSerial()
{
    byte n = SUART.available();
    String y;
    if (n > 0)
    {
        String x = SUART.readString();
        y = x;
        String temp = String(y[0]) + String(y[1]);
        String humid = String(y[2]) + String(y[3]);
        // String gas = y.substring(4);
        String gas = String(y[4]) + String(y[5]+ String(y[6]));
        temperature = temp.toInt();
        humidity = humid.toInt();
        gasvalue = gas.toInt();
        Serial.print(temperature);
        Serial.print(humidity);
        Serial.println(gasvalue);
    }
}

void ReadDataAll()
{
    if (SUART.available())
    {
        String FullData = "";
        for (int i = 0; i < 4; i++)
        {
            char TempData = SUART.read();
            FullData += TempData;
        }
        Serial.print(FullData);
    }
}
# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Node_MCU_Code\\Wifi_Functions.ino"
void InitWiFi()
{
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

// void InitWiFiSilent()
// {
//     delay(10);
//     WiFi.begin(ssid, password);

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(20);
//     }

//     randomSeed(micros());

//     Serial.println("WiFi connected");
// }

void UpdateBuffer()
{
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject &JSONencoder = JSONbuffer.createObject();

    JSONencoder["GasSensorValue"] = String(gasvalue);
    JSONencoder["Temperature"] = String(temperature);
    JSONencoder["Humidity"] = String(humidity);



    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println("Sending message to MQTT topic..");
    Serial.println(JSONencoder.measureLength());
    Serial.println(JSONmessageBuffer);
}
