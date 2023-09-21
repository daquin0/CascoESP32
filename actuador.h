class class_actuador_buzzer{          //Inicio de la clase actuador del buzzer//

  public:                             //Declaración de Metodos//
    void Buzzer_activo(void);         //Método para activar el buzzer
    void Buzzer_begin (void);         //Método para iniciar el buzzer
    void Buzzer_inactivo(void);       //Método para desactivar el buzzer
};

void class_actuador_buzzer::Buzzer_activo (void ){          //Método para encender el buzzer
    digitalWrite(BUZZER_PIN, HIGH);
 }
void class_actuador_buzzer::Buzzer_inactivo (void ){        //Método para apagar el buzzer
   digitalWrite(BUZZER_PIN, LOW); 
 }

void class_actuador_buzzer::Buzzer_begin (void){             //Se coloca el modo en que se le mandara la información, Salida
  pinMode(BUZZER_PIN,OUTPUT);
}
