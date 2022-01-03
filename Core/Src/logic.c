#include "logic.h"
#include "ssd1306_tests.h"
#include "ssd1306.h"
#include "DHT.h"
#include <stdio.h>

//18к на землю 5.1к на +
#define AVERAGING_ADC 5

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern WWDG_HandleTypeDef hwwdg;

int zaradAkb;
int isLowAkb;
int page;
int buttonKeyFlg;
DHT_sensor room = {GPIOB, GPIO_PIN_4, DHT22, 1};
DHT_data t;
int errCnt;
extern int time1, time2, time3;
int cntAdcFilter;
int massAdcCanel1[AVERAGING_ADC];
int zaradAkbView;

void init(){
HAL_TIM_Base_Start_IT(&htim1);   
  HAL_ADCEx_Calibration_Start(&hadc1);  
  
  //ssd1306_TestAll();
  ssd1306_Init();
  ssd1306_Fill(Black);
  /*  ssd1306_SetCursor(2, 2);
  ssd1306_WriteString("Load.", Font_16x26, White);
  ssd1306_UpdateScreen();
  HAL_Delay(670);
  ssd1306_SetCursor(2, 2);
  ssd1306_WriteString("Load..", Font_16x26, White);
  ssd1306_UpdateScreen();
  HAL_Delay(670);
  ssd1306_SetCursor(2, 2);
  ssd1306_WriteString("Load...", Font_16x26, White);
  ssd1306_UpdateScreen();
  HAL_Delay(670);*/
  
  ssd1306_SetCursor(10, 0);
  ssd1306_WriteString("temper &", Font_11x18, White);
  ssd1306_UpdateScreen();
  ssd1306_SetCursor(10, 14);
  ssd1306_WriteString("vlaznost", Font_11x18, White);
  ssd1306_UpdateScreen();
  HAL_Delay(1900);
  page = 0;
}

void loop(){
  if(time1>30){
    time1=0;
    //button
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
      if(buttonKeyFlg==0){
        buttonKeyFlg = 1;
        page++;
        time2=0;
        if(page>=4)page=0;
      }
    }else{
      buttonKeyFlg = 0;
    }
  }
  if(time2>60000*1){
    time2=0;
    //сон
    ssd1306_Fill(Black); 
    ssd1306_SetDisplayOn(0);
    //остановка тактирования
    HAL_TIM_Base_Stop_IT(&htim1);
    HAL_TIM_Base_Stop(&htim1);
    HAL_SuspendTick();//регистр  TICKINT
    //засыпаем
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON , PWR_SLEEPENTRY_WFI);
    //просыпаемся от прерывания он осталя от кнопки
  }
  if(time3>300){
    time3=0;
    
    //read dht
    DHT_data d = DHT_getData(&room);
    //обработка ошибок
    if((d.temp == 0) || (d.hum == 0))      errCnt++;
    else errCnt = 0;
    if(errCnt > 3){
      t.temp = t.hum = 88;
    }else{
      t.temp = d.temp;
      t.hum = d.hum;
    }
    //read adc
    HAL_ADC_Start(&hadc1);//старт
    HAL_ADC_PollForConversion(&hadc1, 1000);//ожидаем окончания
    massAdcCanel1[cntAdcFilter] = (int)HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    
    //filter
    long sum = 0;
    for(int i=0;  i<=AVERAGING_ADC-1; i++){ sum += massAdcCanel1[i]; }
    cntAdcFilter = (cntAdcFilter < AVERAGING_ADC-1) ? cntAdcFilter+1 : 0; 
    zaradAkb = (int)(sum/AVERAGING_ADC);
    
    
    
    //view
    char buffTemp[5];
    ssd1306_Fill(Black);  
    switch(page){
      //temper, hum ,полоска
    case 0:
      if(t.temp<10)sprintf(buffTemp, "0%i$", (int)t.temp);
      else sprintf(buffTemp, "%i$", (int)t.temp);
      ssd1306_SetCursor(10, 2);
      ssd1306_WriteString(buffTemp, Font_16x26, White);
      
      if(t.hum<10)sprintf(buffTemp, "0%i%", (int)t.hum);
      else sprintf(buffTemp, "%i%", (int)t.hum);
      ssd1306_SetCursor((16*4)+10, 2); 
      ssd1306_WriteString(buffTemp, Font_16x26, White);
      
      //zarad akb
      //18к на землю 5.1к на +
      //3.4v-3000
      //3.6v-3200 ->
      //4.2v-3700
      if(zaradAkb<=3000)zaradAkb=3000;
      if(zaradAkb>=3700)zaradAkb=3700;
      //max 3680
      if(zaradAkb<3701)zaradAkbView = 127;
      if(zaradAkb<3600)zaradAkbView = 108;
      if(zaradAkb<3500)zaradAkbView = 90;
      if(zaradAkb<3400)zaradAkbView = 72;
      if(zaradAkb<3300)zaradAkbView = 54;
      if(zaradAkb<3200)zaradAkbView = 36;
      if(zaradAkb<3100)zaradAkbView = 18;
      //min 2950
      
      if(zaradAkbView>36){
        ssd1306_Line(0, SSD1306_HEIGHT-1, zaradAkbView, SSD1306_HEIGHT-1, White);
      }else{
        if(isLowAkb>2){
          ssd1306_Line(0, SSD1306_HEIGHT-1, zaradAkbView, SSD1306_HEIGHT-1, White);
          isLowAkb = 0;
        }else isLowAkb++;
      }
      break;
      // температура(десятые) 
    case 1:
      if(t.temp<10.0)sprintf(buffTemp, "0%.1f$C", t.temp);
      else sprintf(buffTemp, "%.1f$C", t.temp);
      ssd1306_SetCursor(13, 2);
      ssd1306_WriteString(buffTemp, Font_16x26, White);
      break;
      // влажность (десятые) 
    case 2:
      if(t.hum<10.0)sprintf(buffTemp, "0%.1f%", t.hum);
      else sprintf(buffTemp, "%.1f%", t.hum);
      ssd1306_SetCursor(17, 2);
      ssd1306_WriteString(buffTemp, Font_16x26, White);
      break;
      //заряд акб
    case 3:
      sprintf(buffTemp, "Akb: %i  ", (int)zaradAkb);
      ssd1306_SetCursor(2, 0);
      ssd1306_WriteString(buffTemp, Font_11x18, White);
      sprintf(buffTemp, "      %i  ", (int)zaradAkbView);
      ssd1306_SetCursor(2, 14);
      ssd1306_WriteString(buffTemp, Font_11x18, White);
      break;
    }
    
    ssd1306_UpdateScreen();
  }
}