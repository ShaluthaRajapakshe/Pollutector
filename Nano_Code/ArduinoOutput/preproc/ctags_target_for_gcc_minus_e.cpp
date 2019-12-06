# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino"
# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino"
# 2 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino" 2
# 3 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino" 2

void setup()
{
    InitSerialCommunication();
}

void loop()
{
    ReadSensorData();
}
# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\SensorData.ino"
void ReadSensorData()
{
    dht11.read(&temperature, &humidity, 
# 3 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\SensorData.ino" 3 4
                                       __null
# 3 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\SensorData.ino"
                                           );
    gassensorValue = analogRead(A1); // read analog input pin 0 
    // Serial.println(sensorValue, DEC); // prints the value read
    //---show temp and humidity as integers on Serial moniotr
    Serial.print("Temperature = ");
    Serial.print((int)temperature);
    Serial.print(" degC");
    Serial.print("  "); //space
    Serial.print("Humidity = ");
    Serial.print((int)humidity);
    Serial.print(" %H");
    Serial.print("Gas = ");
    Serial.println((int)gassensorValue);

    String DataMessage = String(temperature) + String(humidity) + String(gassensorValue);

    SUART.print(DataMessage);
    delay(1000);
}
# 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Serial_Com.ino"
void InitSerialCommunication()
{
    Serial.begin(9600);
    SUART.begin(9600); //to match with NodeMCU which prefers higher Bd to work
}

void ReadSerial()
{
    if (SUART.available())
    {
        char message = SUART.read();
    }
}

void WaitforMain(char Text)
{
    while (1)
    {
        if (SUART.available())
        {
            char message = SUART.read();
            if (message == Text)
            {
                break;
            }
        }
    }
}
