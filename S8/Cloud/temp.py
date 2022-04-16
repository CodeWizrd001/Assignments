# Example-33.py
#!/usr/bin/env python3
import sys
import libvirt

domName = 'Lubuntu-1'

conn = None
try:
    conn = libvirt.open("qemu:///system")
except libvirt.libvirtError as e:
    print(repr(e), file=sys.stderr)
    exit(1)

dom = conn.lookupByID(14)
print(f'[+] Domain : {dom.name()}')
if dom == None:
    print('Failed to find the domain '+domName, file=sys.stderr)
    exit(1)

stats = dom.getCPUStats(True)

print('cpu_time:    '+str(stats[0]['cpu_time']))
print('system_time: '+str(stats[0]['system_time']))
print('user_time:   '+str(stats[0]['user_time']))

conn.close()

help(stats)

a = 1
print(a)
