//******************************************************************************

#include "SPI.h"
#include <TFT_eSPI.h>
//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h"
#include <Keypad.h>

#define TFT_CS 15    
#define TFT_DC 2
#define TFT_MOSI 23
#define TFT_SCLK 18
#define REST  4
#define BUZZER_PIN 5

//#define TFT_CS 10    
//#define TFT_DC 9



//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TFT_eSPI tft = TFT_eSPI();
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, REST);
 const uint8_t ROWS = 4;
 const uint8_t COLS = 4;

 char keys[ROWS][COLS] = {
  { 'S', 'U', '3', 'A' },
  { 'L', 'K', 'R', 'B' },
  { '7', 'D', '9', 'C' },
  { '*', '0', '#', 'F' }
 };

 String Dirc_Ball[9][9] = {
  { "DR", "RL", "DRL","RL","DRL","RL","DRL","RL","DL" },

  {"UD", ""   ,"UD"  , ""  ,"UD" ,""   ,"UD" ,""   ,"UD" },

  {"UDR", "RL" ,"UDRL","RL" ,"UDRL","RL","UDRL", "RL" ,"UDL"},

  {"UD", ""   ,"UD"  , ""  ,"UD" ,""   ,"UD" ,""   ,"UD" },

  {"UDR", "RL" ,"UDRL","RL" ,"UDRL","RL","UDRL", "RL" ,"UDL"},

  {"UD", ""   ,"UD"  , ""  ,"UD" ,""   ,"UD" ,""   ,"UD" },

  {"UDR", "RL" ,"UDRL","RL" ,"UDRL","RL","UDRL", "RL" ,"UDL"},

  {"UD", ""   ,"UD"  , ""  ,"UD" ,""   ,"UD" ,""   ,"UD" },
  { "UR", "RL", "URL", "RL", "URL", "RL", "URL", "RL","UL"}
 };

int underworld_tempo[] = {
100,100,100,100,
50,50,50,80,
80,80,80,80

};
int pint_Ball [9][9];
int selcte_lvel [3]{1,2,3};
 uint8_t colPins[COLS] = { 26, 25, 33, 32 }; // Pins connected to C1, C2, C3, C4
 uint8_t rowPins[ROWS] = { 13, 12, 14, 27 }; // Pins connected to R1, R2, R3, R4
 Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
 int Row = 25;
 int Row_Circut = 15;
 int page_num;
 int time_count = 59;
 int start_time,T_start;
 int Ball_count;
 int UpDown,Move_RL,Move_UD,Lac_R,Lac_L,Lac_U,Lac_D,box_R,box_L,box_U,box_D;
 int Location_x , Location_y;
 long signed t , t1 , t2 ;
 int m , n;
 char Res;
 void setup(){
 tft.begin();
 pinMode(BUZZER_PIN, OUTPUT);

 Location_x = 0 , Location_y = 0 , pint_Ball [0][0] = 1 , selcte_lvel [0] = 1 , start_time = 0 , T_start = 250 , UpDown = 1 , Move_RL = 15 , Move_UD = 15;
 t = 0 , t1 = 0 , t2 = 0 , m = 0 , n = 0;
 
 message ();
 delay(20);
 page_num = 0;
 tft.fillScreen(TFT_BLACK);
 Slecte_lvel();
 delay(20);
 lvel_Gamse ();
 delay(20);
 }

 void loop() {
 int stat_UpDown = UpDown ;   
  switch (page_num) {
   case 0:  
      if(stat_UpDown >=1 and stat_UpDown <= 3){
       UpDown_p1 (); 
      }
    break;

   case 1:
      
      Drow_Gamse ();
      page_num = 2;
    break;

   case 2:
      Move_Ball();
    break;
  
   case 3:
      Show_Reseolt();
      delay(3000);
    
      Location_x = 0 , Location_y = 0;
      Ball_count = 1 , UpDown = 1 , T_start = 250 , UpDown = 1 , Move_RL = 15 , Move_UD = 15 , time_count = 59 , Row = 25 , Row_Circut = 15;
      for(int x = 0 ; x < 9 ; x++){
        
        for(int y = 0 ; y < 9 ; y++){
          pint_Ball [x][y] = 0;
          delay(100);
        }
      }
       pint_Ball [0][0] = 0 , selcte_lvel [0] = 1;
      m = 0 , t = 0 , n = 0; 
      Slecte_lvel() , page_num = 0 , lvel_Gamse (); 
    break;

   case 4:
       tft.fillScreen(TFT_BLACK);
       tft.setCursor(10, 55);
       tft.setTextSize(2);
       tft.setTextColor(TFT_GREEN);
       if (Res == '#'){
         tft.println("Back To List....");
        
         for(int x = 10 ; x <= 215 ; x = x+1 ){
           tft.fillRect(10, 90, x, 10, TFT_GREEN); 
           delay(2);
          }
        }
      Location_x = 0 , Location_y = 0;
      Ball_count = 1 , UpDown = 1 , T_start = 250 , UpDown = 1 , Move_RL = 15 , Move_UD = 15 , time_count = 59 , Row = 25 , Row_Circut = 15;
      for(int x = 0 ; x < 9 ; x++){
        
        for(int y = 0 ; y < 9 ; y++){
          pint_Ball [x][y] = 0;
          delay(20);
        }
      }
       pint_Ball [0][0] = 0 , selcte_lvel [0] = 1;
       m = 0 , t = 0 , n = 0; 
      Slecte_lvel() , page_num = 0 , lvel_Gamse (); 
    break; 
  }
 }




void Drow_Gamse (){

  tft.fillScreen(TFT_BLACK);

  tft.fillRect(0, 0, 235, 5, TFT_WHITE);
  tft.fillRect(0, 0, 5, 225, TFT_WHITE);
  tft.fillRect(234, 0, 5, 230, TFT_WHITE);
  tft.fillRect(0, 225, 235, 5, TFT_WHITE);

  for(int x = 1 ; x <= 9 ; x++ ){ 
   tft.fillCircle(Row_Circut,15, 3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 40,3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 65,3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 90,3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 115,3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 140,3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 165,3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 190,3,TFT_YELLOW);
   tft.fillCircle(Row_Circut, 215,3,TFT_YELLOW);
   Row_Circut = Row_Circut + 25 ;
   delay(25); 
  }
  
  for(int x = 1 ; x <= 4 ; x++ ){ 
   tft.fillRect(25,Row, 30, 30, TFT_PINK);
   tft.fillRect(75, Row, 30, 30, TFT_PINK);
   tft.fillRect(125, Row, 30, 30, TFT_PINK);
   tft.fillRect(175, Row, 30, 30, TFT_PINK);
   Row = Row + 50 ;
   delay(100); 
  }

  tft.fillCircle(15, 15, 8, TFT_YELLOW);

  tft.fillRect(0, 233, 235, 5, TFT_WHITE);
  tft.fillRect(0, 315, 235, 5, TFT_WHITE);
  tft.fillRect(0, 233, 5, 315, TFT_WHITE);
  tft.fillRect(235, 233, 5, 315, TFT_WHITE);

  tft.setCursor(10, 245);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN);
  tft.println("Time:");
  tft.setCursor(80, 245);
  tft.println(time_count);
  tft.setCursor(10, 285);
  tft.println("Ball:");
  tft.setCursor(80, 285);
  tft.println(Ball_count);
  delay(250);
}


void Slecte_lvel(){
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 235, 5, TFT_WHITE);
  tft.fillRect(0, 0, 5, 225, TFT_WHITE);
  tft.fillRect(234, 0, 5, 230, TFT_WHITE);
  tft.fillRect(0, 225, 235, 5, TFT_WHITE);

  tft.setCursor(17, 25);
  tft.setTextSize(2);
  tft.setTextColor(TFT_PINK);
  tft.println("Plese Select....");

  tft.setCursor(85, 75);
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  tft.println("EASY");
 
  tft.setCursor(70, 120);
  tft.println("MIDDLE");

  tft.setCursor(85, 170);
  tft.println("HARDE");
}

void UpDown_p1 (){
 char Dir = keypad.getKey();
   if (Dir != NO_KEY) {
     switch (Dir) {
     case 'U':
     beging_musicupdwon();
     UpDown = UpDown -1;
     if(UpDown == 0){UpDown = 1; Dir = 'U';}
     else{lvel_Gamse ();}
     break;

     case 'D':
     beging_musicupdwon();
     UpDown = UpDown + 1;
     if(UpDown == 4) {UpDown = 3;}
     else{lvel_Gamse ();}
     break;

     case 'K':
     beging_musicupdwon();
     if(UpDown == 1) {T_start = 250; }
     else if(UpDown == 2) {T_start = 150; }
     else if(UpDown == 3) {T_start = 100; }
     
     lowding();
     if(millis() - t2 <= 2000){ beging_music();}
     //beging_music();
     page_num = 1;
     break;

     case '*':
     beging_musicupdwon();
     Restart();
     start_time = 0 ;
     page_num = 4 ;
     break;
     
    }
  } 
}

void lvel_Gamse (){    
 switch (UpDown) {
   case 1:
       tft.fillRect(20, 55, 200, 165, TFT_BLACK);
       tft.setCursor(70, 120);
       tft.setTextSize(3);
       tft.setTextColor(TFT_WHITE);
        tft.println("MIDDLE");

       tft.setCursor(85, 170);
       tft.setTextSize(3);
       tft.setTextColor(TFT_WHITE);
       tft.println("HARDE");
    
       tft.fillRect(75, 65, 90, 40, TFT_YELLOW);
       tft.drawRect(75, 65, 90, 40,TFT_RED);
       tft.fillCircle(35, 85, 8, TFT_YELLOW);
       tft.drawCircle(35, 85, 8,TFT_RED);
       tft.setCursor(85, 75);
       tft.setTextSize(3);
       tft.setTextColor(TFT_RED);
       tft.println("EASY");
       break;

       case 2:
       tft.fillRect(20, 55, 200, 165, TFT_BLACK);
       tft.setCursor(85, 75);
       tft.setTextSize(3);
       tft.setTextColor(TFT_WHITE);
        tft.println("EASY");

       tft.setCursor(85, 170);
       tft.setTextSize(3);
       tft.setTextColor(TFT_WHITE);
       tft.println("HARDE");
    
       tft.fillRect(65, 110, 120, 40, TFT_YELLOW);
       tft.drawRect(65, 110, 120, 40,TFT_RED);
       tft.fillCircle(35, 130, 8, TFT_YELLOW);
       tft.drawCircle(35, 130, 8,TFT_RED);
       tft.setCursor(70, 120);
       tft.setTextSize(3);
       tft.setTextColor(TFT_RED);
       tft.println("MIDDLE");
       break;

       case 3:
       tft.fillRect(20, 55, 200, 165, TFT_BLACK);
       tft.setCursor(85, 75);
       tft.setTextSize(3);
       tft.setTextColor(TFT_WHITE);
        tft.println("EASY");

       tft.setCursor(70, 120);
       tft.setTextSize(3);
       tft.setTextColor(TFT_WHITE);
       tft.println("MIDDLE");
    
       tft.fillRect(75, 160, 110, 40, TFT_YELLOW);
       tft.drawRect(75, 160, 110, 40,TFT_RED);
       tft.fillCircle(35, 180, 8, TFT_YELLOW);
       tft.drawCircle(35, 180, 8,TFT_RED);
       tft.setCursor(85, 170);
       tft.setTextSize(3);
       tft.setTextColor(TFT_RED);
       tft.println("HARDE");
       break;    
  }delay(100);   
}



void message (){

 tft.fillScreen(TFT_BLACK);
 tft.setCursor(20, 35);
 tft.setTextSize(2);
 tft.setTextColor(TFT_YELLOW);
 tft.println("Wellcom Of Gamse");

 tft.drawRect(12, 70, 225, 230,TFT_WHITE);

 tft.fillCircle(35, 155, 6, TFT_YELLOW);
 tft.drawCircle(35, 155, 6,TFT_RED);
 tft.setCursor(55, 140);
 tft.setTextSize(3);
 tft.setTextColor(TFT_BLUE);
 tft.println("Moath");

 tft.fillCircle(35, 225, 6, TFT_YELLOW);
 tft.drawCircle(35, 225, 6,TFT_RED);
 tft.setCursor(55, 215);
 tft.println("Faisal");

 
 tft.setCursor(17, 90);
 tft.setTextSize(2);
 tft.setTextColor(TFT_GREEN);
 tft.println("This Pruject Make:");
 //************************************************
 delay(1500);

 tft.setCursor(20, 35);
 tft.setTextSize(2);
 tft.setTextColor(TFT_WHITE);
 tft.println("Wellcom Of Gamse");
 delay(500);

 tft.setCursor(20, 35);
 tft.setTextSize(2);
 tft.setTextColor(TFT_RED);
 tft.println("Wellcom Of Gamse");
 delay(500);

 tft.setCursor(20, 35);
 tft.setTextSize(2);
 tft.setTextColor(TFT_GREEN);
 tft.println("Wellcom Of Gamse");
 delay(500);

 tft.setCursor(20, 35);
 tft.setTextSize(2);
 tft.setTextColor(TFT_BLUE);
 tft.println("Wellcom Of Gamse");
 delay(500);

 tft.setCursor(20, 35);
 tft.setTextSize(2);
 tft.setTextColor(TFT_PINK);
 tft.println("Wellcom Of Gamse");
 delay(500);

 tft.setCursor(20, 35);
 tft.setTextSize(2);
 tft.setTextColor(TFT_YELLOW);
 tft.println("Wellcom Of Gamse");
 delay(1000);

}


void lowding(){
 tft.fillScreen(TFT_BLACK); 
 tft.setCursor(10, 150);
 tft.setTextSize(2);
 tft.setTextColor(TFT_GREEN);
 tft.println("Loading Gamse ....");

 for(int x = 10 ; x <= 215 ; x = x+1 ){
   /*tft.setCursor(x, 150);
   tft.setTextSize(2);
   tft.setTextColor(ILI9341_GREEN);
   tft.println(".");*/
   tft.fillRect(10, 195, x, 10, TFT_GREEN);
   tone(BUZZER_PIN, x - 200 ); 
   delay(10);
   noTone(BUZZER_PIN); 
   delay(20);
 }
}

void beging_music(){
  for(int i = 0 ; i <= 12 ; i++){
   tone(BUZZER_PIN, underworld_tempo[i]);
   delay(50);
   noTone(BUZZER_PIN);
   delay(100);
  }

}

void Show_Reseolt(){
  if(m == 1){ 
  tft.fillRect(0, 0, 235, 5, TFT_WHITE);
  tft.fillRect(0, 0, 5, 225, TFT_WHITE);
  tft.fillRect(234, 0, 5, 230, TFT_WHITE);
  tft.fillRect(0, 225, 235, 5, TFT_WHITE);

  tft.setCursor(40, 40);
  tft.setTextSize(2);
  tft.setTextColor(TFT_YELLOW);
  tft.println("Your Ball:");
  tft.setCursor(170, 40);
  tft.println(Ball_count); 

  if (Ball_count <= 20 ){
    tft.fillRect(15, 100, 30, 30, TFT_BLACK);
    tft.setCursor(15, 100);
    tft.println("Low Degree..!!");
  }
  else if (Ball_count > 20 and  Ball_count <= 40){
    tft.fillRect(15, 100, 30, 30, TFT_BLACK);
    tft.setCursor(15, 100);
    tft.println("Good Degree..!!");
  }
  else if (Ball_count > 40){
    tft.setCursor(15, 100);
    tft.println("Excellent Degree..");
    tft.setCursor(95, 150);
    tft.println("^_^");
  }
  tft.fillRect(85, 185, 60, 30, TFT_YELLOW);
  tft.drawRect(85, 185, 60, 30,TFT_RED);
  tft.setCursor(105, 195);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);
  tft.println("OK");
  n = 1;
  } 
  
}

void Move_Ball(){
  char Dir = keypad.getKey();
 if (Dir != NO_KEY) {
   switch (Dir) {
    case 'R':
    beging_musicupdwon();
    start_time = 1 ;
    if(Dirc_Ball[Location_y][Location_x] == "DR" or Dirc_Ball[Location_y][Location_x] == "RL" or Dirc_Ball[Location_y][Location_x] == "UR" or Dirc_Ball[Location_y][Location_x] =="DRL" or Dirc_Ball[Location_y][Location_x] =="URL" or Dirc_Ball[Location_y][Location_x] =="UDR" or Dirc_Ball[Location_y][Location_x] =="UDRL"){
      Location_x = Location_x + 1;
       Move_RL = Move_RL + 25;
    tft.fillCircle(Move_RL, Move_UD, 8, TFT_YELLOW);
    tft.fillCircle(Move_RL-25, Move_UD, 8, TFT_BLACK);
    tft.fillRect(180, 285, 30, 30, TFT_BLACK);
    tft.setCursor(180, 285);
    //tft.println(Dirc_Ball[Location_y][Location_x]);
    if (pint_Ball[Location_y][Location_x] == 0) {
          Ball_count = Ball_count + 1;
          pint_Ball[Location_y][Location_x] = 1;
        }
        tft.fillRect(80, 285, 50, 30, TFT_BLACK);
        tft.setCursor(80, 285);
        tft.println(Ball_count);
    }
    break;

    case 'L':
    beging_musicupdwon();
    if(Dirc_Ball[Location_y][Location_x] == "DL" or Dirc_Ball[Location_y][Location_x] == "RL" or Dirc_Ball[Location_y][Location_x] == "UL" or Dirc_Ball[Location_y][Location_x] =="DRL" or Dirc_Ball[Location_y][Location_x] =="URL" or Dirc_Ball[Location_y][Location_x] =="UDL" or Dirc_Ball[Location_y][Location_x] =="UDRL"){
        Location_x = Location_x - 1;
        Move_RL = Move_RL - 25;
        tft.fillCircle(Move_RL+25, Move_UD, 8, TFT_BLACK);
        tft.fillCircle(Move_RL, Move_UD, 8, TFT_YELLOW);
        tft.fillRect(180, 285, 50, 30, TFT_BLACK);
        tft.setCursor(180, 285);
       // tft.println(Dirc_Ball[Location_y][Location_x]);
        if (pint_Ball[Location_y][Location_x] == 0) {
          Ball_count = Ball_count + 1;
          pint_Ball[Location_y][Location_x] = 1;
        }
        tft.fillRect(80, 285, 50, 30, TFT_BLACK);
        tft.setCursor(80, 285);
        tft.println(Ball_count);
      }
    break;

    case 'D':
    beging_musicupdwon();
    start_time = 1 ;
    if(Dirc_Ball[Location_y][Location_x] == "DL" or Dirc_Ball[Location_y][Location_x] == "DR" or Dirc_Ball[Location_y][Location_x] == "UD" or Dirc_Ball[Location_y][Location_x] == "DRL" or Dirc_Ball[Location_y][Location_x] =="UDR" or Dirc_Ball[Location_y][Location_x] =="UDL" or Dirc_Ball[Location_y][Location_x] =="UDRL"){
      Location_y = Location_y + 1;
      Move_UD = Move_UD + 25;
      tft.fillCircle(Move_RL, Move_UD, 8, TFT_YELLOW);
      tft.fillCircle(Move_RL, Move_UD - 25, 8, TFT_BLACK);
      tft.fillRect(180, 250, 50, 30, TFT_BLACK);
      tft.setCursor(180, 250);
      //tft.println(Dirc_Ball[Location_y][Location_x]);
      if (pint_Ball[Location_y][Location_x] == 0) {
          Ball_count = Ball_count + 1;
          pint_Ball[Location_y][Location_x] = 1;
        }
      tft.fillRect(80, 285, 50, 30, TFT_BLACK);
      tft.setCursor(80, 285);
      tft.println(Ball_count);
     }
    break; 

    case 'U':
    beging_musicupdwon();
    if(Dirc_Ball[Location_y][Location_x] == "UR" or Dirc_Ball[Location_y][Location_x] == "UL" or Dirc_Ball[Location_y][Location_x] == "URL" or Dirc_Ball[Location_y][Location_x] == "UD" or Dirc_Ball[Location_y][Location_x] =="UDR" or Dirc_Ball[Location_y][Location_x] =="UDL" or Dirc_Ball[Location_y][Location_x] =="UDRL"){
      Location_y = Location_y - 1;
      Move_UD = Move_UD - 25;
      tft.fillCircle(Move_RL, Move_UD + 25, 8, TFT_BLACK);
      tft.fillCircle(Move_RL, Move_UD, 8, TFT_YELLOW);
      tft.fillRect(180, 250, 50, 30, TFT_BLACK);
      tft.setCursor(180, 250);
      //tft.println(Dirc_Ball[Location_y][Location_x]);
      if (pint_Ball[Location_y][Location_x] == 0) {
          Ball_count = Ball_count + 1;
          pint_Ball[Location_y][Location_x] = 1;
        }
        tft.fillRect(80, 285, 50, 30, TFT_BLACK);
        tft.setCursor(80, 285);
        tft.println(Ball_count);
    }
    break; 

    case '#':
     Res = Dir;
     beging_musicupdwon();
     start_time = 0 ;
     page_num = 4 ;
    break;

    case 'B':
     beging_musicupdwon();
     Restart();
     start_time = 0 ;
     page_num = 4 ;
    break;
    
   }
    
 }if(millis()- t >T_start){t = millis(); Time_Games();} 
}

void Time_Games(){
  
  if(start_time == 1){
    time_count = time_count -1;
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN);
  tft.fillRect(80, 245, 50, 30, TFT_BLACK);
  tft.setCursor(80, 245);
  tft.println(time_count);
  }if(time_count == 0 and n == 0){tft.fillScreen(TFT_BLACK);start_time = 0;page_num = 3; m = 1;}

}

void beging_musicupdwon(){
   tone(BUZZER_PIN, 500);
   delay(50);
   noTone(BUZZER_PIN);
   delay(50);
}

void Restart(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 55);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN);
  tft.println("Restart Gamse....");
  for(int x = 10 ; x <= 215 ; x = x+1 ){
     tft.fillRect(10, 90, x, 10, TFT_RED); 
     delay(50);
    }
  //fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, 
  //uint16_t y2, uint16_t color);
  message ();
  delay(10);

}
