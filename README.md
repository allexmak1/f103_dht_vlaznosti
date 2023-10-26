# f103_dht_vlaznosti

Корманный прибор измерения влажности и температуры,
работающий на акб.

## Hardware 
 * STM32F103RET6 (72 MHz SYSCLK)
 * датчик влажности DHT
 * дисплей
 * аккумулятор 

### Pins

|LCD Board|Nucleo |STM32F411RE| Description       |
| ------- |:-----:| ---------:|	--------------:	  |
|VCC      |CN6-4  | -         | 3.3V              |
|GND      |CN6-6  | -         | GND	              |
|CS       |CN5-3  | PB6       | D10, Chip Select  |
|RST      |CN9-5  | PB5       | D4,  LCD Reset    |
|DC       |CN7-21 | PB7       | Data control      |
|MOSI     |CN5-4  | PA7       | D11, MOSI         |
|SCK      |CN5-6  | PA5       | D13, SCK          |
|LED      |CN7-5  | VDD       | 5V                |
|MISO     |CN5-5  | PA6       | D12, MISO         |

## To-Do

 - [x] Закончить проект, протестироть
 - [ ] Подключить более высокоточный датчик


## To-Do

 - [x] Partial framebuffer 
 - [x] Touchscreen
 - [x] Graphs
 - [ ] FreeRTOS 

## Resources

 allexmak, 2021
