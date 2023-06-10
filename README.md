# Segundo parcial Sistema de Procesamiento de Datos - UTN 
## Tecnicatura Universitaria en Programación

## Autor: Ferraris Ezequiel Manuel
# Prototipo detector de incencios - Arduino 1 en Tinkercad
### [Link al proyecto en Tinkercad](https://www.tinkercad.com/things/ciP7IaodqdI)


![Proyecto](https://github.com/EzequielFerraris/Segundo-parcial-SPD---Arduino-en-Tinkercad/blob/main/Imagenes/proyecto.png)
## Descripción
Este proyecto fue desarrollado en base a las consignas provistas por la cátedra de SPD de la Tecnicatura Universitaria en Programación, para la promoción del segundo parcial. 

Las mismas establecían que debía desarrollarse un sistema que **simulara un detector de incendios**, con el objetivo de aplicar los conceptos vistos durante el desarrollo del cuatrimestre. En este sentido, el mismo utiliza para su funcionamiento los conceptos de salidas digitales, entradas analógicas, salidas analógicas, circuitos electrónicos y manejo básico del lenguaje C++.

## Funcionalidad
Al correr el programa, el detector funciona de la siguiente manera:
1. El display LCD comienza APAGADO, es decir, no muestra ninguna información en pantalla. Con el botón de PWR en el control infrarrojo puede cambiarse el estado entre APAGADO y PRENDIDO.
2. Una vez encendido, el display LCD mostrará la temperatura ambiente medida por el sensor de temperatura en el renglón superior del display, y el mensaje "CONFIG.-> 1-4" en el inferior, señalando que con los botones 1 a 4 puede configurarse la estación del año en la que se encuentra el usuario. La estación del año determina la temperatura máxima a partir de la cual el sistema comenzará a operar. Antes de la selección de una estación, el sistema NO SE ACTIVARÁ al variar la temperatura.
3. Si el usuario modifica la temperatura mediante el sensor, el sistema tiene tres estados posibles:
  * La temperatura es menor a la temperatura de alarma por más de 20 grados celsius: no hay variación en el display. El led verde se encuentra encendido.
  * La temperatura es menor a la temperatura de alarma por menos de 20 grados celsius: no hay variación en el display. El led verde y el amarillo se encuentran prendidos marcando alerta.
  * La temperatura es igual o mayor a la temperatura de alarma: el display muestra el mensaje "ALERTA-INCENDIO" en el segundo renglón. Los tres leds (verde, amarillo y rojo) se encuentran encendidos. El Servomotor es activado para simular una respuestas ante la detección de una temperatura peligrosa. 
4. Si el sistema contra incendios es activado, el funcionamiento del Servo no se verá interrrumpido hasta terminar su acción, por lo que aunque el usuario cambie la temperatura de vuelta a una que no implique alarma, el sistema completará su acción y luego se acomodará al nuevo parámetro.
5. Apagar el sistema implica reiniciar el sistema a su estado inicial, por lo que al prenderlo nuevamente el usuario deberá volver a establecer una estación del año.

## Componentes
* Arduino 1
* Display LCD
* Sensor TMP36
* IR sensor
* IR remote
* Micro Servo
* 3 led lights
* Breadboard Small

## Explicación del código
* El código está escrito en C++ y utiliza las librerías IRremote.h, Servo.h y LiquidCrystal.h. 
* Utiliza 5 funciones para lograr su funcionalidad:
  a.  
