
% x = input('Wprowadü x:');
% y = input('Wprowadü y:');
userInputX=[2,8,22,13,10,15,4];
userInputY=[11,23,35,47,50,10,30];
N = length(userInputX);
assert(length(userInputX) == length(userInputY));
columnX = userInputX';
columnY = userInputY';

vanderMatrix = [];
for i = 0:N
    p = columnX.^i;
    vanderMatrix = [vanderMatrix,p];
end
A = vanderMatrix\columnY;


newX = (min(userInputX)-1):0.1:(max(userInputX)+1);
newX = newX';
vanderMatrixNew = [];
for i= 0:N
    p = newX.^i;
    vanderMatrixNew = [vanderMatrixNew,p];
end
newY = vanderMatrixNew*A;
plot(userInputX,userInputY, 'o', newX, newY)
xlim([min(userInputX)-1, max(userInputX)+1])