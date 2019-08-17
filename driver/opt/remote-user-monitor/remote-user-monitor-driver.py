#!/usr/bin/env python

import binascii
import os
import serial
import subprocess
import time


def loop(port):
    path = os.path.dirname(os.path.realpath(__file__))

    while True:
        # Get state
        ps = not subprocess.call('bash {}/process.sh'.format(path), shell=True, stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE)
        names = subprocess.check_output('bash {}/users.sh'.format(path), shell=True).split('\n')

        # Generate message
        msg = bytearray()
        msg.append('#')
        msg.append('1' if ps else '0')
        msg.append(' ')
        for name in names:
            msg.extend(name)
            msg.append(',')
        msg.append('\n')
        # print msg[:-1]

        # Send message
        port.write(msg)
        port.flush()

        # Read requests
        while port.in_waiting:
            req = port.readline()[:-2]
            # print req

            if req == 'GTFO':  # Get The Fuck Out
                print 'Received request to throw users out... bye bye users'
                subprocess.call('bash {}/gtfo.sh'.format(path), shell=True)

        # Wait
        time.sleep(1)


def main():
    port = serial.Serial('/dev/ttyUSB0', 115200, timeout=1, writeTimeout=1)

    try:
        loop(port)
    except:
        print '\nExiting'
        port.flush()
        port.close()
        print 'Goodbye'


if __name__ == "__main__":
    main()
