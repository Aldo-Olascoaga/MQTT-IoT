# Import the necessary modules after installing the Paho MQTT Python client library
import paho.mqtt.client as mqtt


# Create a client instance
client = mqtt.Client()


# Let's connect to our broker
broker_address = "our-broker-address-aws"
broker_port = 1883
client.connect(broker_address, broker_port)


# Let's publish a message
topic = "temperature"
message = "24.5"  # Replace with the message payload
client.publish(topic, message)


# Disconnect from the broker
client.disconnect()
