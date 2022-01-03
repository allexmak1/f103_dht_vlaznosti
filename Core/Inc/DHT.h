//#include "stm32f1xx_hal.h"
#ifndef DHT_H_
#define DHT_H_

#include "main.h"

/* ��������� */
#define DHT_TIMEOUT 			10000	//���������� ��������, ����� ������� ������� ����� ������ ��������
#define DHT_POLLING_CONTROL		1	//��������� �������� ������� ������ �������
#define DHT_POLLING_INTERVAL_DHT11	2000	//�������� ������ DHT11 (0.5 �� �� ��������). ����� ��������� 1500, ����� ��������
#define DHT_POLLING_INTERVAL_DHT22	1000	//�������� ������ DHT22 (1 �� �� ��������)

/* ��������� ������������ �������� ������ */
typedef struct {
  float hum;
  float temp;
} DHT_data;

/* ��� ������������� ������� */
typedef enum {
  DHT11,
  DHT22
} DHT_type;

/* ��������� ������� ������� */
typedef struct {
  GPIO_TypeDef *DHT_Port;	        //���� ������� (GPIOA, GPIOB, etc)
  uint16_t DHT_Pin;		//����� ���� ������� (GPIO_PIN_0, GPIO_PIN_1, etc)
  DHT_type type;			//��� ������� (DHT11 ��� DHT22)
  uint8_t pullUp;			//����� �� �������� � ������� (0 - ���, 1 - ��)
  
  //�������� ������� ������ �������. �������� �� ���������!
#if DHT_POLLING_CONTROL == 1
  uint32_t lastPollingTime;       //����� ���������� ������ �������
  float lastTemp;			 //��������� �������� �����������
  float lastHum;			 //��������� �������� ���������
#endif
} DHT_sensor;


/* ��������� ������� */
DHT_data DHT_getData(DHT_sensor *sensor); //�������� ������ � �������

#endif