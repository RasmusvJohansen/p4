
int data[7];

void WaitForNextStep()
{
  Serial.println("Waitting for signal:");
  while (digitalRead(5) == 1)
  {
  }
}

String readData(int bitHolder[])
{
  while (digitalRead(5) == 0)
  {

  }

  Serial.println("Read:");
  String RecivedMsg = "";
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  bitHolder[0] = digitalRead(13);
  bitHolder[1] = digitalRead(12);
  bitHolder[2] = digitalRead(11);
  bitHolder[3] = digitalRead(10);
  bitHolder[4] = digitalRead(9);
  bitHolder[5] = digitalRead(8);
  bitHolder[6] = digitalRead(7);
  bitHolder[7] = digitalRead(6);
  
  for (int i = 7; i >= 0; i--)
  {
    RecivedMsg += String(bitHolder[i]);
  }
 
  return RecivedMsg;
}

void sendData(int x, int y, int z, int j, int i, int k, int m, int n)
{
  Serial.println("Sending:");
  while (digitalRead(5) == 1)
  {
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, x);
    digitalWrite(7, y);
    digitalWrite(8, z);
    digitalWrite(9, j);
    digitalWrite(10, i);
    digitalWrite(11, k);
    digitalWrite(12, m);
    digitalWrite(13, n);
    digitalWrite(4, HIGH);
  }
}

int arr[8];
int trig = 1;
void setup()
{
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
  pinMode(4, OUTPUT); //TX pin 4
  pinMode(5, INPUT);  // RX pin 5
  digitalWrite(4, LOW);
}

void loop()
{

  //Serial.println(digitalRead(5));
  // put your main code here, to run repeatedly:

  // wait for trigger form FPGA
  

  if (digitalRead(5) == 1)
  {
    Serial.println("Waking up");
    sendData(1, 0, 0, 0, 0, 0, 0, 0); //pusher beskeden indtil FPGA trækker RX lav.
    Serial.println("Data Send");
    digitalWrite(4, LOW);
    //WaitForNextStep();
    Serial.println(readData(data));
    
    //pinMode(6, INPUT);
    //pinMode(13, INPUT);
    //Serial.println(digitalRead(6));
    //Serial.println(digitalRead(13));
    
    
    /*
    if (readData(data) == "00000001")
    {
      Serial.println("Hej");
    }
    */
   
  }
}

/*
if (digitalRead(5) == 0b00000010)
{

  
  sendData(1, 1, 1, 1, 1, 1, 1, 1);
  sendData(0, 0, 0, 0, 0, 0, 0, 1);
}

if (digitalRead(5) == 0b00000001)
{
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

  if (digitalRead(5) == HIGH && trig == 0)
  {
    digitalWrite(4, HIGH);
    Serial.println("TX er LAV");
    for (int i = 6; i <= 13; i++)
    {
      arr[i - 6] = digitalRead(i);
    }
    for (int i = 6; i <= 13; i++)
    {
      Serial.print(arr[i - 6]);
    }
    Serial.println("");
    delay(50);
    trig = 1;
  }
}

if (digitalRead(4) == 0b00000011)
{
  return;
}
}
*/
