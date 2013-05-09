#include <SoftwareSerial.h>

//Asignación de los pines para comunicación con el módulo wifi (2=RX y 3=TX)
SoftwareSerial bluetooth(2, 3);

int led = 13; //Led del Arduino

int val; //Valor leido del softserial del módulo bluetooth

//Estados de las órdenes recibidas:
int LS = LOW; //Led status
int RS = LOW; //Auxiliar para el futuro.
int US = LOW; //Auxiliar para el futuro.
int DS = LOW; //Auxiliar para el futuro.

void setup()
{
  
  pinMode(led, OUTPUT); //Configuramos el pin del led como salida.

  //Establecemos una comunicación serie para debugging
  Serial.begin(9600);
  Serial.println("Consola abierta");
  
  //Establecemos la comunicación en serie con el módulo bluetooth
  bluetooth.begin(9600);
  
}

void loop()
{
  if(datosBluetooth()){ //Solo actualizamos el estado si hemos recibido información relevante por bluetooth
    if(LS){
      
      //Qué hace cuando está high
      
    }else{
      
      //Qué hace cuando está low
      
    }
    
    } //Fin de IF de datos bluetooth.

} //Fin de función loop().


//---------- FUNCIONES ----------//

//Función para leer los datos que el módulo reciba
boolean datosBluetooth(){ //Devolvemos un booleano indicando si hemos recibido información relevante
  boolean informacionRelevante = false; //Por defecto indicaremos que no hemos encontrado nada útil
  if (bluetooth.available()) {
    val = bluetooth.read();
    Serial.write(val); //Escribimos lo leído en el serial para debugging
    Serial.println();
    if (val == '#') { //Si detectamos un caracter #, la información relevante viene a continuación
      val = bluetooth.read(); //Leemos la información relevante
      Serial.write(val); //Escribimos lo leído en el serial para debugging
      switch(val){ //Establecemos la actuación en función del carácter recibido
        case 'U': //Flecha de arriba
          US=!US;
        break;
        case 'D': //Flecha de abajo
          DS=!DS;
        break;
        case 'R': //Flecha derecha
          RS=!RS;
        break;
        case 'L': //Flecha izquierda
          LS=!LS;
        break;
         case 'C': //Tecla Control
          CS=!CS;
        break;
      }
      informacionRelevante=true; //Una vez leída la información y actuado en consecuencia, avisamos
    }
  }
  return informacionRelevante;
}

}
