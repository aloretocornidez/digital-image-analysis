% HW 3: Hough Transform To Detect Straight Lines

E = imread('edges.png');

deltaTheta = 2; deltaRho = 2;
[H, theta, rho] = myhough(E, deltaTheta, deltaRho);
%imshow(-H,[]) % display the peaks as black
imshow(H,[])   % display the peaks as white
thresh = ??;
peaks = myhoughpeaks(H, thresh)
lines = myhoughlines(E, theta, rho, peaks)

function [H, theta, rho] = myhough(E, deltaTheta, deltaRho)
    [nrows,ncols] = size(E);
    theta = ??:??:??;
    rho = ??:??:??;
    nTheta = length(theta);
    nRho = length(rho);
    H = zeros(nTheta,nRho);
    for r = 1:nrows
        for c = 1:ncols
            if E(r,c) > 0
                for i = 0:(nTheta-1)
                    x = ??;
                    y = ??;
                    thetaval = ?? + i*??;
                    rhoval = x*?? + y*??;
                    j = floor(?? + 0.5);
                    if j >= 0 && j < nRho
                        H(i+1,j+1) = H(i+1,j+1) + 1;
                    end
                end
            end
        end
    end
end

function peaks = myhoughpeaks(H, thresh)
    [nTheta,nRho] = size(H);
    peaks = [];
    % Add code for cases where (i,j) is along a border of the H array.
    % Here is the code for the interior elements of the H array:
    for i = 2:(nTheta-1)
        for j = 2:(nTheta-1)
            if H(i,j) >= thresh && H(i,j) >= H(??) && H(i,j) >= H(??) && etc.
                peaks = [peaks; [i,j]];
            end
        end
    end
end

function lines = myhoughlines(E, theta, rho, peaks)
    lines = [];
    for k = 1:size(peaks,1)
        lines = [lines; [theta(peaks(k,1)),rho(peaks(k,2))]];
    end
end