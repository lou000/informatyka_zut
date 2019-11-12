% x = input('Wprowadü x:');
% y = input('Wprowadü y:');
% P = input('Wprowadü stopien wielomianu:');
P=3;
userInputX=[4,14,22,25,31,43];
userInputY=[13,41,22,1,122,21];
N = length(userInputX);
assert(P<=N);
assert(length(userInputX) == length(userInputY));
columnX = userInputX';
columnY = userInputY';

specialMatrixSum=zeros(P+1,P+1);
for i=1:N
    firstRow = [];
    specialMatrix = [];
    for k=0:P
       p=userInputX(i)^k;
       firstRow = [firstRow, p];
    end
    for k=0:P
        specialMatrix = [specialMatrix; firstRow];
        firstRow=firstRow*userInputX(i);
    end
    specialMatrixSum=(specialMatrixSum+specialMatrix);
end

specialColumnYSum=zeros(P+1,1);
for i=1:N
    specialColumnY=[];
    for k=0:P
        specialColumnY=[specialColumnY; userInputY(i)*userInputX(i)^k];
    end
    specialColumnYSum = specialColumnYSum+specialColumnY;
end

A = specialMatrixSum\specialColumnYSum;

newX = (min(userInputX)-1):0.1:(max(userInputX)+1);
newX = newX';
vanderMatrixNew = [];
for i= 0:P
    p = newX.^i;
    vanderMatrixNew = [vanderMatrixNew,p];
end
newY = vanderMatrixNew*A;
plot(userInputX,userInputY, 'o', newX, newY)
xlim([min(userInputX)-1, max(userInputX)+1])
