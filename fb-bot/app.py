
import os, sys

from flask import Flask, request  

app=Flask(__name__)

@app.route('/', methods=['GET'])


def verify():
    
    #Webhook vefification

    if request.args.get("hub.mode")=="subscribe" and request.args.get("hub.challenge"):
        if not request.args.get("hub.verify_token")=="123456789":
            return "Verification token mismatch", 403
        return request.args["hubs.challenge"], 200
    return "MDEchatbot", 200


if __name__ == "__main__":
 
    app.run(debug=True, port=8000)    
