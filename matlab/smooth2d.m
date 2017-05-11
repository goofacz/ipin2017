function [ out ] = smooth2d(inp,windowSize, func)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

if ~exist('windowSize','var')
    windowSize = 1;
end
if ~exist('func', 'var')
    func = 'mean';
end

[c,r]=size(inp);
out = inp;
for x=1:c
    for y=1:r
        new_val = fVal(inp, x,y, windowSize, func);
        out(x,y) = new_val;
    end
end

end

function new_val = fVal(inp, x, y, wSize, func)

if wSize<1
    wSize=1;
end
if wSize>size(inp,1) || wSize>size(inp,2)
    wSize = min([size(inp,1), size(inp,2)]);
end

minX = max([x-wSize, 1]);
minY = max([y-wSize, 1]);
maxX = min([x+wSize, size(inp,1)]);
maxY = min([y+wSize, size(inp,2)]);

data = inp(minX:maxX, minY:maxY);
dataV = reshape(data,1,size(data,1)*size(data,2));
if strcmpi(func,'max')
    new_val = max(dataV);
elseif strcmpi(func,'min')
    new_val = max(dataV);
elseif strcmpi(func,'median')
    new_val = median(dataV);
else
    new_val = mean(dataV);
end
end