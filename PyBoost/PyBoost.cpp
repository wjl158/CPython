// PyBoost.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>

#include<boost/python.hpp>  
using namespace boost::python;

int _tmain(int argc, _TCHAR* argv[])
{

	 Py_Initialize();

    // 检查初始化是否成功
    if ( !Py_IsInitialized() )
    {
        return -1;
    }



    PyRun_SimpleString("import sys");  
    PyRun_SimpleString("sys.path.append('./')");  

    object mainModule;
    object mainNamespace;

    try
    {
        mainModule = import("__main__");
        mainNamespace = mainModule.attr("__dict__");
        exec("import os", mainNamespace, mainNamespace);  
        exec("print(os.getcwd())", mainNamespace, mainNamespace);  
    }
    catch( ... )
    {
            if (PyErr_Occurred())  
            PyErr_Print();  
    }

    //// 关闭Python
    //
	//Py_Finalize();
	system("pause");
	return 0;

}







