const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int thumbdialMore = 8;
const int thumbdialLess = 7;

#define KEY_LEFT_CTRL  0x01
#define KEY_LEFT_SHIFT  0x02
#define KEY_RIGHT_CTRL  0x10
#define KEY_RIGHT_SHIFT 0x20

#define KEY_LEFT_CTRLALTSHIFT 0x07
#define KEY_LEFT_CTRLSHIFT 0x03

int buttonState = 0;
int thumbdialState = 0;
uint8_t buf[8] = { 0 };   // Keyboard report buffer

int i = 0;
int analogValue = 0;

int value = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  
  // initialize the button pins as an inputs
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(thumbdialMore, INPUT_PULLUP);
  pinMode(thumbdialLess, INPUT_PULLUP);

  Serial.begin(9600);

  delay(200);
}

void loop() {
  // PUSH BUTTON
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
    randomColor();
  }

  // POTENTIOMETER
  analogValue = analogRead(A0);

  if (analogValue > i + 5) {
    i = analogValue;
    value = analogValue/10;
    rightArrow();
  } else if (analogValue < i - 5) {
    i = analogValue;
    value = analogValue/10;
    leftArrow();
  }

  // THUMB DIAL
  thumbdialState = digitalRead(thumbdialMore);
  
  if (thumbdialState == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
    redo();
  }

  thumbdialState = digitalRead(thumbdialLess);
  
  if (thumbdialState == HIGH) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
    undo();
  }
}

void undo() {
  buf[0] = KEY_LEFT_CTRL;   // Ctrl
  buf[2] = 29;    // Z
  Serial.write(buf, 8); // Send keypress
  releaseKeyDelay();
}

void redo() {
  buf[0] = KEY_LEFT_CTRLSHIFT;   // Ctrl+SHIFT
  buf[2] = 29;    // Z
  Serial.write(buf, 8); // Send keypress
  releaseKeyDelay();
}

void rightArrow() {
  buf[2] = 79;
  Serial.write(buf, 8); // Send keypress
  releaseKey();
}

void leftArrow() {
  buf[2] = 80;
  Serial.write(buf, 8); // Send keypress
  releaseKey();
}

void randomColor() {
  buf[0] = KEY_LEFT_CTRLALTSHIFT;   // Ctrl+Alt+Shift
  buf[2] = 21;    // R
  Serial.write(buf, 8); // Send keypress
  releaseKeyDelay();
}

void releaseKey() {
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}

void releaseKeyDelay() {
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
  delay(333);
}
