#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

Adafruit_ADS1115 ads1115;

const int min_sensor = 300;
const int max_sensor = 20000;

std_msgs::Float32 sensor_data_msg0, sensor_data_msg1, sensor_data_msg2;
ros::Publisher sensor_data_l0("srbl_sensor_data_l0", &sensor_data_msg0);
ros::Publisher sensor_data_l1("srbl_sensor_data_l1", &sensor_data_msg1);
ros::Publisher sensor_data_l2("srbl_sensor_data_l2", &sensor_data_msg2);

void setup(void)
{
  nh.initNode();
  nh.advertise(sensor_data_l0);
  nh.advertise(sensor_data_l1);
  nh.advertise(sensor_data_l2);
  // Serial.begin(9600);
  ads1115.begin();
  ads1115.setGain(GAIN_ONE);

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
  float adc0, adc1, adc2;
  adc0 = ads1115.readADC_SingleEnded(0);
  adc1 = ads1115.readADC_SingleEnded(1);
  adc2 = ads1115.readADC_SingleEnded(2);
  //adc3 = ads1115.readADC_SingleEnded(3);    

  //sensor_data_msg0.data = adc0;
  //sensor_data_msg1.data = adc1;
  //sensor_data_msg2.data = adc2;
  sensor_data_msg0.data = (adc0-min_sensor)/(max_sensor-min_sensor);
  sensor_data_msg1.data = (adc1-min_sensor)/(max_sensor-min_sensor);
  sensor_data_msg2.data = (adc2-min_sensor)/(max_sensor-min_sensor);
  sensor_data_l0.publish(&sensor_data_msg0);
  sensor_data_l1.publish(&sensor_data_msg1);
  sensor_data_l2.publish(&sensor_data_msg2);
  nh.spinOnce();
  delay(10);
}
