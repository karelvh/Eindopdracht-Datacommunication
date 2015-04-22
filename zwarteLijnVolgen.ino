int rechterMotorPin1 = 5;
int rechterMotorPin2 = 6;
int linkerMotorPin1 = 10;
int linkerMotorPin2 = 11;
int led = 13;
int snelheidLinks;
int snelheidRechts;
int sensorLinks = 7;
int sensorMidden = 4;
int sensorRechts = 3;
//waarde van de lichtsensor
int sensorWaardeLinks;
int sensorWaardeMidden;
int sensorWaardeRechts;

//const int standR=125;
//const int standL=100;
const int standR=95;
const int standL=70;

void setup() {
  pinMode(5,OUTPUT); //Linkermotor pin 1
  pinMode(6,OUTPUT); //Linkermotor pin 2
  pinMode(10,OUTPUT); //Rechtermotor pin 1
  pinMode(11,OUTPUT); //Rechtermotor pin 2
  pinMode(13,OUTPUT); //Led
  pinMode (A1,OUTPUT); //ultrasone (echo)
  Serial.begin(9600); 
  //We laten de led 1 seconden flikkeren, om het begin van de baan aan te duiden.
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
  digitalWrite(13,HIGH);
}

void loop() {
//    motorAandrijven();
    sensorWaardeLinks = digitalRead(sensorLinks);
//    Serial.println(digitalRead(sensorLinks));
    sensorWaardeMidden = digitalRead(sensorMidden);
//    Serial.println(digitalRead(sensorMidden));
    sensorWaardeRechts = digitalRead(sensorRechts);
//    Serial.println(digitalRead(sensorRechts));
//    Serial.print("sensor links = " );
//    Serial.println(sensorWaardeLinks);
//    Serial.print("\t sensor midden = ");
//    Serial.println(sensorWaardeMidden);
//    Serial.print("\t sensor rechts = ");
//    Serial.println(sensorWaardeRechts);
    delay(100);
    
    
    if(sensorWaardeMidden==1)
    {
      linkerMotor(standL);
      rechterMotor(standR);
      Serial.print("Sensor midden zwart" );
    }
    //Hier zien de middelste sensor en de sensor links ervan de zwarte lijn. Bijgevolg moet de rechtermotor sneller draaien, om terug op de lijn te komen.
    else if((sensorWaardeMidden==1)&&(sensorWaardeLinks==1))
    {
      rechterMotor(standR+10);
      linkerMotor(standL-10);
        Serial.print("Sensor midden en links zwart" );
    }
    //Hier zien de middelste sensor en de sensor rechts ervan de zwarte lijn. Bijgevolg moet de linkermotor sneller draaien, om terug op de lijn te komen.
    else if((sensorWaardeMidden==1)&&(sensorWaardeRechts==1))
    {
      rechterMotor(standR-10);
      linkerMotor(standL+10);
        Serial.print("Sensor midden en rechts zwart" );
    }
     //Hier ziet de sensor links van de middelste senor de zwarte lijn. Bijgevolg moet de rechtermotor sneller draaien, om terug op de lijn te komen.
    else if(sensorWaardeLinks==1)
    {
      linkerMotor(standL-30);
      rechterMotor(standR+35);
        Serial.print("Sensorlinks zwart" );
    }
    //Hier ziet de sensor rechts van de middelste senor de zwarte lijn. Bijgevolg moet de linkermotor sneller draaien, om terug op de lijn te komen.
    else if(sensorWaardeRechts==1)
    {
      linkerMotor(standL+35);
      rechterMotor(standR-30);
        Serial.print("Sensor rechts zwart" );
    }
    else if((sensorWaardeRechts==0)&&(sensorWaardeMidden==0)&&(sensorWaardeLinks==0))
    {
      ObstakelDetecteren();
      Serial.println("obstakel detecteren");
    }
}

void motorAandrijven(){
    linkerMotor(100);
    rechterMotor(125);
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

void ObstakelDetecteren()
{ 
  digitalWrite(A1, HIGH);
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(8, OUTPUT);// attach pin 3 to Trig
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(5);
  digitalWrite(8, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode (A1, INPUT);//attach pin 4 to Echo
  duration = pulseIn(A1, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
 
//  Serial.print(inches);
//  Serial.print("in, ");
//  Serial.print(cm);
//  Serial.print("cm");
//  Serial.println();
 
  delay(100);
  
  if(cm < 10 )
  {
     Serial.println("de afstand is kleiner dan 10cm");
     Serial.println(cm);
     linkerMotor(standL+45);
     rechterMotor(standR-30);
  }
  else
  {
    linkerMotor(standL);
    rechterMotor(standR);
    Serial.println("rechtdoor");
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

