//Setup pins for motors
void motor_setup(){
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  stopMotors();
}

//Move the motors with joystick
void drive(){
  // --- Read joystick values ---
  xValue = analogRead(X_pin);
  yValue = analogRead(Y_pin);

  // --- Normal joystick control ---
  if (yValue > center + deadZone) { //Forward
    speedValue = map(yValue, center + deadZone, 1023, 0, 255);
    forward(speedValue);
  }
  else if (yValue < center - deadZone) { //Backward
    speedValue = map(yValue, center - deadZone, 0, 0, 255);
    backward(speedValue);
  }
  else if (xValue > center + deadZone) { //Right
    speedValue = map(xValue, center + deadZone, 1023, 0, 255);
    right(speedValue);
  }
  else if (xValue < center - deadZone) { //Left
    speedValue = map(xValue, center - deadZone, 0, 0, 255);
    left(speedValue);
  }
  else {
    stopMotors();
  }

  // --- Print info ---
  //Serial.print("X: "); Serial.print(xValue);
  //Serial.print("  Y: "); Serial.print(yValue);
}

// --- Motor Control Functions ---
void forward(int spd) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, spd); analogWrite(enB, spd-50);
}


void backward(int spd) {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, spd); analogWrite(enB, spd);
}


void left(int spd) {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, spd); analogWrite(enB, spd);
}


void right(int spd) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, spd); analogWrite(enB, spd);
}


void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}
