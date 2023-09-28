# Distributed-systems

## Ejercicio2a:

Ejemplo de comunicación en sistemas distribuidos entre **2 máquinas virtuales**, utilizando **Vagrant** para el despliegue y la compilación y ejecución de los ejecutables .c automatizados.

Los ejecutables se ejecutan con distintos tamaños de buffer de comunicación y se guarda la salida en la carpeta compartida "resultados" dentro del archivo cliente.txt.

**Ejecucion:**
        
    vagrant up

## Ejercicio2b:

Ejemplo de comunicacion distribuida entre una **máquina virtual y el host**, utilizando **Vagrant** para el despliegue y la compilación y ejecución de los ejecutables  .c automatizados.

Los ejecutables se ejecutan con distintos tamaños de buffer de comunicación y se guarda la salida en la carpeta compartida "resultados" dentro del archivo cliente.txt.

**Ejecucion:**

    ./initscript.sh 
*(en casos que no tenga permisos de ejecucion chmod +x initscript.sh)*

