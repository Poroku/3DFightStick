#include <XInput.h>
 
//LED Pins
const int Pin_ledR = 3;
const int Pin_ledG = 4;
const int Pin_ledB = 5;
const int Pin_ledControl = 2;
 
// Trigger Pins
const int Pin_TriggerL = 14;
const int Pin_TriggerR = 15;
 
// Button Pins
const int Pin_ButtonA = 18;
const int Pin_ButtonB = 20;
const int Pin_ButtonX = 19;
const int Pin_ButtonY = 21;
 
const int Pin_ButtonLB = 16;
const int Pin_ButtonRB = 17;
 
const int Pin_ButtonBack  = 6;
const int Pin_ButtonStart = 23;
 
const int Pin_ButtonL3 = 22;
const int Pin_ButtonR3 = 7;
 
// Directional Pad Pins
const int Pin_DpadUp  = 11;
const int Pin_DpadDown  = 12;
const int Pin_DpadLeft  = 10;
const int Pin_DpadRight = 9;
 
void setup() {
    pinMode(Pin_ledR, OUTPUT);
    pinMode(Pin_ledG, OUTPUT);
    pinMode(Pin_ledB, OUTPUT);
    pinMode(Pin_ledControl, INPUT_PULLUP);
    pinMode(Pin_TriggerL, INPUT_PULLUP);
    pinMode(Pin_TriggerR, INPUT_PULLUP);
    
    pinMode(Pin_ButtonA, INPUT_PULLUP);
    pinMode(Pin_ButtonB, INPUT_PULLUP);
    pinMode(Pin_ButtonX, INPUT_PULLUP);
    pinMode(Pin_ButtonY, INPUT_PULLUP);
    
    pinMode(Pin_ButtonLB, INPUT_PULLUP);
    pinMode(Pin_ButtonRB, INPUT_PULLUP);
    
    pinMode(Pin_ButtonBack, INPUT_PULLUP);
    pinMode(Pin_ButtonStart, INPUT_PULLUP);
    
    pinMode(Pin_ButtonL3, INPUT_PULLUP);
    pinMode(Pin_ButtonR3, INPUT_PULLUP);
    
    pinMode(Pin_DpadUp, INPUT_PULLUP);
    pinMode(Pin_DpadDown, INPUT_PULLUP);
    pinMode(Pin_DpadLeft, INPUT_PULLUP);
    pinMode(Pin_DpadRight, INPUT_PULLUP);
    
    XInput.setAutoSend(false);  // Wait for all controls before sending
    
    XInput.begin();
}

#define BUTTON_DEBOUNCE_MS 200
 
void loop() {
    static int ledMode;
    static int buttonState;
    static unsigned long debounceTime;
    static int led_r, led_g, led_b;

    if ( buttonState == 0 && (digitalRead(Pin_ledControl) == LOW) ) {
        ledMode++;
        if (ledMode > 5) ledMode = 0;
        buttonState = 1;
        debounceTime = millis();
    }
    if ( buttonState == 1 && ((millis() - debounceTime) > BUTTON_DEBOUNCE_MS) ) {
        if (digitalRead(Pin_ledControl) == HIGH) {
            buttonState = 0;
        }
    }

    switch (ledMode) {
        case 0:
            led_r = 0;
            led_g = 255;
            led_b = 255;
            break;
        case 1:
            led_r = 255;
            led_g = 155;
            led_b = 255;
            break;
        case 2:
            led_r = 155;
            led_g = 0;
            led_b = 255;
            break;
        case 3:
            /* Note: you can tune this value to make it white */
            led_r = 190;
            led_g = 255;
            led_b = 230;
            break;
        case 4:
            {
                static unsigned int count;
                count++;
                
                if(count == 800) {
                    if (led_b > 0 && led_g == 0) {
                        led_r++;
                        led_b--;
                    }
                    else if (led_r > 0 && led_b == 0) {
                        led_r--;
                        led_g++;
                    }
                    else if (led_g > 0 && led_r == 0) {
                        led_b++;
                        led_g--;
                    }
                    else {
                        led_r = 0;
                        led_g = 0;
                        led_b = 255;
                    }
                    count = 0;
                }
            }
            break;
        case 5:
            led_r = 0;
            led_g = 0;
            led_b = 0;
            break;
    }
    

    analogWrite(Pin_ledR, 255 - led_r);
    analogWrite(Pin_ledG, 255 - led_g);
    analogWrite(Pin_ledB, 255 - led_b);

    // Read pin values and store in variables
    // (Note the "!" to invert the state, because LOW = pressed)
    boolean buttonA = !digitalRead(Pin_ButtonA);
    boolean buttonB = !digitalRead(Pin_ButtonB);
    boolean buttonX = !digitalRead(Pin_ButtonX);
    boolean buttonY = !digitalRead(Pin_ButtonY);
    
    boolean buttonLB = !digitalRead(Pin_ButtonLB);
    boolean buttonRB = !digitalRead(Pin_ButtonRB);
    
    boolean buttonBack  = !digitalRead(Pin_ButtonBack);
    boolean buttonStart = !digitalRead(Pin_ButtonStart);
    
    boolean buttonL3 = !digitalRead(Pin_ButtonL3);
    boolean buttonR3 = !digitalRead(Pin_ButtonR3);
    
    boolean dpadUp  = !digitalRead(Pin_DpadUp);
    boolean dpadDown  = !digitalRead(Pin_DpadDown);
    boolean dpadLeft  = !digitalRead(Pin_DpadLeft);
    boolean dpadRight = !digitalRead(Pin_DpadRight);
    
    // Set XInput buttons
    XInput.setButton(BUTTON_A, buttonA);
    XInput.setButton(BUTTON_B, buttonB);
    XInput.setButton(BUTTON_X, buttonX);
    XInput.setButton(BUTTON_Y, buttonY);
    
    XInput.setButton(BUTTON_LB, buttonLB);
    XInput.setButton(BUTTON_RB, buttonRB);
    
    XInput.setButton(BUTTON_BACK, buttonBack);
    XInput.setButton(BUTTON_START, buttonStart);
    
    XInput.setButton(BUTTON_L3, buttonL3);
    XInput.setButton(BUTTON_R3, buttonR3);
    
    // Set XInput DPAD values
    XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);
    
    // Set XInput trigger values
    // Read trigger buttons
    boolean triggerLeft  = !digitalRead(Pin_TriggerL);
    boolean triggerRight = !digitalRead(Pin_TriggerR);
    
    // Set the triggers as if they were buttons
    XInput.setButton(TRIGGER_LEFT, triggerLeft);
    XInput.setButton(TRIGGER_RIGHT, triggerRight);
    
    // Send control data to the computer
    XInput.send();
}
