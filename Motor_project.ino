const int motorPin = 25;
volatile unsigned long pulseCount = 0;

bool started= false;

int pwm=38;
int targetRPM=1500;
float kp=.01;

void IRAM_ATTR pulseISR() {
  pulseCount++;
}

void setup() {
  ledcAttach(motorPin, 5000, 8);

  Serial.begin(115200);

  pinMode(27, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(27),
    pulseISR,
    FALLING);
}

void loop() {
  if (!started)
  {
    analogWrite(motorPin,30);
    if (pulseCount>0);
{
  started=true;
}
return;
  }

  pulseCount = 0;
  delay(100);
  float rpm = pulseCount * 600.0;

  float error= targetRPM-rpm;
  float change = kp*error;
  change=constrain(change,-3,3);
  pwm+= change;
  pwm= constrain(pwm,0,180);

  analogWrite(motorPin, pwm);
  Serial.print("RPM: ");
  Serial.println(rpm);

  /*analogWrite(motorPin, 20);
  delay(5000);

  pulseCount = 0;
  delay(1000);
  rpm = pulseCount * 60;
  Serial.println(rpm);

  /*  analogWrite(motorPin, 120);  
  delay(2000);

    pulseCount=0;
    delay(1000);
    rpm=pulseCount*60;
    Serial.println(rpm);

  analogWrite(motorPin, 200);  
  delay(2000);

    pulseCount=0;
    delay(1000);
    rpm=pulseCount*60;
    Serial.println(rpm);
*/
}
