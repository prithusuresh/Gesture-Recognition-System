int RDArray [9] = {0};
int IArray[9] = {0};
int FSArray[9] = {0};
int start[9] = {0};

float LUT [17][9] = {{31.16666667, -10.66666667,  4.5, 17.83333333, 37.16666667, -115,  8.666666667, 30.66666667, -122.6666667},//A

  {8.888888889, 45.55555556, 15.77777778, -8,  9.777777778, -0.888888889, -7.777777778,  10.88888889, 0},//B

  { -30.44444444, -11.44444444,  -18.33333333,  -5.444444444,  72.66666667, -56.88888889,  -1.333333333,  72.66666667, -48.77777778},//C
  { -12.93333333,  36.73333333 , -8.2  , 4.533333333 , 18.06666667 , 1.8 , -2.733333333  , 51.2  , -97.33333333}, //D

  { -21.3, 69.6,  -44.4, -9.9  , 54  , -112.6  , -19.2 - 4  , -131.6}, //E


  { -15.22222222, 2.222222222, 4.666666667, 2.777777778, 76.88888889, -78.88888889,  19.22222222, -2.777777778,  -3},//F
  {35.0625 , 40.75 , -21.5625  , 64.75 , 35.4375 , -59.5 , 47.1875 , -24.4375  , -80.3125}, //G
  {52.75, -6.625,  -84.9375,  78.6875, 14.4375, -58.9375,  51.0625, -17.625, -69.875},//H
  {13.1 , -52.1 , 2.3 , -1.8  , -37.1, -7.5 , -6.2  , 37.8 , -47.6}, //K
  { -26.125 , -28.875 , -44.875 , 0.9375  , -13 , 1.1875  , -7.875  , 8.875 , -122.8125}, //L
  {12.33333333, 67.44444444, -3.222222222,  -8.111111111,  23.33333333, -99.66666667,  -14.33333333,  27.22222222, -101.1111111},//M

  {15.28571429 , 7.714285714 , 5.928571429 , -11.57142857  , 31.35714286 , -104.8571429  , -31.21428571  , 32.42857143 , -103.8571429}, //N

  {4.210526316  , 45.31578947 , -4.105263158  , -7.789473684  , 40.47368421 , -52.10526316  , 3.368421053 , 57.68421053 , -56.73684211},//O
  { -23.70588235 , -80.29411765  , -65.17647059 , 2.705882353 , 45.70588235, -65.23529412 , -9  , -32 , -129.4117647}, //P
  {35.77777778,  10  , -109.3333333  , 19.22222222 , 5, -127.7777778  , -20.55555556  , -81.66666667  , -62.11111111}, //Q

  {67.33333333, 59.66666667 , 6.666666667, 21.5  , -9.333333333  , 0.083333333 , -11.25  , -5.833333333  , -1.083333333},//R



  {5.769230769, 52.07692308 , 2.461538462 , 6.076923077 , -31.84615385  , 2.769230769 , -0.769230769  , -32.76923077  , 4.461538462}//U

};

int test[9] = {32 , 30, 32, 30, 11, 13, 12, 8 , -123};
const int mux_input = A1;
const int middleX = A2;
const int middleY = A3;
const int middleZ = A4;

char s[17] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'U'};

const int select4 = 7;
const int select5 = 6;
const int select6 = 5;

const int delta = 30;
const int BaudRate = 9600;

float mSum[9];

long prev, prev1, prev2;
int count;

void setup() {

  // put your setup code here, to run once:

  pinMode(mux_input, INPUT);
  pinMode(middleX, INPUT);
  pinMode(middleY, INPUT);
  pinMode(middleZ, INPUT);

  pinMode(select4, OUTPUT);
  pinMode(select5, OUTPUT);
  pinMode(select6, OUTPUT);

  Serial.begin(BaudRate);
  Serial.println("SETUP Ready ...");
  Serial.println("Ready to record initial array");
  while (millis() - prev < 2000 ) {

  }
  updateMux();
  updateMiddle();
  Serial.print("Initial Array is ...");
  for (int i = 0; i < 9; i++)
  {
    IArray[i] = RDArray[i];
    Serial.print(IArray[i]);
    Serial.print(" ");

  }

  while (millis() - prev < 2000 ) {}
  prev = millis();

  //Serial.println("Ready to record gestures");  //comment this for recognition mode

  Serial.println("Gonna recog in 2 sec");
  while (millis() - prev < 2000) {}                // uncomment for recognition mode
  prev = millis();

}

void loop() {
  while (millis() - prev < 3000)
  {
    updateMux();
    updateMiddle();
    for (int i = 0; i < 9; i++)
    {
      test[i] = RDArray[i] - IArray[i];
    }

  }


  for (int i = 0; i < 9; i += 1) {
    Serial.print(test[i]);
    Serial.print(" ");
  }

  manhattan(LUT, test);
  Serial.print("HERE");
  int index = recog();
  Serial.print (s[index]);
  while (1) {}
}

void manhattan (float a[17][9], int b[9])
{
  float sum = 0;
  for (int i = 0; i < 17; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      sum = sum + abs(a[i][j] - b[j]);
    }
    mSum[i] = sum;
    sum = 0;
  }
}

int recog()
{
  float mini = 1000.0;
  int j = 10;
  for (int i = 0; i < 17; i++)
  {
    if (mSum[i] < mini)
    {
      mini = mSum[i];
      j = i;
    }
  }
  return j;
}

void updateMux()

{ for (int i = 0; i < 6; i++)
  {
    digitalWrite(select4, HIGH && (i & B00000001));//7-A
    digitalWrite(select5, HIGH && (i & B00000010));//6-B
    digitalWrite(select6, HIGH && (i & B00000100));//5-c

    while (millis() - prev1 < 50 ) {} prev1 = millis();
    RDArray[i] = analogRead(mux_input);
  }
}

boolean gStart() {
  updateMux();
  updateMiddle();
  for (int i = 0; i < 9; i++)
  {
    start[i] = abs(IArray[i] - RDArray[i]);
    if (start[i] > delta)
    {
      return true;
    }
  }
  return false;

}

void updateMiddle()
{
  RDArray[6] = analogRead(middleX);
  RDArray[7] = analogRead(middleY);
  RDArray[8] = analogRead(middleZ);

  while (millis() - prev2 < 50 ) {} prev2 = millis();

}


