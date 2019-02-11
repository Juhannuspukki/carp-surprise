
const int number = 6;
int readingsB[number];
int readingsG[number];

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 
}



void x() {

  for (int i = 0; i < number; i++) {
    readingsB[i] = 0;
    readingsG[i] = 0;
  }
  
  int secondB = 0;
  int secondG = 0;
  int totalB = 0;
  int totalG = 0;
  int l = 0;
  int a = 0;
  int oldaverage = 0;
  while ( true ) {
    // read the input on analog pin 0:

    int firstB = analogRead(A0);
    int Blueseed = abs(secondB-firstB);
      
    secondB = firstB;

    
    //Serial.print("FirstB"); Serial.println(firstB);
    //Serial.print("Blueseed"); Serial.println(Blueseed);


    Blueseed = ((Blueseed-2)*12-20);
    readingsB[1] = constrain(Blueseed, 0, 1023);

    for( int i=0; i<number; i++) {
      if(readingsB[i]>l) l=readingsB[i];
    }
      
    
    //int averageB = totalB/number;
    int averageB = l;

    if(averageB < oldaverage-40) averageB=oldaverage-40;

    
    oldaverage = averageB;
    
    //Serial.println(averageB);
    
    int outputValueBlue = map(averageB, 0, 1023, 0, 220);
    //outputValueBlue = 0;
     
    analogWrite(10, outputValueBlue);
    
    l = 0;
    totalB = 0;

    /////////////////////////////////////////
    
    int firstG = analogRead(A5);
    int Greenseed = abs(secondG-firstG);
      
    secondG = firstG;
      
    Greenseed = (Greenseed)*12-20;
    readingsG[1] = constrain(Greenseed, 0, 1024);

    for( int i=0; i<number; i++) {
      if(readingsG[i]>a) a=readingsG[i];
    }
    int averageG = a;
    
    Serial.print("\n");
    Serial.print("B:"); Serial.print(averageB); Serial.print(" G:"); Serial.print(averageG);
    
    int outputValueGreen = map(averageG, 0, 1023, 0, 220);
    
    analogWrite(9, outputValueGreen);

    totalG = 0;
    a = 0;
    
    delay(2);
    
    for (int i = (number-1); i > 1; i--) {
      readingsB[i] = readingsB[i-1];
      totalB = totalB + readingsB[i];
      
      readingsG[i] = readingsG[i-1];
      totalG = totalG + readingsG[i];
    }

    
  }    
}

void loop() {
  x();
}
