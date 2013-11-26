/* This project is modied from BTcar,
 * But it's only used two motor , 
 * Because the project will be apply to power wheelchair,
 * The power wheelchair can avoid obstacle,
 * So , I need following hardware provide pin :
 * 
 *     1. two ultrasonic sensor (used GPIO) 
 *     2. two motor (used PWM)   
 *     3. one Serial port (through USB to connector bb-xM)
 *    
 *     the motor's motion table and pin set:
 *	   	PinNum		Motor		function			
 *     --------------------------------------------
 *        8			  A			Forward / Reverse
 *        11 		  A			PWM speed control
 *        12          B         Forward / Reverse
 *        10          B         PWM spped control 
 * 
 *     Modified by JackABK  
 *     Github: https://github.com/JackABK
 *     E-mail: gn771018@hotmail.com
 * 
 */

/*Setting the ultrasonic pin number*/
#define TRIGPIN_L 13
#define ECHOPIN_L 7
#define TRIGPIN_R 5
#define ECHOPIN_R 6
 
/*motor's  pin number*/
#define INA  8 //motor A reversing control pin
#define PWMA  11 //motor A speed control pin
#define INB  12 //motor B reversing control pin
#define PWMB  10 //motor B speed control pin
#define SpeedValue 50

/*Global var setting*/
char val;
char acpt_cmd_temp[2]; 

/*setting pin mode */
void setup()
{
		/*MotorA and MotorB*/
		pinMode(INA,OUTPUT);
		pinMode(INB,OUTPUT);
		pinMode(PWMA,OUTPUT);
		pinMode(PWMB,OUTPUT);

		/*Initialization the Motor*/
		stop_motion();

		/*Ultrasonic*/
		pinMode(TRIGPIN_L, OUTPUT);
		pinMode(ECHOPIN_L, INPUT);   
		pinMode(TRIGPIN_R, OUTPUT);
		pinMode(ECHOPIN_R, INPUT);   

		/*set baud rate  9600bps*/ 
		Serial.begin(9600);    
}
/*Main code do something*/
void loop()
{
		long cm_L,cm_R;

 
		while(Serial.available()>0){
				acpt_cmd_temp[1]=acpt_cmd_temp[0];
				acpt_cmd_temp[0]=Serial.read();
		}
		PerformCommand();


		/*enable the auto-avoidence obstacle*/
		cm_L=Get_Dist_From_Ultrasonic(TRIGPIN_L , ECHOPIN_L);
		cm_R=Get_Dist_From_Ultrasonic(TRIGPIN_R , ECHOPIN_R);
		if( (cm_L<50) && !(cm_R<50)){
			go_right();
			delay(100);
		}
		else if( !(cm_L<50) && (cm_R<50) ){
			go_left();
			delay(100);
		}
		else if((cm_L<50) && (cm_R<50) ){
			go_right();
			delay(100);
		}	
		else{
			go_forward();
			delay(100);
		}
}
/*ultrasonic get distance function*/
long Get_Dist_From_Ultrasonic(int TRIGPIN , int ECHOPIN)
{
		digitalWrite(TRIGPIN, LOW);
		delayMicroseconds(2);
		digitalWrite(TRIGPIN, HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIGPIN, LOW);
		return pulseIn(ECHOPIN, HIGH)/58;
}
/*Setting the Car initialization*/
void Car_Init()
{
		go_forward();
		delay(500);
		stop_motion();
		delay(500);
		go_reverse();
		delay(500);
		stop_motion();
}
/*determine the command from Serail port*/
void PerformCommand()
{
		if(acpt_cmd_temp[0] == 'f'){
				//if(acpt_cmd_temp[1] == 'r') go_forward_R();
				//else if(acpt_cmd_temp[1] == 'l') go_forward_L();
				//else go_forward();
				go_forward();
		}
		else if(acpt_cmd_temp[0] == 's'){
				stop_motion();
		}
		else if(acpt_cmd_temp[0] == 'b'){
				//if(acpt_cmd_temp[1] == 'r') go_reverse_R();
				//else if(acpt_cmd_temp[1] == 'l') go_reverse_L();
				//else go_reverse();
				go_reverse();
		}
		else if(acpt_cmd_temp[0] == 'l'){
				go_left();
		}
		else if(acpt_cmd_temp[0] == 'r'){
				go_right();
		}
		else{
				/*do not anything*/
		}
}

/**************Action Code Part******************/
void go_forward()
{
		digitalWrite(INA,HIGH);   
		digitalWrite(INB,HIGH);
		analogWrite(PWMA,SpeedValue);
		analogWrite(PWMB,SpeedValue);
}
void go_reverse()
{
		digitalWrite(INA,LOW);   
		digitalWrite(INB,LOW);
		analogWrite(PWMA,SpeedValue);
		analogWrite(PWMB,SpeedValue);

}
void go_left()
{
		digitalWrite(INA,LOW);   
		digitalWrite(INB,HIGH);
		analogWrite(PWMA,SpeedValue);
		analogWrite(PWMB,SpeedValue);

}
void go_right()
{
		digitalWrite(INA,HIGH);   
		digitalWrite(INB,LOW);
		analogWrite(PWMA,SpeedValue);
		analogWrite(PWMB,SpeedValue);

}
void go_forward_L()
{

}
void go_forward_R()
{

}
void go_reverse_L()
{

}
void go_reverse_R()
{

}
void stop_motion()
{
		digitalWrite(INA,LOW);   
		digitalWrite(INB,LOW);
		digitalWrite(PWMA,LOW);
		digitalWrite(PWMB,LOW);
}
/*************End Action Code*******************/
