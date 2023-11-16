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




auto getDown(Led led, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatLeft(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDown(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatUp(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatTopLeft(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatTopRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDownRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  else{
    getMatDownLeft(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
}

auto getDownRight(int x, int y, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatTopRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDownRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatDownLeft(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatTopRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatUp(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDown(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  else{
    getMatRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
}

auto getDownLeft(int x, int y, int* row, int*col){
  int mpuAngle= mpu6050.getAngleX();
  if (mpuAngle==0){
    getMatTopLeft(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==90){
    getMatDownLeft(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==180){
    getMatDownRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle==270){
    getMatTopRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<270){
    getMatUp(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<180){
    getMatRight(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  elif (mpuAngle<90){
    getMatDown(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
  else{
    getMatLeft(led.Row,led.Col,&row,&col);
    *row=&row;
    *col=&col;
  }
}


void setled(int matrix,int x,int y,bool Bool){
  if matrix==MATRIX_A{
    lc_a.setLed(matrix,x,y,Bool);
  }
  else{
    lc_b.setLed(matrix,x,y,Bool);
  }
}

void updateMat(int addr, int connectionx, int connectiony){
  for (led:Led){
        getDown(led,&x,&y)
        int downCoordx=&x;
        int downCoordy=&y;
        getDownRight(led,&rx,&ry)
        int downRCoordx=&rx;
        int downRCoordy=&ry;
        getDownLeft(led,&x,&y)
        int downLCoordx=&x;
        int downLCoordy=&y;
        if ((downCoordx==0 && downCoordy==0)) || ((downCoordy==9 && downCoordy==9)){
        }
        else {
          if (rand() % 2)==0{
            if ((downLCoordx==0 && downLCoordy==0)) || ((downLCoordy==9 && downLCoordy==9)){
              if downLCoordx==0{  // to matrix B
                setled(MATRIX_A, row, col, false);
                setled(MATRIX_B, BconnectionX,BconnectionY, true);
              }
              else{
                setled(MATRIX_B, row, col, false);
                setled(MATRIX_A, AconnectionX,AconnectionY, true);
              }
          }
            elif ((downRCoordx==0 && downRCoordy==0)) || ((downRCoordy==9 && downRCoordy==9)){
              if ((downLCoordx==0 && downLCoordy==0)) || ((downLCoordy==9 && downLCoordy==9)){
                if downLCoordx==0{  // to matrix B
                  setled(MATRIX_A, row, col, false);
                  setled(MATRIX_B, BconnectionX,BconnectionY, true);
                }
                else{
                  setled(MATRIX_B, row, col, false);
                  setled(MATRIX_A, AconnectionX,AconnectionY, true);              
            }
          else{
            if ((downRCoordx==0 && downRCoordy==0)) || ((downRCoordy==9 && downRCoordy==9)){
              if ((downLCoordx==0 && downLCoordy==0)) || ((downLCoordy==9 && downLCoordy==9)){
                if downLCoordx==0{  // to matrix B
                  setled(MATRIX_A, row, col, false);
                  setled(MATRIX_B, BconnectionX,BconnectionY, true);
                }
                else{
                  setled(MATRIX_B, row, col, false);
                  setled(MATRIX_A, AconnectionX,AconnectionY, true);
          }
            elif ((downLCoordx==0 && downLCoordy==0)) || ((downLCoordy==9 && downLCoordy==9)){
              if ((downLCoordx==0 && downLCoordy==0)) || ((downLCoordy==9 && downLCoordy==9)){
                if downLCoordx==0{  // to matrix B
                  setled(MATRIX_A, row, col, false);
                  setled(MATRIX_B, BconnectionX,BconnectionY, true);
                }
                else{
                  setled(MATRIX_B, row, col, false);
                  setled(MATRIX_A, AconnectionX,AconnectionY, true);
            }
          }
        }
        if (binary_search(row.begin(), row.end(),downCoordx) && binary_search(col.begin(), col.end(),downCoordy)){
          setled(MATRIX_A, row, col, false);
          setled(MATRIX_A, downCoordx, downCoordy, true);
          return
        }
        else{ 
          if (rand() % 2)==0 {
            if (binary_search(row.begin(), row.end(),downRCoordx) && binary_search(col.begin(), col.end(),downRCoordy)){
              setled(MATRIX_A, row, col, false);
              setled(MATRIX_A, downRCoordx, downRCoordy, true);
              return;
            }
            else{
                if (binary_search(row.begin(), row.end(),downLCoordx) && binary_search(col.begin(), col.end(),downLCoordy)){
                  setled(MATRIX_A, row, col, false);
                  setled(MATRIX_A, downLCoordx, downLCoordy, true);
                  return;
                }
              }
          } else{
              if (binary_search(row.begin(), row.end(),downLCoordx) && binary_search(col.begin(), col.end(),downLCoordy)){
                setled(MATRIX_A, row, col, false);
                setled(MATRIX_A, downLCoordx, downLCoordy, true);
                return;
              }
              else{
                if (binary_search(row.begin(), row.end(),downRCoordx) && binary_search(col.begin(), col.end(),downRCoordy)){
                  setled(MATRIX_A, row, col, false);
                  setled(MATRIX_A, downRCoordx, downRCoordy, true);
                  return;
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
}















