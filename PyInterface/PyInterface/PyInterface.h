#include <tchar.h>
#include <Python.h>


#ifdef DLL_IMPLEMENT 

#define DLL_API  extern "C" __declspec(dllexport) 

#else 

#define DLL_API  extern "C" __declspec(dllimport) 

#endif 

DLL_API int _cdecl add(int x, int y);
DLL_API wchar_t* _cdecl MyReturnStr(const wchar_t *x,const wchar_t *y);


////���÷���
//DLL_API wchar_t* cdecl My_Py_CallMethodByParam1(const char* ModuleName, const char* MethodName, const wchar_t* Param);
//DLL_API wchar_t* cdecl My_Py_CallMethodNoParam1(const char* ModuleName, const char* MethodName);

////���÷���
//DLL_API void cdecl My_Py_CallProcByParam1(const char* ModuleName, const char* MethodName, const wchar_t* Param);
//DLL_API void cdecl My_Py_CallProcNoParam1(const char* ModuleName, const char* MethodName);



DLL_API wchar_t* _cdecl My_Py_Initialize();    //����Python
DLL_API void _cdecl My_Py_Finalize();          //�ر�Python

//����ģ��
/*DLL_API PyObject* cdecl My_PyImport_ImportModule(const char* ModuleName);*/  
DLL_API PyObject* cdecl My_PyImport_ImportModule(const char* path, const char* ModuleName); 


//���÷��� 
DLL_API wchar_t* cdecl My_Py_CallMethodByParam(PyObject *pmodule, const char* MethodName, const wchar_t* Param);
DLL_API wchar_t* cdecl My_Py_CallMethodNoParam(PyObject *pmodule, const char* MethodName);


//���ù���
DLL_API void cdecl My_Py_CallProcByParam(PyObject *pmodule,  const char* MethodName, const wchar_t* Param);
DLL_API void cdecl My_Py_CallProcNoParam(PyObject *pmodule,  const char* MethodName);

//ִ�нű�
DLL_API int cdecl My_PyRun_Simple_String(const char* s);