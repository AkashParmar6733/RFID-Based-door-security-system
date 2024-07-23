#include <SPI.h> 
#include <MFRC522.h> 
#define RST_PIN 9   // Reset pin for the RFID sensor 
#define SS_PIN 10   // Slave Select pin for the RFID sensor 
#define relay 3 
#define led 2 
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an instance of the RFID 
sensor 
void setup() 
{ 
	Serial.begin(9600);   // Initialize serial communication 
	pinMode(relay,OUTPUT); 
	pinMode(led,OUTPUT); 
	SPI.begin();         
	// Initialize SPI communication 
	mfrc522.PCD_Init();   // Initialize the RFID sensor 
	Serial.println("Ready to scan RFID cards!"); 
} 
void loop() 
{
 // Scan for RFID cards 
	if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
	{ 
		// Get the UID of the card 
		String uid = ""; 
		for (byte i = 0; i < mfrc522.uid.size; i++) 
		{ 
			uid += String(mfrc522.uid.uidByte[i], HEX); 
		} 
		Serial.println("RFID Card UID: " + uid)   
		// Compare the UID with the allowed UID(s) 
		if (uid == "2e6ea662") 
		{ 
			// Replace "ABCD1234" with the UID of your 
			allowed card(s) 
			Serial.println("Access granted!"); 
			digitalWrite(relay,1); 
			// Unlock the door 
			delay(2000); // Wait for 1 second 
			digitalWrite(relay,0); 
		} 
		else 
		{ 
			Serial.println("Access denied!"); // Display access denied message 
			digitalWrite(relay,0);  
		}   
		mfrc522.PICC_HaltA(); // Halt PICC 
		mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD 
		
	} 
}