int CLK = 9;               // Pin 9 to clk on encoder
int DT = 8;                // Pin 8 to DT on encoder
int led = 13;
int encoderPPR = 1200;     //Encoder Points Per Rotation value
int RotPosition = 0;
int rotation;
int value;
boolean LeftRight;

unsigned long previousMillis = 0;
const long interval = 1000;
double milis0;
double milis1;
double enc0;   //encoder sample 0
double enc1;   //encoder sample 1
int division;
int rpmCountTotal;
int rpmCount0;
int rpmCount1;

void setup() {
  Serial.begin (2000000);
  Serial.println("Rotary Encoder Startup");
  pinMode (CLK, INPUT);
  pinMode (DT, INPUT);
  pinMode(led, OUTPUT);
  rotation = digitalRead(CLK);
}

void loop() {
  rotary1();
  rpmspeedTime();
}

void rotary1() {
  value = digitalRead(CLK);
  if (value != rotation) { // we use the DT pin to find out which way we turning.
    if (digitalRead(DT) != value) {  // Clockwise
      RotPosition --;
      LeftRight = true;
    } else { //Counterclockwise
      LeftRight = false;
      RotPosition++;
    }
  }
  rotation = value;
}

void rpmspeed() {
  division = RotPosition % 2;
  if (division == 0) {
    enc0 = micros();
  }
  if (division == 1) {
    enc1 = micros();
    Serial.print("Degree  : ");
    double degree;
    degree = RotPosition / 3.3333333;
    Serial.println(degree);
    Serial.print("Delta = ");
    Serial.println(enc1 - enc0);
  }
}

void rpmspeedTime() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis == 0) {
    rpmCount0 = RotPosition;
  }
  if (currentMillis - previousMillis >= interval) {
    double rpm;
    rpmCount1 = RotPosition;
    rpmCountTotal = rpmCount1 - rpmCount0;
    rpm = ((rpmCountTotal * 60) / encoderPPR);
    //    rpm = rpmCountTotal / 3;
    Serial.print("Count per sec    = ");
    Serial.println(rpmCountTotal);
    Serial.print("Rotation per min = ");
    Serial.println(rpm);

    Serial.print("Current Millis   = ");
    Serial.println(currentMillis);
    Serial.print("Previous Millis  = ");
    Serial.println(previousMillis);
    Serial.println();
    previousMillis = currentMillis;
  }
}

void rotationspeed() {
  if (RotPosition < 0) {
    RotPosition = 1200;
  }
  if (RotPosition == 1) {
    milis0 = millis();
  }
  if (RotPosition > 1200) {
    RotPosition = 0;
    milis1 = millis();
    Serial.print("T0 = ");
    Serial.println(milis0);
    Serial.print("T1 = ");
    Serial.println(milis1);
    Serial.print("Time elapsed = ");
    Serial.print((milis1 - milis0) / 1000);
    Serial.println(" Seconds");

    Serial.print("Speed = ");
    double rpm;
    rpm = (60 / ((milis1 - milis0) / 1000));
    Serial.print(rpm);
    Serial.println(" RPM");
  }
}
