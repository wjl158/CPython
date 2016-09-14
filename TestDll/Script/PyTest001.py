def ReturnStr():
    return "MyFun"
	
def Add(arg):
    x = eval(arg)
    return "%s"%(x[0] + x[1])	
	
def GetDictValue(arg):
    x = eval(arg)
    return "%s"%(x['a'])