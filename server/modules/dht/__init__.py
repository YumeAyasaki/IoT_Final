from flask import Blueprint, request

from modules.data import update_data

bp = Blueprint('dht', __name__)

@bp.route('/update/', methods=['GET']) # Get information from the sensor
def get_data():
    print('Update request received')

    update_data(request.args.get('temperature'), request.args.get('humidity'))

    # Return receive ok code
    return 'ok', 200