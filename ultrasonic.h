#define RIGHT_TRIGPIN  7
#define RIGHT_ECHOPIN  6
#define LEFT_TRIGPIN   4
#define LEFT_ECHOPIN   5

const int trials = 20;

struct ultrasensor{
  int trigpin;
  int echopin;
  float distances[trials];
  int distindex;
  float averageDist;
  float distCM;
} Rsensor, Lsensor;

void sensorSetup(ultrasensor sensor, int trigpin, int echopin){
  sensor.trigpin = trigpin;
  sensor.echopin = echopin;
  for (int i = 0; i < trials; i++){ sensor.distances[i] = 150; }
  sensor.distindex = 0;
  sensor.averageDist = 150;
  sensor.distCM = (0.0343 * sensor.averageDist) / 2;
  pinMode(sensor.trigpin, OUTPUT);
  pinMode(sensor.echopin, INPUT);
}
void ultrasonicSetup(){
  sensorSetup(Rsensor, RIGHT_TRIGPIN, RIGHT_ECHOPIN);
  sensorSetup(Lsensor, LEFT_TRIGPIN, LEFT_ECHOPIN);
}

float sendPing(ultrasensor sensor){
    digitalWrite(sensor.trigpin, LOW);
    delayMicroseconds(10);
    digitalWrite(sensor.trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(sensor.trigpin, LOW);
    float traveltime = pulseIn(sensor.echopin, HIGH); 
    sensor.distances[sensor.distindex] = traveltime;
    sensor.distindex++;
    sensor.distindex = sensor.distindex % trials;
    float acc = 0;
    for (int i = 0; i < trials; i++){
      acc += sensor.distances[i];
    }
    sensor.averageDist = acc / trials;
    sensor.distCM = (0.0343 * sensor.averageDist) / 2;
    return traveltime;
}
