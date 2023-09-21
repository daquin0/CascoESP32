                                    //Libreria creada para utilizar MQTT
#include <WiFi.h>
  WiFiClient ESP32_WIFI;            //Intrucción para la conexión a travez de ESP32

#include <PubSubClient.h>
PubSubClient client ( ESP32_WIFI );
const char* HOTSPOT_WIFI = "Missael";                 //Nombre del hotspot al que se conecta la placa
const char* HOTSPOT_PWD = "missael2021";              //Contraseña del hotspot al que se conecta la placa
const char* MQTT_SERVER = "test.mosquitto.org";       //Nombre del servidor de mosquito para conectar la placa
#define MQTT_PORT 1883                                //Numero de puerto en el que escucha el servidor
#define TOPIC "Practica2"                             //Nombre del topic en donde se publicara la información

class MQTT {                                //Inicio de la clase MQTT//
  
  public:                                   //Declaración de Metodos//
    void publish_MQTT ( void );                     //Método para publicar
    void reconnect_MQTT ( void );                   //Método para reconectar
    void setup_WiFi ( void );                       //Método para configurar la conexión WiFi
    void set_MQTT_server ( void );                  //Método para conectarse al servidor
    void callback (char *, byte *,unsigned int);

    
  };

 

void MQTT :: set_MQTT_server ( void ) {               //Método para la inicializacion del servidor MQTT

  client.setServer ( MQTT_SERVER, MQTT_PORT );        //Instrucción para conectarse al servidor
  
}

void MQTT :: publish_MQTT ( void ) {                  //Método que publicara la informacion recabada de los sensores

  Serial.println ( "Publicando información" );
  client.publish( TOPIC,  MSD.JSON_STRING.c_str() );  //Se publica la información a traves de un JSON  
}

void MQTT :: reconnect_MQTT ( void ) {                //Método que reconecta la placa al servidor de Mosquito

  if ( ! client.connected ( ) ) {                       //Se ejecuta la instrcción cuando todavia no se conecta al cliente

    while ( ! client.connected ( ) ) {
      
    Serial.println ( "Conectado nuevamente al servidor" );

    if ( client.connect ( "6C/E1" ) ) {                 //Informa que se a conectado al servidor
      
      Serial.println ( "Cliente conectado" );

      client.subscribe("Equipo 1");                     //Intrucción para suscribirse al topic

      
    } else {                                            //Informa si no a podido conectarse al servidor deseado
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  }
  client.loop();
  
}

void MQTT :: setup_WiFi ( void ) {                //Método que configura la conexión a la red WiFi

  delay ( 10 );
  Serial.println ( "Configurando WiFi: " );
  WiFi.begin ( HOTSPOT_WIFI, HOTSPOT_PWD );       //Inicializa la conexión con el HOTSPOT
  
  
  while ( WiFi.status ( ) != WL_CONNECTED ) {     //Instrucción para dar informacion
                                                  // de que se esta estableciondo la conexión 
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println ( "WiFi configurado con la IP: " );
}
