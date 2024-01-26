# For global variables, we can use the global keyword to access them from within a function.

data = {
    'temperature': 0,
    'humidity': 0
}

def update_data(temperature, humidity):
    data['temperature'] = temperature
    data['humidity'] = humidity

def get_data():
    return data