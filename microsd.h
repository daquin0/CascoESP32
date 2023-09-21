class MicroSD {                     //Inicio de la clase para la Micro SD//
 public:
    String filename = "", JSON_STRING= "";       //Variable string para el nombre del documento y declaración del JSON
   
  public:                           //Declaración de Metodos//
    void MicroSD_init (void);     //Método para iniciar la micro SD
    void FileID (void);           //Método para dar nombre al archivo
    void JSON (void);             //Método para crear el JSON
    void JSON_SaveFile ();        //Método para guardar el JSON
};

void MicroSD::MicroSD_init (void) {               //Inicialización de la micro SD
  
  while (!SD.begin(MICROSD_PIN )) {               //Se inicia la función de la micro SD y verifica la conexión
    Serial.println(F("Error de reconocimiento en la MicroSD revisa las conexiones"));
    delay(1000);
  }
  Serial.println(F("La librería MicroSD se ha inicializado con exito"));
}

void MicroSD::FileID  (void) {                    //Método para colocarle un nombre al documento creado

  filename = '/';                                 //Instrucción para localizar la raiz de la micro SD
  if (RTC.dia < 10) filename += '0';
  filename+= RTC.dia;
  if (RTC.mes < 10) filename += '0';
  filename += RTC.mes;
  filename += RTC.ano;
  filename += EXTENSION;                          //Extensión .json
  
}

void MicroSD::JSON  (void) {                      //Método que creará el JSON con los datos de los sensores
  JSON_STRING = "";
  RTC.get_time();                                 //Obtiene los datos del reloj
  RTC.format_time();                              //Obtiene el formato del tiempo
  RTC.format_date();                              //Obtiene el formato de la fecha
  
  DynamicJsonDocument doc (1024);                       //Se crea el documento JSON
  doc ["temperatura"] = uint8_t(sen.temperatura);       //y se colocan los datos dentro del documento
  doc ["humedad"]= uint8_t(sen.h);
  doc ["monoxido"]= uint16_t(sen.promedio_monoxido); 
  doc ["metano"]= uint16_t(sen.promedio_metano);
  doc ["tiempo"] = RTC.tiempo.c_str();
  doc ["fecha"] = RTC.fecha.c_str();
  if (sen.buzzer_metano){                                     //Coloca la información del buzzer si éste es activado
    doc["buzzer metano"]=sen.buzzer_metano; 
    doc["fecha buzzer metano "]=sen.fecha_buzzer_metano;
    doc["tiempo buzzer metano"]= sen.tiempo_buzzer_metano;
    }
     if (sen.buzzer_mono){                                    //Coloca la información del buzzer si éste es activado
    doc["buzzer mono"]=sen.buzzer_mono;
    doc["fecha buzzer mono "]=sen.fecha_buzzer_mono;
    doc["tiempo buzzer mono"]= sen.tiempo_buzzer_mono;
    }

    sen.buzzer_metano = 0 ;
    sen.buzzer_mono = 0 ;
 
  
  serializeJson(doc, JSON_STRING);

}

void MicroSD::JSON_SaveFile  ( ) {              //Clase para guardar el JSON en el documento
  FileID();                                     //Se llama el nombre del documento
  MicroSD_File = SD.open (filename, FILE_APPEND);     //Se abre la micro SD y se crea el documento
  
  if (MicroSD_File) {                           //Intrucción para guardar el JSON en el documento creado
     //serializeJson(*doc, JSON_STRING);
     MicroSD_File.print ( JSON_STRING);         //Imprime el JSON dentro del documento
     MicroSD_File.println (',');
     MicroSD_File.close ();
     Serial.println(F("Se ha guardado con exito"));
  }
  else{                                         //Intrucción para informar el error de guardado
    Serial.println(F("Error error al guardar en la SD"));
    }
  delay (1000);
}
