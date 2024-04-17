import subprocess
import time
import serial
import mysql.connector
import webbrowser

ser = serial.Serial('/dev/ttyS0', 9600)

try:
    # Connect to MySQL database
    db_connection = mysql.connector.connect(
        host="localhost",
        user="root",
        password="",
        database="authentication_test"
    )
    db_cursor = db_connection.cursor()
    print("Connected to database")
except mysql.connector.Error as e:
    print("Error connecting to database:", e)
    exit(1)

# Read data from serial port
try:
    while True:
        # Read line from serial
        data = ser.readline().decode().strip()
        
        if data.startswith("Flame Detected"):
            print("Flame Detected!")
            webbrowser.get('google-chrome').open_new("http://localhost/Iot/alert2.php")
            
        # Check if gas value is received
        if data.startswith("Gas Value:"):
            gas_value = int(data.split(":")[1])  # Extract gas value
            # Save gas value to database
            query = "INSERT INTO gas_values (value) VALUES (%s)"
            db_cursor.execute(query, (gas_value,))
            db_connection.commit()
            print("Gas value inserted into database:", gas_value)
            
            # Open the URL in Google Chrome using subprocess
            try:
                subprocess.Popen(["google-chrome", "http://localhost/Iot/alert.php"])
                print("Alert webpage opened")
            except Exception as e:
                print("Error opening web browser:", e)

        # Add a small delay before reading the serial port again
        time.sleep(1)

except KeyboardInterrupt:
    print("Exiting...")
    # Close serial port
    ser.close()
    # Close database connection
    db_cursor.close()
    db_connection.close()
