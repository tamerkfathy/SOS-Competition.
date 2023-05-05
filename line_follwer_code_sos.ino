//al code kolo bta3 al automatic
#include <EEPROM.h>
#define LM1 6       // left motor
#define LM2 5       // left motor
#define RM1 10       // right motor
#define RM2 9       // right motor
int  movingsensor ;
#define button 8

int a ;
int sr ;
int LLS, LS, CS , RS , RRS;

int bLL , bL , bC , bR , bRR;

int wLL, wL , wC , wR , wRR;

int lls , ls , cs , rs , rrs;

void LFcomaprator()
{
  Serial.print("start");
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
  delay(5000);
  bLL = analogRead(A5);
  bL  = analogRead(A4);
  bC  = analogRead(A3);
  bR  = analogRead(A2);
  bRR = analogRead(A1);
  ba = analogRead(A0);
  Serial.print("Black");
  digitalWrite(13, 1);
  delay(5000);

  wLL = analogRead(A5);
  wL  = analogRead(A4);
  wC  = analogRead(A3);
  wR  = analogRead(A2);
  wRR = analogRead(A1);
  wa = analogRead(A0);
  digitalWrite(13, 0);
  Serial.print("White");
  lls = (wLL + bLL) / 2 ;
  ls  = (wL + bL)   / 2;
  cs  = (wC + bC)   / 2;
  rs  = (wR + bR)   / 2;
  rrs = (wRR + bRR) / 2;
  a = (wa + ba) / 2;
  EEPROM.write(0, lls / 4);
  EEPROM.write(1, ls / 4);
  EEPROM.write(2, cs / 4);
  EEPROM.write(3, rs / 4);
  EEPROM.write(4, rrs / 4);
  EEPROM.write(5, a / 4);
}
void eprom ();
{
  lls = EEPROM.read(0) * 4;
  ls = EEPROM.read(1) * 4;
  cs = EEPROM.read(2) * 4;
  rs = EEPROM.read(3) * 4;
  rrs = EEPROM.read(4) * 4;
  a = EEPROM.read(5) * 4;
}

void goforward(int speed1, int speed2) { // Move Forward

  analogWrite(LM1, speed1);
  digitalWrite(LM2, LOW);
  analogWrite(RM1, speed2);
  digitalWrite(RM2, LOW);

}
void gobackward(int speed1, int speed2) {
  digitalWrite(LM1, LOW);
  analogWrite(LM2, speed1);
  digitalWrite(RM1, LOW);
  analogWrite(RM2, speed2);
}

void turnleft(int speed1, int speed2)    // Turn left
{
  digitalWrite(LM1, LOW);
  analogWrite(LM2, speed1);
  analogWrite(RM1, speed2);
  digitalWrite(RM2, LOW);
}
void turnright(int speed1, int speed2) // turn right
{
  analogWrite(LM1, speed1);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  analogWrite(RM2, speed2);
}
void stopmoving()  // stop
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}
int readingofsensor() { // < see white , > see black
  LLS = analogRead(A5);
  LS = analogRead(A4);
  CS = analogRead(A3);
  RS = analogRead(A2);
  RRS = analogRead(A1);
  if ((LLS < lls) && (LS < ls ) && (CS < cs ) && (RS < rs ) && (RRS < rrs )) // see white line only
    sr = 1;
  else if ((LLS > lls) && (LS > ls ) && (CS < cs ) && (RS > rs ) && (RRS > rrs ))//kda al robot mazbot 3alline
    sr = 2;
  else if ((LLS > lls) && (LS < ls ) && (CS < cs ) && (RS > rs ) && (RRS > rrs ))//shaft ymen 1
    sr = 3;
  else if ((LLS > lls) && (LS > ls ) && (CS < cs ) && (RS < rs ) && (RRS > rrs ))//shaft shmal 1
    sr = 4;
  else if ((LLS > lls) && (LS < ls ) && (CS > cs ) && (RS > rs ) && (RRS > rrs ))//shaft ymen 2
    sr = 5;
  else if ((LLS > lls) && (LS > ls ) && (CS > cs ) && (RS < rs ) && (RRS > rrs ))//shaft shmal 2
    sr = 6;
  else if ((LLS < lls) && (LS < ls ) && (CS > cs ) && (RS > rs ) && (RRS > rrs ))//shaft ymen 3
    sr = 7;
  else if ((LLS > lls) && (LS > ls ) && (CS > cs ) && (RS < rs ) && (RRS < rrs ))//shaft shmal 3
    sr = 8;
  else if ((LLS < lls) && (LS > ls ) && (CS > cs ) && (RS > rs ) && (RRS > rrs ))//shaft ymen 4
    sr = 9;
  else if ((LLS > lls) && (LS > ls ) && (CS > cs ) && (RS > rs ) && (RRS < rrs ))//shaft shmal 4
    sr = 10;
  else if ((LLS > lls) && (LS > ls ) && (CS > cs ) && (RS > rs ) && (RRS > rrs )) //can't see white line follower
    sr = 11;
  else if ((LLS < lls) && (LS < ls ) && (CS < cs ) && (RS > rs ) && (RRS > rrs )) //must turn left
    sr = 12;
  else if ((LLS < lls) && (LS < ls ) && (CS < cs ) && (RS < rs ) && (RRS > rrs )) // must turn left
    sr = 13;
  else if ((LLS > lls) && (LS > ls ) && (CS < cs ) && (RS < rs ) && (RRS < rrs )) // must turn right
    sr = 14;
  else if ((LLS > lls) && (LS < ls ) && (CS < cs ) && (RS < rs ) && (RRS < rrs )) // must turn right
    sr = 15;
  return (sr);
}
void followlinefollower(int maxspd) {
  readingofsensor();
  if (sr == 2)
    goforward(maxspd, maxspd);
  else if (sr == 3)
    goforward(maxspd - (maxspd / 8), maxspd);
  else if (sr == 4)
    goforward(maxspd, maxspd - (maxspd / 8));
  else if (sr == 5)
    goforward(maxspd - (maxspd / 6), maxspd);
  else if (sr == 6)
    goforward(maxspd, maxspd - (maxspd / 6));
  else if (sr == 7)
    goforward(maxspd - (maxspd / 3), maxspd);
  else if (sr == 8 )
    goforward(maxspd, maxspd - (maxspd / 3));
  else if (sr == 9)
    goforward(maxspd - maxspd, maxspd);
  else if (sr == 10)
    goforward(maxspd, maxspd - maxspd);

}

void setup() {
  Serial.begin(9600);
  if ( digitalWrite(button) == HIGH) {
    LFcomaprator();
  }
  else {
    eprom();
  }

  readingofsensor();
  Serial.println(LLS);
  Serial.println(LS);
  Serial.println(CS);
  Serial.println(RS);
  Serial.println(RRS);
  movingsensor = analogRead(A0);
  while (movingsensor < a) {}
  delay(3000);
  digitalWrite(13, 1);
  readingofsensor();
  while (sr != 1) {
    readingofsensor();
    followlinefollower(180);
  }
  while (sr == 1) {
    readingofsensor();
    goforward(180, 180);
  }
  delay(100);
  while (sr == 11) {
    readingofsensor();
    goforward(200, 150);
  }
  while (sr != 1) {

    followlinefollower(180);
    readingofsensor();
    if ((sr == 12) || (sr == 13))
      turnleft(170, 170);
  }
  readingofsensor();
  if (sr == 1) {
    stopmoving();
  }
  movingsensor = analogRead(A0);

  while (movingsensor > a)
  {}
  delay(3000);
  readingofsensor();
  while (sr != 1) {
    readingofsensor();
    gobackward(100, 100);

  }
  stopmoving();
  while (sr != 11) {
    turnleft(150, 150);
    readingofsensor();
  } while (sr == 11) {
    turnleft(150, 150);
    readingofsensor();
  }
  readingofsensor();
  while (sr != 1)//aslha 1 bs 5ltha 11 3shan al tagroba
  { followlinefollower(180);
    readingofsensor();
    if ((sr == 14) || (sr == 15))
      turnright(150, 150);
  }
  while (sr != 11);
  { goforward(150, 150);
    readingofsensor();
  }
  readingofsensor();
  while (sr == 11);
  { turnright(150, 150);
    readingofsensor();
  }
  readingofsensor();
  while (sr != 1) {
    followlinefollower(180);
    readingofsensor();
    if ((sr == 14) || (sr == 15))
    { turnright(150, 150);

    } readingofsensor();
    if ((sr == 12) || (sr == 13))
    { turnleft(150, 150);

    }
  }
  readingofsensor();
  if (sr == 1)
    stopmoving();
  movingsensor = analogRead(A0);
  while (movingsensor < a)
  {}
  delay(2000);
  readingofsensor();
  while (sr != 1) {
    gobackward(100, 100);

    readingofsensor();
  }
  stopmoving();
  while (sr != 11) {
    turnleft(150, 150);
    readingofsensor();
  } while (sr == 11) {
    turnleft(150, 150);
    readingofsensor();
  }

  readingofsensor();
  while (sr != 1) {
    followlinefollower(180);
    readingofsensor();
  }
  readingofsensor();
  while (sr == 1)
  { turnright(150, 150);
    readingofsensor();
  }
  readingofsensor();
  while ((sr != 12) || (sr != 13)) {
    followlinefollower(150);
    readingofsensor();
  }
  readingofsensor();
  if (( sr == 12) || (sr == 13))
  { turnleft(150, 150);
    delay(100);
  }
  readingofsensor();
  while (sr != 1) {
    followlinefollower(150);
    readingofsensor();

    if (( sr == 12) || (sr == 13)) {
      goforward(150, 150);
    }
    readingofsensor();
  }
  while (sr == 1) {
    turnright(150, 150);
    readingofsensor();
  }

  readingofsensor();
  while (sr != 1) {
    followlinefollower(150);
    readingofsensor();
  }
  if (sr == 1)
    stopmoving();
}



void loop() {}
