const int pwmPin = 9;

const int encoderA = 2;
const int encoderB = 3;

// Encoder
volatile long pulses = 0;

// Variables
int pwmValue = 0;
int duty = 0;

float rpm = 0;

// Setpoint fijo
float setpoint = 1000;

// Estado
bool motorON = false;

// Modos
bool closedLoop = false;

// Tiempo
unsigned long lastRPM = 0;

// Pulsos por vuelta
// AJUSTAR si hace falta
const int PPR = 20;

// Ganancia proporcional
float Kp = 0.03;

// Encoder interrupt
void countEncoder() {

  pulses++;
}

void setup() {

  Serial.begin(9600);

  pinMode(pwmPin, OUTPUT);

  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);

  // Interrupcion encoder
  attachInterrupt(
    digitalPinToInterrupt(encoderA),
    countEncoder,
    RISING
  );

  Serial.println("========================================");
  Serial.println("CONTROL MOTOR DC");
  Serial.println("SETPOINT FIJO = 1000 RPM");
  Serial.println("e = MOTOR ON");
  Serial.println("a = MOTOR OFF");
  Serial.println("o = LAZO ABIERTO");
  Serial.println("c = LAZO CERRADO");
  Serial.println("========================================");

  // Cabecera CSV
  Serial.println("Tiempo_ms,PWM,Duty,RPM,Setpoint,Modo");
}

void loop() {

  // COMANDOS SERIE
  if (Serial.available()) {

    char c = Serial.read();

    // MOTOR ON
    if (c == 'e' || c == 'E') {

      motorON = true;

      Serial.println("MOTOR ON");
    }

    // MOTOR OFF
    if (c == 'a' || c == 'A') {

      motorON = false;

      analogWrite(pwmPin, 0);

      Serial.println("MOTOR OFF");
    }

    // LAZO ABIERTO
    if (c == 'o' || c == 'O') {

      closedLoop = false;

      Serial.println("MODO ABIERTO");
    }

    // LAZO CERRADO
    if (c == 'c' || c == 'C') {

      closedLoop = true;

      Serial.println("MODO CERRADO");
    }
  }

  // ACTUALIZACION cada 200 ms
  if (millis() - lastRPM >= 200) {

    lastRPM = millis();

    // Calculo RPM
    rpm = (pulses * 300.0) / PPR;

    // Reset pulsos
    pulses = 0;

    // LAZO ABIERTO
    if (!closedLoop) {

      // PWM fijo simple
      pwmValue = 150;
    }

    // LAZO CERRADO
    else {

      float error = setpoint - rpm;

      pwmValue += error * Kp;

      // Limites
      if (pwmValue > 255)
        pwmValue = 255;

      if (pwmValue < 0)
        pwmValue = 0;
    }

    // Duty %
    duty = map(pwmValue, 0, 255, 0, 100);

    // Motor
    if (motorON)
      analogWrite(pwmPin, pwmValue);

    else
      analogWrite(pwmPin, 0);

    // CSV
    Serial.print(millis());
    Serial.print(",");

    Serial.print(pwmValue);
    Serial.print(",");

    Serial.print(duty);
    Serial.print(",");

    Serial.print(rpm);
    Serial.print(",");

    Serial.print(setpoint);
    Serial.print(",");

    if (closedLoop)
      Serial.println("CERRADO");

    else
      Serial.println("ABIERTO");
  }
}