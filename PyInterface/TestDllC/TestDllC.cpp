// TestDllC.cpp : �������̨Ӧ�ó������ڵ㡣
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
   //Py_Initialize();    // ����ǰĿ¼����sys.path    
   //PyRun_SimpleString("import sys");    
   //PyRun_SimpleString("sys.path.append('./')");    // ����hello.pyģ��    
   //PyObject *pmodule = PyImport_ImportModule("test1");    // ��ú���xprint���󣬲����ã������hello world/n��    

   //PyObject *pfunc = PyObject_GetAttrString(pmodule, "xprint");    
   //PyObject_CallFunction(pfunc, NULL);    // �����Hello������ʵ��pinstance��������print��Ա�����������5 6/n��  

   //pfunc = PyObject_GetAttrString(pmodule, "haha");    
   //PyObject_CallFunction(pfunc, "ss", "asf", "sfd");    // �����Hello������ʵ��pinstance��������print��Ա�����������5 6/n��

   //PyObject *pReturn = NULL;  
   //pfunc = PyObject_GetAttrString(pmodule, "haha1");    
   //pReturn = PyObject_CallFunction(pfunc, "ii", 5, 7);//���ú���  

   //������ֵת��Ϊint����  
   //int result;  
   //PyArg_Parse(pReturn, "i", &result);//i��ʾת����int�ͱ���  
   //cout << "5+7 = " << result << endl; 

   //pfunc = PyObject_GetAttrString(pmodule, "haha2");    
   //pReturn = PyObject_CallFunction(pfunc, "ss", "qqq", "bbb");//���ú���  

   //������ֵת��Ϊint����  
   //char *fromPython, result1[1024];
   //PyArg_Parse(pReturn, "s", &fromPython);//i��ʾת����int�ͱ��� 
   //strcpy_s(result1, "Hello , ");                // build up C string
   //strcpy_s(result1, fromPython);               // add passed Python string 
 
   //cout << "5+7 = " << result1 << endl; 

 //  PyObject *pclass    = PyObject_GetAttrString(pmodule, "Hello");    
 //  PyObject *arg       = Py_BuildValue("(i)", 5);    
 //  PyObject *pinstance = PyObject_Call(pclass, arg, NULL);    
 //  PyObject_CallMethod(pinstance, "print", "i", 6);    
 //  Py_Finalize();    
 //  return 0;

//Py_Initialize();//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��  
//PyObject * pModule = NULL;//��������  
//PyObject * pFunc = NULL;//��������  
//pModule =PyImport_ImportModule("Test001");//������Ҫ���õ�Python�ļ���  
//pFunc= PyObject_GetAttrString(pModule, "HelloWorld"); //������Ҫ���õĺ�����  
//PyEval_CallObject(pFunc, NULL); //���ú���,NULL��ʾ����Ϊ��  
//Py_Finalize();//����Py_Finalize,�����Py_Initialize���Ӧ��.  

//PyObject_CallFunction(pFunc, "s", "zhengji");
//����"s"��ʾ����Ϊ�ַ�����"zhengji"Ϊ����pFunc�Ĳ�����
//������ҪpFunc�����������͵Ĳ�������ʹ��
//PyObject_CallFunction(pFunc, "ii", 1, 2);


	   //ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��
    //Py_Initialize();

    //PyRun_SimpleString("import sys");
    //PyRun_SimpleString("sys.path.append('./')");

    //PyObject * pModule = NULL;
    //PyObject * pFunc = NULL;
    //PyObject * pClass = NULL;
    //PyObject * pInstance = NULL;

    ////������Ҫ���õ��ļ���
    //pModule = PyImport_ImportModule("script");
    ////������Ҫ���õĺ�����
    //pFunc= PyObject_GetAttrString(pModule, "hello");
    ////���ú���
    //PyEval_CallObject(pFunc, NULL);
    //Py_DECREF(pFunc);  

    //pFunc = PyObject_GetAttrString(pModule, "world");
    //PyObject_CallFunction(pFunc, "s", "zhengji");
    //Py_DECREF(pFunc);  

    ////���Ե���python����
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
    ////����Py_Finalize�������Py_Initialize���Ӧ�ġ�
    //Py_Finalize();
    //return 0;

 //   wstring sA(L"aaa");
	//wstring sB(L"bbb");

	//wstring wsA = ANSIToUnicode(sA);
 //   wstring wsB = ANSIToUnicode(sB);

	//const wchar_t *wA = sA.data();
	//const wchar_t *wB = sB.data();

 //   wchar_t *p = MyReturnStr(L"���յ�", L"����ת��");

	//wstring ws(p);
	//string s;

	////s = UnicodeToUTF8(ws);
	//wcout.imbue(locale("chs"));
	//wcout<<ws.data();

	//cout<<"�Ǻ�";
	//cout<<1;


 //   CallMyReturnStr();
	//CallAdd();

  //int a = add(1, 2);
  //cout<<a;
  //cout<<1;

  ////Py_Initialize(





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
        exec("print os.getcwd()", mainNamespace, mainNamespace);  
    }
    catch( ... )
    {
            if (PyErr_Occurred())  
            PyErr_Print();  
    }

    // �ر�Python
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

	cout<<"�Ǻ�";
	cout<<1;
}

