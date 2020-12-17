var=99

def abc():
    global var
    var+=1

def test():
    print (var)

    abc()
    print (var)

    
