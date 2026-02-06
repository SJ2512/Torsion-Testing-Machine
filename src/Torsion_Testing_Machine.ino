/*
 PROTOTYPE CONTROL & ESTIMATION CODE
 -----------------------------------
 This code is used for prototype validation of torsion testing architecture.

 NOTE:
 Torque values are currently theoretical estimations derived from
 angular displacement using torsion equations.

 Motor torque constant (Kt) calibration and real torque validation
 using known specimens has not yet been completed.

 This code is part of an ongoing experimental platform and should
 not be considered a calibrated material testing system.
 */

int RPWM = 9;
int LPWM = 8;
int REN = 11;
int LEN = 10;

int encoderPinA = 2;
int encoderPinB = 3;

volatile long pulseCount = 0;

// -------- PHYSICS CONSTANTS --------
const float G = 4.4e10;   // Shear Modulus (Pa)
const float J = 2.7e-13;  // Polar Moment of Inertia (m^4)
const float L = 0.18;     // Length (m)

const float PPR = 800.0;
// Use the exact value you measured for best accuracy
const float GEAR_RATIO = 26.87; 

float targetRPM = 1;
float currentRPM = 0;
float maxRPM = 10;
unsigned long lastUpdate = 0;

// Variables to store live data
float specimenAngleDeg = 0;
float currentTorque = 0;

float rpmToPWM(float rpm) {
  float ratio = rpm / maxRPM;
  if (ratio < 0) ratio = 0;
  if (ratio > 1) ratio = 1;
  return ratio * 255.0;
}

void countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(REN, OUTPUT);
  pinMode(LEN, OUTPUT);
  digitalWrite(REN, HIGH);
  digitalWrite(LEN, HIGH);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), countPulse, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), countPulse, RISING);
}

void loop() {

  // -------- CALCULATE DATA LIVE --------
  long pulsesSnapshot;
  noInterrupts();
  pulsesSnapshot = pulseCount;
  interrupts();

  // 1. Calculate Motor Angle (Total degrees motor spun)
  float motorAngleDeg = (pulsesSnapshot * 360.0) / PPR;

  // 2. Calculate Specimen Angle (Divide by Gear Ratio)
  specimenAngleDeg = motorAngleDeg / GEAR_RATIO;  

  // 3. Torsion Formula Calculation (using Specimen Angle)
  float thetaRad = specimenAngleDeg * PI / 180.0;
  currentTorque = (G * thetaRad * J) / L; // Torque in N*m


  // -------- STOP COMMAND --------
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "stop") {
      // 1. Stop Motor Immediately
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 0);

      // 2. Report ACTUAL captured values
      Serial.println("====== TEST STOPPED - ACTUAL RESULTS ======");
      
      Serial.print("Final Specimen Angle: ");
      Serial.print(specimenAngleDeg);
      Serial.println(" degrees");
      
      Serial.print("Final Calculated Torque: ");
      Serial.print(currentTorque, 4); 
      Serial.println(" N*m");
      Serial.println("===========================================");

      // 3. Reset logic for next run
      noInterrupts();
      pulseCount = 0;
      interrupts();

      // Wait until "start"
      while (true) {
        if (Serial.available()) {
          String cmd2 = Serial.readStringUntil('\n');
          cmd2.trim();
          if (cmd2 == "start") break;
        }
      }

      currentRPM = 0;
      targetRPM = 1;
      delay(300);
    }
  }

  // -------- RPM RAMP --------
  if (millis() - lastUpdate > 50) {
    if (currentRPM < targetRPM) currentRPM += 0.05;
    if (currentRPM > targetRPM) currentRPM -= 0.05;

    float pwm = rpmToPWM(currentRPM);
    analogWrite(RPWM, pwm);
    analogWrite(LPWM, 0);

    lastUpdate = millis();
  }

  // -------- INCREASE RPM --------
  static unsigned long changeTime = millis();
  if (millis() - changeTime > 1000) {
    if (targetRPM < maxRPM) targetRPM++;
    changeTime = millis();
  }

  // -------- SERIAL PLOTTER FORMAT --------
  // x axis = Angle (degrees), y axis = Torque (mN*m for visibility)
  Serial.print("Angle:");
  Serial.print(specimenAngleDeg);        
  Serial.print(" Torque_mNm:");
  Serial.println(currentTorque * 1000.0); 
  
  delay(100);
}
