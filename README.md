# Gesture-Recognition-System-
The arduino code is for a gesture recognition system, capable of recognizing alphabetic gestures in the American Sign Language.  

The accelerometers are placed on three fingers, the thumb, index and little fingers. The thumb accelerometer channels are directly connected to the analog pins of the Arduino uno, and the other two are connected to a multiplexer. 

The Glove functions in two modes: 
1) Recognition Mode: In this mode, the glove recognizes the gesture performed after a calibration phase. 
2) Gesture Record mode: The accelerometer values are stored and further used for processing. 
