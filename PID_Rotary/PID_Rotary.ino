 int CLK = 9;  // Pin 9 to clk on encoder
 int DT = 8;  // Pin 8 to DT on encoder
 int led = 13;
 int RotPosition = 0; 
 int rotation;  
 int value;
 boolean LeftRight;
 
void setup() {
  Serial.begin (9600);
  Serial.println("Rotary Encoder Startup");
  pinMode (CLK,INPUT);
  pinMode (DT,INPUT);
  pinMode(led, OUTPUT);
  rotation = digitalRead(CLK); 

}

void loop() {
  rotary();

}

void rotary(){
     value = digitalRead(CLK);
     if (value != rotation){ // we use the DT pin to find out which way we turning.
       if (digitalRead(DT) != value) {  // Clockwise
         RotPosition ++;
         LeftRight = true;
         digitalWrite(led, HIGH);
         delay(1);
         digitalWrite(led, LOW);
       }else { //Counterclockwise
         LeftRight = false;
         RotPosition--;
         digitalWrite(led, HIGH);
         delay(1);
         digitalWrite(led, LOW);
       }
       
       if (LeftRight){ 
         Serial.println ("clockwise");
       }else{        
         Serial.println("counterclockwise");
       }
       Serial.print("Encoder RotPosition: ");
       Serial.println(RotPosition);
   } 
   rotation = value;
}
