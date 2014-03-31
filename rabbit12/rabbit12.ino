const int motor1a = 30;
const int motor1b = 32;
const int motor2a = 34;
const int motor2b = 36 ;
String song[4] = {"BDDDDUUUUUUUUUDDDUUUUNDDDDDDUUUUUUDDDDDDBDDDUUUUDDUUUUDDUUUUDDDDDDDSN",
                  "BDDDDUUUUUUUUUDDDUUUUNDDDDDDUUUUUUDDDDDDBDDDUUUUDDUUUUDDUUUUDDDDDDDSN",
                 "BDDDDUUUUUUUUUDDDUUUUNDDDDDDUUUUUUDDDDDDBDDDUUUUDDUUUUDDUUUUDDDDDDDSN",
                "BDDDDUUUUUUUUUDDDUUUUNDDDDDDUUUUUUDDDDDDBDDDUUUUDDUUUUDDUUUUDDDDDDDSN"} ;
char ppo[255]; 
int counter = 0 ;
enum EarMotion {
  up,
  down
};

EarMotion ear  = up ;
int addrpin=6;
char addr;

 void setup()
 {
   pinMode(motor1a,OUTPUT);
   pinMode(motor1b,OUTPUT);
   pinMode(motor2a,OUTPUT);
   pinMode(motor2b,OUTPUT);
   pinMode(addrpin, OUTPUT);
   Serial.begin(9600);
    Serial1.begin(9600);
    Serial.println("program Start here");
    EarFlip('D' ,300);
    StopeEarFlip();
 }

 void loop()
 {
   
    // MotionExecution(song[0]);
 shockrabbit();
//Serial.println("motion end here ...... ");
 delay(500);
 }

void playsound(char sn)
{
       Serial.print("now playing song #");
       Serial.println(sn,HEX) ;
       PlayVoice(sn,addrpin);
}
void shockrabbit()
{
  char ii ;
 if (Serial1.available())
 {
   ii = Serial1.read() ;
   Serial.print("receive from bluetooth :");
   Serial.print("(");
   Serial.print(counter);
   Serial.print("):(");
   Serial.print(ii, DEC);
   Serial.println(")");
   counter ++ ;
   if (ii >=49 && ii <= 52)
    {
       Serial.println("now send deancing");
     MotionExecution(song[ii-49]);
    Serial.print("Sound Code is :(");
    Serial.print(ii-49,HEX);
    Serial.println(")");
     playsound(ii-49);
    } 
    // MotionExecution(
 }
}
void MotionExecution(String po)
{
  int ll = 0 ;
 if  (po.length() > 0)
 //char ppo[po.length()];
 po.toCharArray(ppo, po.length());
   for (ll = 0 ; ll < po.length()-1 ; ll++)
     {
        Motion(ppo[ll]);
         Serial.print("motion :( ");
         Serial.print(ll);
         Serial.print("/ ");
         Serial.print(po.length());
         Serial.print("/ ");         
         Serial.print(ppo[ll]);
          Serial.println(") ");        
     }
    delay(100);
}
void Motion(char pp)
{
  
  switch (pp)
  {
    case 'U' :
      EarFlip('U' ,10);
      break ;
      
    case 'D' :
      EarFlip('D' ,10);
      break ;
      
    case 'S' :
      StopeEarFlip();
      break ;
      
    case 'B' :
      Dancing();
      break ;
      
     case 'N' :
      StopDancing();
      break ;
    default :
      break ;
  }

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


void PlayVoice(unsigned char addr,unsigned int addrpin)
{
digitalWrite(addrpin,0);
delay(5);
for(int i=0;i<8;i++)
{
digitalWrite(addrpin,1);
if(addr & 1)
{
delayMicroseconds(600);
digitalWrite(addrpin,0);
delayMicroseconds(300);
}
else
{
delayMicroseconds(300);
digitalWrite(addrpin,0);
delayMicroseconds(600);
}
addr>>=1;  //此行用>>=还是=>>还不确定
}
digitalWrite(addrpin,1);
}


/*用于播放由一串地址组成的语句*/
void PlayVoiceSerial(unsigned int addrserial[],unsigned int len,unsigned int addrpin,unsigned int busypin)
{
for(int i=0;i<len;i++)
{
addr=addrserial[i];
PlayVoice(addr,addrpin);
pulseIn(busypin,0);
pulseIn(busypin,1);
}
}

