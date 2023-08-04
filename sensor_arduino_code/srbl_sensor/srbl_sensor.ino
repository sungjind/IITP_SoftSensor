#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

Adafruit_ADS1115 ads1115;

std_msgs::Int32 sensor_data_msg;
ros::Publisher sensor_data("srbl_sensor_data", &sensor_data_msg);

void setup(void)
{
  nh.initNode();
  nh.advertise(sensor_data);
  // Serial.begin(9600);
  ads1115.begin();
  ads1115.setGain(GAIN_TWO);

  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 
}

void loop(void)
{
  float adc0;
  adc0 = ads1115.readADC_SingleEnded(0);
  //adc1 = ads1115.readADC_SingleEnded(1);
  //adc2 = ads1115.readADC_SingleEnded(2);
  //adc3 = ads1115.readADC_SingleEnded(3);    
 
  // Serial.println(adc0,0);
  sensor_data_msg.data = adc0;
  sensor_data.publish(&sensor_data_msg);
  nh.spinOnce();
  delay(10);
}
