const int motor1a = 30;
const int motor1b = 32;
const int motor2a = 34;
const int motor2b = 36 ;

enum EarMotion {
  up,
  down
};

EarMotion ear  = up ;

 void setup()
 {
   pinMode(motor1a,OUTPUT);
   pinMode(motor1b,OUTPUT);
   pinMode(motor2a,OUTPUT);
   pinMode(motor2b,OUTPUT);
   Serial.begin(9600);
   Dancing();
   delay(6000);
   StopDancing();
    EarFlip('U' ,800);
    StopeEarFlip();
 }

 void loop()
 {

 }

 void Dancing()
 {
    Serial.println("rabbit is dancing");
   digitalWrite(motor2a,HIGH);
   digitalWrite(motor2b,LOW);
 }
 void StopDancing()
 {
   digitalWrite(motor2a,LOW);
   digitalWrite(motor2b,LOW);
   Serial.println("rabbit stop dancing");
 }

void EarFlip(char motion, int delayseconds)
{
 if  (motion == 'U' )
 {
    digitalWrite(motor1a,LOW) ;
    digitalWrite(motor1b,HIGH);
    Serial.println("rabbit's ears Flip Upward");
 }
 else
 {
    digitalWrite(motor1a,HIGH) ;
    digitalWrite(motor1b,LOW); 
    Serial.println("rabbit's ears Flip Downward");
 }
  delay(delayseconds);
}

void StopeEarFlip()
{
    digitalWrite(motor1a,LOW) ;
    digitalWrite(motor1b,LOW); 
    Serial.println("rabbit's ears Stop Moving");

}
