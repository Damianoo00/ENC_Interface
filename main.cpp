/**
 * @file main.cpp
 * @author Damian Płaskowicki (damian.plaskowicki.stud@pw.edu.pl)
 * @brief Rotary Encoder Controler with i2c comunication on Arduino
 * @version 0.1
 * @date 2022-05-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/sensors.h"
#include "../include/uart.h"
#include "../include/i2c.h"
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Wire.h>

/**
 * @brief define or remove correct line to switch any mode {#define [param]}
 * @param LOG define to enabel logging
 * @param WORK  define to send speed value via i2c
 */
#define WORK

/***** POUT *****/
#define ENC_A A0
#define ENC_B A1

/*** UART params***/
#define BAUD 115200
#define TIMEOUT 10

/*** I2C params ***/
#define I2C_NODE_ADRESS 8

static int speed_sensor = 0;

RotaryEncoder encoder(ENC_A, ENC_B, RotaryEncoder::LatchMode::TWO03);

void setup()
{
  uart_begin(BAUD, TIMEOUT);
  i2c_begin_slave(I2C_NODE_ADRESS);
}

void loop()
{

  speed_sensor = GetSpeed(&encoder);

#ifdef WORK
  update_message(speed_sensor);
#endif

#ifdef LOG
  /************************** Set header and params to log **********************************/
  const String header = "time,speed_sensor";
  const long log_parametrs[] = {millis(), speed_sensor};
  /********************************************************************************************/

  const int NumOfParams = sizeof(log_parametrs) / sizeof(log_parametrs[0]);
  log_uart(header, log_parametrs, NumOfParams);
#endif
}