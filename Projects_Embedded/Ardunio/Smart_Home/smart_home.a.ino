#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

int const Gas    = 10; // Gas sensor pin
int const Lm_35  = A0; // LM35 sensor pin
int const RedLed = 9;  
int const Buzzer = 8;
int const led =  11;
int const lamp = 12;
int const motor =13;

int dataBlu; // Use char to store incoming data

void setup() {
  Init();
  Serial.begin(9600);
  lcd.print("Welcome Marwan");
  lcd.setCursor(0, 1);
  lcd.print("SMART_HOME_IEEE");
  delay(800);
  lcd.clear();
  

}

void loop() {
  if (Serial.available() > 0) {
    dataBlu = Serial.read(); // Read as char


    lcd.clear();
 

    // Process received commands
    switch(dataBlu) {
      case 30: // Turn LED ON
        digitalWrite(led, HIGH);
        lcd.clear();
        lcd.print("LED ON ");
        delay(400);
        lcd.clear();
        
        break;
      case 68: // Turn LED OFF
        digitalWrite(led, LOW);
        lcd.clear();
        lcd.print("LED OFF ");
        delay(400);
        lcd.clear();

        break;
      case 17: // Lamp ON
        digitalWrite(lamp, HIGH);
        lcd.clear();
        lcd.print("Lamp ON ");
        delay(400);
        lcd.clear();
        break;
      case 61: // Lamp OFF
        digitalWrite(lamp, LOW);
        lcd.clear();
        lcd.print("Lamp OFF ");
        delay(400);
        lcd.clear();
        break;
      case 15: // Motor ON
        digitalWrite(motor, HIGH);
        lcd.clear();
        lcd.print("Air Condition ON ");
        delay(400);
        lcd.clear();
        break;
      case 248: // Motor OFF
        digitalWrite(motor, LOW);
        lcd.clear();
        lcd.print("Air Condition OFF ");
        delay(400);
        lcd.clear();
        break;
      default:
        
        break;
    }
  // Display received message for 1 second
    lcd.clear();
  }

  temperture_sensor();
  gas_sensor();
}

void Init() {
  lcd.begin(16,2);
  pinMode(Gas, INPUT);
  pinMode(Lm_35, INPUT);    
  pinMode(RedLed, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(lamp, OUTPUT);
  pinMode(motor, OUTPUT);
  // Initialize all to LOW
  digitalWrite(led, LOW);
  digitalWrite(lamp, LOW);
  digitalWrite(motor, LOW);
}

void temperture_sensor() {
  int num = analogRead(Lm_35);
  float v = num * (5.0 / 1023.0);
  float c = v * 100;
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print((int)c);
  lcd.print(" C");

  if(c>25)
  {
    digitalWrite(motor, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Air Condition ON ");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("Air Condition OFF ");
  }
  delay(400); // Reduced delay for responsiveness
  lcd.clear();
}

 void gas_sensor()
 {

    if(digitalRead(Gas) ){
        lcd.setCursor(0,0);
        lcd.print("     Alert!");
        lcd.setCursor(0,1);
        lcd.print("Gas detected!");
        digitalWrite(RedLed , HIGH);
        digitalWrite(Buzzer, HIGH);
        while(digitalRead(Gas));
      }
    else{
      digitalWrite(RedLed , LOW);
      digitalWrite(Buzzer, LOW);
    }
//    delay(100);
    lcd.clear();
 }