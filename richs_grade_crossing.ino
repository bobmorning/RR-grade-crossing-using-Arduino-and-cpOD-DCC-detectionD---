// initialization

//This sketch is designed for use with a cpOD detector and will drive LED grade crossing signals.
//Designed for use on Rich Nemchik's layout
//July-Sept 2021

int ledPin = 8;
int cpOD = 10;
int trk_occupancy = 0;
//int sensorPin = A0;

// Defines for specific grade crossing outputs

// defines for led outputs
int continue_flash = 0;
int led1 = 4; // Led 1 pin first alternating flasher   used to be 10
int led2 = 5; // Led 2 pin first alternating flasher   used to be 11
int led3 = 6; // Led 3 pin second alternating flasher  used to be 12
int led4 = 7; // Led 4 pin second alternating flasher  used to be 13
int detector_test_led = 9; //to verify detector logic is working from JMRI Logix
int flash_state = 0;
long flash_time = 0;
long flash_interval = 900; // time in milliseconds between alternating flashes

int initialization = 1;

void flash_leds() {
  if (flash_time > millis()) return;
 Serial.println("In flash leds");
 flash_state = ~flash_state;
 digitalWrite(led1, flash_state); // Alternate flashers
 digitalWrite(led3, flash_state);
 digitalWrite(led2, ~flash_state);
 digitalWrite(led4, ~flash_state);
 flash_time = millis()+flash_interval;
 }


void starting_sequence() {
    Serial.println("In starting sequence");
    continue_flash = 1;
    flash_leds(); // keep flashing leds
    }

 
void ending_sequence() {

Serial.println("In ending sequence");
 digitalWrite(led1, HIGH); // flashers completely off
 digitalWrite(led3, HIGH);
 digitalWrite(led2, HIGH);
 digitalWrite(led4, HIGH);
 digitalWrite(detector_test_led, HIGH);
 continue_flash = 0;
}


void setup() {
  // put your setup code here, to run once:
  // set the digital pin as output:
//  Serial.println(FILE);
  Serial.begin(9600);
  pinMode(cpOD,INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
//  pinMode(sensorPin,INPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led1, LOW); // Start with all flashers off
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW); 
  flash_time = millis(); // time since sketch started
}

void loop() {
  if (continue_flash) {
        flash_leds();
    }
  
  // put your main code here, to run repeatedly:
  // Serial.println(analogRead(sensorPin));                                      
  // digitalWrite(ledPin, HIGH);          // Pin 13 = 5 V, LED emits light
  delay(1500);                      // ..for 0.5 seconds
  // digitalWrite(ledPin, LOW);           // Pin 13 = 0 V, LED no light
  // delay(500);                      // ..for 0.5 seconds
  trk_occupancy = digitalRead(cpOD);
  if (trk_occupancy == 0)
    {
    Serial.println("Track Occupied");
    starting_sequence();
    digitalWrite(ledPin, HIGH);
    }
  else
    {
    Serial.println("Track Vacant");
    ending_sequence();
    digitalWrite(ledPin, LOW);
    }
  }
