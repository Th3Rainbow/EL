void updateLaser(int i) {
  if (shoot[i] == false) {
    rando[i] = int(random(0, chance));
    startTime[i] = millis();
  }
  if (rando[i] == 50) {
    shoot[i] = true;
    laserShoot(i);
  }
}

void laserShoot(int i) {
  currentTime[i] = millis() - startTime[i];
  int percentage = (currentTime[i] * 100) / chargeTime;
  if (currentTime[i] >= 0 && currentTime[i] < chargeTime / 2) {
    laserStage1(i);
    note = 1;
  }
  if (currentTime[i] >= chargeTime / 2 && currentTime[i] < chargeTime) {
    laserStage2(i);
    note = 2;
  }
  if (currentTime[i] >= chargeTime) {
    laserStage3(i);
    note = 5;
  }
  if (currentTime[i] >= chargeTime + (chargeTime / 2)) {
    shoot[i] = false;
    note = 0;
    turnOff(i);
  }
}

void laserStage1(int i) {
  if (i < 7) {
    Blue[i * 2] = 0B1011111111111111;
    Blue[i * 2 + 1] = 0B1011111111111111;

    Red[i * 2] = ~(~0B0111111111111111 | ~Red[i * 2]);
    Red[i * 2 + 1] = ~(~0B0111111111111111 | ~Red[i * 2 + 1]);
  }
  else {
    word temp = ~Red[15] | ~Example[i];
    Red[15] =  ~temp;
    Blue[15] = ~Red[15] | 0B1100000000000000;
  }

}

void laserStage2(int i) {
  if (i < 7) {
    Blue[i * 2] = 0B1111111111111111;
    Blue[i * 2 + 1] = 0B1111111111111111;

    Red[i * 2] = ~(~0B0011111111111111 | ~Red[i * 2]);
    Red[i * 2 + 1] = ~(~0B0011111111111111 | ~Red[i * 2 + 1]);
  }
  else {
    word temp = ~Red[14] | ~Example[i];
    Red[14] =  ~temp;
    Blue[14] = ~Red[14] | 0B1100000000000000;
  }

}

void laserStage3(int i) {
  if (i < 7) {
    Red[i * 2] = 0B0000000000000000;
    Red[i * 2 + 1] = 0B0000000000000000;
    activeY[i] = true;
  }
  else {
    for (int o = 0; o < 16; o++) {
      Red[o] = ~(~Red[o] | ~Example[i]);
      Red15 = ~(Red[o] | ~Example[i]);
    }
    activeX[i - 6] = true;
  }
  note = 5;
}

void turnOff(int i) {
  if (i < 7) {

    for (int o = 0; o < 16; o++) {
      Red[o] = Red[14] | ~Example[i];
    }

    Blue[i * 2] = 0B0011111111111111;
    Blue[i * 2 + 1] = 0B0011111111111111;
    activeY[i] = false;
  }
  else {
    for (int o = 0; o < 16; o++) {
      Red[o] = Red[14] | ~Example[i];
    }
    Blue[14] = ~Red[14] | 0B1100000000000000;
    Blue[15] = ~Red[15] | 0B1100000000000000;
    activeX[i - 6] = false;
  }
}

boolean checkIfDead() {
  if (activeY[playerY] || activeX[playerX]) {
    dead = true;
  }
  if (dead && digitalRead(SW_pin) == LOW) {
    dead = false;
    for(int i = 0; i < 14; i++){
      shoot[i] = false;
      startTime[i] = 0;
    }
  }
}
