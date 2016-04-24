/*
LCD name badge thing.

Using circuit layout from https://www.arduino.cc/en/Tutorial/HelloWorld
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char name[] = "Justin Collins  ";
char twitter[] = "@presidentbeef  ";
char work[] = "SurveyMonkey    ";
char bmp[] = "Brakeman Pro    ";
int p_delay = 100; //150;
int l_delay = 300; //2000;
int c_delay = 10; //100;

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

byte frowny[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
};

void setup() {
  lcd.createChar(0, smiley);
  lcd.begin(16, 2);
}

void print_chars(char pword[]) {
  for(int i = 0; i < 16; i++) {
   lcd.print(pword[i]); 
   delay(p_delay);
  } 
}

void scroll_chars(char pword[]) {
  for(int i = 0; i < 16; i++) {
   lcd.setCursor(0, 1);
   for(int j = (15 - i); j < 16; j++) {
     lcd.print(pword[j]);
   }
   delay(p_delay);
  } 
   delay(p_delay);
}

void clear_bottom() {
 delay(l_delay);
 lcd.setCursor(0, 1);
 lcd.print("                "); 
 lcd.setCursor(0, 1);
 delay(c_delay);
}

void clear_all() {
 for(int i = 0; i < 32; i++) {
   lcd.setCursor(i / 2, i % 2);
   lcd.print(" ");
   delay(20);
 } 
}

void scroll_all() {
   for(int i = 0; i < 15; i ++) {
    lcd.scrollDisplayRight();
    delay(50);
  } 
}

void name_display() {
  lcd.clear();
  for(int i = 0; i < 15; i ++) {
    lcd.scrollDisplayLeft();
  }
  
  lcd.setCursor(0,0);

  for(int i = 0; i < 14; i++) {
   lcd.print(name[i]);
  }
  
  write_at(byte(0), 15, 0);
  
  for(int i = 0; i < 15; i ++) {
    lcd.scrollDisplayRight();
    delay(50);
  }
  
  clear_bottom();

  print_chars(twitter);

  clear_bottom();

  scroll_chars(work);
  
  clear_bottom();

  print_chars(bmp);

  delay(l_delay);
  int x = random(3);
  if (x == 0) {
    left_to_right();
  }
  else if (x == 1) {
    clear_all();
  }
  else {
    scroll_all(); 
  }
}

void print_at(const char c[], int col, int row) {
  lcd.setCursor(col, row);
  lcd.print(c);
}

void write_at(byte b, int col, int row) {
  lcd.setCursor(col, row);
  lcd.write(b);  
}

void left_to_right() {
 int b = 15;
 for(int i = 0; i < 16; i++) {
   print_at("O", i, 0);
   print_at("O", b, 1);
   delay(100);
   print_at(" ", i, 0);
   print_at(" ", b, 1);
   b--;
  }
}

void loop() {
  name_display();
}

