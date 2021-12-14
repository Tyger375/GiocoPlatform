import asyncio
import random
import socket
import threading
import time

HEADER = 64
PORT = 5000
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
FORMAT = "utf-8"
DISCONNECT_MESSAGE = "!DISCONNECT"

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

global ip, pos1, pos2

ip = []

pos1 = ()
pos2 = ()


def always():
    global ip
    while True:
        # print("test")
        try:
            # print(len(ip))
            for connection in range(len(ip)):
                # print(connection)
                if connection == 0:
                    if pos2:
                        print("sending to player1 player2's position: " + str(pos2[0]) + " " + str(pos2[1]))
                        ip[connection].send((str(pos2[0]) + " " + str(pos2[1]) + "\x00").encode(FORMAT))
                    else:
                        ip[connection].send("no data\x00".encode(FORMAT))
                else:
                    if pos1:
                        print("sending to player2 player1's position: " + str(pos1[0]) + " " + str(pos1[1]))
                        ip[connection].send((str(pos1[0]) + " " + str(pos1[1]) + "\x00").encode(FORMAT))
                    else:
                        ip[connection].send("no data\x00".encode(FORMAT))
        except Exception:
            pass


def handle_client(conn, addr):
    print(f"new connection {addr} connected")

    connected = True
    while connected:
        global pos1, pos2
        """if ip[0] == conn:
            if pos2:
                conn.send((str(pos2[0]) + " " + str(pos2[1]) + "\x00").encode(FORMAT))
            else:
                conn.send("no data\x00".encode(FORMAT))
        else:
            if pos1:
                conn.send((str(pos1[0]) + " " + str(pos1[1]) + "\x00").encode(FORMAT))
            else:
                conn.send("no data\x00".encode(FORMAT))"""
        msg_length = conn.recv(HEADER).decode(FORMAT)
        # print(msg_length)
        if msg_length:
            # msg_length = int.from_bytes(msg_length, byteorder='big', signed=False)
            # msg_length = int(msg_length)
            # print(msg_length)
            # msg = conn.recv(100).decode('latin-1').encode("utf-8")
            msg = str(msg_length)
            # print("msg = " + str(msg))
            # conn.send("test\x00".encode(FORMAT))
            newMsg = msg.replace("\x00", "")
            if newMsg == DISCONNECT_MESSAGE:
                connected = False
                break
            # conn.send(f"nice\x00".encode(FORMAT))
            splitMsg = msg.split(" ")
            # print(splitMsg)
            posX = float(splitMsg[0])
            posY = float(str(splitMsg[1].replace("\x00", "")))

            posX = round(posX, 2)
            posY = round(posY, 2)

            # print("posX: " + str(posX) + "\nposY: " + str(posY))
            if ip[0] == conn:
                # print("cambio player 1")
                pos1 = (posX, posY)
            else:
                # print("cambio player 2")
                pos2 = (posX, posY)
            # print(f"{addr}: {msg}")

    ip.pop(ip.index(conn))
    conn.close()


def start():
    server.listen()
    print(f"server is listening on {SERVER}")
    boh = threading.Thread(target=always)
    boh.start()
    while True:
        global ip
        conn, addr = server.accept()
        conn.send((str(len(ip) + 1) + "\x00").encode(FORMAT))
        ip.append(conn)
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"connections: {threading.activeCount() - 1}")
        # print("test")
        """conn.send("nice".encode(FORMAT))
        if len(ip) == 2:
            global turno
            turno = random.randint(0, 1)
            print(turno)
            for connection in range(2):
                if connection == 1:
                    ip[connection].send("X".encode(FORMAT))
                else:
                    ip[connection].send("O".encode(FORMAT))
            time.sleep(1)
            ip[turno].send("you".encode(FORMAT))


            """


print("starting")
start()