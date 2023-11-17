#include "Arduino.h"
#include <MPU6050_tockn.h>
#include "LedControl.h"
#include "Delay.h"

#define  MATRIX_A  1
#define MATRIX_B  0

MPU6050 mpu6050(Wire);

// Matrix
#define A_PIN_DATAIN 12
#define A_PIN_CLK 11
#define A_PIN_LOAD 10

#define B_PIN_DATAIN 9
#define B_PIN_CLK 8
#define B_PIN_LOAD 7

LedControl lc_a= LedControl(A_PIN_DATAIN, A_PIN_CLK, A_PIN_LOAD, 2); 
int AConnectionX=1;
int AConnectionY=1;

LedControl lc_b= LedControl(B_PIN_DATAIN, B_PIN_CLK, B_PIN_LOAD, 2);
int BConnectionX=8;
int BConnectionY=8;

class Led{
  int id;
  int Row;
  int Col;
  int matrix;
}

Led lightsArray[60]={
L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,
L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,
L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,
L31,L32,L33,L34,L35,L36,L37,L38,L39,L40,
L41,L42,L43,L44,L45,L46,L47,L48,L49,L50,
L51,L52,L53,L54,L55,L56,L57,L58,L59,L60,
};

int rows[8]={1,2,3,4,5,6,7,8};
int cols[8]={1,2,3,4,5,6,7,8};


auto getMatLeft(int x, int y, int* row, int* col) {
  x = x-1;
  y = y+1;
  *row=x;
  *col=y;
}

auto getMatRight(int x, int y, int* row, int* col) {
  x = x+1;
  y = y-1;
  *row=x;
  *col=y;
}

auto getMatUp(int x, int y, int* row, int* col) {
  x = x+1;
  y = y+1;
  *row=x;
  *col=y;
}

auto getMatDown(int x, int y, int* row, int* col) {
  x = x-1;
  y = y-1;
  *row=x;
  *col=y;
}

auto getMatDownLeft(int x, int y, int* row, int* col) {
  x = x-1;
  y = y;
  *row=x;
  *col=y;
}

auto getMatTopRight(int x, int y, int* row, int* col) {
  x = x+1;
  y = y;
  *row=x;
  *col=y;
}

auto getMatTopLeft(int x, int y, int* row, int* col) {
  x = x;
  y = y+1;
  *row=x;
  *col=y;
}

auto getMatDownLeft(int x, int y, int* row, int* col) {
  x = x;
  y = y-1;
  *row=x;
  *col=y;
}


auto getDown(int x, int y, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatTopLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDownLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatDownRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatTopRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatUp(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDown(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  else{
    getMatLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
}


auto getDownRight(int x, int y, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatTopRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDownRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatDownLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatTopRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatUp(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDown(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  else{
    getMatRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
}

auto getDownLeft(int x, int y, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatTopLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDownLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatDownRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatTopRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatUp(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDown(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  else{
    getMatLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
}

bool checkIfOccupied(int addr, int row, int col){
  for (led:lightsArray){
    if (led.Row==row && led.Col==col && led.matrix==addr){
      return false;
    }
  }
  return true;
}

void moveLed(Led led,int addr, int tox,int toy){
  if led.matrix==MATRIX_A{
    lc_a.setLed(MATRIX_A,led.Row,led.Col,false);
    if addr==MATRIX_A{
      lc_a.setLed(MATRIX_A,x,y,true);
      led.Row=x;
      led.Col=y;
      led.matrix=MATRIX_A;
    }
    else{
      lc_b.setLed(MATRIX_B,x,y,true);
      led.Row=x;
      led.Col=y;
      led.matrix=MATRIX_B;
    }
  else{
    lc_b.setLed(MATRIX_B,led.Row,led.Col,false);
    if addr==MATRIX_A{
      lc_a.setLed(MATRIX_A,x,y,true);
      led.Row=x;
      led.Col=y;
      led.matrix=MATRIX_A;
    }
    else{
      lc_b.setLed(MATRIX_B,x,y,true);
      led.Row=x;
      led.Col=y;
      led.matrix=MATRIX_B;
  }
  }
}

void updateMat(){
  for (led:lightsArray){
    getDown(led,&x,&y)
    int downCoordx=&x;
    int downCoordy=&y;
    // DOWN CHECK
    if (binary_search(row.begin(), row.end(),downCoordx) && binary_search(col.begin(), col.end(),downCoordy)){
      if checkIfOccupied(led.matrix, downCoordx, downCoordy){
        moveLed(led,led.matrix,downCoordx,downCoordy);
        return;
      }
    }
    else{
      if led.matrix==MATRIX_A{
        if(downCoordx==0 && downCoordy==0){
          moveLed(led,MATRIX_B,8,8);
          return;
        }
      }
      else{
        if(downCoordx==8 && downCoordy==8){
          moveLed(led,MATRIX_A,0,0);
          return;
        }
      }
    }
    if (rand() % 2)==0{
      getDownRight(led,&rx,&ry)
      int downRCoordx=&rx;
      int downRCoordy=&ry;
      getDownLeft(led,&lx,&ly)
      int downLCoordx=&lx;
      int downLCoordy=&ly;  
      //DOWN RIGHT
      if (binary_search(row.begin(), row.end(),downRCoordx) && binary_search(col.begin(), col.end(),downRCoordy)){
        if checkIfOccupied(led.matrix, downRCoordx, downRCoordy){
          moveLed(led,led.matrix,downRCoordx,downRCoordy);
          return;
        }
      }
      else{
        if led.matrix==MATRIX_A{
          if(downRCoordx==0 && downRCoordy==0){
            moveLed(led,MATRIX_B,8,8);
            return;
          }
        }
        else{
          if(downRCoordx==8 && downRCoordy==8){
            moveLed(led,MATRIX_A,0,0);
            return;
          }
        }
      }
    }
    else{
      //DOWN LEFT
      if (binary_search(row.begin(), row.end(),downLCoordx) && binary_search(col.begin(), col.end(),downLCoordy)){
         if checkIfOccupied(led.matrix, downCoordx, downCoordy){
           moveLed(led,led.matrix,downCoordx,downCoordy);
           return;
        }
      }
      else{
        if led.matrix==MATRIX_A{
          if(downLCoordx==0 && downLCoordy==0){
            moveLed(led,MATRIX_B,8,8);
            return;
          }
        }
        else{
          if(downLCoordx==8 && downLCoordy==8){
            moveLed(led,MATRIX_A,0,0);
            return;
          }
        }
      }
    }
  }
}

void setup(){
   mpu6050.begin();
   int id=1;
   int row=1;
   int col=1;
  for (led:Led){
    led.id=id;
    led.Row=row;
    led.Col=col;
    led.matrix=MATRIX_A;
    id++;
    if row>9{
      row++;
    }
    else{
      col++;
      row=1;
    }
  }
}

void loop(){
  updateMat(MATRIX_A, AConnectionX, AConnectionY);
  updateMat(MATRIX_B, BConnectionX, BConnectionY);
  delay(1000);
}
