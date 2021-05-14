void sendData(int x, int y, int z, int j, int i, int k, int m, int n) {
  while (digitalRead(5) != 1) {
    digitalWrite(6, x);
    digitalWrite(7, y);
    digitalWrite(8, z);
    digitalWrite(9, j);
    digitalWrite(10, i);
    digitalWrite(11, k);
    digitalWrite(12, m);
    digitalWrite(13, n);
  }
}

int arr[8];
int trig = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(4, OUTPUT); //TX
  pinMode(5, INPUT); // RX
  digitalWrite(5, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if (digitalRead(5)== 1) {
  digitalWrite(4, 0b10000000);
  }


  if (digitalRead(5) == 0b00000010) {
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    sendData(0, 0, 0, 0, 0, 0, 0, 0);
    sendData(1, 1, 1, 1, 1, 1, 1, 1);
    sendData(0, 0, 0, 0, 0, 0, 0, 1);
  }


  if (digitalRead(5) == 0b00000001) {
    pinMode(13, INPUT);
    pinMode(12, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);
    pinMode(9, INPUT);
    pinMode(8, INPUT);
    pinMode(7, INPUT);
    pinMode(6, INPUT);
  if (digitalRead(5) == LOW && trig == 1)
    {
      Serial.println("RX er høj");
      digitalWrite(4, LOW);
      trig = 0;
    }

    if (digitalRead(5) == HIGH && trig == 0)  {
      digitalWrite(4, HIGH);
      Serial.println("TX er LAV");
      for (int i = 6 ; i <= 13 ; i++) {
        arr[i - 6] = digitalRead(i);
      }
      for ( int i = 6; i <= 13; i++) {
        Serial.print(arr[i - 6]);
      }
      Serial.println("");
      delay(50);
      trig = 1;

    }
  }

  if(digitalRead(4) == 0b00000011){
    return;
  }
}
