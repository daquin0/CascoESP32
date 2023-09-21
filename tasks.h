class class_task {                              //Inicio de la clase de las tareas//
  public:                                       //Declaración de variables//
  unsigned long t_sen1= 0;
  unsigned long t_sen2= 0;
  unsigned long tS_sen = 0;
  unsigned long t_mqtt3= 0;
  unsigned long t_mqtt4= 0;
  unsigned long tS_mqtt1 = 0;
  unsigned long tiempolcd1 = 0;
  unsigned long tiempolcd2 = 0;
  unsigned long tiempoSegundoslcd = 0;
  
z
  public:                                       //Declaración de Métodos//
    void task_sensores(void);
    void task_mqtt(void);
    void task_LCD(void);
  
};


void class_task::task_sensores(){               //Tarea que se encarga de activar los sensore y mandar los datos JSON//
 t_sen2 = millis();
  if(t_sen2 > (t_sen1+10000)){
    t_sen1 = millis();                           //Actualiza el tiempo actual
    tS_sen = (t_sen1/1000);
    Serial.println("10 segundos ");
      sen.temperature();                        //Se llama al método de temperatura
      sen.mq4_metano();                         //Se llama al método de metano
      sen.mq7_monox();                          //Se llama al método de monóxido
      sen.humidity();                           //Se llama al método de humedad
      MSD.JSON();                               //Se llama al método para crear el JSON
      MSD.JSON_SaveFile();                      //Se llama al método de para guardar el JSON
  } 
}

void class_task::task_LCD(){                  //Tarea que se encarga de publicar en el LCD 
 tiempolcd1 = millis();
  if(tiempolcd1 > (tiempolcd2+5000)){
    tiempolcd2 = millis();                           //Actualiza el tiempo actual
    tiempoSegundoslcd = (tiempolcd2/1000);
  
  lcd.clear();                                //Se imprimen los datos de los sensores en la LCD
  lcd.setCursor(0, 0);                        //Lugar del cursor donde se imprimen los datos en el LCD
  lcd.print("T:"); 
  lcd.print(uint8_t(sen.temperatura));        //Se imprimen los datos de temperatura recabados
  lcd.print("C");
  
  lcd.print(" ");
  lcd.print("H: ");
  lcd.print(uint8_t(sen.h));                  //Se imprimen los datos de humedad recabados
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("CO "); 
  lcd.print(uint16_t(sen.promedio_monoxido));  //Se imprimen los datos de monóxido recabados
  lcd.print("U ");
  
  lcd.print("CH4 "); 
  lcd.print(uint16_t(sen.promedio_metano));   //Se imprimen los datos de metano recabados
  lcd.print("U");
  
  } 
}


void class_task::task_mqtt(){                  //Tarea que se encarga de publicar en el servidor de Mosquito//
 t_mqtt4 = millis();
  if(t_mqtt4 > (t_mqtt3+15000)){
    t_mqtt3 = millis();                             //Actualiza el tiempo actual
    tS_mqtt1 = (t_mqtt3/1000);
    Serial.println("15 segundos ");
    mqtt.publish_MQTT();                        //Tarea para publicar
  } 
}
