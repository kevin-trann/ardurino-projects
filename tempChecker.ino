#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal.h>

#define DHTPIN 6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)){
    lcd.clear();
    lcd.print("Error reading");
    lcd.setCursor(0,1);
    lcd.print("sensor");
    return;
  }

  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");

}
