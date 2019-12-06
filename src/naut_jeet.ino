char ch,tmp='x';
int Speed=120;
bool hmode = false;
int diff=0;
void setup() {
  //Upwards Motor
  pinMode(A3,OUTPUT);
  pinMode(5,OUTPUT);
  
  pinMode(A1,OUTPUT);
  pinMode(6,OUTPUT);

  //X-Y Plane Motion
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);  //changed
  pinMode(11,OUTPUT);

  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);  //changed
  pinMode(10,OUTPUT);
  Serial.begin(9600);

}

void forward()
{
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  analogWrite(11,Speed);

  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  analogWrite(10,Speed);
   if(hmode==false)
  {  digitalWrite(5,LOW);
     digitalWrite(6,LOW);
  }
}

void yaw_lft()
{
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  analogWrite(11,Speed);

  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  analogWrite(10,Speed);
   if(hmode==false)
  {  digitalWrite(5,LOW);
     digitalWrite(6,LOW);
  }
}

void yaw_rt()
{
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  analogWrite(11,Speed);

  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  analogWrite(10,Speed);

  if(hmode==false)
  {  digitalWrite(5,LOW);
     digitalWrite(6,LOW);
  }
}

void fwd_lft()
{
  digitalWrite(A3,HIGH);
  analogWrite(5,Speed);
  digitalWrite(A1,HIGH);
  analogWrite(6,Speed/2);
  
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
void fwd_rt()
{
  digitalWrite(A3,HIGH);
  analogWrite(5,Speed/2);
  digitalWrite(A1,HIGH);
  analogWrite(6,Speed);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
void bwd_lft()
{
  digitalWrite(A3,LOW);
  analogWrite(5,Speed);
  digitalWrite(A1,LOW);
  analogWrite(6,Speed/2);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
void bwd_rt()

  digitalWrite(A3,LOW);
  analogWrite(5,Speed/2);
  digitalWrite(A1,LOW);
  analogWrite(6,Speed);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
void sink()
{
  digitalWrite(A1,LOW);
  analogWrite(6,Speed);
  digitalWrite(A3,LOW);
  analogWrite(5,Speed);
  analogWrite(10,0);
  analogWrite(11,0); 
  hmode=false;

}

void surface()
{
  digitalWrite(A1,HIGH);
  analogWrite(6,Speed);
  digitalWrite(A3,HIGH);
  analogWrite(5,Speed/2);
  analogWrite(10,0);
  analogWrite(11,0);
  hmode=false;
}

void pitch_fwd()
{
  digitalWrite(8,HIGH);
  analogWrite(11,Speed/2);
  digitalWrite(4,LOW);
  analogWrite(10,Speed/3);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}
void pitch_bwd()
{
  digitalWrite(8,LOW);
  analogWrite(11,Speed/3);
  digitalWrite(4,HIGH);
  analogWrite(10,Speed/2);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}

void kill()
{
analogWrite(5,0);
analogWrite(6,0);
analogWrite(10,0);
analogWrite(11,0);
hmode=false;
}

void hover()
{
  diff=ch;
  digitalWrite(A1,HIGH);
  analogWrite(6,constrain(Speed+diff,0,255));
  digitalWrite(A3,HIGH);
  analogWrite(5,constrain(Speed-diff,0,255));
  hmode = true;
  
}

void loop() {
 if(Serial.available())
 {
  ch=Serial.read();
  label:
  if(ch=='a')
     forward();
  else if(ch=='b')
     yaw_lft();
  else if(ch=='c')
     yaw_rt();
  else if(ch=='d')
     pitch_fwd();
  else if(ch=='e')
     pitch_bwd();
  else if(ch=='f')
     sink();
  else if(ch=='g')
     surface();
  else if(ch=='h')
     reverse();
  else if(ch=='x')
     kill();
  else if(ch=='u')
     fwd_lft();
  else if(ch=='i')
     fwd_rt();
   else if(ch=='o')
     bwd_lft();
   else if(ch=='p')
     bwd_rt();
   else if((int)ch>=50 || (int)ch <= -50)
     hover();
  else if((int)ch>=0  && (int)ch<=13)
    {
      Speed=20*ch*0.9;
      Serial.println(Speed);
      ch=tmp;
      goto label;
    }
     tmp=ch;
  
    Serial.println(ch);
  
 }

}

