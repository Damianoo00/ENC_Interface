#include "../include/sensors.h"
#include "../include/uart.h"
#include "../include/i2c.h"
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Wire.h>

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

  speed_sensor = get_speed(&encoder);

#ifdef WORK
  update_message(100);
#endif

#ifdef LOG
  /*** Set params to log ***/
  const long log_parametrs[] = {millis(), speed_ref, speed_sensor, 0, curr_sensor, PIctrl_curr.y};

  const int num_of_params = sizeof(log_parametrs) / sizeof(log_parametrs[0]);
  log_uart(log_parametrs, num_of_params);
#endif
}