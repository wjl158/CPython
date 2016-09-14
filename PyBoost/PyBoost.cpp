// PyBoost.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>

#include<boost/python.hpp>  
using namespace boost::python;

int _tmain(int argc, _TCHAR* argv[])
{

	 Py_Initialize();

    // ����ʼ���Ƿ�ɹ�
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

    //// �ر�Python
    //
	//Py_Finalize();
	system("pause");
	return 0;

}







