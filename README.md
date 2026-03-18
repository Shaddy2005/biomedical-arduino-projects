# Heart Rate Monitor — Arduino Simulation

## What it does
Simulates a pulse sensor signal and calculates BPM in real time,
displaying results on a 16x2 LCD. LED blinks on each detected heartbeat.
Classifies reading as Bradycardia, Normal, or Tachycardia.

## Components (simulated on Wokwi)
- Arduino Uno
- LCD 16x2 (I2C)
- Red LED + 220Ω resistor
- Simulated pulse sensor (analog signal)

## How it works
- Generates a sine wave mimicking a 75 BPM heartbeat signal
- Uses threshold-crossing detection to identify peaks
- Calculates BPM from time interval between beats (60000ms / interval)
- Classifies reading as bradycardia (<60), normal (60-100), or tachycardia (>100)

## What I learned
- Analog signal reading and threshold detection
- BPM calculation from beat intervals
- I2C LCD communication
- Clinical heart rate classification
- Git version control

## Wokwi Simulation
[Click here to view the simulation][https://wokwi.com/projects/458596672496898049]

## Medical Relevance
This is the foundation of any patient vitals monitor. The same
threshold detection concept is used in clinical pulse oximeters
and ECG R-peak detection algorithms.

## Author
Medical Engineering Student — Technical University of Mombasa