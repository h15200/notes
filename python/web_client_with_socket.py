import socket

# intantiate class with family, type
my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect to endpoint on port 80, which is standard for web server. note that it takes in 1 arg, a tuple
my_socket.connect(('data.pr4e.org', 80)) 

# define request
# turn unicode string into utf-8 byte array, which is the default of encode()
get_req = 'GET http://data.pr4e.org/romeo.txt\r\n\r\n'.encode()
my_socket.send(get_req)

while True:
  data = my_socket.recv(512)
  if (len(data) < 1):
    break
  print(data.decode()) # decode utf-8 byte array into unicode, which is python strings
my_socket.close