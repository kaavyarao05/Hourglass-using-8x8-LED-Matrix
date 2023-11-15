#include "Arduino.h"
#include <MPU6050_tockn.h>
#include "LedControl.h"
#include "Delay.h"

#define  MATRIX_A  1
#define MATRIX_B  0

MPU6050 mpu6050(Wire);

// Values are 260/330/400
#define ACC_THRESHOLD_LOW -25
#define ACC_THRESHOLD_HIGH 25

// Matrix
#define A_PIN_DATAIN 12
#define A_PIN_CLK 11
#define A_PIN_LOAD 10

#define B_PIN_DATAIN 9
#define B_PIN_CLK 8
#define B_PIN_LOAD 7

LedControl lc_a= LedControl(A_PIN_DATAIN, A_PIN_CLK, A_PIN_LOAD, 2); 
int AmatConnectionX=1;
int AmatConnectionY=1;

LedControl lc_b= LedControl(B_PIN_DATAIN, B_PIN_CLK, B_PIN_LOAD, 2);
int BmatConnectionX=8;
int BmatConnectionY=8;

int rows[8]={1,2,3,4,5,6,7,8};
int cols[8]={1,2,3,4,5,6,7,8};

// x=row y=col
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
    getMatLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDown(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatUp(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatTopLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatTopRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDownRight(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
  else{
    getMatDownLeft(x,y,&row,&col);
    *row=&row;
    *col=&col;
  }
}

auto getDownRight(int x, int y, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatTopRight(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDownRight(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatDownLeft(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatTopRight(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatUp(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatRight(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDown(x,y);
    *row=&row;
    *col=&col;
  }
  else{
    getMatRight(x,y);
    *row=&row;
    *col=&col;
  }
}

auto getDownLeft(int x, int y, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatTopLeft(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDownLeft(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatDownRight(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatTopRight(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatUp(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatRight(x,y);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDown(x,y);
    *row=&row;
    *col=&col;
  }
  else{
    getMatLeft(x,y);
    *row=&row;
    *col=&col;
  }
}

bool isOn(row,col){
  return 
}

void updateMatA(){
  for (row:rows){
    for (col:cols){
      if (isOn(row,col)){
        if (row==AmatConnectionX) && (col==AmatConnectionY){
          if mpu6050.getAngleX()==90{
            lc_a.setLed(MATRIX_A, row, col, false);
          }
        }
        getDown(row,col,&x,&y)
        int downCoordx=&x;
        int downCoordy=&y;
        if (binary_search(row.begin(), row.end(),downCoordx) && binary_search(col.begin(), col.end(),downCoordy)){
          lc_a.setLed(MATRIX_A, row, col, false);
          lc_a.setLed(MATRIX_A, downCoordx, downCoordy, true);
          return
        }
        else{ 
          if (rand() % 2)==0 {
            getDownRight(row,col,&x,&y)
            int downRCoordx=&x;
            int downRCoordy=&y;
            if (binary_search(row.begin(), row.end(),downRCoordx) && binary_search(col.begin(), col.end(),downRCoordy)){
              lc_a.setLed(MATRIX_A, row, col, false);
              lc_a.setLed(MATRIX_A, downRCoordx, downRCoordy, true);
              return;
            }
            else{
                getDownLeft(row,col,&x,&y)
                int downLCoordx=&x;
                int downLCoordy=&y;
                if (binary_search(row.begin(), row.end(),downLCoordx) && binary_search(col.begin(), col.end(),downLCoordy)){
                  lc_a.setLed(MATRIX_A, row, col, false);
                  lc_a.setLed(MATRIX_A, downLCoordx, downLCoordy, true);
                  return;
                }
              }
          } else{
              getDownLeft(row,col,&x,&y)
              int downLCoordx=&x;
              int downLCoordy=&y;
              if (binary_search(row.begin(), row.end(),downLCoordx) && binary_search(col.begin(), col.end(),downLCoordy)){
                lc_a.setLed(MATRIX_A, row, col, false);
                lc_a.setLed(MATRIX_A, downLCoordx, downLCoordy, true);
                return;
              }
              else{
                getDownRight(row,col,&x,&y)
                int downRCoordx=&x;
                int downRCoordy=&y;
                if (binary_search(row.begin(), row.end(),downRCoordx) && binary_search(col.begin(), col.end(),downRCoordy)){
                  lc_a.setLed(MATRIX_A, row, col, false);
                  lc_a.setLed(MATRIX_A, downRCoordx, downRCoordy, true);
                  return;
              }
          }
      }
    }
  }
}

void setup(){
   mpu6050.begin();
}

void loop(){
}















