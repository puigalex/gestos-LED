import requests

# WLED device IP address
wled_ip = '192.168.0.180'

preset = 1

url = f'http://{wled_ip}/win&PL={preset}'

# Send the GET request
response = requests.get(url)

# Check the response
if response.status_code == 200:
    print('Preset set successfully!')
else:
    print(f'Failed to set preset, status code: {response.status_code}')



