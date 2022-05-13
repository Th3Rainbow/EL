void playerMove() {
  if (analogRead(xAxis) < 300) {
    if (playerY * 2 < 2) {
      return;
    }
    currentTime1 = millis() - startGameTime;

    if (currentTime1 > 300) {
      playerY -= 1;
      Green[playerY * 2] = Green[playerY * 2 + 2];
      Green[playerY * 2 + 1] = Green[playerY * 2 + 2];
      Green[playerY * 2 + 2] = 0B1111111111111111;
      Green[playerY * 2 + 3] = 0B1111111111111111;
      startGameTime = millis();
    }
  }

  if (analogRead(xAxis) > 700) {
    if (playerY * 2 > 10) {
      return;
    }
    currentTime1 = millis() - startGameTime;

    if (currentTime1 > 300) {
      playerY += 1;
      Green[playerY * 2] = Green[playerY * 2 - 2];
      Green[playerY * 2 + 1] = Green[playerY * 2 - 2];
      Green[playerY * 2 - 2] = 0B1111111111111111;
      Green[playerY * 2 - 1] = 0B1111111111111111;
      startGameTime = millis();
    }
  }

  if (analogRead(yAxis) > 700) {
    if (playerX * 2 < 4) {
      return;
    }
    currentTime1 = millis() - startGameTime;

    if (currentTime1 > 300) {
      playerX -= 1;
      word temp = Green[playerY * 2];
      temp = ~temp;
      temp = temp << 2;
      Green[playerY * 2] = ~temp;
      Green[playerY * 2 + 1] = ~temp;
      startGameTime = millis();
    }
  }

  if (analogRead(yAxis) < 300) {
    if (playerX * 2 > 12) {
      return;
    }
    currentTime1 = millis() - startGameTime;

    if (currentTime1 > 300) {
      playerX += 1;
      word temp = Green[playerY * 2];
      temp = ~temp;
      temp = temp >> 2;
      Green[playerY * 2] = ~temp;
      Green[playerY * 2 + 1] = ~temp;
      startGameTime = millis();
    }
  }
}
