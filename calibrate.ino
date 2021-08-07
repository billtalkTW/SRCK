byte lightPin[3] = {A0, A1, A2}; // 右 中 左

void setup() {
  // put your setup code here, to run once:
  for(int e=0; e<3 ;e++){
    pinMode(lightPin[e], INPUT);
  }
  Serial.begin(9600);
  delay(100);
  lightCallibrate();
}

void loop() {
  // put your main code here, to run repeatedly:

}


int rawValue(int pin){
  return analogRead(lightPin[pin]);
}
void lightCallibrate(){
  int Max[3] = {0, 0, 0};
  int Min[3] = {9999, 9999, 9999};
  int Mid[3];
  while(true){
    for(int i = 0; i < 3; i++){
      int v = rawValue(i);
      Max[i] = max(Max[i], v);
      Min[i] = min(Min[i], v);
      Mid[i] = (Max[i] + Min[i]) / 2;
    }
    Serial.print(String("\n") + "右\t" + "中\t" + "左\n");
    Serial.print(String("") + Mid[0] + "\t" + Mid[1] + "\t" + Mid[2] + "\n");
  }
}
