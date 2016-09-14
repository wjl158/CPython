// PyInterface.cpp : ���� DLL Ӧ�ó���ĵ���������
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
   Py_Initialize();    // ����ǰĿ¼����sys.path    
   //PyRun_SimpleString("import sys");    
   //PyRun_SimpleString("sys.path.append('./')");    // ����hello.pyģ��    
   PyObject *pmodule = PyImport_ImportModule("test1");    // ��ú���xprint���󣬲����ã������hello world/n��    

   PyObject *pfunc = NULL;// PyObject_GetAttrString(pmodule, "xprint");    
   //PyObject_CallFunction(pfunc, NULL);    // �����Hello������ʵ��pinstance��������print��Ա�����������5 6/n��  

   //pfunc = PyObject_GetAttrString(pmodule, "haha");    
   //PyObject_CallFunction(pfunc, "ss", "asf", "sfd");    // �����Hello������ʵ��pinstance��������print��Ա�����������5 6/n��

   PyObject *pReturn = NULL;  
   pfunc = PyObject_GetAttrString(pmodule, "haha1");    
   pReturn = PyObject_CallFunction(pfunc, "ii", x, y);//���ú���  

   //������ֵת��Ϊint����  
   int result;  
   PyArg_Parse(pReturn, "i", &result);//i��ʾת����int�ͱ���  
   Py_Finalize();  

   return result;
   
}

wchar_t* _cdecl MyReturnStr(const wchar_t *x,const wchar_t *y)
{
   Py_Initialize();    // ����ǰĿ¼����sys.path    
   //PyRun_SimpleString("import sys");    
   //PyRun_SimpleString("sys.path.append('./')");    // ����hello.pyģ��    
   PyObject *pmodule = PyImport_ImportModule("test1");    // ��ú���xprint���󣬲����ã������hello world/n�� 

   PyObject *pfunc = NULL;

   PyObject *pReturn = NULL;  

   char szA[100];  
   char szB[100]; 


   pfunc = PyObject_GetAttrString(pmodule, "haha2");    
   pReturn = PyObject_CallFunction(pfunc, "uu", x, y);//���ú���  

   wchar_t *fromPython;
   PyArg_Parse(pReturn, "u", &fromPython);//i��ʾת����int�ͱ���             // add passed Python string 

   Py_Finalize();  


   return fromPython;
}

//��ʼ��
wchar_t* _cdecl My_Py_Initialize()
{
	   Py_Initialize();   
	   if (!Py_IsInitialized())
	   {
		   return L"��ʼ��ʧ��";
	   }
	   else
	   {
		   return L"";
	   }
}


//ж��
void _cdecl My_Py_Finalize()
{
	   Py_Finalize();   

}



///////////////////////////////////////////////һ�µķ���Ҳ��Ч��������Ҫ����Modulename///////////////////////////////////////////////////////////////////////////////////////
////���÷��� �в���
//wchar_t* cdecl My_Py_CallMethodByParam1(const char* ModuleName, const char* MethodName, const wchar_t* Param)
//{
//
//   Py_Initialize(); 
//   PyObject *pfunc = NULL;
//
//   PyObject *pReturn = NULL;  
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // ��ú���xprint���󣬲����ã������hello world/n��    
//
//
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   pReturn = PyObject_CallFunction(pfunc, "u", Param);//���ú���  
//
//   wchar_t *fromPython;
//   PyArg_Parse(pReturn, "u", &fromPython);//i��ʾת����int�ͱ���             // add passed Python string 
//   Py_Finalize();
//
//   return fromPython;
//}
//
////���÷��� �޲���
//wchar_t* cdecl My_Py_CallMethodNoParam1(const char* ModuleName, const char* MethodName)
//{
//	Py_Initialize(); 
//   PyObject *pfunc = NULL;
//
//   PyObject *pReturn = NULL;  
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // ��ú���xprint���󣬲����ã������hello world/n�� 
//
//
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   pReturn = PyObject_CallFunction(pfunc, NULL);//���ú���  
//
//   wchar_t *fromPython;
//   PyArg_Parse(pReturn, "u", &fromPython);//i��ʾת����int�ͱ���             // add passed Python string 
//   Py_Finalize();
//
//   return fromPython;
//
//}
//
////���ù���
//void cdecl My_Py_CallProcByParam1(const char* ModuleName, const char* MethodName, const wchar_t* Param)
//{
//	Py_Initialize(); 
//   PyObject *pfunc = NULL;
//
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // ��ú���xprint���󣬲����ã������hello world/n�� 
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   PyObject_CallFunction(pfunc, "u", Param);//���ú���  
//   Py_Finalize();
//
//
//
//}
//void cdecl My_Py_CallProcNoParam1(const char* ModuleName, const char* MethodName)
//{
//	Py_Initialize(); 
//   PyObject *pfunc = NULL;
//   PyObject *pmodule = PyImport_ImportModule(ModuleName);    // ��ú���xprint���󣬲����ã������hello world/n�� 
//   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
//   PyObject_CallFunction(pfunc, NULL);//���ú���  
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
       PyRun_SimpleString(a);    // ����hello.pyģ��  
   } 
   PyObject *pmodule = PyImport_ImportModule(ModuleName);    
   return pmodule;
}

wchar_t* cdecl My_Py_CallMethodByParam(PyObject *pmodule, const char* MethodName, const wchar_t* Param)
{
   PyObject *pfunc = NULL;

   PyObject *pReturn = NULL;  


   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   pReturn = PyObject_CallFunction(pfunc, "u", Param);//���ú���  

   wchar_t *fromPython;
   PyArg_Parse(pReturn, "u", &fromPython);//i��ʾת����int�ͱ���             // add passed Python string 

   return fromPython;
}

wchar_t* cdecl My_Py_CallMethodNoParam(PyObject *pmodule, const char* MethodName)
{
   PyObject *pfunc = NULL;

   PyObject *pReturn = NULL;   


   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   pReturn = PyObject_CallFunction(pfunc, NULL);//���ú���  

   wchar_t *fromPython;
   PyArg_Parse(pReturn, "u", &fromPython);//i��ʾת����int�ͱ���             // add passed Python string 

   return fromPython;
}


//���÷���
void cdecl My_Py_CallProcByParam(PyObject *pmodule,  const char* MethodName, const wchar_t* Param)
{

   PyObject *pfunc = NULL;
   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   PyObject_CallFunction(pfunc, "u", Param);//���ú���  


}
void cdecl My_Py_CallProcNoParam(PyObject *pmodule,  const char* MethodName)
{
   PyObject *pfunc = NULL;
   pfunc = PyObject_GetAttrString(pmodule, MethodName);    
   PyObject_CallFunction(pfunc, NULL);//���ú���  
}


int cdecl My_PyRun_Simple_String(const char* s)
{
	
     return PyRun_SimpleString(s);  //0 �ɹ� -1 ʧ��
}