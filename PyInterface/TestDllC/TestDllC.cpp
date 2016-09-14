// TestDllC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>


#define DLL_IMPLEMENT
#include "../PyInterface/PyInterface.h"
#include<boost/python.hpp>  
#include<Python.h>
#include <string>
#include<Windows.h>
using namespace std;
using namespace boost::python;



string UnicodeToUTF8( const wstring& str )
{
	 char*     pElementText;
	 int    iTextLen;
	 // wide char to multi char
	 iTextLen = WideCharToMultiByte( CP_UTF8,
			 0,
			 str.c_str(),
			 -1,
			 NULL,
			 0,
			 NULL,
			 NULL );
	 pElementText = new char[iTextLen + 1];
	 memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	 ::WideCharToMultiByte( CP_UTF8,
			 0,
			 str.c_str(),
			 -1,
			 pElementText,
			 iTextLen,
			 NULL,
			 NULL );
	 string strText;
	 strText = pElementText;
	 delete[] pElementText;
	 return strText;
}




wstring UTF8ToUnicode( const string& str )
{
	 int  len = 0;
	 len = str.length();
	 int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
				0,
				str.c_str(),
				-1,
				NULL,
				0 );  
	 wchar_t *  pUnicode;  
	 pUnicode = new  wchar_t[unicodeLen+1];  
	 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	 ::MultiByteToWideChar( CP_UTF8,
			 0,
			 str.c_str(),
			 -1,
			 (LPWSTR)pUnicode,
			 unicodeLen );  
	 wstring  rt;  
	 rt = ( wchar_t* )pUnicode;
	 delete  pUnicode; 
 
	 return  rt;  
}



wstring ANSIToUnicode( const string& str )
{
	 int  len = 0;
	 len = str.length();
	 int  unicodeLen = ::MultiByteToWideChar( CP_ACP,
				0,
				str.c_str(),
				-1,
				NULL,
				0 );  
	 wchar_t *  pUnicode;  
	 pUnicode = new  wchar_t[unicodeLen+1];  
	 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	 ::MultiByteToWideChar( CP_ACP,
			 0,
			 str.c_str(),
			 -1,
			 (LPWSTR)pUnicode,
			 unicodeLen );  
	 wstring  rt;  
	 rt = ( wchar_t* )pUnicode;
	 delete  pUnicode; 
 
	 return  rt;  
}


void CallMyReturnStr();

void CallAdd()
{
	int a = add(2, 3);
	cout<<a;
	cout<<1;
}

int _tmain(int argc, _TCHAR* argv[])
{

    //Py_Initialize();

    //PyRun_SimpleString("print('run python ...')");
    //PyRun_SimpleString("import script");
    //PyRun_SimpleString("print(script.message)");
    //PyRun_SimpleString("x = script.message");
    //PyRun_SimpleString("print(script.transform(x))");


	////http://jingyan.baidu.com/article/67508eb4371b9e9cca1ce412.html?qq-pf-to=pcqq.c2c
	////http://jingyan.baidu.com/article/67508eb4371b9e9cca1ce412.html?qq-pf-to=pcqq.c2c
	////http://www.udpwork.com/item/10422.html

   // //Py_Finalize();
   //Py_Initialize();    // 将当前目录加入sys.path    
   //PyRun_SimpleString("import sys");    
   //PyRun_SimpleString("sys.path.append('./')");    // 导入hello.py模块    
   //PyObject *pmodule = PyImport_ImportModule("test1");    // 获得函数xprint对象，并调用，输出“hello world/n”    

   //PyObject *pfunc = PyObject_GetAttrString(pmodule, "xprint");    
   //PyObject_CallFunction(pfunc, NULL);    // 获得类Hello并生成实例pinstance，并调用print成员函数，输出“5 6/n”  

   //pfunc = PyObject_GetAttrString(pmodule, "haha");    
   //PyObject_CallFunction(pfunc, "ss", "asf", "sfd");    // 获得类Hello并生成实例pinstance，并调用print成员函数，输出“5 6/n”

   //PyObject *pReturn = NULL;  
   //pfunc = PyObject_GetAttrString(pmodule, "haha1");    
   //pReturn = PyObject_CallFunction(pfunc, "ii", 5, 7);//调用函数  

   //将返回值转换为int类型  
   //int result;  
   //PyArg_Parse(pReturn, "i", &result);//i表示转换成int型变量  
   //cout << "5+7 = " << result << endl; 

   //pfunc = PyObject_GetAttrString(pmodule, "haha2");    
   //pReturn = PyObject_CallFunction(pfunc, "ss", "qqq", "bbb");//调用函数  

   //将返回值转换为int类型  
   //char *fromPython, result1[1024];
   //PyArg_Parse(pReturn, "s", &fromPython);//i表示转换成int型变量 
   //strcpy_s(result1, "Hello , ");                // build up C string
   //strcpy_s(result1, fromPython);               // add passed Python string 
 
   //cout << "5+7 = " << result1 << endl; 

 //  PyObject *pclass    = PyObject_GetAttrString(pmodule, "Hello");    
 //  PyObject *arg       = Py_BuildValue("(i)", 5);    
 //  PyObject *pinstance = PyObject_Call(pclass, arg, NULL);    
 //  PyObject_CallMethod(pinstance, "print", "i", 6);    
 //  Py_Finalize();    
 //  return 0;

//Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化  
//PyObject * pModule = NULL;//声明变量  
//PyObject * pFunc = NULL;//声明变量  
//pModule =PyImport_ImportModule("Test001");//这里是要调用的Python文件名  
//pFunc= PyObject_GetAttrString(pModule, "HelloWorld"); //这里是要调用的函数名  
//PyEval_CallObject(pFunc, NULL); //调用函数,NULL表示参数为空  
//Py_Finalize();//调用Py_Finalize,这个和Py_Initialize相对应的.  

//PyObject_CallFunction(pFunc, "s", "zhengji");
//其中"s"表示参数为字符串，"zhengji"为函数pFunc的参数。
//假设需要pFunc调用两个整型的参数，可使用
//PyObject_CallFunction(pFunc, "ii", 1, 2);


	   //使用python之前，要调用Py_Initialize();这个函数进行初始化
    //Py_Initialize();

    //PyRun_SimpleString("import sys");
    //PyRun_SimpleString("sys.path.append('./')");

    //PyObject * pModule = NULL;
    //PyObject * pFunc = NULL;
    //PyObject * pClass = NULL;
    //PyObject * pInstance = NULL;

    ////这里是要调用的文件名
    //pModule = PyImport_ImportModule("script");
    ////这里是要调用的函数名
    //pFunc= PyObject_GetAttrString(pModule, "hello");
    ////调用函数
    //PyEval_CallObject(pFunc, NULL);
    //Py_DECREF(pFunc);  

    //pFunc = PyObject_GetAttrString(pModule, "world");
    //PyObject_CallFunction(pFunc, "s", "zhengji");
    //Py_DECREF(pFunc);  

    ////测试调用python的类
    //pClass = PyObject_GetAttrString(pModule, "Student");
    //if (!pClass) {
    //    printf("Can't find Student class.\n");
    //    return -1;
    //}
    //pInstance = PyInstance_New(pClass, NULL, NULL);
    //if (!pInstance) {
    //    printf("Can't create Student instance.\n");
    //    return -1;
    //}
    //PyObject_CallMethod(pInstance, "SetName", "s","my family");
    //PyObject_CallMethod(pInstance, "PrintName",NULL,NULL);
    ////调用Py_Finalize，这个根Py_Initialize相对应的。
    //Py_Finalize();
    //return 0;

 //   wstring sA(L"aaa");
	//wstring sB(L"bbb");

	//wstring wsA = ANSIToUnicode(sA);
 //   wstring wsB = ANSIToUnicode(sB);

	//const wchar_t *wA = sA.data();
	//const wchar_t *wB = sB.data();

 //   wchar_t *p = MyReturnStr(L"狗日的", L"编码转换");

	//wstring ws(p);
	//string s;

	////s = UnicodeToUTF8(ws);
	//wcout.imbue(locale("chs"));
	//wcout<<ws.data();

	//cout<<"呵呵";
	//cout<<1;


 //   CallMyReturnStr();
	//CallAdd();

  //int a = add(1, 2);
  //cout<<a;
  //cout<<1;

  ////Py_Initialize(





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
        exec("print os.getcwd()", mainNamespace, mainNamespace);  
    }
    catch( ... )
    {
            if (PyErr_Occurred())  
            PyErr_Print();  
    }

    // 关闭Python
    Py_Finalize();
    system("pause");



}

void CallMyReturnStr()
{
 //   wstring sA(L"aaa");
	//wstring sB(L"bbb");
	//const wchar_t *wA = sA.data();
	//const wchar_t *wB = sB.data();

    wchar_t *p = MyReturnStr(L"aaa", L"bbb");

	wcout.imbue(locale("chs"));
	wcout<<p;

	cout<<"呵呵";
	cout<<1;
}

