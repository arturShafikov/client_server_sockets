# client_server_sockets
Client and server using Berkeley Sockets

## Build server application:
```
cd client_server_sockets/server/
mkdir build
cd build/
cmake ..
make
```

## Build client application:
```
cd client_server_sockets/client/
mkdir build
cd build/
cmake ..
make
```

## Run server:
```
cd client_server_sockets/server/build/
./server
```

## Run client in TCP mode:
```
cd client_server_sockets/client/build/
./client tcp
```

## Run client in UDP mode:
```
cd client_server_sockets/client/build/
./client udp
```

