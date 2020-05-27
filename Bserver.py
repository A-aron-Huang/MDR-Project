import bluetooth #From PyBluez library


serverAddress = 'B8:27:EB:D7:1B:CE'#Address of server
port = 1#port client connects too
backlog = 1
BserverSocket = bluetooth.BluetoothSocket(bluetooth.RFCOMM) #Opens Socket with RFCOMM
BserverSocket.bind(('B8:27:EB:D7:1B:CE',1)) #Binds the socket to specified port and address as server socket
BserverSocket.listen(backlog)
try:    
    Bclient, address = BserverSocket.accept() #Accepts connection from client
    print('Connection Accepted')
    fileSize = Bclient.recv(1024)#First string recived is file size
    print(int(fileSize))
    
    with open("imageReceived.jpg","wb") as fileReceived: #Opens a file on server end to read bytes into        
        print('Image Opened')
        fileByte = Bclient.recv(4)#Reads first byte
        print('First Byte Received')
        print(fileByte, 0)
        i = 1
        while fileByte:
            fileReceived.write(fileByte)#Writes byte to file
            fileByte = Bclient.recv(3) #Receives next byte
            print(fileByte,i, chr(fileByte))
            i = i + 1
except:
    #Bclient.close()#Closes socket on client end
    BserverSocket.close()#Closes serversocket on server end
    print('closed')
    
