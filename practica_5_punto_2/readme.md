# Práctica 5:

**

## Consigna:

Por UART recibe los siguientes comandos (case-insensitive) y responde según corresponda:
HELP → imprime lista de comandos disponibles.
LED ON / LED OFF / LED TOGGLE → enciende, apaga o conmuta el LED (usar la función que ya tengan del práctico anterior).
STATUS → imprime “LED is ON/OFF”.

El protocolo tiene las siguientes reglas:
La línea termina con \r\n, \n o \r.
Múltiples espacios o tabs se ignoran.
Las respuestas siempre terminan con \r\n.
Mensajes de error claros: 	
ERROR: line too long\r\n
ERROR: unknown command\r\n
ERROR: bad arguments\r\n

**