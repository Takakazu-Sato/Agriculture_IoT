#define PWM_PIN 3

int prev_val = LOW;
long high_level_start = 0L;
long high_level_end = 0L;
long low_level_start = 0L;
long low_level_end = 0L;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, INPUT);
}

void loop() {
  long cycle_start_time = millis();
  int pin_in = digitalRead(PWM_PIN);

  if(pin_in == HIGH){
    if(prev_val == LOW){
      long time_high = high_level_end - high_level_start;
      long time_low = low_level_end - low_level_start;
      long ppm = 5000*(time_high - 0.002)/(time_high + time_low - 0.004);
      Serial.println("PPM = " + String(ppm));
      high_level_start = cycle_start_time;
      prev_val = HIGH;
    }else{
        high_level_end = cycle_start_time;
    }
  }else{
      if(prev_val == HIGH){
        low_level_start = cycle_start_time;
        prev_val = LOW;
    }else{
      low_level_end = cycle_start_time;
       } 
    }
}
