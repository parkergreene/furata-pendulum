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

# Initialize data storage lists
timestamps = []
data_values = []

# Start time tracking
start_time = time.time()

print("Collecting data for 20 seconds...")

# Collect data for 20 seconds
while time.time() - start_time < 20:
    if ser.in_waiting > 0:
        # Read the incoming data from Arduino
        data = ser.readline().decode('utf-8').strip()
        if data:
            # Append data and timestamp
            timestamps.append(time.time() - start_time)  # Store elapsed time
            data_values.append(float(data))  # Assuming Arduino sends numeric values

# Close the serial connection
ser.close()

# Adjust the encoder position to represent a pendulum with 0 degrees at the straight down position
# Assuming the encoder's 0-360 degrees is mapped to a 0-180 degree swing
adjusted_positions = [((deg + 180) % 360) - 180 for deg in data_values]  # Adjust for the straight down position

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(timestamps, adjusted_positions, label="Pendulum Position", color='b')

# Set the plot title and labels
plt.title('Pendulum Position Over Time (0° is straight down)')
plt.xlabel('Time (seconds)')
plt.ylabel('Position (Degrees)')
plt.axhline(0, color='k', linestyle='--', label='Zero Position (Straight Down)')  # Line at 0 degrees (straight down)
plt.grid(True)
plt.legend()

# Show the plot
plt.show()
