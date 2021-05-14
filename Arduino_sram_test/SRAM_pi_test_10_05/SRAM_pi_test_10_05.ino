unsigned int dataPin7 = 37;
unsigned int dataPin6 = 36;
unsigned int dataPin5 = 35;
unsigned int dataPin4 = 34;
unsigned int dataPin3 = 33;
unsigned int dataPin2 = 32;
unsigned int dataPin1 = 31;
unsigned int dataPin0 = 30;
unsigned int PCLK = 53;
unsigned int vsync = 42; //write
unsigned int href = 43;   //read

unsigned int mem_pin = 9;
//unsigned int RW_pin = 8;

unsigned long start = 0;
unsigned long stopt = 0;
unsigned long tid = 0;

void setAdr(int y) {
  //digitalWrite(rpi, HIGH);

  PORTB = y;
  
  digitalWrite(mem_pin, LOW);
  digitalWrite(mem_pin, HIGH);
  digitalWrite(mem_pin, LOW);
}

void wrData(int x) { 
  digitalWrite(PCLK, HIGH);
  digitalWrite(mem_pin, HIGH);
  digitalWrite(href, HIGH);

  PORTA = x;
  
 
  digitalWrite(href, LOW);
  digitalWrite(mem_pin, LOW);
  digitalWrite(mem_pin, HIGH); 
  digitalWrite(PCLK, LOW);
}

void rdData() {
  digitalWrite(PCLK, LOW);
  digitalWrite(mem_pin, HIGH);
  digitalWrite(vsync, LOW);
  //digitalWrite(rpi, HIGH);
  int x = PINC;

  Serial.println(x);
  
  Serial.print(digitalRead(dataPin0));
  Serial.print(digitalRead(dataPin1));
  Serial.print(digitalRead(dataPin2));
  Serial.print(digitalRead(dataPin3));
  Serial.print(digitalRead(dataPin4));
  Serial.print(digitalRead(dataPin5));
  Serial.print(digitalRead(dataPin6));
  Serial.println(digitalRead(dataPin7));
  digitalWrite(PCLK, HIGH);
}




void setup() {
  // put your setup code here, to run once:
  pinMode(dataPin7, INPUT);
  pinMode(dataPin6, INPUT);
  pinMode(dataPin5, INPUT);
  pinMode(dataPin4, INPUT);
  pinMode(dataPin3, INPUT);
  pinMode(dataPin2, INPUT);
  pinMode(dataPin1, INPUT);
  pinMode(dataPin0, INPUT);
  pinMode(PCLK, OUTPUT);
  Serial.begin(9600);
  pinMode(href, OUTPUT);
  pinMode(vsync, OUTPUT);
  pinMode(mem_pin, OUTPUT);

  DDRA = 0b11111111;
  DDRB = 0b11111111;
  DDRC = 0b00000000;

  digitalWrite(vsync, LOW);
  for(long j = 0; j< 256; j++){
    //setAdr(j);
     wrData(j);
     //delay(1000);
  }
  digitalWrite(vsync, HIGH);
  //digitalWrite(vsync, LOW);
  //delay(1000);
  Serial.println("slut moms");


  
}

void loop() {
  // put your main code here, to run repeatedly:



  }
