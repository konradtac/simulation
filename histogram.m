
title('histogram');

fileID = fopen('histUniform.txt','r');
fileID2 = fopen('histExp.txt','r');
formatSpec = '%f';
A = fscanf(fileID,formatSpec);
B = fscanf(fileID2,formatSpec);
hist(A)
figure;
ylabel('tekst');
hist(B)
