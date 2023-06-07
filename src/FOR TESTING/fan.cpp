// #include <Arduino.h>
// #include "FlexCAN_T4.h"

// #define bufferSize 15
// #define R1 2.2
// #define R2 10.0
// #define workingVoltage 3.3
// #define vmaxPin A17
// #define invertPwm 1

// FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
// CAN_message_t msg;

// String reading = "";
// int aout[4] = {0, 0, 0, 0};
// uint32_t lastAdjTime = 0;
// int fdbkBuffer[4][bufferSize];
// int bufferIdx = 0;
// float target[4] = {0, 0, 0, 0};
// float finalTarget[4] = {0, 0, 0, 0};
// int targetInt[4] = {0, 0, 0, 0};
// float p[4], i[4] = {0, 0, 0, 0}, d[4];
// float lastV[4] = {0, 0, 0, 0};
// float dScale[4] = {0, 0, 0, 0};
// float voltage[4] = {0, 0, 0, 0};
// const float voltageScale = (R1 + R2) / R1 / 1023 * workingVoltage;
// float vmax = 12.0;
// uint32_t currentTime;
// uint32_t sum[4];

// uint8_t ctrlPins[4] = {2, 5, 9, 6};
// uint8_t rpmPins[4] = {3, 4, 8, 7};
// float maxRpms[4] = {4000, 4000, 4000, 4000};
// float targetRpms[4] = {0, 0, 0, 0};
// uint8_t fdbkPins[4] = {A10, A11, A12, A13};
// bool controlModes[4] = {0, 0, 0, 0}; //0=voltage, 1=rpm

// uint32_t lastFallTimes[4] = {0, 0, 0, 0};
// float rpms[4] = {0, 0, 0, 0};
// uint8_t rpmErrs[4] = {0, 0, 0, 0};
// bool lastState[4] = {0, 0, 0, 0};

// void updatePID(uint8_t ch, float dt) {
//   if(controlModes[ch] == 1){
//     target[ch] += min(max(targetRpms[ch] - target[ch], -dt * 0.2), dt * 0.5);
//     if(targetRpms[ch] == 0)target[ch] = 0;
//     return;
//   }
//   target[ch] += min(max(finalTarget[ch] - target[ch], -dt * 0.005), dt * 0.005);
//   p[ch] = target[ch] - voltage[ch];
//   i[ch] += p[ch] * dt * 8;
//   i[ch] = min(max(i[ch], -20.0), 2100.0);
//   d[ch] = (lastV[ch] - voltage[ch]) / dt;
//   dScale[ch] = (min(abs(targetInt[ch] - aout[ch]) * 0.002, 1)) * dt * 0.01 + (dScale[ch] * (1 - (dt * 0.01)));
//   d[ch] *= (dScale[ch] * dScale[ch]);
//   p[ch] *= (dScale[ch] * dScale[ch]);
//   lastV[ch] = voltage[ch];
//   aout[ch] = (p[ch] * 10000.0) + i[ch] + (d[ch] * 500.0);
//   aout[ch] = min(max(aout[ch], 0), 2048);
//   if(invertPwm){
//     analogWrite(ctrlPins[ch], 2048 - aout[ch]);
//   }else{
//     analogWrite(ctrlPins[ch], aout[ch]);
//   }
// }

// void calcRPM(uint8_t ch) {
//   uint32_t ct = micros();
//   float rpmDt = ct - lastFallTimes[ch];
//   lastFallTimes[ch] = ct;
//   float rpm = 30000000.0 / rpmDt;
//   if (((rpm - rpms[ch])/rpmDt < 0.02) && (rpm < 5000.0)) { //filter out unreasonable signals
//     rpmErrs[ch] = 0;
//     rpms[ch] = rpm*0.25 + rpms[ch]*0.75;
//     rpmErrs[ch] = 0;
//     //Serial.print("rpm"); Serial.print(ch); Serial.print(": ");
//     //Serial.println(rpm);
//   }else if((rpm < 5000.0)){
//     rpmErrs[ch]++;
//     if(rpmErrs[ch] >= 20){
//       rpms[ch] = rpm;
//     }
//   }

//   //pid control on rpm
//   if(controlModes[ch] == 0)return;
//   //target[ch] = targetRpms[ch];
//   p[ch] = target[ch] - rpms[ch];
//   i[ch] += p[ch] * rpmDt * 0.00002;
//   i[ch] = min(max(i[ch], -20.0), 2100);
//   d[ch] = (lastV[ch] - rpms[ch]) / rpmDt;
//   //dScale[ch] = (min(abs(targetInt[ch] - aout[ch]) * 0.002, 1)) * rpmDt * 0.01 + (dScale[ch] * (1 - (rpmDt * 0.01)));
//   //d[ch] *= (dScale[ch] * dScale[ch]);
//   //p[ch] *= (dScale[ch] * dScale[ch]);
//   lastV[ch] = rpms[ch];
//   aout[ch] = (p[ch] * 10) + i[ch] + (d[ch] * 1);
//   aout[ch] = min(max(aout[ch], 0), 2048);
//   if(target[ch] == 0) aout[ch] = 0;
//   if(invertPwm){
//     analogWrite(ctrlPins[ch], 2048 - aout[ch]);
//   }else{
//     analogWrite(ctrlPins[ch], aout[ch]);
//   }
// }

// void ISR0() {
//   calcRPM(0);
// }
// void ISR1() {
//   calcRPM(1);
// }
// void ISR2() {
//   calcRPM(2);
// }
// void ISR3() {
//   calcRPM(3);
// }

// void setOutputVoltage(float v, uint8_t ch) {
//   //controlModes[ch] = 0;
//   if(controlModes[ch])return;
//   v = min(max(v, 0), vmax);
//   finalTarget[ch] = v;
//   targetInt[ch] = v / vmax * 2048;
// }

// void setOutputDutyCycle(int dutyCycle, uint8_t ch) {
//   controlModes[ch] = 0;
//   dutyCycle = min(max(dutyCycle, 0), 2048);
//   targetInt[ch] = dutyCycle;
//   finalTarget[ch] = dutyCycle * vmax / 2048.0;
// }

// void setFanRpm(float rpm, uint8_t ch){
//   if(!controlModes[ch])return;
//   targetRpms[ch] = rpm;
// }

// void setControlMode(bool mode, uint8_t ch){
//   controlModes[ch] = mode;
// }

// void setup() {
//   // put your setup code here, to run once:
//   can1.begin();
//   can1.setBaudRate(1000000);
//   msg.flags.extended = 1;

//   analogWriteResolution(11);
//   for (uint8_t i = 0; i < 4; i++) {
//     pinMode(ctrlPins[i], OUTPUT);
//     analogWriteFrequency(ctrlPins[i], 73242.19);
//     analogWrite(ctrlPins[i], invertPwm * 2048);
//     pinMode(rpmPins[i], INPUT);
//   }

//   // attachInterrupt(digitalPinToInterrupt(rpmPins[0]), ISR0, FALLING);
//   // attachInterrupt(digitalPinToInterrupt(rpmPins[1]), ISR1, FALLING);
//   // attachInterrupt(digitalPinToInterrupt(rpmPins[2]), ISR2, FALLING);
//   // attachInterrupt(digitalPinToInterrupt(rpmPins[3]), ISR3, FALLING);

//   Serial.begin(500000);
//   for (uint8_t i = 0; i < 4; i++) {
//     for (uint8_t j = 0; j < bufferSize; j++) {
//       fdbkBuffer[i][j] = 0;
//     }
//   }

//   //get max voltage
//   vmax = analogRead(vmaxPin) * voltageScale + 0.01;
//   // analogWrite(ctrlPins[0], 2048);
//   // delay(1000);
//   // vmax = analogRead(fdbkPins[0]) * voltageScale + 0.05;
//   // Serial.println(vmax);
//   // analogWrite(ctrlPins[0], 0);
// }

// uint8_t count = 0;//debug only, remove on final
// uint32_t lastCountT = 0;

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(can1.read(msg)){
//     if(msg.id == 69420){//voltage control
//       setOutputVoltage((((int)msg.buf[0] << 8) + msg.buf[1])*12/2047.0, 0);//map 0~2047 to 0~12
//       setOutputVoltage((((int)msg.buf[2] << 8) + msg.buf[3])*12/2047.0, 1);
//       setOutputVoltage((((int)msg.buf[4] << 8) + msg.buf[5])*12/2047.0, 2);
//       setOutputVoltage((((int)msg.buf[6] << 8) + msg.buf[7])*12/2047.0, 3);
//     }
//     if(msg.id == 69421){//rpm control
//       setFanRpm((((int)msg.buf[0] << 8) + msg.buf[1]), 0);
//       setFanRpm((((int)msg.buf[2] << 8) + msg.buf[3]), 1);
//       setFanRpm((((int)msg.buf[4] << 8) + msg.buf[5]), 2);
//       setFanRpm((((int)msg.buf[6] << 8) + msg.buf[7]), 3);
//     }
//     if(msg.id == 69422){//control modes
//       setControlMode(msg.buf[0], 0);
//       setControlMode(msg.buf[1], 1);
//       setControlMode(msg.buf[2], 2);
//       setControlMode(msg.buf[3], 3);
//     }
//   }

//   count++;
//   if (count == 0) {
//     //Serial.print("Hz: ");
//     //Serial.println(256.0 / (currentTime - lastCountT) * 1e6);
//     //Serial.println(dt);
//     vmax = analogRead(vmaxPin) * voltageScale + 0.01;
//     lastCountT = currentTime;
//   }

//   for (int i = 0; i < 4; i++) {
//     fdbkBuffer[i][bufferIdx] = analogRead(fdbkPins[i]);
//   }
//   bufferIdx++;
//   if (bufferIdx >= bufferSize)bufferIdx = 0;
//   for (int i = 0; i < 4; i++) {
//     sum[i] = 0;
//     for (uint8_t j = 0; j < bufferSize; j++) {
//       sum[i] += fdbkBuffer[i][j];
//     }
//   }
//   for (int i = 0; i < 4; i++) {
//     voltage[i] = sum[i] * voltageScale / bufferSize;
//   }

//   if (Serial.available() > 0) {//set voltage through usb
//     char r = Serial.read();
//     if (r == '\n') {
//       if (reading == "setV") {
//         // analogWrite(ctrlPins[0], 2048);
//         // delay(1000);
//         vmax = analogRead(vmaxPin) * voltageScale + 0.01;
//         Serial.println(vmax);
//         for (int i = 0; i < 4; i++) {
//           finalTarget[i] = targetInt[i] * vmax / 2048.0;
//         }
//       } else {
//         for (int i = 0; i < 4; i++) {
//           setControlMode(1, i);
//           setFanRpm(reading.toInt(), i);
//         }
//       }
//       reading = "";
//     } else {
//       reading += String(r);
//     }
//   }

//   currentTime = micros();
//   float dt = (currentTime - lastAdjTime) * 0.001;
//   lastAdjTime = currentTime;

//   for (int i = 0; i < 4; i++) {
//     updatePID(i, dt);
//     if (currentTime - lastFallTimes[i] > 5e5){
//       lastFallTimes[i] = currentTime;
//       rpms[i] = 0; //Set rpm to 0 if no signal detected in 0.5s
//       calcRPM(i);
//     }
//   }

//   for (int i = 0; i < 4; i++) {
//     bool currState = digitalRead(rpmPins[i]);
//     if (!currState && lastState[i])calcRPM(i);
//     lastState[i] = currState;
//   }

//   if (0) {//debug print
//     //Serial.println(dt);
//     uint8_t ch = 2;
//     Serial.print(" aout:");
//     Serial.print(aout[ch]);
//     Serial.print(" target:");
//     Serial.print(target[ch]);
//     Serial.print(" voltage:");
//     Serial.print(voltage[ch]);
//     Serial.print(" dScale:");
//     Serial.print(dScale[ch]);

//     Serial.print(" p:");
//     Serial.print(p[ch]);
//     Serial.print(" i:");
//     Serial.print(i[ch]);
//     Serial.print(" d:");
//     Serial.println(d[ch]);
//   }

//   //  Serial.println();
// }