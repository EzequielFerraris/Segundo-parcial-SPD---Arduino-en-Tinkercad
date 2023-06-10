// Alumno: Ferraris Ezequiel Manuel - 1F

#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define ROJO 13
#define AMARILLO 12
#define VERDE 10

String estacion = "Configurar-> 1-4"; //mensaje por defecto
int temperaturaMaxima = 600; //Inicializo en un temp inalcanzable para que no se active
int flag = 1;
bool encendido = false;

//Inicializo los objetos de los dispositivos
LiquidCrystal displayLCD(2, 3, 4, 5, 6, 7); //crea el display
IRrecv controlIR(11); //crea el sensor del IR
Servo sistemaContraIncendio;

//Setup
void setup()
{
  displayLCD.begin(16,2);
  controlIR.enableIRIn();
  sistemaContraIncendio.attach(9);
  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  Serial.begin(9600);
}

//Sistema de alarma (Muestra alerta y mueve Servo)
void alarma()
{
  displayLCD.setCursor(0,1);
  displayLCD.print("PELIGRO-INCENDIO");
  sistemaContraIncendio.write(90);
  delay(1000);
  sistemaContraIncendio.write(180);
  delay(1000);
}

//Prende los leds correspondientes
void prenderLed(int led)
{
  	digitalWrite(ROJO, LOW);
    digitalWrite(AMARILLO, LOW);
    digitalWrite(VERDE, LOW);
	if(led == 1)
    {
      	digitalWrite(VERDE, HIGH);
    }
  	else if(led == 2)
    {
      	digitalWrite(AMARILLO, HIGH);
      	digitalWrite(VERDE, HIGH);
    }
  	else if(led == 3)
    {
      	digitalWrite(AMARILLO, HIGH);
      	digitalWrite(VERDE, HIGH);
        digitalWrite(ROJO, HIGH);
    }
}

//Lee la temperatura y la imprime en el display
void evaluarTemperatura() 
{
  	char cadenaTemperatura[16];
    int lectura, mostrar;
  
  	lectura = analogRead(A0);
  	mostrar = map(lectura, 20, 358, -40, 125); 
  	sprintf(cadenaTemperatura, "Temperatura: %d  ", mostrar);
	displayLCD.setCursor(0,0);
  	displayLCD.print(cadenaTemperatura);
  	//Si la temperatura supera en 10 grados el maximo inicia el sistema
  	if(mostrar > temperaturaMaxima + 10 && mostrar < temperaturaMaxima + 20) 
    {
      	prenderLed(2);
    }
  	else if(mostrar > temperaturaMaxima + 19)
    {
    	prenderLed(3);
    	alarma();
    }
  	else //Si la temperatura volvió a niveles normales
    {
      prenderLed(1);
      displayLCD.setCursor(0,1);
      displayLCD.print(estacion);
    }
}

//Chequea si un boton entre 1 y 4 es presionado en el control
//En base a ello imprime la estación en el display y fija la temperatura máxima
void mostrarEstacion()
{
  	long botonApretado;
  
	if(controlIR.decode())
  	{
      //devuelve un valor distinto según el botón presionado
      botonApretado = controlIR.decodedIRData.decodedRawData; 
      botonApretado = botonApretado * -1; //pasa de neg a positivo
	  //Serial.println(botonApretado);
      switch(botonApretado)
      {
          case 284115200:
              estacion = "PRIMAVERA       ";
              temperaturaMaxima = 25;
          break;
          case 300826880:
              estacion = "VERANO          ";
              temperaturaMaxima = 32;
          break;
          case 317538560:
              estacion = "OTONO           ";
              temperaturaMaxima = 24;
          break;
          case 350961920:
              estacion = "INVIERNO        ";
              temperaturaMaxima = 17;
          break;
          default:
          break;
      }
      
      displayLCD.setCursor(0,1);
      displayLCD.print(estacion);
      controlIR.resume();
  	}
  	else if(flag == 1) //Establece el mensaje por defecto al iniciar el sistema
    {
      displayLCD.setCursor(0,1);
      displayLCD.print(estacion);
      controlIR.resume();
  	  flag += 1;
    }
}

//Enciende y apaga el dispositivo
bool encendidoApagado()
{
  long botonInicio;
  if(controlIR.decode())
  {
    botonInicio = controlIR.decodedIRData.decodedRawData;
    botonInicio = botonInicio * -1;
    if(botonInicio == 16728320)
    {
      encendido = !encendido;
      controlIR.resume();
    }
  }
}

//Loop principal 16728320 
void loop()
{
  if(encendido)
  {
    mostrarEstacion();
   	evaluarTemperatura();
  }
  else
  {
    displayLCD.clear(); //Apaga la pantalla
    prenderLed(4); //Apaga los leds
    flag = 1; //Reestablece a modo configurar
    estacion = "Configurar-> 1-4";
    temperaturaMaxima = 600; 
  }
  encendidoApagado();
}