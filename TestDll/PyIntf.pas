unit PyIntf;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;




type
  TPython = class
  public
    List: TStringList;
    CurrModule: string;
    constructor Create();    virtual;
    destructor Destroy; override;

//    //调用模块方法  有参数
//    function CallMethod(MethodName: string; Param: string): string; overload;
//    //调用模块方法  无参数
//    function CallMethod(MethodName: string): string; overload;

    function CallMethod(MethodName: string; Param: string): string; overload;
    function CallMethod(MethodName: string): string; overload;

//    //调用模块过程
//    procedure CallProc(MethodName: string; Param: string); overload;
//
//    //调用模块过程
//    procedure CallProc(MethodName: string);  overload;

    //调用模块过程
    procedure CallProc(MethodName: string; Param: string); overload;

    //调用模块过程
    procedure CallProc(MethodName: string);  overload;

    //调用模块中类的方法
    function CallClassMethod(clsName: string; MethodName: string):string;

    //执行代码
    function ExecStr(Code: string): Boolean;

    function AddPath(path: string): Boolean;

    function Import(ModuleName:string): Boolean;
    function GetCurrModuleObj(CurrModule: string): Pointer;


  end;

  function  add(x: integer; y: integer): integer; cdecl;
  function  MyReturnStr(x: PWChar; y: PWChar): PWChar; cdecl;

  //加载Python
  function My_Py_Initialize: PWChar; cdecl;

  //关闭Python
  procedure My_Py_Finalize; cdecl;


  //加载模块
  function My_PyImport_ImportModule(const path: PAnsiChar; const ModuleName: PAnsiChar): Pointer; cdecl;

//  //调用方法  有参数
//  function My_Py_CallMethodByParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar; Param: string): PWChar; cdecl;
//
//  //调用方法    无参数
//  function My_Py_CallMethodNoParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar): PWChar; cdecl;

//  //调用过程
//  procedure My_Py_CallProcByParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar; Param: PWChar); cdecl;
//
//  //调用过程
//  procedure My_Py_CallProcNoParam1(const ModuleName: PAnsiChar; MethodName: PAnsiChar); cdecl;


  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //调用方法  有参数
  function My_Py_CallMethodByParam(PyObject: Pointer; MethodName: PAnsiChar; Param: string): PWChar; cdecl;
  //调用方法    无参数
  function My_Py_CallMethodNoParam(PyObject: Pointer; MethodName: PAnsiChar): PWChar; cdecl;

  //调用过程
  procedure My_Py_CallProcByParam(PyObject: Pointer; MethodName: PAnsiChar; Param: PWChar); cdecl;

  //调用过程
  procedure My_Py_CallProcNoParam(PyObject: Pointer;  MethodName: PAnsiChar); cdecl;

  //执行代码
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
  Result := ExecStr(Format('sys.path.append(''%s'')', [path]));
  if not Result then
  begin
    ShowMessage('添加路径失败');
  end;

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
  My_Py_CallProcByParam(GetCurrModuleObj(CurrModule), PAnsiChar(AnsiString(MethodName)), PWideChar(WideString(Param)));
end;

procedure TPython.CallProc(MethodName: string);
begin
  My_Py_CallProcNoParam(GetCurrModuleObj(CurrModule), PAnsiChar(AnsiString(MethodName)));
end;

constructor TPython.Create;
begin
  List := TStringList.Create;
end;


destructor TPython.Destroy;
begin

  inherited;
  List.Free;
end;

function TPython.ExecStr(Code: string): Boolean;
begin
 if My_PyRun_Simple_String(PAnsiChar(AnsiString(Code))) = 0 then
   Result := True
 else
   Result := False;
end;

function TPython.GetCurrModuleObj(CurrModule: string): Pointer;
var
  I: integer;
begin
  I := List.IndexOf(CurrModule);
  if I >= 0 then
  begin
    Result := Pointer(List.Objects[I]);
  end
  else
  begin
    Result := nil;
    ShowMessage('获取模块失败');
  end;
end;

function TPython.Import(ModuleName: string): Boolean;
var
  PyObject: Pointer;
begin
  Result := False;
  if List.IndexOf(ModuleName) >= 0 then
  begin
    ShowMessage('已存在同名的模块');
    Exit;
  end;

  PyObject := My_PyImport_ImportModule(nil, PAnsiChar(AnsiString(ModuleName)));
  if PyObject = nil then
  begin
    ShowMessage('导入模块失败');
    Exit;
  end
  else
  begin
      List.AddObject(ModuleName, TObject(PyObject));
      Result := True;
  end;
end;

function TPython.CallMethod(MethodName, Param: string): string;
begin
  Result := My_Py_CallMethodByParam(GetCurrModuleObj(CurrModule),PAnsiChar(AnsiString(MethodName)), PWideChar(WideString(Param)));
end;


function TPython.CallMethod(MethodName: string): string;
begin
  Result := My_Py_CallMethodNoParam(GetCurrModuleObj(CurrModule),PAnsiChar(AnsiString(MethodName)));
end;

end.
