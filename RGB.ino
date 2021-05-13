const int redPin = 5;
const int greenPin = 6;
const int bluePin = 7;
const int echoPin = 9;
const int trigPin = 8;

int distance;

void setup() {

  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
}

void loop() {
  sendPing();
  int duration = pulseIn(echoPin,HIGH);
  distance = 0.034 * duration / 2;
  distance = clamp(distance, 0, 50);

  // mappa distance til rgb value-ið
  int mapped_dist = map(distance,0,50,0,1530);

  // rautt fade in
  if(mapped_dist <= 255){
    analogWrite(redPin, mapped_dist);
  }
  // blátt fade out
  else if(mapped_dist > 255 && mapped_dist <= 510){
    // mappa í 255-0 svo að ég gæti notað distance value-ið til að lækka í einhverjum lit
    int blue_mapped = map(mapped_dist,256,510,255,0);
    analogWrite(bluePin, blue_mapped);
  }
  // grænn fade in
  else if(mapped_dist > 510 && mapped_dist <= 765){
    analogWrite(greenPin, mapped_dist - 510);
  }
  // rautt fade út
  else if(mapped_dist > 765 && mapped_dist <= 1020){
    // mappa í 255-0 svo að ég gæti notað distance value-ið til að lækka í einhverjum lit
    int red_mapped = map(mapped_dist,766,1020,255,0);
    analogWrite(redPin, red_mapped);
  }
  // blátt fade in
  else if(mapped_dist > 1020 && mapped_dist <= 1275){
    analogWrite(bluePin, mapped_dist - 1020);
  }
  // grænt fade út
  else if(mapped_dist > 1275 && mapped_dist <= 1530){
    // mappa í 255-0 svo að ég gæti notað distance value-ið til að lækka í einhverjum lit
    int green_mapped = map(mapped_dist,1276,1530,255,0);
    analogWrite(greenPin, green_mapped);
  }
  
}

void sendPing(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
}

// notað til að festa value-ið á distance breytuni svo það fari ekki yfir eða undir min eða maxið sem ég set á það
int clamp(int VAL, int min, int max) {
  if(VAL <= min){
    VAL = min;
    return VAL;
  }
  else if(VAL >= max){
    VAL = max;
    return VAL;
  }
  else{
    return VAL;
  }
}
