#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define trigger_pin D6
#define Echo_pin D7
#define LED_satu D3
#define LED_dua D4
#define LED_tiga D5
#define Buzzer D8

/* two variables to store duraion and distance value */
long duration;
int distance;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x3F, 16 column and 2 rows

/* configure D9 and D11 as digital input and output respectively */
void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();

  pinMode(trigger_pin, OUTPUT); // configure the trigger_pin(D9) as an Output
  pinMode(Echo_pin, INPUT);     // configure the Echo_pin(D11) as an Input
  pinMode(LED_satu, OUTPUT);
  pinMode(LED_dua, OUTPUT);
  pinMode(LED_tiga, OUTPUT);
  pinMode(Buzzer, OUTPUT); // Set the LED (D13) pin as a digital output
  Serial.begin(9600);      // Enable the serial with 9600 baud rate
}

void loop()
{

  digitalWrite(trigger_pin, LOW); // set trigger signal low for 2us
  delayMicroseconds(2);

  /*send 10 microsecond pulse to trigger pin of HC-SR04 */
  digitalWrite(trigger_pin, HIGH); // make trigger pin active high
  delayMicroseconds(10);           // wait for 10 microseconds
  digitalWrite(trigger_pin, LOW);  // make trigger pin active low

  /*Measure the Echo output signal duration or pulss width */
  duration = pulseIn(Echo_pin, HIGH); // save time duration value in "duration variable
  distance = duration * 0.034 / 2;    // Convert pulse duration into distance

  /*if distance greater than 15cm, turn on LED*/
  if (distance > 10)
  {
    digitalWrite(LED_satu, HIGH);
    digitalWrite(LED_dua, LOW);
    digitalWrite(LED_tiga, LOW);

    lcd.setCursor(0, 1);
    lcd.print("AMAN BANJIR");
    delay(3000);
  }
  else if (distance <= 10 && distance >= 5)
  {
    digitalWrite(LED_satu, LOW);
    digitalWrite(LED_dua, HIGH);
    digitalWrite(LED_tiga, LOW);

    lcd.setCursor(0, 1);
    lcd.print("WASPADA BANJIR");
    delay(3000);
  }
  else if (distance < 5)
  {
    for (int j = 1; j <= 2; j++)
    {
      digitalWrite(Buzzer, HIGH);
      delay(1000);
      digitalWrite(Buzzer, LOW);
      delay(100);
    }
    digitalWrite(LED_satu, LOW);
    digitalWrite(LED_dua, LOW);
    digitalWrite(LED_tiga, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("BAHAYA BANJIR");
    delay(3000);
  }

  // print measured distance value on Arduino serial monitor
  lcd.clear();
  lcd.setCursor(0, 0); // start to print at the first row
  lcd.print("JARAK: ");
  lcd.print(distance);
  lcd.print(" cm");
  delay(1000);
}