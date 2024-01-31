#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32, 16, 2);

const int MAX_LEVEL = 100; 
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 0;
int velocity = 1000;
int highscore = 1;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop(){
  
  while(level == 0){
    show_welcome();
    randomSeed(analogRead(5));
    int rnd = random(0,1000);
    delay(rnd);
    generate_sequence();
    delay(100);
    level = 1;
    lcd.clear();
  }
  
  while(level != 0){
    Serial.println(level);
    show_points();
    show_sequence();
    get_sequence();
    
  }
}

void  show_sequence(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  for (int i = 0; i < level; i++){
    digitalWrite(sequence[i], HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
}

void  get_sequence(){
  int flag = 0; 

  for  (int i = 0; i < level; i++){
    flag = 0;
    while(flag == 0){
      if (digitalRead(A0) == LOW){
        digitalWrite(5, HIGH);
        tone(6, 300);
        your_sequence[i] = 5;
        flag = 1;
        delay(200);
        noTone(6);
        if  (your_sequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
      digitalWrite(5, LOW);
    }

    if (digitalRead(A1) == LOW){
      digitalWrite(4, HIGH);
      tone(6, 280);
      your_sequence[i] = 4;
      flag = 1;
      delay(200);
      noTone(6);
      if (your_sequence[i] != sequence[i]){
        wrong_sequence();
      return;
      }
      digitalWrite(4,  LOW);
    }

    if (digitalRead(A2) == LOW){
      digitalWrite(3, HIGH);
      tone(6, 260);
      your_sequence[i] = 3;
      flag = 1;
      delay(200);
      noTone(6);
      if (your_sequence[i] != sequence[i]){
        wrong_sequence();
        return;
      }
      digitalWrite(3,  LOW);
    }
      
      if (digitalRead(A3) == LOW){
        digitalWrite(2, HIGH);
        tone(6, 240);
        your_sequence[i] = 2;
        flag = 1;
        delay(200);
        noTone(6);
        if (your_sequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
        digitalWrite(2, LOW);
      }
    }
  }
  right_sequence();
}

void generate_sequence(){
  randomSeed(millis());  
  for (int i = 0; i < MAX_LEVEL; i++){
    sequence[i] = random(2,6);
  }  
}

void wrong_sequence(){
  for (int i = 0; i < 3;  i++){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    tone(6, 1000);
    delay(250);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    noTone(6);
    delay(250);
  }
  level  = 0;
  velocity = 1000;
}

void right_sequence(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(250);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(500);
  if  (level < MAX_LEVEL){
    level++;
    if(highscore < level){
      highscore = level;
    }
    velocity -= 50;
  }
}

void show_points(){
  lcd.setCursor(0,0);
  lcd.printstr("Level: ");
  lcd.print(level);
  lcd.setCursor(0,1);
  lcd.print("Highscore: ");
  lcd.print(highscore);
  delay(1000);
}

void show_welcome(){
  lcd.setCursor(0,0);
  lcd.print("Wilkommen");
  lcd.setCursor(0,1);
  lcd.print("Knopf = Start");
}
