//Pins
#define trig 3
#define echo 2
#define rightBk 8
#define rightFw 9
#define leftFw 10
#define leftBk 11

//Objective
#define obj 20

//Constants
float kp = 5, ki = 0, kd = 100;
float kfw = 0.93, kbk = 0.95;
float D = 0, I = 0;

int dist = 0, prevD = 0;
unsigned long int t1, t2;
int duty = 10000;

//Functions
void getDist();
void fwPwm(int pct);
void bkPwm(int pct);
void pwm(int pct);
int prop();

void setup()
{
  pinMode(rightFw, OUTPUT);
  pinMode(rightBk, OUTPUT);
  pinMode(leftFw, OUTPUT);
  pinMode(leftBk, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop()
{
  getDist(); 
  pwm(kp*prop() + kd*D + ki*I);
}

void getDist()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  while(!digitalRead(echo))t1 = micros();
  while(digitalRead(echo)) t2 = micros() - t1;

  prevD = dist;
  dist = ((340 * t2) / (20000)) - obj;

  D = dist - prevD;
  I += dist; 
}

void fwPwm(int pct)
{
  digitalWrite(leftFw, HIGH);
  digitalWrite(rightFw, HIGH);
  delayMicroseconds(kfw*100*pct);
  digitalWrite(rightFw, LOW);
  delayMicroseconds((1-kfw)*100*pct);
  digitalWrite(leftFw, LOW);
  delayMicroseconds(100*(100 - pct));
}

void bkPwm(int pct)
{
  digitalWrite(leftBk, HIGH);
  digitalWrite(rightBk,HIGH);
  delayMicroseconds(kbk*(-100)*pct);
  digitalWrite(rightBk, LOW);
  delayMicroseconds((1 - kbk)*(-100)*pct);
  digitalWrite(leftBk, LOW);
  delayMicroseconds(100*(100 + pct));
}

void pwm(int pct)
{
  if (pct > 100) pct = 100;
  else if (pct < -100) pct = -100;
  
  t1 = micros();
  t2 = micros();

  while(t2 - t1 < duty)
  {
    if (pct >= 0)fwPwm(pct); 
    else if(pct < 0)bkPwm(pct);
    
    t2 = micros();
  }
}

int prop()
{
  int A = (100 * dist) / obj;
  
  if (A >= 100) A = 100;
  else if (A <= -100) A = -100;
  
  return A;
}
