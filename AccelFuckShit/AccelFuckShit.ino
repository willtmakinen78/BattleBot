int waitTime = 200;
int lowTimeA = 400;
int lowTimeB = 200;
int highTime = 1;
boolean RanA = false;
boolean RanB = false;
int ocra = 1;
int i = 1;
int j = 1;

void setup() {
    TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 1;
  TCCR1B |= (1 << WGM21);
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TIMSK1 |= (1 << OCIE1A);
   
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;  
  OCR2A = 1;
  TCCR2A |= (1 << WGM21); 
  TCCR2B |= (1 << CS21);   
  TIMSK2 |= (1 << OCIE2A);
  
  sei();
  
  pinMode (2, OUTPUT);
  pinMode (4, OUTPUT);
}
ISR(TIMER2_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
   //interrupt commands here
   if (RanA == false)
    {
      digitalWrite (2, HIGH);
      RanA = true; 
    }
    else
    {
     digitalWrite (2, LOW);
     i = i + 1;
       if (i == lowTimeA)
       {
        RanA =false;
       }
    }
}



ISR(TIMER1_COMPA_vect){
  if (RanB == false)
    {
      digitalWrite (4, HIGH);
      RanB = true;   
    }
    else
    {
     digitalWrite (4, LOW);
     j = j + 1;
       if (j == lowTimeB)
       {
        RanB = false;
       } 
    }
}





void loop() {
  // put your main code here, to run repeatedly:

}
