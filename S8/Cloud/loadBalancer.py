import libvirt
import logging
import time
import sys
import os

from threading import Thread
import socket


vmServer = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
mainServer = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

VM_HOST_PORT = 5678
SRV_HOST_PORT = 5679
BUFFER_SIZE = 2048
RUNNING = True
TEMPLATE_VM = "Lubuntu_1"

MAIN_SERVER_DOMAIN = "Lubuntu_1-clone"
NEXT_VM = "Lubuntu_1-clone1"

CLONE_COMMAND = f"sudo virt-clone --original Lubuntu_1 --auto-clone"

CLONE_LOCK = False
START_LOCK = False


# In Seconds
CPU_THRESHOLD = 75
poolTime = 0.5
scaleFactor = poolTime * 10**9


domains = {}
activeDomains = []
activeServers = {}
stats = {}

try:
    connection = libvirt.open("qemu:///system")
except libvirt.libvirtError:
    print('Failed to open connection to the hypervisor')
    sys.exit(1)

print(f'[+] Running Initial Preps')
for d in connection.listAllDomains() :
    if d.name() == TEMPLATE_VM :
        continue
    domains[d.name()] = d
    try :
        if d.isActive() :
            d.shutdown()
            while d.isActive() :
                time.sleep(0.5)
        else :
            continue
    except Exception as e :
        print(f'[!] SetupException : {e}')

try :
    domains[MAIN_SERVER_DOMAIN].create()
    while not domains[MAIN_SERVER_DOMAIN].isActive() :
        time.sleep(0.5)
except Exception as e :
    print(f'[!] CreateException : {e}')

print(f'[+] Initial Preps Done')

def acquireCloneLock() :
    global CLONE_LOCK
    if CLONE_LOCK :
        return False
    else :
        CLONE_LOCK = True
        return True

def releaseCloneLock() :
    global CLONE_LOCK
    CLONE_LOCK = False

def acquireStartLock() :
    global START_LOCK
    if START_LOCK :
        return False
    else :
        START_LOCK = True
        return True

def releaseStartLock() :
    global START_LOCK
    START_LOCK = False

def addServer(ip) :
    for domName in domains :
        if domName not in activeDomains and domains[domName].isActive() and domName != TEMPLATE_VM:
            activeDomains.append(domName)
            activeServers[domName] = ip
    print(f'[*] Continuing With Configuration : {activeServers}')

def cloneServer() :
    global NEXT_VM
    next_vm = NEXT_VM.replace(MAIN_SERVER_DOMAIN,'')
    next_vm = str(int(next_vm)+1)
    next_vm = MAIN_SERVER_DOMAIN + next_vm
    try :
        connection.lookupByName(next_vm)
        print(f'[+] Cloning Not Needed VM Already Exists')
        NEXT_VM = next_vm
    except Exception as e :
        if acquireCloneLock() : 
            print(f'[*] Cloning in process')

            print(f'[-] Live Cloning Disabled')
            # os.system(CLONE_COMMAND)
            releaseCloneLock()
            try :
                d = connection.lookupByName(next_vm)
                print(f'[+] Cloning Complete')
                d.create()
                d.shutdown()
            except :
                print(f'[-] Cloning Failed')
            for d in connection.listAllDomains() :
                if d.name() not in domains :
                    NEXT_VM = d.name()
                domains[d.name()] = d
        else :
            print(f'[!] CloneError : Cloning Already in Progress')

def startNext() :
    try :
        dom = connection.lookupByName(NEXT_VM)
    except Exception as e :
        print(f'[+] Next VM Does Not Exist')
    if acquireStartLock() :
        pass
    else :
        print(f'[+] Start Already in Progress')
        return
    try :
        print(f'[+] Starting VM : {NEXT_VM}')
        dom.create()
        time.sleep(10)
        releaseStartLock()
        cloneServer()
    except Exception as e : 
        print(f'[!] StartNextException : {NEXT_VM} {e}')
    
def handle_connected(connection=None,address=""):
    print(f'[+] Received New Server from {address}')
    data = connection.recv(BUFFER_SIZE)
    data = data.decode()
    if "RegNewServer" == data :
        addServer(address)
    else :
        print(f'[+] Received : {data.decode()}')

def getServer() :
    d = getLowLoadDomain()
    return d , activeServers[d][0]

def handle_request(connection=None,address="") :
    # print(f'[+] Received Request from : {address}')
    req = connection.recv(BUFFER_SIZE)
    c = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    d , s = getServer()
    addr = (s,SRV_HOST_PORT)
    print(f'[+] Sending Request to : {s:16s} : {d:20s}')
    c.connect(addr)
    c.send(req)
    res = c.recv(BUFFER_SIZE)
    connection.send(res)

def getLowLoadDomain() :
    l = stats[MAIN_SERVER_DOMAIN]['sLoad']
    lDom = MAIN_SERVER_DOMAIN

    # print(f'[+] Choosing Server : {stats}')
    for domName in stats :
        if stats[domName]['sLoad'] < l :
            # print(f'[----] Moving to server with load : {l} ::: domName : {domName}')
            l = stats[domName]['sLoad']
            lDom = domName
    return lDom

def systemMonitor() :
    print(f'[+] VM Monitor Running')
    time.sleep(10)
    while RUNNING :
        time.sleep(1)
        for domName in activeDomains :
            if domName == TEMPLATE_VM :
                continue
            dom = connection.lookupByName(domName)
            pStats = dom.getCPUStats(True)[0]
            time.sleep(poolTime)
            cStats = dom.getCPUStats(True)[0]
            usage = 100 * (cStats['cpu_time']-pStats['cpu_time']) / scaleFactor
            if usage > 100 :
                usage = 100
            try :
                sLoad = stats[domName]['sLoad']
            except KeyError as e :
                sLoad = 0
            stats[domName] = {
                'cpu' : usage,
                'sLoad' : (sLoad*4+usage) / 5
            }
        flag = len(stats) != 0 
        for domName in stats :
            print(f'[+] Domain : {domName:25s}   ::: CPU : {stats[domName]["cpu"]:6.2f} %   ::: Sustained : {stats[domName]["sLoad"]:6.2f}')
            pass
        for domName in stats :
            if stats[domName]['sLoad'] < CPU_THRESHOLD :
                flag = False
                break
        if flag :
            startNext()


def vmHandle() :
    vmServer.bind(("0.0.0.0",VM_HOST_PORT))
    vmServer.listen(5)
    print(f'[+] VM Server Listening on : 0.0.0.0:{VM_HOST_PORT}')
    while RUNNING :
        connection , client_address = vmServer.accept()
        connectionThread = Thread(target=handle_connected,args=(connection,client_address,))
        connectionThread.start()

def srvHandle() :
    mainServer.bind(("0.0.0.0",SRV_HOST_PORT))
    mainServer.listen(5)
    print(f"[+] Main Server Listening on : 0.0.0.0:{SRV_HOST_PORT}")
    while RUNNING :
        connection , client_address = mainServer.accept()
        connectionThread = Thread(target=handle_request,args=(connection,client_address,))
        connectionThread.start()

if __name__ == "__main__" :
    vmThread = Thread(target=vmHandle)
    srvThread = Thread(target=srvHandle)
    monitorThread = Thread(target=systemMonitor)

    vmThread.start()
    srvThread.start()
    monitorThread.start()

    try :
        while True :
            inp = input()
            if inp == "exit" :
                print(f'[+] Exiting')
                print(f'[+] Ctrl+C to stop running threads')
                RUNNING = False
                vmThread.join()
                srvThread.join()
                monitorThread.join()
                exit(0)
    except KeyboardInterrupt as e :
        vmThread.join()
        srvThread.join()
        monitorThread.join()
        exit(0)