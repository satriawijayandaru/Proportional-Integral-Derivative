 int CLK = 9;  // Pin 9 to clk on encoder
 int DT = 8;  // Pin 8 to DT on encoder
 int led = 13;
 int RotPosition = 0; 
 int rotation;  
 int value;
 boolean LeftRight;

 int CLK2 = 10;  // Pin 9 to clk on encoder
 int DT2 = 11;  // Pin 8 to DT on encoder
 int RotPosition2; 
 int rotation2;  
 int value2;
 boolean LeftRight2;

 double milis0;
 double milis1;
 double enc0;   //encoder sample 0
 double enc1;   //encoder sample 1
 

 #include <Servo.h> 
 
Servo myservo;
int pos;
 
void setup() {
  Serial.begin (9600);
  Serial.println("Rotary Encoder Startup");
  pinMode (CLK,INPUT);
  pinMode (DT,INPUT);
  
  pinMode (CLK2,INPUT);
  pinMode (DT2,INPUT);
  
  pinMode(led, OUTPUT);
  rotation = digitalRead(CLK); 
  rotation2 = digitalRead(CLK2); 
  myservo.attach(7);
  myservo.write(RotPosition);
  delay(1000);
  Serial.println("READY");
}

void loop() {
  rotary1();

  rotationspeed();
//  rpmspeed();
}

void rotary1(){
     value = digitalRead(CLK);
     if (value != rotation){ // we use the DT pin to find out which way we turning.
       if (digitalRead(DT) != value) {  // Clockwise
         RotPosition --;
         LeftRight = true;
       }else { //Counterclockwise
         LeftRight = false;
         RotPosition++;
       }
       
//       if (LeftRight){ 
//         Serial.println ("clockwise");
//       }else{        
//         Serial.println("counterclockwise");
//       }

       
//       Serial.print("Encoder : ");
//       Serial.println(RotPosition);
//       Serial.print("Degree  : ");
//       double degree;
//       degree = RotPosition/3.3333333;
//       Serial.println(degree);
    rpmspeed();
       

       
//       myservo.write(RotPosition*12);
//       Serial.print("Encoder 2: ");
//       Serial.println(RotPosition2);
   } 
   rotation = value;
}

void rpmspeed(){
  int division;
  division = RotPosition;
  Serial.println(RotPosition%2);
}

void rotationspeed(){
         if (RotPosition < 0){
        RotPosition = 1200;
       }
       if (RotPosition == 1){
        milis0 = millis();
       }
       if (RotPosition > 1200){
        RotPosition = 0;
        milis1 = millis();
        Serial.print("T0 = ");
        Serial.println(milis0);
        Serial.print("T1 = ");
        Serial.println(milis1);
        Serial.print("Time elapsed = ");
        Serial.print((milis1-milis0)/1000);
        Serial.println(" Seconds");

        Serial.print("Speed = ");
        double rpm;
        rpm = (60/((milis1-milis0)/1000));
        Serial.print(rpm);
        Serial.println(" RPM");
       }
       }

void rotary2(){
     value2 = digitalRead(CLK2);
     if (value2 != rotation2){ // we use the DT pin to find out which way we turning.
       if (digitalRead(DT2) != value2) {  // Clockwise
         RotPosition2 ++;
         LeftRight2 = true;
       }else { //Counterclockwise
         LeftRight2 = false;
         RotPosition2 --;
       }
       
   } 
   rotation2 = value2;
}
