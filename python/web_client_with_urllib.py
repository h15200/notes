import urllib.request, urllib.parse, urllib.error

# the request method defaults to GET request

res = urllib.request.urlopen('http://data.pr4e.org/romeo.txt')

print(type(res))

# ignores all headers
for bytes in res:
  print(bytes.decode().rstrip())


