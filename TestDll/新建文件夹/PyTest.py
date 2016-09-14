class Hello:
    def __init__(self, x):
        self.a = x
    def print(self, x=None):
        print(x)
def xprint():
    print("hello world")

def haha(x, y):
    print(x + y)
def haha1(x, y):
    return x + y
	
def haha2(x, y):
    return x + y

def helloWord():
    return "нуху"
def MyFun(x):
    a = eval(x)
    return a['a']
	
def Add(arg):
    a = eval(arg)
    return "%s"%(a[0] + a[1])

if __name__ == "__main__":
    xprint()
    h = Hello(5)
    h.print()
	

# print(MyFun("{'a':'1',}"))