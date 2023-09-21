class DS1307_RTC {               //Inicio de la clase para el funcionamiento del reloj//
 public:                                //Declaración de variables//
    uint8_t hora, minuto, segundo, dia, mes;
    uint16_t ano;
    String fecha = "", tiempo= ""; 

  public:                            //Declaración de Métodos//
    void RTC_init (void);             //Método para iniciar el reloj
    void get_time (void);             //Método para obtener el tiempo y fecha
    void format_date (void);          //Método para dar formato a la fecha
    void format_time (void);          //Método para dar formato a la hora

};

void DS1307_RTC:: RTC_init (void) {               //Método para la inicializar el Reloj
  while (! rtc.begin ( )) {                       //Se verifica la conexión del Reloj
    Serial.println(F("El RTC no ha iniciado correctamente, ERROR, revisar conexión y alimenantación "));
    Serial.flush ( );                             //Espera a que la transmisión de datos de salida serie termine.
  }
  Serial.println(F("El RTC ha iniciado correctamente, YEI"));  
}

void DS1307_RTC:: get_time (void) {             //Método para obtener los datos (Fecha y Hora) de la computadora
      DateTime now = rtc.now ();                //Instrucción para obtener los datos de fecha y hora de la computadora
      ano = now.year();
      mes = now.month();
      dia = now.day();
      hora = now.hour ();
      minuto = now.minute ();
      segundo = now.second ();
}


void DS1307_RTC :: format_date(void) {        //Método para darle un formato a la fecha obtenida
                                              //y se coloca en un String
  fecha = "";
  if (dia < 10) fecha += '0';
  fecha += dia;
  fecha += '/';
  
  if (mes < 10) fecha += '0';
  fecha += mes;
  fecha += '/';
  
  fecha += ano;
}

void DS1307_RTC :: format_time(void) {        //Método para darle un formato a la hora obtenida
                                              //y se coloca en un String
  tiempo =""; 
  if (hora < 10) tiempo += '0';
  tiempo += hora;
  tiempo += ':';
  
  if (minuto < 10) tiempo += '0';
  tiempo += minuto;
  tiempo += ':';
  
  if (segundo < 10) tiempo += '0';
  tiempo += segundo;
  tiempo += ':';
}
