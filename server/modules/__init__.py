from flask import Flask
from flask_cors import CORS

from modules.dht import bp as dht_bp

def create_app():
    global data

    app = Flask(__name__)
    CORS(app)
    app.register_blueprint(dht_bp)
    return app