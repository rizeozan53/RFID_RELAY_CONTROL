// BU PROJEDEKİ AMAÇ SERİAL MONİTÖRDEKİ BİLGİLER VE  RFİD MODÜLE DOĞRU KART OKUTTUĞUMUZDA RÖLEYİ ÇEKTİRMESİ DOĞRUKARTI TEKRAR OKUTTUĞUMUZDA RÖLE MANYETİĞİNİ BIRAKMASI....
//THE PURPOSE OF THIS PROJECT IS TO PULL THE RELAY WHEN WE READ THE CARD CORRECTLY TO THE INFORMATION ON THE SERIAL MONITOR AND RFID MODULE, AND TO RELEASE THE RELAY MAGNET WHEN WE RE-READ THE CARD CORRECTLY....

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(10, 9); 
const int relayPin = 6;  // Add a constant for the relay pin

bool relayState = false;  // Add a boolean flag to keep track of the relay's state

void setup() {
  pinMode(relayPin, OUTPUT);  // Set the relay pin as an output
  Serial.begin(9600);             
  SPI.begin();                    
  mfrc522.PCD_Init();             
  Serial.println("Kartinizin okunmasi için yaklastiriniz...");
  Serial.println();
}

void loop() 
{
  // Yeni kartlar aranıyor
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //UID numarası yazdırılıyor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "3A AD 9D 16") // Bu bölümü sizin kartınoz UID değerine göre değiştiriniz //Please change this section according to the UID value of your card
  {
    if (!relayState) {  // Check if the relay is currently off
      digitalWrite(relayPin, HIGH);
      delay(2000);
            relayState = true;  // Set the relay state to true
    } else {  // If the relay is already on, turn it off
      digitalWrite(relayPin, LOW);  // Turn off the relay
      relayState = false;  // Set the relay state to false
      delay(1000);
    }
  }
  else   {
    Serial.println("yanlış kart- FALSE CARD!!") ;
    delay(750);
  }
}