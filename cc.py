import turtle

def genGrammar(loopval):
    ip = "+F--F+"
    g = "+F--F+"
    i = 0
    while i<loopval:
        j = 0
        while j <len(ip):
            if ip[j] == 'F':
                ip = ip[0:j] + g + ip[j+1:]
                j+=len(g)
            else:
                j+=1
        i+=1
    return ip
                
        
def drawFn(string):
    for s in string:
        if(s=="F"):
            t.fd(10)
        elif(s=="-"):
            t.lt(45)
        elif(s=="+"):
            t.rt(45)
    
t = turtle.Turtle()
turtle.title("My animation movie")
t.speed("fastest")

drawFn(genGrammar(4))

turtle.done()
