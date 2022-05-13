const int latchPin = 5;
const int clockPin = 4;
const int dataPin = 6;
const int resetPin = 2;

const int xAxis = 0;
const int yAxis = 1;
const int SW_pin = 8;

int playerX = 3;
int playerY = 3;
int note = 0;

int chargeTime = 2000;
int chance = 2000;
unsigned long startGameTime = millis();
unsigned long currentTime1;

unsigned long startTimer = millis();
boolean Wait = false;

boolean dead = false;
boolean clickedUp = false;
boolean clickedDown = false;
boolean clickedLeft = false;
boolean clickedRight = false;
boolean off = false;

int rando[14] = {
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

boolean shoot [14] = {
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
};

unsigned long currentTime [14] = {
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

unsigned long startTime [14] = {
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

boolean activeY[7] = {
  false, false, false, false,
  false, false, false
};

boolean activeX[7] = {
  false, false, false, false,
  false, false, false
};

word Red15;

word Example[14] = {
  0B1111111111111111,
  0B1100111111111111,
  0B1111001111111111,
  0B1111110011111111,
  0B1111111100111111,
  0B1111111111001111,
  0B1111111111110011,
  0B1100111111111111,
  0B1111001111111111,
  0B1111110011111111,
  0B1111111100111111,
  0B1111111111001111,
  0B1111111111110011,
  0B1111111111111100,
};

word Dead[16] = {
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1001100011011001,
  0B1010101110101010,
  0B1010100010001010,
  0B1010101110101010,
  0B1001100010101001,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111
};

word Red[16] = {
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111
};

word Green[16] = {
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111110011111111,
  0B1111110011111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111,
  0B1111111111111111
};
word Blue[16] = {
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B0011111111111111,
  0B1100000000000000,
  0B1100000000000000
};

word Rows[16] = {
  0B1000000000000000,
  0B0100000000000000,
  0B0010000000000000,
  0B0001000000000000,
  0B0000100000000000,
  0B0000010000000000,
  0B0000001000000000,
  0B0000000100000000,
  0B0000000010000000,
  0B0000000001000000,
  0B0000000000100000,
  0B0000000000010000,
  0B0000000000001000,
  0B0000000000000100,
  0B0000000000000010,
  0B0000000000000001
};

word Sound[9] = {
  0B00000000,
  0B10000000,
  0B01000000,
  0B00100000,
  0B00010000,
  0B00001000,
  0B00000100,
  0B00000010,
  0B00000001
};


void setup() {
  Serial.begin(9600);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  randomSeed(138);

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  Serial.println(note);
  playerMove();
  checkIfDead();
  if (!dead) {
    for (int i = 0; i < 14; i++) {
      laser(i);
    }
  }
  for (int collum = 0; collum < 16; collum++) {
    if (dead) {
      deadSound();
      displayX(collum);
    } else {
      displayLaser(collum);
      delay(0.0001);
    }
  }
}
void displayLaser(int c) {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, Sound[note]); //Lyd
  shiftOut(dataPin, clockPin, LSBFIRST, Red[c]); //Rød Top plade
  shiftOut(dataPin, clockPin, LSBFIRST, Green[c]); //Grøn Top plade
  shiftOut(dataPin, clockPin, LSBFIRST, Blue[c]); //Blå Top plade
  shiftOut(dataPin, clockPin, LSBFIRST, Rows[c]); //Række vælger Venstre plade

  shiftOut(dataPin, clockPin, LSBFIRST, Red[c] >> 8); //Rød Bund plade
  shiftOut(dataPin, clockPin, LSBFIRST, Green[c] >> 8); //Grøn Bund plade
  shiftOut(dataPin, clockPin, LSBFIRST, Blue[c] >> 8); //Blå Bund plade
  shiftOut(dataPin, clockPin, LSBFIRST, Rows[c] >> 8); //Række vælger Højre plade

  digitalWrite(latchPin, HIGH);
}

void displayX(int c) {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, Sound[note]); //Lyd
  shiftOut(dataPin, clockPin, LSBFIRST, Dead[c]); //Rød Top plade
  shiftOut(dataPin, clockPin, LSBFIRST, 0B1111111111111111); //Grøn Top plade
  shiftOut(dataPin, clockPin, LSBFIRST, 0B1111111111111111); //Blå Top plade
  shiftOut(dataPin, clockPin, LSBFIRST, Rows[c]); //Række vælger Venstre plade

  shiftOut(dataPin, clockPin, LSBFIRST, Dead[c] >> 8); //Rød Bund plade
  shiftOut(dataPin, clockPin, LSBFIRST, 0B1111111111111111); //Grøn Bund plade
  shiftOut(dataPin, clockPin, LSBFIRST, 0B1111111111111111); //Blå Bund plade
  shiftOut(dataPin, clockPin, LSBFIRST, Rows[c] >> 8); //Række vælger Højre plade

  digitalWrite(latchPin, HIGH);

}

void deadSound() {
 note = 0;
}

boolean wait(int waitTime) {
  if (Wait == false) {
    startTimer = millis();
  }
  unsigned long currentTime = millis() - startTimer;
  if (currentTime >= waitTime) {
    Wait = false;
    return true;
  } else {
    Wait = true;
    return false;
  }
}
