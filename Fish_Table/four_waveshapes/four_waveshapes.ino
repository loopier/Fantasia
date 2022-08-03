#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// This script implements 4 waveforms based on arrays
// describing the mean velocity and orientation of a 
// group of particles.
// v1 and v2 are two different velocities phi1 and 2 are two different orientation

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=691,379
AudioSynthWaveform       waveform1;      //xy=692,283
AudioSynthWaveform       waveform4;      //xy=691,573
AudioSynthWaveform       waveform3;      //xy=692,475
AudioEffectDigitalCombine combine1;       //xy=939,342
AudioEffectDigitalCombine combine2;       //xy=947,492
AudioOutputI2S           i2s1;           //xy=1189,401
AudioConnection          patchCord1(waveform2, 0, combine1, 1);
AudioConnection          patchCord2(waveform1, 0, combine1, 0);
AudioConnection          patchCord3(waveform4, 0, combine2, 1);
AudioConnection          patchCord4(waveform3, 0, combine2, 0);
AudioConnection          patchCord5(combine1, 0, i2s1, 0);
AudioConnection          patchCord6(combine2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=974,165
// GUItool: end automatically generated code

// GUItool: end automatically generated code

//SD CARD PINS
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

int PotPort1 = A0; // select the input pins for the potentiometers
int PotPort2 = A1;
int PotPort3 = A2;
int PotPort4 = A3;

int Boton1 = 2;    // pushbutton connected to digital pinS
int Boton2 = 5; 
int Boton3 = 25; 
int Boton4 = 27; 
int Gate1 = 3; 
int Gate2 = 6; 
int Encoderbut = 4;

 // Variables to store port values 
float PotValue1 = 0; 
float PotValue2 = 0;
float PotValue3 = 0;
float PotValue4 = 0;
int BotonValue1 = 0;   
int BotonValue2 = 0;
int BotonValue3 = 0;
int BotonValue4 = 0;
int GateValue1 = 0;
int GateValue2 = 0;
int EncoderbutValue = 0;



const int16_t v1_array[256] = {-18317, -8507, 1624, 178, -8197, -10834, -13313, -15176, -16759,
-18391, -19843, -20636, -21158, -21500, -21931, -22365, -22595, -23013, -23157, -23561, 
-24020, -24257, -24493, -24024, -24306, -25886, -27201, -27584, -27809, -28338, -29520, 
-30722, -30687, -30393, -30365, -30991, -31921, -31583, -31030, -31681, -32604, -32768, 
-32058, -31497, -31423, -30648, -29462, -27731, -24909, -21081, -17061, -12863, -9943,
-7478, -4865, -2743, 155, 3490, 5805, 7619, 8992, 10630, 12605, 14289, 15797, 17085, 
18480, 20417, 22629, 24827, 26368, 27611, 28975, 30194, 31080, 31938, 32734, 32768, 
32552, 32262, 31765, 31129, 30441, 29581, 28465, 27029, 25131, 22949, 20704, 18594, 
16869, 15496, 14610, 14053, 13633, 13488, 13817, 14041, 14143, 14235, 14230, 14112, 
13952, 13960, 14052, 14439, 14605, 15402, 16406, 17082, 18377, 19622, 20716, 21403, 
21352, 20839, 19949, 18828, 17349, 15334, 13057, 10670, 8034, 5224, 2359, -440, -3058,
-5737, -8316, -10456, -12372, -13821, -15108, -15804, -15164, -14109, -12228, -9191, 
-5891, -2556, 1137, 4922, 8848, 12267, 15227, 17991, 20490, 22618, 23934, 25049, 25929,
26091, 26195, 25793, 24881, 24037, 22857, 21597, 20072, 18276, 16362, 14390, 12624, 10633,
8557, 6490, 4502, 2692, 757, -843, -2088, -2990, -3577, -3426, -3157, -2066, -236, 1379,
2952, 5261, 7204, 8641, 10164, 11715, 12906, 13858, 14666, 15467, 15675, 16015, 16934, 
17871, 18591, 18886, 18917, 18682, 18460, 17985, 16875, 15481, 14030, 12458, 10692, 
8978, 7345, 5756, 4194, 2792, 1666, 738, -56, -599, -209, 230, 1365, 2435, 3364, 4227, 
5452, 6594, 7544, 8595, 10007, 11472, 13101, 14400, 15432, 16682, 17964, 18954, 19566, 
20163, 20126, 19686, 19041, 18211, 17585, 16379, 14782, 12933, 10661, 8393, 6224, 3937, 
1264, -1255, -3376, -4913, -6327, -7932, -9668, -11171, -12639, -13968, -15141, -15843};


const int16_t v2_array[256] = {-14063, -14660, -14562, -14812, -14614, -13881, -13787, -13106, 
-12296, -11642, -10235, -8269, -6209, -3717, -900, 1212, 3771, 6664, 9532, 12108, 14608, 17164,
19571, 22302, 24613, 26706, 28367, 29522, 30194, 30573, 30887, 30637, 29428, 28116, 26806, 25631,
23963, 21985, 20152, 18176, 15835, 13387, 11009, 9090, 6586, 3703, 1113, -540, -1020, -1159,
-1971, -3550, -4234, -4301, -4090, -4435, -4737, -4502, -4503, -4701, -4761, -4083, -2846,
-1376, 428, 2462, 4981, 7702, 11204, 14512, 17838, 20750, 23478, 26142, 28343, 30210, 31084,
30997, 30389, 29232, 27784, 26236, 24176, 21756, 19177, 16327, 13332, 10268, 7014, 3393, -408, 
-4095, -7560, -11039, -14489, -17136, -19508, -22217, -24134, -24867, -25700, -27025, -28870,
-29771, -30683, -31839, -32767, -32269, -31476, -31161, -29741, -28412, -26481, -24624, -23705,
-22155, -19272, -14757, -10924, -8374, -4870, -1644, 1718, 5367, 9107, 14586, 19144, 22409, 
26180, 28396, 30459, 32160, 32767, 32150, 31076, 30057, 28298, 26056, 23696, 21168, 18678, 
16137, 13696, 11395, 8892, 6557, 4604, 2821, 750, -1429, -3061, -4288, -5778, -7505, -9254, 
-10909, -12503, -14285, -16177, -18170, -20106, -21808, -22894, -23393, -24248, -25253, -26003,
-26634, -26679, -26465, -26769, -27495, -28168, -28874, -29258, -29826, -30736, -31608, -32213, 
-32277, -31957, -31643, -31101, -29642, -27721, -26044, -24318, -20778, -17321, -13837, -9437, 
-4483, -1152, 338, 5081, 10612, 14925, 16550, 17699, 19243, 19968, 20091, 20074, 20149, 19648, 
18724, 17417, 15536, 13480, 11558, 9492, 7757, 6489, 4931, 3516, 2231, 1131, -127, -1354, -2211, 
-2137, -1307, -557, 826, 3733, 6680, 9851, 12701, 14990, 17097, 19033, 21228, 23113, 24223, 25054,
25388, 25333, 25023, 24334, 23168, 21612, 19689, 17348, 14581, 11547, 8515, 5434, 2280, -918,
-4046, -7081, -9846, -12606, -15608, -17577, -19059};

const int16_t phi1_array[256] =  {21774, 19862, 18714, 18866, 20243, 22013, 23116, 22653, 
20199, 16525, 12576, 9537, 7807, 6905, 5880, 4660,3171, 1439, -955, -4181, -8185, -12761,
-17459, -22675, -27109, -29937, -29186, -24614, -17684, -10087, -3037, 2881, 7589, 11266,
13478, 14495, 14799, 15159, 16237, 17808, 19900, 21983, 23846, 25332, 26534, 27513, 27641, 
26970, 25918, 24854, 24266, 23999, 24042, 24078, 24074, 23971, 24016,23942, 23519, 22552, 
21385, 20854, 21250, 22561, 24401, 26413, 27859, 28682, 28860, 28986, 29100, 29066, 28814,
28193, 27532, 26991, 26752, 26886, 27547, 27997, 27954, 27506, 27110, 27507, 28623, 30103, 
31120, 31482, 31417, 31375, 31510, 31853, 32222, 32346, 32456, 32531, 32711, 32768, 32757, 
32413, 31867, 31032, 29984, 28857, 28199, 28269, 28932, 29793, 30462, 30745, 30523, 30140, 
29554, 29131, 28691, 27895, 27293, 26809, 26324, 26372, 26945, 27942, 28738, 29309, 29188,
28596, 27730, 27185, 27335, 27745, 28131, 27745, 26889, 25683, 24909, 25168, 26121, 27371, 
28165, 28224, 27440, 25749, 23339, 20749, 18648, 17044, 16761, 17597, 18826, 20033, 20794, 
20987, 20396, 19241, 16881, 13450, 8898, 4681, 1684, 757, 2307, 5432, 8922, 11261, 12330, 
11510, 8246, 2477, -5625, -15091, -23973, -30166, -32768, -32026, -28788, -24747, -20523, 
-15793, -10958, -6914, -4215, -2986, -2546, -1338, 1118, 5002, 8983, 11975, 13569, 14036, 
13910, 14319, 15947, 18731, 22356, 25790, 28129, 28982, 28654, 27673, 26810, 26312, 26041,
25624, 24867, 23959, 23173, 23094, 23709, 24537, 25317, 25977, 26226, 26175, 25615, 24595,
23645,23225, 23651, 24367, 24589, 23991, 22682, 21007, 20039, 20109, 21196, 22796, 24564, 
26094, 27328, 28440, 29495, 30276, 30567, 30567, 30409,30422, 30324, 30341, 30216, 29683, 
29191, 28761, 28732, 29264, 30262, 31422, 32216, 32319, 31707, 30837, 30014, 29660, 29715, 
30033};


const int16_t phi2_array[256] =  {24916, 23728, 23043, 22670, 22097, 21055, 19805, 18724, 
18615, 19461, 20600, 21674, 22582, 22925, 22855, 22084, 20680, 19373, 18795, 19382, 20367, 
20671, 19849, 18048, 15743, 14411, 14507, 16003, 18205, 20638, 22743, 24441, 25971, 27423,
28497, 28898, 28898, 28681, 28699, 28563, 28587, 28415, 27681, 27005, 26413, 26373, 27105, 
28478, 30075, 31167, 31309, 30467, 29269, 28136, 27650, 27726, 28163, 28252, 28264, 27619, 
26769, 25480, 24202, 22911, 21831, 21142, 21175, 21887, 22777, 23685, 24109, 23815, 22809, 
21788, 21297, 21946, 23853, 26419, 28563, 29467, 29208, 28178, 26559, 24395, 21769, 18395, 
14448, 10510, 7037, 5482, 6604, 9943, 13713, 15707, 15421, 13414, 10954, 9270, 8803, 9742, 
11236, 12080, 12369, 12646, 13515, 15168, 16632, 16191, 13354, 7798, 861, -5877, -11034, -14548,
-17726, -21712, -26074, -29866, -32128, -32767, -31977, -29733, -26639, -23148, -20160, -17688,
-15327, -13260, -11291, -9975, -9690, -10599, -11845, -11940, -10042, -6754, -2859, 163, 1216, 
1023, -155, -1540, -2760, -2675, 29, 5067, 11022, 15913, 18446, 18185, 16116, 13886, 12964, 13412,
14884, 16450, 16848, 16636, 15722, 14437, 13582, 12625, 11339, 9837, 8921, 9002, 9622, 11116, 13284,
16287, 19744, 23139, 24923, 24926, 23188, 20976, 19965, 21213, 24148, 27441, 29706, 30482, 30255,
29279, 28299, 27567, 27068, 26558, 26040, 25474, 25440, 25982, 26895, 28045, 29228, 30007, 30243,
29951, 29058, 28284, 27529, 27386, 27789, 28418, 29327, 30333, 31326, 32265, 32767, 32466, 31215,
29030, 26403, 24071, 23026, 23215, 24426, 25529, 25632, 24805, 23671, 22956, 22907, 23690, 24729, 
25749, 26008, 25935, 26083, 26918, 27939, 28981, 29269, 28848, 27441, 25495, 23700, 22389, 22228, 
23252, 24996, 26605, 27817, 27759, 25824, 21650, 15770, 9129, 3780, 1658, 3606, 8216, 13430, 17054, 
17280, 13868};


void setup() {
//Audio setup
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(Boton1, INPUT_PULLUP);    // sets the digital pin 2 as input
  pinMode(Boton2, INPUT_PULLUP); 
  pinMode(Boton3, INPUT_PULLUP); 
  pinMode(Boton4, INPUT_PULLUP); 
  pinMode(Gate1, INPUT_PULLUP); 
  pinMode(Gate2, INPUT_PULLUP); 
  pinMode(Encoderbut, INPUT_PULLUP); 



  pinMode(30, OUTPUT);    
  pinMode(32, OUTPUT); 
  pinMode(33, OUTPUT); 
  pinMode(28, OUTPUT); 
  pinMode(31, OUTPUT); 
  pinMode(26, OUTPUT); 
  pinMode(29, OUTPUT); 
  pinMode(9, OUTPUT); 

  // Wavetable variables
  int wavetype = WAVEFORM_ARBITRARY;
  waveform1.begin(wavetype);
  waveform2.begin(wavetype);
  waveform3.begin(wavetype);
  waveform4.begin(wavetype);
  
  waveform1.amplitude(1);
  waveform2.amplitude(1);
  waveform3.amplitude(1);
  waveform4.amplitude(1);
}


void loop() {
  
 
  BotonValue1 = digitalRead(Boton1);   
  BotonValue2 = digitalRead(Boton2); 
  BotonValue3 = digitalRead(Boton3); 
  BotonValue4 = digitalRead(Boton4); 
  GateValue1 = digitalRead(Gate1); 
  GateValue2 = digitalRead(Gate2); 
  EncoderbutValue = digitalRead(Encoderbut); 



  // read the value from the pots:
  PotValue1 = (float)analogRead(PotPort1) / 1023.0;
  PotValue2 = (float)analogRead(PotPort2) / 1023.0; 
  PotValue3 = (float)analogRead(PotPort3) / 1023.0; 
  PotValue4 = (float)analogRead(PotPort4) / 1023.0;  


// it is possible to modify the range of frequency variation for each waveform 
  waveform1.frequency(PotValue1*500);
  waveform2.frequency(PotValue3*600);
  waveform3.frequency(PotValue2*200);
  waveform4.frequency(PotValue4*300);

  // you can try this other setup!
  //waveform1.frequency(PotValue1*60);
  //waveform2.frequency(PotValue3*600);
  //waveform3.frequency(PotValue2*100);
  //waveform4.frequency(PotValue4*150);
  

  waveform1.arbitraryWaveform(v1_array, 400);
  waveform2.arbitraryWaveform(v2_array, 400);
  waveform3.arbitraryWaveform(phi1_array, 400);
  waveform4.arbitraryWaveform(phi2_array, 400);


  Serial.print("Potes:");
  Serial.print(PotValue1);
  Serial.print("\t"); 
  Serial.print(PotValue2);
  Serial.print("\t"); 
  Serial.print(PotValue3);
  Serial.print("\t"); 
  Serial.println(PotValue4);

  
}