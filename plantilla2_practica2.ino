/*****************************************************************************
*                                                                            *
*      NOMBRE:      Práctica 2.1.                                            *
*      FECHA:       16 de Mayo de 2022.                                      *
*      VERSIÓN:     1.0.                                                     *
*                                                                            *
*      AUTOR:       Equipo 1                                                 *
*      E-MAIL:      "ovelasco@ucol.mx "                                      *
*      E-MAIL:      "daquino@ucol.mx "                                       *
*      E-MAIL:      "jvazquez@ucol.mx "                                      *
*      E-MAIL:      "jdiaz33@ucol.mx "                                       *
*      E-MAIL:      "cvargas8@ucol.mx "                                       *
*      E-MAIL:      "rperalta0@ucol.mx "                                     *
*      COMPAÑÍA:    Universidad de Colima - Facultad de Telemática.          *
*                                                                            *                                 
*      Nombre:      ESP32.                                                   *
*                                                                            *
******************************************************************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Casco para evitar la intoxicación de los    *            
*      mineros.                                                              * 
*                                                                            *
******************************************************************************/

/*NOTAS:
 * ESP32 requiere instalar el json de su placa.
*/


#include "practica1_2.h"      //incluimos la libreria donde tenemos nuestra clase y metódos  
void setup( void ) {

  Serial.begin ( 115200 );    // Configuración BaudRate, un sistema puede tener varios puertos seriales físicos.
  delay(1000);                    //Asignamos un delay de un segundo
  sen.MQ4_begin();                //Llamamos al sensor MQ4
  sen.MQ7_begin();                //Llamamos al sensor MQ7
  sen.temp_begin();               //Llamamos al sensor de temperatura
  sen.hum_begin();                //Llamamos al sensor de humedad
  sen.lcd_begin();                //Llamamos a la LCD
  act.Buzzer_begin();             //Llamamos al buzzer
  RTC.RTC_init();                 //Llamamos al reloj
  MSD.MicroSD_init ();            //Llamamos a la micro SD
  mqtt.setup_WiFi ( );            //Llamamos al mqtt para configurar la WiFi
  mqtt.set_MQTT_server ( );       //Llamamos al servidor mqtt
  client.setCallback(callback);   //Llamamos al metodo callback
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~CICLO INFINITO DE TRABAJO~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop ( void ) {         //Mandámos a llamar a las tareas necesarias
  tsk.task_sensores();       //Tarea para los sensores
  tsk.task_mqtt();           //Tarea para publicar con mqtt
  tsk.task_LCD();            //Tarea para el funcionamiento del LCD
  mqtt.reconnect_MQTT ( );   //Tarea para reconectar al servidor
  RTC.get_time ();           //Tarea para obtener el tiempo
}

 void callback(char* topic, byte* payload, unsigned int length) {  //Método   para recibir mensajes mandados
  Serial.print("Message arrived [");                                //al topic de la placa ESP32
  Serial.print(topic);                                            //Nombre del topic del ESP32
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);                               //Se optiene y se imprime el mensaje recibido
  }
}
