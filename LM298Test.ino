/*OPEN JUMPER L298 Shield*/
int INA = 8; //motor A reversing control pin
int PWMA = 11; //motor A speed control pin
int INB = 12; //motor B reversing control pin
int PWMB = 10; //motor B speed control pin
void setup(){
		pinMode(INA,OUTPUT);
		pinMode(INB,OUTPUT);
}
void loop(){
		int value[4] , SpeedValue;
		char temp[4];
		/*for(value = 0 ; value <= 255; value+=5){
		  digitalWrite(INA,HIGH);
		  digitalWrite(INB,HIGH);
		  analogWrite(PWMA,value);
		  analogWrite(PWMB,value);
		  delay(50);
		  }*/
		while(Serial.available()>0){
				temp[0]=temp[1];
				temp[1]=temp[2];
				temp[2]=temp[3];
				temp[3]=Serial.read();
		}


		/*manual test*/
		value[0]=0;
		value[1]=1;
		//value[2]=0;
		//value[3]=1;
		digitalWrite(12,value[0]);
		digitalWrite(8,value[1]);
		//digitalWrite(10,value[2]);
		//digitalWrite(11,value[3]);
		analogWrite(10 , 100);
		analogWrite(11 , 100);	


		/*auto test*/
		/*for(SpeedValue = 0 ; SpeedValue <= 255; SpeedValue+=5){
		  digitalWrite(12,value[0]);
		  digitalWrite(8,value[1]);
		  analogWrite(10 , SpeedValue);
		  analogWrite(11 , SpeedValue);	
		  delay(50);
		  }*/
}
