# Segundo parcial Sistema de Procesamiento de Datos - UTN 
## Tecnicatura Universitaria en Programación

## Autor: [Ferraris Ezequiel Manuel](https://github.com/EzequielFerraris)
# Prototipo detector de incencios - Arduino 1 en Tinkercad

![Proyecto](https://github.com/EzequielFerraris/Segundo-parcial-SPD---Arduino-en-Tinkercad/blob/main/Imagenes/proyecto.png)
### [Link al proyecto en Tinkercad](https://www.tinkercad.com/things/ciP7IaodqdI)

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

a. ```mostrarEstacion()```: Como su nombre lo indica, evalúa si se presiona alguno de los botones numéricos del remoto del 1 al 4. En base a ello fija la estación y la temperatura máxima en cada caso:
     1. PRIMAVERA. Temperatura máxima: 25.
     2. VERANO. Temperatura máxima: 32.
     3. OTOÑO. Temperatura máxima: 24.
     4. INVIERNO. Temperatura máxima: 17.
Luego escribe el mensaje correspondiente en el display LCD.
  
b. ```evaluarTemperatura()```: Detecta la temperatura a través del sensor TMP36. Mapea la señal recibida a una temperatura entre -40 y 125 grados centigrados y la imprime en el renglón superior del display LCD. Luego evalúa si la temperatura es menor al máximo de la estación seleccionada. Si es menor, prende el led verde llamando a la función ```prenderLed()```. Si la temperatura es superior en 10 grados, prende el led amarillo llamando a ```prenderLed()```. Si la temperatura es mayor en 20 grados al máximo, prende el led rojo con ```prenderLed()``` y llama a la función ```alarma()```.
 
c. ```prenderLed(int)```: Esta función recibe como parámetro un entero. Lo primero que hace es apagar todos los leds. Luego, si el número es 1, prende el led verde. Si es 2 prende el amarillo. Si es 3, prende el led rojo. Cualquier otro parámetro solo apaga los leds.

d. ```alarma()```: Lo primero que hace esta función es mostrar en la pantalla del display el mensaje "PELIGRO-INCENDIO". Luego activa el Servomotor para que realice dos movimientos, con un intervalo de 1 segundo entre ambos y 1 segundo de delay luego del segundo.

e. ```encendidoApagado()```: esta función cambia el valor de la variable ```encendido``` si se ha presionado el botón PWR en el control remoto. Esto permite prender o apagar el dispositivo en el loop principal del programa.

f. Finalmente, el loop principal del programa evalúa si el sistema está encendido o apagado en función a la variable booleana ```encendido``` (false por defecto). Si está encendido, llama a las funciones ```mostrarEstacion()``` y ```evaluarTemperatura()```. En caso contrario limpia el display LCD y reincia las variables iniciales.
