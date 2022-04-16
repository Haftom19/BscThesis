#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int redLed = 8;
int greenLed =9;
int buzzer = 10;
int yellowLed=13;
int smokeA0 = A5;
void setup()
{
 // put your setup code here, to run once:
 Serial.begin(9600);
 analogWrite(6,20);
 pinMode(redLed, OUTPUT);
 pinMode(greenLed, OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(yellowLed, OUTPUT);
 pinMode(smokeA0, INPUT);
 lcd.begin(16, 2);
 lcd.setCursor(0, 0);
 lcd.print("Alcohl detection ");
 lcd.setCursor(0,1);
 lcd.print("   System  ");
 delay(5000);
}
void loop() {
  // put your main code here, to run repeatedly:
 int analogSensor = analogRead(smokeA0);
 Serial.print("Pin A0: ");
 
  if (analogSensor <=200)
  {
    digitalWrite(redLed, LOW);
    delay(200);
    digitalWrite(greenLed, LOW);
    delay(200);
    digitalWrite(yellowLed, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alcohl detection ");
     lcd.scrollDisplayLeft();
    lcd.setCursor(0, 1);
    lcd.print(analogSensor);
    lcd.print("     System  ");
    delay(1000);
  }
  if (analogSensor >200 && analogSensor <=350 )
  {
    digitalWrite(redLed, LOW);
    delay(200);
    digitalWrite(greenLed, HIGH);
    delay(200);
    digitalWrite(yellowLed, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Driver is sober  ");
    lcd.setCursor(0, 1);
    lcd.print("     ");
    lcd.print(analogSensor);
    lcd.print("ppm ");
    delay(1000);
  //  tone(buzzer,1000,1000);
   
   
  }
    if (analogSensor >350  && analogSensor < 450) 
    {
    digitalWrite(greenLed, LOW);
    delay(200);
    digitalWrite(redLed, LOW);
     delay(200);
    digitalWrite(yellowLed, HIGH);
     delay(200);
     lcd.setCursor(0,0);
     lcd.print(" slightly Drunk ");
    // lcd.scrollDisplayLeft();
    lcd.setCursor(0, 1);
    lcd.print("     ");
    lcd.print(analogSensor);
    lcd.print("ppm");
    Serial.flush();
    //tone(buzzer,1000,1000);
   
   
    }
    if (analogSensor >=450)
    {
    digitalWrite(greenLed, LOW);
    delay(200);
    digitalWrite(redLed, HIGH);
    delay(200);
    digitalWrite(yellowLed, LOW);
    delay(200);
   tone(buzzer,1000,1000);
   lcd.clear();
   lcd.print(" Driver is drunken ");
   lcd.setCursor(0, 1);
   lcd.print("     ");
   lcd.print(analogSensor);
   lcd.print("ppm");
   if (Serial.available())
  {
    
    SendSMS(); 
       //Send one SMS
     delay(10000); //Give enough time for GSM to register on Network
   while(1); 
  // Serial.flush();
  }  
          }
        }
      void SendSMS()
{
  
  Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  Serial.println("AT+CMGS=\"0928538755\"\r"); //Change to destination phone number 
  delay(1000);
  Serial.println("Hello traffic alcohol detected by driver !");//the content of the message
  delay(200);
  Serial.println((char)26); //the stopping character Ctrl+Z
  delay(1000);  
}
 