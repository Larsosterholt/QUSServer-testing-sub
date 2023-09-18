# pip install opcua

from opcua import Client
import random
import time

# Initialize client and connect
client = Client("opc.tcp://lars-VirtualBox:4841/")

# Set authentication credentials
client.set_user("user1")
client.set_password("password1")


client.connect()



# Loop to continuously update temperature
while True:
    # Read current temperature from server
    
    temp_var = client.get_node("ns=0;i=50241") 
    current_temp = temp_var.get_value()

    # Generate simulated datacd 
    simulated_temp = current_temp + random.uniform(-1, 1)

    # Write new temperature back to server
    temp_var.set_value(simulated_temp)

    # Log and wait
    print(f"Updated temperature to {simulated_temp}")
    time.sleep(1)