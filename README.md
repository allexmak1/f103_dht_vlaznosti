# f103_dht_vlaznosti

Корманный прибор измерения влажности и температуры,
работающий на акб. После минуты бездействия уходит в сон и пробуждается по нажатию кнопки.
![Image alt](https://github.com/allexmak1/f103_dht_vlaznosti/main/image/image.jpg)

## Hardware 
 * CPU: STM32F103RET6 (72 MHz SYSCLK)
 * DISPLAY: ssd1306
 * Датчик влажности: DHT22
 * АКБ: Li-Ion (3,7v) 
 * зарядная плата: TP4056

### Pins

|STM32F103REV6|Description |Info          |STM32F103REV6|Description |Info|
|------------:|:-----------|:-------------|------------:|:-----------|:--------------|
|PB12         |           |               |GND          |        |       |
|PB13         |           |               |GND          |        |       |
|PB14         |           |               |3V3          |        |       |
|PB15         |           |               |PB10         |        |       |
|PA8          |           |               |PB2          |        |       |
|PA9          |           |               |PB1          |        |       |
|PA10         |           |               |PB0          |        |       |
|PA11         |           |               |PA7          |        |       |
|PA12         |           |               |PA6          |        |       |
|PA15         |           |               |PA5          |        |       |
|PB3          |           |               |PA4          |        |       |
|PB4          | GPIO      | DHT22         |PA3          |        |       |
|PB5          |           |               |PA2          |        |        |
|PB6          | I2C       | дисплей       |PA1          | EXTI1  | кнопка |
|PB7          | I2C       | дисплей       |PA0          | ADC1   | заряд с акб |
|PB8          |           |               |RESET        |        |       |


## To-Do

 - [x] Закончить проект, протестироть
 - [ ] Подключить более высокоточный датчик


## Resources

 allexmak, 2021
