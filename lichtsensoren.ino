//pinnen van de lichtsensors
int sensor1 = 7;
int sensor2 = 4;
int sensor3 = 3;
//waarde van de lichtsensor
int sensorWaarde1;
int sensorWaarde2;
int sensorWaarde3;

//pinnen van de motors
int rechterMotorPin1 = 5;
int rechterMotorPin2 = 6;
int linkerMotorPin1 = 10;
int linkerMotorPin2 = 11;

int snelheidRechts;
int snelheidLinks;

const int standR=240;
const int standL=240;

//pin van de led
int led = 13;

void setup() {
  //motoren op output zetten
  pinMode(5,OUTPUT); //Rechtermotor pin 1
  pinMode(6,OUTPUT); //Rechtermotor pin 2
  pinMode(10,OUTPUT); //Linkermotor pin 1
  pinMode(11,OUTPUT); //Linkermotor pin 2
  pinMode(13,OUTPUT); //Led
  //begin van de seriele com
  Serial.begin(9600); 
  //als controle eerst de led 3x laten flikkeren
  for(int i = 0; i < 3; i++){
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}

void loop() {
  motorAandrijven();
  // put your main code here, to run repeatedly:
  //Eerst worden de sensoren gemapt. De waarden tussen 0 en 650 werden gemapt tussen 0 en 1, en niet het volledige bereik van 0 tot 1023, omdat we merkten dat de waarden hoger dan 650, nooit bereikt werden.
  sensorWaarde1 = map(analogRead(sensor1), 0, 250, 0, 1);
  sensorWaarde2 = map(analogRead(sensor2), 0, 250, 0, 1);
  sensorWaarde3 = map(analogRead(sensor3), 0, 250, 0, 1);
  //De sensorwaarden werden binnengelezen via de seriële monitor, om zo te kijken of de sensoren op een correcte afstand boven de grond hingen.
  Serial.print("sensor 1 = " );
  Serial.println(sensorWaarde1);
  Serial.print("\t sensor 2 = ");
  Serial.println(sensorWaarde2);
  Serial.print("\t sensor 3 = ");
  Serial.println(sensorWaarde3);
  delay(100);
  
//  if(sensorWaarde2==1){
//    linkerMotor(standL);
//    rechterMotor(standR);
//  }
//  //Hier zien de middelste sensor en de sensor links ervan de zwarte lijn. Bijgevolg moet de rechtermotor sneller draaien, om terug op de lijn te komen.
//  else if((sensorWaarde2==1)&&(sensorWaarde1==1)){
//    rechterMotor(standR+10);
//    linkerMotor(standL-10);
//  }
//  //Hier zien de middelste sensor en de sensor rechts ervan de zwarte lijn. Bijgevolg moet de linkermotor sneller draaien, om terug op de lijn te komen.
//  else if((sensorWaarde2==1)&&(sensorWaarde3==1)){
//    rechterMotor(standR-10);
//    linkerMotor(standL+10);
//  }
//   //Hier ziet de sensor links van de middelste senor de zwarte lijn. Bijgevolg moet de rechtermotor sneller draaien, om terug op de lijn te komen.
//  else if(sensorWaarde1==1){
//    linkerMotor(standL-30);
//    rechterMotor(standR+30);
//  }
//  //Hier ziet de sensor rechts van de middelste senor de zwarte lijn. Bijgevolg moet de linkermotor sneller draaien, om terug op de lijn te komen.
//  else if(sensorWaarde3==1){
//    linkerMotor(standL+30);
//    rechterMotor(standR-30);
//  }
  
}

void motorAandrijven(){
    linkerMotor(255);
    rechterMotor(255);
}

void linkerMotor(int snelheidLinks)
{
  digitalWrite(linkerMotorPin2, LOW);
  analogWrite(linkerMotorPin1, snelheidLinks);
}
void rechterMotor(int snelheidRechts)
{
    digitalWrite(rechterMotorPin2, LOW);
    analogWrite(rechterMotorPin1, snelheidRechts);
}
