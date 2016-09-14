unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, PyIntf;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    PY: TPython;
  end;

var
  Form1: TForm1;


implementation


{$R *.dfm}


procedure TForm1.Button1Click(Sender: TObject);
var
  str: string;
begin

   PY.AddPath('./');
   PY.AddPath('./Script');
   PY.Import('PyTest001');   //�������·������ͬ��ģ�飬�������·��Ϊ׼��

   PY.CurrModule := 'PyTest001';  //���õ�ǰģ��

   str := PY.CallMethod('GetDictValue', '{''a'':''���'',}');  //�����ֵ���a��ֵ ���
   ShowMessage(str);

   str := PY.CallMethod('Add', '(1,2)');   //���� 1 + 2 �ĺ� 3
   ShowMessage(str);

   str := PY.CallMethod('ReturnStr');
   ShowMessage(str);





end;

procedure TForm1.Button2Click(Sender: TObject);
var
  str:string;
begin
   PY.AddPath('./Script');
   PY.Import('GetUrl');   //�������·������ͬ��ģ�飬�������·��Ϊ׼��
   PY.CurrModule := 'GetUrl';
   str := PY.CallMethod('Go');
   Memo1.Lines.Clear;
   Memo1.Lines.Text := str;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  str: string;
begin
  str := My_Py_Initialize;
  if str <> '' then
  begin
    ShowMessage(str);
  end;
  PY := TPython.Create;


end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  My_Py_Finalize;
end;

end.
