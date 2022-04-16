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

print(stats)

stats = []

scaleFactor = 10**9

stats.append(dom.getCPUStats(True))
print(f'[+] Pass 1')
for stat in stats[0][0] :
    stats[0][0][stat] /= scaleFactor

print('cpu_time:    '+str(stats[0][0]['cpu_time']))
print('system_time: '+str(stats[0][0]['system_time']))
print('user_time:   '+str(stats[0][0]['user_time']))

time.sleep(1)
stats.append(dom.getCPUStats(True))

print(f'[+] Pass 2')
for stat in stats[1][0] :
    stats[1][0][stat] /= scaleFactor
print('cpu_time:    '+str(stats[1][0]['cpu_time']))
print('system_time: '+str(stats[1][0]['system_time']))
print('user_time:   '+str(stats[1][0]['user_time']))

usage = 100*(stats[1][0]['cpu_time'] - stats[0][0]['cpu_time'])

print(f'[+] Usage % : {usage}')