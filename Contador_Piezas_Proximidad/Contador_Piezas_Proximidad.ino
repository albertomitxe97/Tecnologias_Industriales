// test code for Grove - Sound Sensor
// loovee @ 2016-8-30
const int pinAdc = A0;    //el pin Analogico que recibe la señal del sensor
int count=0;              //inicializamos el contador
int led=8;                //el pin Digital donde esta el LED de lectura
int led2=6;               //el pin Digital donde esta el LED que simula la cinta
int pit=A5;               //el pin Analogico donde esta la alarma
int range=300;            //valor que activa el count 
long sum = 0;             //inicializamos una variable de lectura del sensor
int res=5;                //El número de piezas que queremos contar antes de retirarlas
const int trigPin=12;     //Inicializar el emisor del sensor de proximidad
const int echoPin=13;     //Inicializar el receptor del sensor de proximidad
long duration;            //Variable tiempo sensor proximidad
int distance;             //Variable distancia sensor proximidad
int dis=6;

      // En el setup se especifican las condiciones iniciales
void setup(){
    Serial.begin(115200);
    Serial.println("Contador de piezas de Alkorta");
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(pit,OUTPUT);
    digitalWrite(led,HIGH);
    digitalWrite(led2,HIGH);
    analogWrite(pit,0);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
}
      //Este es el código que se va a ejecutar contínuamente
void loop()
{
    sum=analogRead(pinAdc);     //Se lee el valor del sensor y se guarda en sum
    if(sum>range)               //Si sum es mayor que el valor establecido previamente como 
                                //límite quiere decir que ha caido una pieza
    {
      count+=1;                 //El contador de piezas se incrementa en 1
      digitalWrite(led,LOW);    //Se apaga el LED
    Serial.print(count);
    if(count==1)Serial.print(" pieza"); else Serial.print(" piezas");
    Serial.println("");
    
    if (count==5){    //Cuando el contador llega al límite de piezas que queremos salta la alarma 
                      //que nos avisa que tenemos que retirarlas
      
      digitalWrite(led2,LOW);    //Se apaga el LED2
      Serial.println("Retirar piezas");
      distance=calcdist();
      
      while(distance<dis){   //Parte del código que emite un pitido hasta que se quita el recipiente
        analogWrite(pit,150);
        delay(500);        
        analogWrite(pit,0);
        delay(500);
        distance=calcdist();
       }
       analogWrite(pit,0);
       count=0;
       while(distance>dis)
       {
        Serial.println("Esperando recipiente");
        distance=calcdist();
        }
    }
    delay (2500);
    digitalWrite(led,HIGH);     //El LED se vuelve a encender dando la señal de que puede recibir una nueva pieza
    digitalWrite(led2,HIGH);
    }
}
int calcdist()
{
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration=pulseIn(echoPin, HIGH);
      distance=duration*0.034/2;
      return (distance);
}
      
