/* Convert Arduino to a MIDI controller using as many digital inputs 
* as you need. 
* 
* This sketch is set up to send 2 MIDI notes on MIDI channel 5, 
* but it can be easily reconfigured for other notes and channels 
* 
* Created 3 Nov 2008 
* By Hyeki Min 
* 
* Modified 14 May 2009 
* By Petyr Stretz 
* Changed switch logic so that the pin low and high made the 
* notes play like a keyboard, removed unneeded pins, changed 
* output MIDI channel to 5 
*
* Modified 15 April 2014
* By Petyr Stretz 
* Instructables user Andrew.Wilson.7 reported BYTE is no 
* longer used in Arduino 1.0 or later. Removed it from noteOn()
*/

// define the pins we use, MIDI port is always on Arduino pin 1 (TX)
int switchPin1 = 2; 
int switchPin2 = 3;

// general midi notes
char note1 = 60; //Middle C
char note2 = 62; //D

// Variables
int switchState1 = LOW;
int switchState2 = LOW;
int currentSwitchState1 = LOW;
int currentSwitchState2 = LOW;

void setup() { 
// set the states of the I/O pins: 
pinMode(switchPin1, INPUT); 
pinMode(switchPin2, INPUT);

// set MIDI baud rate : 
Serial.begin(31250); 
}
void loop() { //switchPin1 
currentSwitchState1 = digitalRead(switchPin1); 
if( currentSwitchState1 == HIGH && switchState1 == LOW ) // push 
//Note on channel 5 (0x94), some note value (note), middle velocity (0x45): 
noteOn(0x94, note1, 0x45); 
if( currentSwitchState1 == LOW && switchState1 == HIGH ) // release 
//Note on channel 5 (0x94), some note value (note), silent velocity (0x00): 
noteOn(0x94, note1, 0x00); 
switchState1 = currentSwitchState1; //switchPin2 
currentSwitchState2 = digitalRead(switchPin2); 
if( currentSwitchState2 == HIGH && switchState2 == LOW ) // push 
//Note on channel 5 (0x94), some note value (note), middle velocity (0x45): 
noteOn(0x94, note2, 0x45); 
if( currentSwitchState2 == LOW && switchState2 == HIGH ) // release 
//Note on channel 5 (0x94), some note value (note), silent velocity (0x00): 
noteOn(0x94, note2, 0x00); 
switchState2 = currentSwitchState2;
}// Send a MIDI note-on/off message. 

void noteOn(char cmd, char data1, char data2) { 
Serial.print(cmd); 
Serial.print(data1); Serial.print(data2);
}
