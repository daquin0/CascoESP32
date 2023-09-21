                                // Incluimos las librerias creadas//
                                
#include <ArduinoJson.h>      //Incluimos la libreria de JSON para Arduino
#define MICROSD_PIN 5         //Pin de la micro SD
#define EXTENSION ".json"     //Extensión del archivo que se creara para la micro SD

#include <SPI.h>              //Protocolo para utilizar micro SD
#include <SD.h>               //Libreria para utilizar micro SD
File MicroSD_File;            //Creacion del archivo a guardar
#include <Wire.h>             // I2C
#include "RTClib.h"           //Se incluyen las librerias para que el reloj obtenga los datos
  RTC_DS1307 rtc;             //y funcione con normalidad  
  
long lastMsg = 0;

#include <LiquidCrystal_I2C.h>              //Libreria para el funcionamiento de la pantalla LCD
LiquidCrystal_I2C lcd(0x27,16,2);           //Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas

                                     // Definimos los pines digitales donde se conectan los sensores
#include <DHT.h>                     //Libreria del sensor DHT11
#define DHTPIN 17                    //Sensor DHT11
#define MQ4_PIN 35                   //Sensor MQ4 Metano
#define MQ7_PIN 34                   //Sensor MQ7 Monóxido de Carbono

#define BUZZER_PIN 32                //Pines del actuador Buzzer

#define DHTTYPE DHT11                //Indicamos el tipo de sensor DHT
DHT dht(DHTPIN, DHTTYPE);            //Inicializamos el sensor DHT11

                //Se incluyen las librerias creadas para el funcionamiento del sistema embebido//
#include "rtc.h"
DS1307_RTC RTC; 

#include "actuador.h"
class_actuador_buzzer act;

#include "sensors.h"
class_sensor sen;

#include "microsd.h"
  MicroSD MSD;

#include "MQTT.h"
 MQTT mqtt;
 
                        //Libreria para las tareas de los dispositivos//
#include "tasks.h"
class_task tsk;
