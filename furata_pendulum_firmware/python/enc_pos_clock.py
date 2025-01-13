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

# Set up the figure for the polar plot
fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
ax.set_ylim(0, 1)  # Set the radius limit to give space to the plot
ax.set_yticks([])

# Plot configuration
ax.set_title('Rotary Encoder Position (Real-Time)', va='bottom')
ax.grid(True)

# Create a point on the polar plot to represent the current position
point, = ax.plot([], [], 'bo', markersize=10)

# Function to update the plot
def update_plot(angle):
    point.set_data(np.radians(angle), 1)  # Update the angle and keep the radius at 1
    plt.draw()  # Redraw the plot
    plt.pause(0.01)  # Pause briefly to update the plot
    print(angle)

# Collect data and plot in real-time
print("Collecting data in real-time...")

try:
    while plt.fignum_exists(fig.number):  # Check if the figure window is still open
        if ser.in_waiting > 0:
            # Read the incoming data from Arduino
            data = ser.readline().decode('utf-8').strip()
            if data:
                try:
                    # Convert data to a float representing the encoder position (degrees)
                    angle = float(data)

                    # Normalize the angle if necessary (optional step depending on your encoder setup)
                    # e.g., angle = angle % 360  # Ensure the angle stays within 0 to 360 degrees

                    # Update the polar plot with the new angle
                    update_plot(angle)
                except ValueError:
                    pass  # Ignore invalid data
except KeyboardInterrupt:
    print("Data collection stopped.")

# Close the serial connection once done
ser.close()
