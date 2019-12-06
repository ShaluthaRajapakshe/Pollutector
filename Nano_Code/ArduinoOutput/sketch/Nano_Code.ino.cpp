#include <Arduino.h>
#line 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino"
#line 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino"
#include "_Def.h"
#include "_Var.h"

#line 4 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino"
void setup();
#line 9 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino"
void loop();
#line 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\SensorData.ino"
void ReadSensorData();
#line 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Serial_Com.ino"
void InitSerialCommunication();
#line 7 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Serial_Com.ino"
void ReadSerial();
#line 15 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Serial_Com.ino"
void WaitforMain(char Text);
#line 4 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Nano_Code.ino"
void setup()
{
    InitSerialCommunication();
}

void loop()
{
    ReadSensorData(); 
}
#line 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\SensorData.ino"
void ReadSensorData()
{
    dht11.read(&temperature, &humidity, NULL);    
    gassensorValue = analogRead(gas_sensor_pin); // read analog input pin 0 
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

#line 1 "c:\\Users\\Shalutha\\Documents\\IOT_Project_Pollutector\\Nano_Code\\Serial_Com.ino"
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
