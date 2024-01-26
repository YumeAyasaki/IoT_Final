from flask import Flask, Blueprint, render_template

from modules.data import get_data

bp = Blueprint('front_end', __name__)

@bp.route('/')
def index():
    data = get_data()
    return render_template('home.html', data=data)

@bp.route('/temperature')
def temperature():
    data = get_data()
    return render_template('temperature.html', data=data)

@bp.route('/humidity')
def humidity():
    data = get_data()
    return render_template('humidity.html', data=data)