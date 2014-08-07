// encoder pin names
const int alpha =          7;
const int alphaNot =       6;
const int beta =           5;
const int betaNot =        4;
const int index =          3;
const int indexNot =       2;
const int encCntrlPin =    A0;

// encoder variables
int encCnt =               0;
int encDir =               0;
int encRes =               256;
int encSpd =               127;
int greyCnt =              0;

// setup
void setup() {
  pinMode(alpha, OUTPUT);
  pinMode(alphaNot, OUTPUT);
  pinMode(beta, OUTPUT);
  pinMode(betaNot, OUTPUT);
  pinMode(index, OUTPUT);
  pinMode(indexNot, OUTPUT);
}

// program starts
void loop() {
  // read the control pin
  int encCntrlVal = analogRead(encCntrlPin);
  int range = map(encCntrlVal, 0, 1024, 0, 2);
  
  // decide what to do
  if (range == 0) {
    greyCnt--;
    if (greyCnt < 0) {
      greyCnt = 3;
    }
    encCnt--;
    if (encCnt < 0) {
      encCnt = encRes;
    }
    encDir = -1;
  }
  else if (range == 2) {
    greyCnt++;
    if (greyCnt > 3) {
      greyCnt = 0;
    }
    encCnt++;
    if (encCnt > encRes) {
      encCnt = 0;
    }
    encDir = 1;
  }
  else {
    encDir = 0;
    return;
  }
  delay(512 - encSpd);
  encOutput();
}

void encOutput() {
  indexOut();
  alphaOut();
  betaOut();
} 

void indexOut() {
  if (encCnt == encRes) {
    digitalWrite(index, HIGH);
    digitalWrite(indexNot, LOW);
  }
  else {
    digitalWrite(index, LOW);
    digitalWrite(indexNot, HIGH);
  }
}

void alphaOut() {
  if (greyCnt == 0) {
    digitalWrite(alpha, LOW);
    digitalWrite(alphaNot, HIGH);
  }
  else if (greyCnt < 3) {
    digitalWrite(alpha, HIGH);
    digitalWrite(alphaNot, LOW);
  }
  else {
    digitalWrite(alpha, LOW);
    digitalWrite(alphaNot, HIGH);
  }
}

void betaOut() {
  if (greyCnt == 0) {
    digitalWrite(beta, LOW);
    digitalWrite(betaNot, HIGH);
  }
  else if (greyCnt > 1) {
    digitalWrite(beta, HIGH);
    digitalWrite(betaNot, LOW);
  }
  else {
    digitalWrite(beta, LOW);
    digitalWrite(betaNot, HIGH);
  }
}
