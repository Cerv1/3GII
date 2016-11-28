import fileinput
import sys

file="/etc/ssh/sshd_config"
old_port="Port 22"
list1=sys.argv[1:]

new_port="Port "+"".join(list1)


for line in fileinput.input(file, inplace=1):
    if old_port in line:
        line = line.replace(old_port,new_port)
    sys.stdout.write(line)
