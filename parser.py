def parse(data, port, origin):
    print ("[" + origin + ":" + str(port) + "]" + "\n" + str(data))
        #print ":".join("{:02x}".format(ord(c)) for c in data)

#il y a un lf ( + un cr) en fin de data ducoup c'est pour ca que ca print sur 2 lignes, faites un bail du genre pour print sur 1:
#print ("[" + origin + ":" + str(port) + "]" + data, end='') je c meme pas si ca marche mais c'est un bail du genre pour sur
