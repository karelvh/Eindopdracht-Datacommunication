int rechterMotorPin1 = 5;
int rechterMotorPin2 = 6;
int linkerMotorPin1 = 10;
int linkerMotorPin2 = 11;
int led = 13;
int snelheidLinks;
int snelheidRechts;
int sensorLinks = 3;
int sensorMidden = 4;
int sensorRechts = 7;
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
    Serial.println(digitalRead(sensorLinks));
    sensorWaardeMidden = digitalRead(sensorMidden);
    Serial.println(digitalRead(sensorMidden));
    sensorWaardeRechts = digitalRead(sensorRechts);
    Serial.println(digitalRead(sensorRechts));
    //De sensorwaarden werden binnengelezen via de seriële monitor, om zo te kijken of de sensoren op een correcte afstand boven de grond hingen.
    Serial.print("sensor links = " );
    Serial.println(sensorWaardeLinks);
    Serial.print("\t sensor midden = ");
    Serial.println(sensorWaardeMidden);
    Serial.print("\t sensor rechts = ");
    Serial.println(sensorWaardeRechts);
    delay(100);
    
    
    if(sensorWaardeMidden==1)
    {
      linkerMotor(standL);
      rechterMotor(standR);
    }
    //Hier zien de middelste sensor en de sensor links ervan de zwarte lijn. Bijgevolg moet de rechtermotor sneller draaien, om terug op de lijn te komen.
    else if((sensorWaardeMidden==1)&&(sensorWaardeLinks==1))
    {
      rechterMotor(standR+10);
      linkerMotor(standL-10);
    }
    //Hier zien de middelste sensor en de sensor rechts ervan de zwarte lijn. Bijgevolg moet de linkermotor sneller draaien, om terug op de lijn te komen.
    else if((sensorWaardeMidden==1)&&(sensorWaardeRechts==1))
    {
      rechterMotor(standR-10);
      linkerMotor(standL+10);
    }
     //Hier ziet de sensor links van de middelste senor de zwarte lijn. Bijgevolg moet de rechtermotor sneller draaien, om terug op de lijn te komen.
    else if(sensorWaardeLinks==1)
    {
      linkerMotor(standL-30);
      rechterMotor(standR+30);
    }
    //Hier ziet de sensor rechts van de middelste senor de zwarte lijn. Bijgevolg moet de linkermotor sneller draaien, om terug op de lijn te komen.
    else if(sensorWaardeRechts==1)
    {
      linkerMotor(standL+30);
      rechterMotor(standR-30);
    }
//    motorAandrijven();
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
