class class_sensor {             //Inicio de la clase para el funcionammiento de los sensores//
  public:                                 //Declaración de variables//
    float h =0;                           //Variable para la humedad
    float f =0;                           //Variable para los ferenheit
    float temperatura =0;                 //Variable para la temperatura
    float promedio_monoxido =0;           //Variable para el promedio monóxido
    float resultado_monoxido =0;          //Variable para el resultado monóxido
    float promedio_metano =0;             //Variable para el promedio metano
    float resultado_metano =0;            //Variable para el resultado metano
    bool buzzer_metano =0;                      //Se declaran boleanos para el buzzer
    bool buzzer_mono =0;                        //Se declaran boleanos para el buzzer
    String fecha_buzzer_metano = "";          //Se declaran cadenas para la fecha del sensor metano
    String tiempo_buzzer_metano = "";         //Se declaran cadenas para el tiempo del sensor metano
    String fecha_buzzer_mono = "";            //Se declaran cadenas para la fecha del sensor monóxido
    String tiempo_buzzer_mono = "";           //Se declaran cadenas para el tiempo del sensor monóxido

    public:                                     //Declaración de Métodos//
      void temperature (void);              //Método para los datos de temperatura
      void humidity (void);                 //Método para los datos de humedad
      void mq7_monox (void);                //Método para los datos del sensor monóxido
      void mq4_metano (void);               //Método para los datos del sensor metano
      void MQ4_begin (void);                //Método para iniciar el sensor metano
      void MQ7_begin (void);                //Método para iniciar el sensor monóxido
      void temp_begin (void);               //Método para iniciar el sensor de temperatura
      void hum_begin (void);                //Método para iniciar el sensor de humedad
      void lcd_begin (void);                //Método para iniciar la LCD
};

void class_sensor::lcd_begin (void){          //Método para inicializar la LCD
    Wire.begin();                             //Pin donde inicializamos el LCD                      
    lcd.init();                               //Iniciamos la LCD
    lcd.backlight();                          //Encender la luz de fondo.
    lcd.backlight(); 
}


void class_sensor::temp_begin (void){               //Se inicializa la clase para leer la temperatura
  dht.begin();
}
void class_sensor::hum_begin (void){                //Se inicializa la clase para leer la humedad
  dht.begin();
}

void class_sensor::temperature ( void ) {           //Método para leer la temperatura
 
  temperatura = dht.readTemperature();              // Leemos la temperatura en grados centígrados (por defecto)
  f = dht.readTemperature(true);                    // Leemos la temperatura en grados Fahreheit
 
  if (isnan(temperatura) || isnan(f)) {             // Comprobamos si ha habido algún error en la lectura
    Serial.println("Error obteniendo temperatura del sensor DHT11");
    return;
  }
                                              //Se imprimen los datos de temperatura en el Serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C ");
  Serial.print(f);
  Serial.println(" °F\t");
    
}

void class_sensor::humidity ( void ) {          //Método para leer la humedad
  h = dht.readHumidity();                       //Leemos la humedad
  
  if (isnan(h)) {                               // Comprobamos si ha habido algún error en la lectura
    Serial.println("Error obteniendo humedad del sensor DHT11");
    return;
  }
                                          //Se imprimen los datos de temperatura en el Serial
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println(" %\t");
  
}

void class_sensor::MQ4_begin (void){               //Se coloca el modo en que se lee el sensor MQ4 Metano
  pinMode(MQ4_PIN,INPUT);
}
void class_sensor::MQ7_begin (void){               //Se coloca el modo en que se lee el sensor MQ7 Monóxido de Carbono
  pinMode(MQ7_PIN,INPUT);
}

void class_sensor::mq4_metano (void){               //Método para el sensor que detecta metano MQ4
    promedio_metano = 0;
    resultado_metano = 0;

    float promedioMetano[11];                      //Array para los datos de muestra
    resultado_metano = 0;
    promedio_metano = 0; 
    
    for(int i = 0; i<=11; i++) {                  //Se obtienen muestras y se saca un promedio de los datos
      int mq4_estado = analogRead(MQ4_PIN);
      promedioMetano[i] = mq4_estado; 
      resultado_metano += promedioMetano[i];
    }

    promedio_metano = resultado_metano/11;      //Se saca el promedio de los datos
    
    if(promedio_metano > 900){                  //Se compara los datos y se imprime un aviso
      Serial.print("Ayuda metano de: ");        //Se imprimen los datos en el Serial
      Serial.println(promedio_metano);
      
      act.Buzzer_activo();                      //Activamos el buzzer
                         
      buzzer_metano =1;                         //Bandera del buzzer
      RTC.get_time();
      RTC.format_time();                        //Formato de la hora
      RTC.format_date();                        //Formato de la fecha
      tiempo_buzzer_metano = RTC.tiempo;        //Hora en la que se activo el buzzer
      fecha_buzzer_metano = RTC.fecha;          //Fecha en la que se activo el buzzer
    } else {
 
      Serial.print("No hay riesgo, metano de: "); //Se imprimen los datos en el Serial
      Serial.println(promedio_metano);
      
      act.Buzzer_inactivo();                    //Desactivamos el buzzer
    }
}

void class_sensor::mq7_monox (void){           //Método para el sensor que detecta monóxido de carbono MQ7
    promedio_monoxido = 0;
    resultado_monoxido = 0;
    //buzzer = 0;

    float promedioMonoxido[10];                //Array para los datos de muestra
    resultado_monoxido = 0;
    promedio_monoxido = 0; 
    
    for(int i = 0; i<=10; i++) {              //Se obtienen muestras y se saca un promedio de los datos
      int mq7_estado = analogRead(MQ7_PIN);
      promedioMonoxido[i] = mq7_estado; 
      resultado_monoxido += promedioMonoxido[i];
    }

    promedio_monoxido = resultado_monoxido/10;     //Se saca el promedio de los datos
    
    if(promedio_monoxido > 600){              //Se compara los datos y se imprime un aviso
      Serial.print("Ayuda monoxido de: ");    //Se imprimen los datos en el Serial
      Serial.println(promedio_monoxido);
      
      act.Buzzer_activo();                    //Activamos el buzzer
                                              
      buzzer_mono=1;                          //Bandera del buzzer
      RTC.get_time();
      RTC.format_time();                      //Formato de la hora
      RTC.format_date();                      //Formato de la fecha
      tiempo_buzzer_mono= RTC.tiempo;         //Hora en la que se activo el buzzer
      fecha_buzzer_mono = RTC.fecha;          //Fecha en la que se activo el buzzer
    } else {
      Serial.print("No hay riesgo, monoxido de: ");     //Se imprimen los datos en el Serial
      Serial.println(promedio_monoxido);
      
      act.Buzzer_inactivo();                            //Desactivamos el buzzer
    }
}
