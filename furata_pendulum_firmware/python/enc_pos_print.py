import serial
import time
import matplotlib.pyplot as plt
import numpy as np

# Configure the serial connection (adjust 'COM3' to your Arduino port)
arduino_port = 'COM3'  # Replace with your Arduino's serial port
baud_rate = 9600        # Baud rate set in the Arduino code

# Open serial connection to Arduino
try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    print(f"Connected to Arduino on port {arduino_port} at {baud_rate} baud.")
except serial.SerialException:
    print(f"Failed to connect to Arduino on port {arduino_port}. Make sure the port is correct and the Arduino is plugged in.")
    exit()

# Collect data and plot in real-time
print("Collecting data in real-time...")

while True:
    angle = ser.readline().decode('utf-8').strip()
    print(angle)

# Close the serial connection once done

