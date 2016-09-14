unit PyIntf;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;




type
  TPython = class
  public
    ModuleName: string;
    PyObject: Pointer;
    constructor Create(ModuleName: string; path: string = ''); virtual;

//    //����ģ�鷽��  �в���
//    function CallMethod(MethodName: string; Param: string): string; overload;
//    //����ģ�鷽��  �޲���
//    function CallMethod(MethodName: string): string; overload;

    function CallMethod(MethodName: string; Param: string): string; overload;
    function CallMethod(MethodName: string): string; overload;

//    //����ģ�����
//    procedure CallProc(MethodName: string; Param: string); overload;
//
//    //����ģ�����
//    procedure CallProc(MethodName: string);  overload;

    //����ģ�����
    procedure CallProc(MethodName: string; Param: string); overload;

    //����ģ�����
    procedure CallProc(MethodName: string);  overload;

    //����ģ������ķ���
    function CallClassMethod(clsName: string; MethodName: string):string;

    //ִ�д���
    function ExecStr(Code: string): Boolean;

    function AddPath(path: string): Boolean;


  end;

  function  add(x: integer; y: integer): integer; cdecl;
  function  MyReturnStr(x: PWChar; y: PWChar): PWChar; cdecl;

  //����Python
  function My_Py_Initialize: PWChar; cdecl;

  //�ر�Python
  procedure My_Py_Finalize; cdecl;


  //����ģ��
  function My_PyImport_ImportModule(const path: PAnsiChar; const ModuleName: PAnsiChar): Pointer; cdecl;

//  //���÷���  �в���
//  function My_Py_CallMethodByParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar; Param: string): PWChar; cdecl;
//
//  //���÷���    �޲���
//  function My_Py_CallMethodNoParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar): PWChar; cdecl;

//  //���ù���
//  procedure My_Py_CallProcByParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar; Param: PWChar); cdecl;
//
//  //���ù���
//  procedure My_Py_CallProcNoParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar); cdecl;


  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //���÷���  �в���
  function My_Py_CallMethodByParam(PyObject: Pointer; MethodName: PAnsiChar; Param: string): PWChar; cdecl;
  //���÷���    �޲���
  function My_Py_CallMethodNoParam(PyObject: Pointer; MethodName: PAnsiChar): PWChar; cdecl;

  //���ù���
  procedure My_Py_CallProcByParam(PyObject: Pointer; MethodName: PAnsiChar; Param: PWChar); cdecl;

  //���ù���
  procedure My_Py_CallProcNoParam(PyObject: Pointer;  MethodName: PAnsiChar); cdecl;

  //ִ�д���
  function My_PyRun_Simple_String(const Code: PAnsiChar): integer;cdecl;



implementation


function add; cdecl; external 'PyInterface.dll';
function MyReturnStr; cdecl; external 'PyInterface.dll';

function My_Py_Initialize; cdecl; external 'PyInterface.dll';
procedure My_Py_Finalize; cdecl; external 'PyInterface.dll';
function My_PyImport_ImportModule; cdecl; external 'PyInterface.dll';
//function My_Py_CallMethodByParam1; cdecl; external 'PyInterface.dll';
//function My_Py_CallMethodNoParam1; cdecl; external 'PyInterface.dll';
//procedure My_Py_CallProcByParam1; cdecl; external 'PyInterface.dll';
//procedure My_Py_CallProcNoParam1; cdecl; external 'PyInterface.dll';


function My_Py_CallMethodByParam; cdecl; external 'PyInterface.dll';
function My_Py_CallMethodNoParam; cdecl; external 'PyInterface.dll';
procedure My_Py_CallProcByParam; cdecl; external 'PyInterface.dll';
procedure My_Py_CallProcNoParam; cdecl; external 'PyInterface.dll';
function My_PyRun_Simple_String; cdecl; external 'PyInterface.dll';


{ TPython }


function TPython.AddPath(path: string): Boolean;
begin
  Result := ExecStr('import sys');
//  Result := ExecStr(Format('sys.path.append(''%s'')', [path]));

end;

function TPython.CallClassMethod(clsName, MethodName: string): string;

begin
  Result := '';
end;

//function TPython.CallMethod1(MethodName: string): string;
//begin
//  Result := My_Py_CallMethodNoParam1(PAnsiChar(AnsiString(ModuleName)),PAnsiChar(AnsiString(MethodName)));
//end;
//
//
//function TPython.CallMethod1(MethodName, Param: string): string;
//begin
//  Result := My_Py_CallMethodByParam1(PAnsiChar(AnsiString(ModuleName)),PAnsiChar(AnsiString(MethodName)), PWideChar(WideString(Param)));
//end;

//procedure TPython.CallProc1(MethodName: string);
//begin
//  My_Py_CallProcNoParam1(PAnsiChar(AnsiString(ModuleName)),PAnsiChar(AnsiString(MethodName)));
//end;
//
//procedure TPython.CallProc1(MethodName, Param: string);
//begin
//  My_Py_CallProcByParam1(PAnsiChar(AnsiString(ModuleName)),PAnsiChar(AnsiString(MethodName)), PWideChar(WideString(Param)));
//end;

procedure TPython.CallProc(MethodName, Param: string);
begin
  My_Py_CallProcByParam(Self.PyObject, PAnsiChar(AnsiString(MethodName)), PWideChar(WideString(Param)));
end;

procedure TPython.CallProc(MethodName: string);
begin
  My_Py_CallProcNoParam(Self.PyObject, PAnsiChar(AnsiString(MethodName)));
end;

constructor TPython.Create(ModuleName: string; path: string);
begin
  Self.ModuleName := ModuleName;
  if path = '' then
    PyObject := My_PyImport_ImportModule(nil, PAnsiChar(AnsiString(ModuleName)))
  else
    PyObject := My_PyImport_ImportModule(PAnsiChar(AnsiString(path)), PAnsiChar(AnsiString(ModuleName)));

end;


function TPython.ExecStr(Code: string): Boolean;
begin
 if My_PyRun_Simple_String(PAnsiChar(AnsiString(Code))) = 0 then
   Result := True
 else
   Result := False;
end;

function TPython.CallMethod(MethodName, Param: string): string;
begin
  Result := My_Py_CallMethodByParam(Self.PyObject,PAnsiChar(AnsiString(MethodName)), PWideChar(WideString(Param)));
end;


function TPython.CallMethod(MethodName: string): string;
begin
  Result := My_Py_CallMethodNoParam(Self.PyObject,PAnsiChar(AnsiString(MethodName)));
end;

end.