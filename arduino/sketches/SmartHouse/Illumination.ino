const float Ra = 48000.0;
const int Ea = 10;

const float R = 200000.0;
const float VCC = 5.0;

int getIllumination(int pin) {
  double voltage = (analogRead(pin) * VCC) / 1024;
  int R1 = (VCC / voltage - 1.0) * R;
  return (Ra * Ea) / pow(R1, 0.9);
}

