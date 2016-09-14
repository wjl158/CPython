// PyInterface.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <Windows.h>

#define DLL_IMPLEMENT 
#include "PyInterface.h"
#include <Python.h>  


BOOL StringReverseW (PWSTR pWideCharStr);
BOOL StringReverseA (PSTR pMultiByteStr);

#ifdef UNICODE
#define StnngReverse StringReverseW
#else
#define StringRevcrsc StringReverseA
#endif // UNICODE



int _cdecl add(int x, int y)
{
  //Py_Finalize();
   Py_Initialize();    // 将当前目录加入sys.path    
   //PyRun_SimpleString("import sys");    
   //PyRun_SimpleString("sys.path.append('./')");    // 导入hello.py模块    
   PyObject *pmodule = PyImport_ImportModule("test1");    // 获得函数xprint对象，并调用，输出“hello world/n”    

   PyObject *pfunc = NULL;// PyObject_GetAttrString(pmodule, "xprint");    
   //PyObject_CallFunction(pfunc, NULL);    // 获得类Hello并生成实例pinstance，并调用print成员函数，输出“5 6/n”  

   //pfunc = PyObject_GetAttrString(pmodule, "haha");    
   //PyObject_CallFunction(pfunc, "ss", "asf", "sfd");    // 获得类Hello并生成实例pinstance，并调用print成员函数，输出“5 6/n”

   PyObject *pReturn = NULL;  
   pfunc = PyObject_GetAttrString(pmodule, "haha1");    
   pReturn = PyObject_CallFunction(pfunc, "ii", x, y);//调用函数  

   //将返回值转换为int类型  
   int result;  
   PyArg_Parse(pReturn, "i", &result);//i表示转换成int型变量  
   Py_Finalize();  

   return result;
   
}

wchar_t* _cdecl MyReturnStr(const wchar_t *x,const wchar_t *y)
{
   Py_Initialize();    // 将当前目录加入sys.path    
   //PyRun_SimpleString("import sys");    
   //PyRun_SimpleString("sys.path.append('./')");    // 导入hello.py模块    
   PyObject *pmodule = PyImport_ImportModule("test1");    // 获得函数xprint对象，并调用，输出“hello world/n” 

   PyObject *pfunc = NULL;

   PyObject *pReturn = NULL;  

   char szA[100];  
   char szB[100]; 


   pfunc = PyObject_GetAttrString(pmodule, "haha2");    
   pReturn = PyObject_CallFunction(pfunc, "uu", x, y);//调用函数  

   wchar_t *fromPython;
   PyArg_Parse(pReturn, "u", &fromPython);//i表示转换成int型变量             // add passed Python string 

   Py_Finalize();  


   return fromPython;
}

//初始化
wchar_t* _cdecl My_Py_Initialize()
{
	   Py_Initialize();   
	   if (!Py_IsInitialized())
	   {
		   return L"初始化失败";
	   }
	   else
	   {
		   return L"";
	   }
}


//卸载
void _cdecl My_Py_Finalize()
{
	   Py_Finalize();   

}



///////////////////////////////////////////////一下的方法也有效果，不过要传入Modulename///////////////////////////////////////////////////////////////////////////////////////
////调用方法 有参数
//wchar_t* cdecl My_Py_CallMethodByParam1(const char* ModuleName, const char* MethodName, const wchar_t* Param)
//{
//
//   Py_Initialize(); 
//   PyObject *pfunc = NULL;
//
//   PyObject *pReturn = NULL;  
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // 获得函数xprint对象，并调用，输出“hello world/n”    
//
//
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   pReturn = PyObject_CallFunction(pfunc, "u", Param);//调用函数  
//
//   wchar_t *fromPython;
//   PyArg_Parse(pReturn, "u", &fromPython);//i表示转换成int型变量             // add passed Python string 
//   Py_Finalize();
//
//   return fromPython;
//}
//
////调用方法 无参数
//wchar_t* cdecl My_Py_CallMethodNoParam1(const char* ModuleName, const char* MethodName)
//{
//	Py_Initialize(); 
//   PyObject *pfunc = NULL;
//
//   PyObject *pReturn = NULL;  
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // 获得函数xprint对象，并调用，输出“hello world/n” 
//
//
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   pReturn = PyObject_CallFunction(pfunc, NULL);//调用函数  
//
//   wchar_t *fromPython;
//   PyArg_Parse(pReturn, "u", &fromPython);//i表示转换成int型变量             // add passed Python string 
//   Py_Finalize();
//
//   return fromPython;
//
//}
//
////调用过程
//void cdecl My_Py_CallProcByParam1(const char* ModuleName, const char* MethodName, const wchar_t* Param)
//{
//	Py_Initialize(); 
//   PyObject *pfunc = NULL;
//
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // 获得函数xprint对象，并调用，输出“hello world/n” 
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   PyObject_CallFunction(pfunc, "u", Param);//调用函数  
//   Py_Finalize();
//
//
//
//}
//void cdecl My_Py_CallProcNoParam1(const char* ModuleName, const char* MethodName)
//{
//	Py_Initialize(); 
//   PyObject *pfunc = NULL;
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // 获得函数xprint对象，并调用，输出“hello world/n” 
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   PyObject_CallFunction(pfunc, NULL);//调用函数  
//   Py_Finalize();
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PyObject* cdecl My_PyImport_ImportModule(const char* path, const char* ModuleName)  
{
   char a[100];
   if (path != NULL)
   {
       PyRun_SimpleString("import sys");    
	   sprintf_s(a, "sys.path.append('%s')", path);
       PyRun_SimpleString(a);    // 导入hello.py模块  
   } 
   PyObject *pmodule = PyImport_ImportModule(ModuleName);    
   return pmodule;
}

wchar_t* cdecl My_Py_CallMethodByParam(PyObject *pmodule, const char* MethodName, const wchar_t* Param)
{
   PyObject *pfunc = NULL;

   PyObject *pReturn = NULL;  


   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   pReturn = PyObject_CallFunction(pfunc, "u", Param);//调用函数  

   wchar_t *fromPython;
   PyArg_Parse(pReturn, "u", &fromPython);//i表示转换成int型变量             // add passed Python string 

   return fromPython;
}

wchar_t* cdecl My_Py_CallMethodNoParam(PyObject *pmodule, const char* MethodName)
{
   PyObject *pfunc = NULL;

   PyObject *pReturn = NULL;   


   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   pReturn = PyObject_CallFunction(pfunc, NULL);//调用函数  

   wchar_t *fromPython;
   PyArg_Parse(pReturn, "u", &fromPython);//i表示转换成int型变量             // add passed Python string 

   return fromPython;
}


//调用方法
void cdecl My_Py_CallProcByParam(PyObject *pmodule,  const char* MethodName, const wchar_t* Param)
{

   PyObject *pfunc = NULL;
   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   PyObject_CallFunction(pfunc, "u", Param);//调用函数  


}
void cdecl My_Py_CallProcNoParam(PyObject *pmodule,  const char* MethodName)
{
   PyObject *pfunc = NULL;
   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   PyObject_CallFunction(pfunc, NULL);//调用函数  
}


int cdecl My_PyRun_Simple_String(const char* s)
{
	
     return PyRun_SimpleString(s);  //0 成功 -1 失败
}