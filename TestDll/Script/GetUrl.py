import requests
def Go():
    r = requests.get('http://cuiqingcai.com')
    return r.text