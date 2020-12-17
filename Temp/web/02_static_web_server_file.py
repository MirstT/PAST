# coding:utf-8
import socket
from multiprocessing import Process
import re

HTML_ROOT_DIR = './html'


def handle_client(client_socket):
    """处理客户端请求"""
    request_data = client_socket.recv(1024)
    print('request_data:', request_data)
    request_lines = request_data.splitlines()
    for line in request_lines:
        print(line)

    request_start_line = request_lines[0]
    file_name = re.match(r"\w+ +(/[^ ]*) ", request_start_line.decode("utf-8")).group(1)
    print(file_name)

    if "/"==file_name:
        file_name = "/index.html"

    try:
        file = open(HTML_ROOT_DIR + file_name, "rb")
    except IOError:
        response_start_line = 'HTTP/1.1 404 Not Found\r\n'
        response_headers = 'Server:My server\r\n'
        response_body = "The file is not found"
    else:
        file_data = file.read()
        file.close()

        response_start_line = 'HTTP/1.1 200 OK\r\n'
        response_headers = 'Server:My server\r\n'
        response_body = file_data.decode("utf-8")

    response = response_start_line + response_headers + '\r\n' + response_body
    print('reponse data:', response)

    client_socket.send(bytes(response, 'utf-8'))

    client_socket.close()


if __name__ == '__main__':
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    server_socket.bind(('', 8000))
    server_socket.listen(128)

    while True:
        client_socket, client_address = server_socket.accept()
        print('[%s,%s]用户连接上了' % client_address)
        handle_client_process = Process(target=handle_client, args=(client_socket,))
        handle_client_process.start()
        client_socket.close()
