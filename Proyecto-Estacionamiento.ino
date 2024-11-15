#include <Servo.h>                                          //Agregamos la biblioteca del servomotor

Servo servo1;
 
const int PINSERVO = 4;                                     //Definimos el servomotor en el pin 4
const int PULSOMIN = 1000;                                  //Establecemos el rango minimo y maximo del giro del servomotor
const int PULSOMAX = 2000;
const int Tiempodelpulso = 100;                             //Definimos el tiempo que habra entre cada pulso
const int TiempoLED = 100;                                  //Definimos el tiempo de retraso en los LEDS
const int Tiempodelsonido = 59;                             //Definimos el tiempo que tarda el sonido en recorrer un cm
const int Trigger = 2;                                      //Definimos en el pin 2 la señal que envía el sensor 
const int Echo = 3;                                         //Definimos en el pin 3 la señal que recibe el sensor
const int LED1 = 12;                                        //Definimos un pin para cada LED(VERDE, AMARILLO, ROJO)
const int LED2 = 11;
const int LED3 = 10;
const int Distanciamin = 0;                                 //Definimos las distancias de los intervalos
const int Distanciafrontera1 = 18;
const int Distanciafrontera2 = 40;
const int Distanciamax = 60;
const int PosicionDeApertura = 0;                           //Definimos las posiciones de la barrera
const int PosicionDeCierre = 180;
const int VelocidadDeLaSenal = 9600;                        //Definimos la velocidad de la señal de comunicación
long t;                                                     //Definen una variable de tiempo t y otra d
long d; 
void setup() { 
  Serial.begin(VelocidadDeLaSenal);                         //Definimos la velocidad de la señal de comunicación
  pinMode(Trigger, OUTPUT);                                 //Definimos que trigger como pin de salida
  pinMode(Echo, INPUT);                                     //Definimos el echo como pin de entrada
  digitalWrite(Trigger, LOW);                               //Establecemos el estado inicial del trigger en 0
  pinMode(LED1, OUTPUT);                                    //Establecemos los pines de los LEDS como pines de salida
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);              //Define el pin del servo y sus angulos mínimo y máximo respectivamente
}
void loop()
{
  digitalWrite(Trigger, HIGH);                              //Envía el pulso
  delayMicroseconds(Tiempodelpulso);                        //Espera un tiempo
  digitalWrite(Trigger, LOW);                               //Deja de enviar el pulso
  
  t = pulseIn(Echo, HIGH);                                  //Mide el tiempo proporcional a la distancia del objeto 
  d = t/Tiempodelsonido;                                    //Convierte el tiempo recorrido por el pulso en una distancia
  
  Serial.print("Distancia: ");                              //Escribe en el serial monitor "Distancia"
  Serial.print(d);                                          //Escribe el d calculado
  Serial.print("cm");                                       //Escribe "cm"
  Serial.println();                                         //Hace que los datos anteriores se envien en una sola oración
  delay(Tiempodelpulso);                                    //Espera el tiempo en el que se prende y apaga el pulso para escribir
  if (d< Distanciafrontera1 && d >= Distanciamin) {         //Establece un intervalo de distancia
    digitalWrite(LED1, HIGH);                               //Enciende el LED1
  }
  else{
      digitalWrite(LED1, LOW);                              //Apaga el LED1
  }
  delay(TiempoLED);                                         //Establece un tiempo de espera para la siguiente lectura
  if (d< Distanciafrontera2 && d >= Distanciafrontera1) {   //Establece un intervalo de distancia
    digitalWrite(LED2, HIGH);                               //Enciende el LED2
     servo1.write(PosicionDeApertura);                      //Rota el servomotor 0 grados para abrir la barrera
  }
  else{
      digitalWrite(LED2, LOW);                              //Apaga el LED2
      servo1.write(PosicionDeCierre);                       //Rota el servomotor 180 grados para cerrar la barrera
  }
  delay(TiempoLED);                                         //Establece un tiempo de espera para la siguiente lectura
  if (d<= Distanciamax && d >= Distanciafrontera2) {        //Establece un intervalo de distancia
    digitalWrite(LED3, HIGH);                               //Enciende el LED3
  }
  else{
      digitalWrite(LED3, LOW);                              //Apaga el LED3
  }
  delay(TiempoLED);                                         //Establece un tiempo de espera para la siguiente lectura
  }

