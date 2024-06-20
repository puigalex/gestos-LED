# Send a message to a WLED device 192.168.0.180 with the following parameters:
# - Set the brightness to 50
# - Set the effect to 1
# - Set the speed to 100

import requests

# WLED device IP address
wled_ip = '192.168.0.180'

# Parameters
brightness = 50
effect = 1
speed = 100

# Construct the URL
url = f'http://{wled_ip}/win&FX={2}&SX={speed}&A={brightness}'




# Send the GET request
response = requests.get(url)

# Check the response
if response.status_code == 200:
    print('Message sent successfully!')
else:
    print(f'Failed to send message, status code: {response.status_code}')
