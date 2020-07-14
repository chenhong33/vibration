%%读取姿态角-位置数据
function [pxyz]  = getxyz()
%%读取位置数据
[filename, pathname] = uigetfile({'*.xls;*.xlsx';'*.txt'},...
    '导入激光跟踪仪位置数据','MultiSelect','off');  %数据路径读入
if isequal(filename,0)
    error('数据未读入，请重新导入数据！')
else
    disp(['User selected ', fullfile(pathname, filename)])
    [pxyz,TXT,RAW] = xlsread(strcat(pathname,filename),'偏角测试数据');%%测量仪坐标
end
pxyz = str2double(TXT(2:end,3:end));
[m2,n2]=size(pxyz);
if (n2 ~= 3)
    error('关节角数据错误，请重新导入数据！')
end
if(m2<=10)
    error('关节角-位置数据不匹配，请重新导入数据！')
end
end