from flask import Flask
from flask_cors import CORS

from modules.dht import bp as dht_bp
from modules.front_end import bp as front_end_bp

def create_app():
    app = Flask(__name__)
    CORS(app)
    app.register_blueprint(dht_bp)
    app.register_blueprint(front_end_bp)
    return app