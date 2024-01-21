from flask import Blueprint, request

bp = Blueprint('dht', __name__)

@bp.route('/update/', methods=['GET']) # Get information from the sensor
def get_data():
    print('Update request received')
    global data 

    data = {
        'temperature': request.args.get('temperature'),
        'humidity': request.args.get('humidity')
    }
    print(data)

    # Return receive ok code
    return 'ok', 200