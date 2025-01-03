/*

*/

unsigned long current_micros = 0;
unsigned long last_triggered_front = 0;
unsigned long last_triggered_rear = 0;
unsigned long interval_front = 2436;
unsigned long interval_rear = 2327;
unsigned long interval_for_skidding = 100000;
unsigned long last_triggered_skidding = 0;
byte wheel_stopped = 0;

const byte front = 3;
const byte front_second_pin = 4;
const byte rear = 5;
const byte rear_second_pin = 6;
const byte button_front = 12;
const byte button_rear = 1;

void setup() {
  pinMode(front, OUTPUT);
  pinMode(front_second_pin, OUTPUT);
  digitalWrite(front_second_pin, LOW); // use instead of GND pin for push/pull action
  pinMode(rear, OUTPUT);
  pinMode(rear_second_pin, OUTPUT);
  digitalWrite(rear_second_pin, LOW); // use instead of GND pin for push/pull action
  pinMode(button_front, INPUT_PULLUP);
  pinMode(button_rear, INPUT_PULLUP);
}

void loop() {
  current_micros = micros();
  if ( (current_micros - last_triggered_skidding) >= interval_for_skidding) {
    toggle_skidding();
    last_triggered_skidding = current_micros;
  }
  if ( (current_micros - last_triggered_front) >= interval_front) {
    toggle_front();
    last_triggered_front = current_micros;
  }
  if ( (current_micros - last_triggered_rear) >= interval_rear) {
    toggle_rear();
    last_triggered_rear = current_micros;
  }
}

void toggle_skidding() {
  if (wheel_stopped == 0) {
    wheel_stopped = 1;
  }
  else {
    wheel_stopped = 0;
  }
}

void toggle_front() {
  if ((wheel_stopped == 0) || (digitalRead(button_front) == 1)) {
  if (digitalRead(front) == HIGH) {
    digitalWrite(front, LOW);
    digitalWrite(front_second_pin, HIGH);
  }
  else {
    digitalWrite(front, HIGH);
    digitalWrite(front_second_pin, LOW);
  }
  }
}

void toggle_rear() {
  if ((wheel_stopped == 0) || (digitalRead(button_rear) == 1)) {
    if (digitalRead(rear) == HIGH) {
      digitalWrite(rear, LOW);
      digitalWrite(rear_second_pin, HIGH);
    }
    else {
      digitalWrite(rear, HIGH);
      digitalWrite(rear_second_pin, LOW);
    }
  }
}
