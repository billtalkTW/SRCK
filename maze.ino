#include <SRCK.h>

int L = 372;
int M = 421;
int R = 422;
//光感值
int state = 0;
//光感狀態
int pwr = 90;
int turnTimes = 0;
int node[4] = {2, 4, 2, 2};  //2=left,4=front,8=right 
int nodeIndex = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initITR20001();
  initUltrasonic();
  initMotor();
  initServo();  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(getUltrasonic() < 10){ 
    setMotor(0,0); 
    setMotor(1,0);
    crossing(); 
  }
    if(getLight_L() > L){ state += 2; }
    if(getLight_M() > M){ state += 4; }
    if(getLight_R() > R){ state += 8; }
    switch(state){
      case 0:
        setMotor(0,pwr);
        setMotor(1,pwr);
        Serial.println("白白白");
        break;
      case 2:
        setMotor(0,-pwr*0.7);
        setMotor(1,pwr);
        Serial.println("黑白白");
        break;
      case 4:
        setMotor(0,pwr);
        setMotor(1,pwr);
        Serial.println("白黑白");
        break;
      case 8:
        setMotor(0,pwr);
        setMotor(1,-pwr*0.7);
        Serial.println("白白黑");
        break;
      case 6:
        setMotor(0,-pwr);
        setMotor(1,pwr);
        Serial.println("黑黑白");
        break; 
      case 12:
        setMotor(0,pwr);
        setMotor(1,-pwr);
        Serial.println("白黑黑");
        break;
      case 10:
        setMotor(0,0);
        setMotor(1,0);
        Serial.println("黑白黑");
        break;
      case 14:
        setMotor(0,0);
        setMotor(1,0);
        crossing();
        Serial.println("黑黑黑");
        break;    
      default:
        Serial.println("error");
        break;         
    }
  state = 0;
  delay(10);
}

void crossing(){
  turnTimes ++;
  if(turnTimes > 13){
    setMotor(0,0);
    setMotor(1,0);
    while(true){}
  }
  int next = 0;
  setServo(180);  //180->left
  if(getUltrasonic() > 15){ next += 2; }
  setServo(90);   //90->middle
  if(getUltrasonic() > 15){ next += 4; }
  setServo(0);    //0->right
  if(getUltrasonic() > 15){ next += 8; }
  //左邊有路next+2，前方有路next+4，右方有路next+8，死路next=0。
  setMotor(0,80);
  setMotor(1,80);
  delay(250);
  setMotor(0,0);
  setMotor(1,0);
  if( next == 6 || next == 10 || next == 12){
    next = node[nodeIndex];
    nodeIndex++;
  }
  switch(next){ //轉彎，2左轉，4直走，8右轉，0迴轉
    case 2:
      setMotor(0,-100);
      setMotor(1,100);
      delay(300);
      while(getLight_M() < M){}
      break;
    case 4:
      break;
    case 8:
      setMotor(0,100);
      setMotor(1,-100);
      delay(300);
      while(getLight_M() < M){}
      break;
    case 0:
      setMotor(0,100);
      setMotor(1,-100);
      delay(800);
      while(getLight_M() < M){}
      break;
  }
  setMotor(0,0);
  setMotor(1,0);
  setServo(90);
}
