// test code for Grove - Sound Sensor
// loovee @ 2016-8-30
const int pinAdc = A0; //el pin Analogico que recibe la señal del sensor
int count=0;    //inicializamos el contador
int led=8;      //el pin Digital donde esta el LED 
int pit=A5;     //el pin Analogico donde esta la alarma
int but=3;      //el pin Digital donde esta el pitido del RESET
int range=300;  //valor que activa el count
long sum = 0;   //inicializamos una variable de lectura del sensor
int res=5;      //El número de piezas que queremos contar antes de retirarlas

      // En el setup se especifican las condiciones iniciales
void setup(){
    Serial.begin(115200);
    Serial.println("Contador de piezas de Alkorta"); 
    pinMode(led, OUTPUT); 
    pinMode(pit,OUTPUT);
    pinMode(but,INPUT);
    digitalWrite(led,HIGH);
    analogWrite(pit,0);
    
}

    //Este es el código que se va a ejecutar contínuamente
void loop()
{
    sum=analogRead(pinAdc);   //Se lee el valor del sensor y se guarda en sum
    if(sum>range)             //Si sum es mayor que el valor establecido previamente como límite quiere decir que ha caido una pieza
    {
      count+=1;               //El contador de piezas se incrementa en 1
      digitalWrite(led,LOW);  //Se apaga el LED
    Serial.print(count);
    if(count==1)Serial.print(" pieza"); else Serial.print(" piezas"); 
    Serial.println("");
    if (count==res){          //Cuando el contador llega al límite de piezas que queremos salta la alarma que nos avisa que tenemos que retirarlas  
    
      Serial.println("Retirar piezas");
      while(digitalRead(but)==LOW){     //Parte del código que emite un pitido hasta que se pulsa el boton de reset
        analogWrite(pit,255);
        delay(500);        
        analogWrite(pit,0);
        delay(500);
       }
       analogWrite(pit,0);
       count=0;
      
    }
    delay (2500);
    digitalWrite(led,HIGH);     //El LED se vuelve a encender dando la señal de que puede recibir una nueva pieza
     
    }
}
