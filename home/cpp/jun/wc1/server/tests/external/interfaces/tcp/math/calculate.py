import socket

import json
import struct

def send_tcp_request(host, port, data):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((host, port))
            print(f"Connected to {host}:{port}")

            json_data = json.dumps(data)
            json_bytes = json_data.encode('utf-8')
            
            data_length = len(json_bytes)
            header = struct.pack('!I', data_length)

            packet = header + json_bytes

            sock.sendall(packet)
            print(f"Sent packet: {packet}")
            
            response = sock.recv(1024)  
            print(f"Received response: {response}")
            
    except Exception as e:
        print(f"An error occurred: {e}")

# ------------------------------------------------------------------------

data_to_send = {
    "request_id": 12345,
    "service": "math",
    "action": "calculate",
    "payload": {
        "expression": "1 + 2 + 3 + 4 + 5"
    }
}

send_tcp_request(
    "127.0.0.1", 24444,
    data_to_send)