import libvirt
import time
import sys

domName = "Lubuntu_1"

try:
    # conn = libvirt.openReadOnly(None)
    conn = libvirt.open("qemu:///system")
except libvirt.libvirtError:
    print('Failed to open connection to the hypervisor')
    sys.exit(1)

try:
    dom = conn.lookupByName(domName)
except libvirt.libvirtError:
    print('Failed to find the main domain')
    sys.exit(1)

print("Domain 0: id %d running %s" % (dom.ID(), dom.OSType()))
print(dom.info())

try :
    stats = dom.getCPUStats(True)
except Exception as e :
    print(f'[!] Exception : {e}')

# In Seconds
poolTime = 0.5
scaleFactor = poolTime * 10**9

while True :
    pStats = dom.getCPUStats(True)[0]
    time.sleep(poolTime)
    stats = dom.getCPUStats(True)[0]
    usage = 100 * (stats['cpu_time']-pStats['cpu_time']) / scaleFactor
    if usage > 100 :
        usage = 100
    print(f'[+] Usage % : {usage}')