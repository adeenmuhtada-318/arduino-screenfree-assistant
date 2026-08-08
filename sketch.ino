#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

const int pirPin = 2;          
const int btnBreak = 3;        // Red
const int btnComplete = 4;     // Blue
const int btnHelp = 5;         // Yellow
const int btnRepeat = 6;       // Green
const int audioOutPin = 9;     // Buzzer (Simulator only)

bool lastPirState = LOW;       
// Buzzer tones for simulator testing
void makeAudioSound(int type) {
  if (type == 1) { 
    tone(audioOutPin, 523, 200); delay(250);
    tone(audioOutPin, 659, 300); delay(350);
  } 
  else if (type == 2) { 
    tone(audioOutPin, 440, 200); delay(250);
    tone(audioOutPin, 554, 200); delay(250);
    tone(audioOutPin, 659, 300); delay(350);
  } 
  else if (type == 3) { 
    tone(audioOutPin, 880, 200); delay(250);
    tone(audioOutPin, 784, 300); delay(350);
  } 
  else if (type == 4) { 
    tone(audioOutPin, 587, 150); delay(200);
    tone(audioOutPin, 659, 150); delay(200);
    tone(audioOutPin, 880, 400); delay(450);
  } 
  else if (type == 5) { 
    tone(audioOutPin, 900, 150); delay(150);
    tone(audioOutPin, 900, 150); delay(150);
    tone(audioOutPin, 900, 300); delay(350);
  }
}

void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  
  pinMode(pirPin, INPUT);
  
  pinMode(btnBreak, INPUT_PULLUP);
  pinMode(btnComplete, INPUT_PULLUP);
  pinMode(btnHelp, INPUT_PULLUP);
  pinMode(btnRepeat, INPUT_PULLUP);
  
  pinMode(audioOutPin, OUTPUT);

  Serial.println("==================================================");
  Serial.println("  SCREEN-FREE ASSISTIVE HOME ROUTINE ASSISTANT   ");
  Serial.println("==================================================");

  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(25);

  /* TODO: Real Hardware Setup
  // PIR needs ~30s to settle on boot
  Serial.println("Warming up PIR...");
  delay(30000); 
  Serial.println("Ready");
  */
}

void loop() {
  // Red - Break
  if (digitalRead(btnBreak) == LOW) {
    Serial.println("\n>>> [RED BUTTON PRESSED]: Break Requested <<<");
    Serial.println("🔊 Voice Prompt: 'It's time for a short break. Sit down and relax.'");
    makeAudioSound(3);
    myDFPlayer.play(3); // Plays 0003.mp3 on Speaker
    delay(500); 
  }

  // Blue - Task Done
  if (digitalRead(btnComplete) == LOW) {
    Serial.println("\n>>> [BLUE BUTTON PRESSED]: Task Completed <<<");
    Serial.println("🔊 Voice Prompt: 'Great job! You completed this activity.'");
    makeAudioSound(4);
    myDFPlayer.play(4); // Plays 0004.mp3 on Speaker
    delay(500); 
  }

  // Yellow - Help
  if (digitalRead(btnHelp) == LOW) {
    Serial.println("\n>>> [YELLOW BUTTON PRESSED]: Help Requested <<<");
    Serial.println("🔊 Voice Prompt: 'Help is on the way. Someone will come assist you.'");
    makeAudioSound(5);
    myDFPlayer.play(5); // Plays 0005.mp3 on Speaker
    delay(500); 
  }

  // Green - Repeat
  if (digitalRead(btnRepeat) == LOW) {
    Serial.println("\n>>> [GREEN BUTTON PRESSED]: Repeat Instruction <<<");
    Serial.println("🔊 Voice Prompt: 'Repeating: Please follow your current routine step.'");
    makeAudioSound(2);
    myDFPlayer.play(2); // Plays 0002.mp3 on Speaker
    delay(500); 
  }

  // PIR Motion Logic (Wokwi Sim Version)
  int currentPirState = digitalRead(pirPin);

  if (currentPirState == HIGH && lastPirState == LOW) {
    lastPirState = HIGH; // Lock state is set to be early to avoid double trigger

    Serial.println("\n=== [PIR SENSOR]: Motion Detected ===");

    Serial.println("🔊 Step 1: 'Welcome! Voice guidance system active.'");
    makeAudioSound(1);
    myDFPlayer.play(1);
    delay(1000);

    Serial.println("🔊 Step 2: 'Follow your daily routine instructions.'");
    makeAudioSound(2);
    myDFPlayer.play(2);
    delay(1000);

    Serial.println("=== Sequence Complete: Waiting for Button Press ===");
  } 
  else if (currentPirState == LOW) {
    lastPirState = LOW;
  }

  /* TODO: Real Hardware Setup (No buzzer tones, real MP3 durations via DFPlayer + 3W Speaker)
  int currentPirState = digitalRead(pirPin);

  if (currentPirState == HIGH && lastPirState == LOW) {
    lastPirState = HIGH;

    Serial.println("\n=== [PIR SENSOR]: Motion Detected ===");

    // Step 1: Audio Playback directly through Speaker
    myDFPlayer.play(1); // Plays 0001.mp3
    delay(3000);        // Match exact duration of 0001.mp3 voice file

    // Step 2: Audio Playback
    myDFPlayer.play(2); // Plays 0002.mp3
    delay(3000);        // Match exact duration of 0002.mp3 voice file

    Serial.println("=== Sequence Complete: Waiting for Button Press ===");
    
    delay(5000); // Cooldown delay to stop repeated motion triggers
  } 
  else if (currentPirState == LOW) {
    lastPirState = LOW;
  }
  */
}
