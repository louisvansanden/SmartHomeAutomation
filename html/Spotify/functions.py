import requests
import json

with open('.secrets.json', 'r') as j:
    secrets = json.load(j)
    CI = secrets["CLIENT_ID"]
    CS = secrets["CLIENT_SECRET"]
    RT = secrets["REFRESH_TOKEN"]


def get_refresh_token():
    return RT


def get_client_id():
    return CI


def get_client_secret():
    return CS


token = ''
current_device = "a508fe7138f3947d91c06b0e63e85e5dc7bded30"


def refresh_access_token():

    payload = {'grant_type': 'refresh_token',
               'refresh_token': get_refresh_token()}
    # Retrieve a new access token with the refresh token.
    req = requests.post('https://accounts.spotify.com/api/token',
                        auth=(get_client_id(), get_client_secret()), data=payload)
    token = 'Bearer ' + req.json().get('access_token')
    return token


def currently_playing_device():
    global current_device, token

    token = refresh_access_token()
    url = 'https://api.spotify.com/v1/me/player/devices'
    headers = {"Accept": "application/json",
               "Content-Type": "application/json",
               "Authorization": token}
    devices = requests.get(url, headers=headers).json()["devices"]

    for device in devices:
        if device["is_active"]:
            current_device = device["id"]


def is_playing():
    global token

    token = refresh_access_token()
    url = 'https://api.spotify.com/v1/me/player/currently-playing'
    headers = {"Accept": "application/json",
               "Content-Type": "application/json",
               "Authorization": token}
    status = requests.get(url, headers=headers)
    status = status.json()
    if 'is_playing' in status.keys():
        print(status['is_playing'])
    else:
        print(False)


def play():
    global current_device

    currently_playing_device()  # Also refreshes token.
    url = 'https://api.spotify.com/v1/me/player/play?device_id=' + current_device
    headers = {"Accept": "application/json",
               "Content-Type": "application/json",
               "Authorization": token}
    requests.put(url, headers=headers)


def pause():
    global current_device

    currently_playing_device()  # Also refreshes token.
    url = 'https://api.spotify.com/v1/me/player/pause?device_id=' + current_device
    headers = {"Accept": "application/json",
               "Content-Type": "application/json",
               "Authorization": token}
    requests.put(url, headers=headers)


def next():
    global current_device

    currently_playing_device()  # Also refreshes token.
    url = 'https://api.spotify.com/v1/me/player/next?device_id=' + current_device
    headers = {"Accept": "application/json",
               "Content-Type": "application/json",
               "Authorization": token}
    requests.post(url, headers=headers)


def prev():
    global current_device

    currently_playing_device()  # Also refreshes token.
    url = 'https://api.spotify.com/v1/me/player/previous?device_id=' + current_device
    headers = {"Accept": "application/json",
               "Content-Type": "application/json",
               "Authorization": token}
    requests.post(url, headers=headers)
