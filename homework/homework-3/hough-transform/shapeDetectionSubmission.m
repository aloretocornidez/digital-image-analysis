% HW 3: Hough Transform To Detect Straight Lines

% Read the image, this image is an edge map.
E = imread('edges.png');



% Given from the problem statment.
deltaTheta = 2; deltaRho = 2;


[H, theta, rho] = myhough(E, deltaTheta, deltaRho);


% imshow(-H,[]) % display the peaks as black
imshow(H,[])   % display the peaks as white


% Picked threshold
thresh = 30;

% Calling custom functions.
peaks = myhoughpeaks(H, thresh)
lines = myhoughlines(theta, rho, peaks)

%MYHOUGH Hough Transform To Calculate Hough Array

function [H, theta, rho] = myhough(E, deltaTheta, deltaRho)
    [nrows,ncols] = size(E);

    % The theta and rho matrices are determined from my coordinate system.
       
    %% Determination of Theta
    % Theta goes from -90 degrees to 90 degrees according to my coordinate system. 
    % 0 Degrees is parallel with the horizontal axis of the image.
    % 90 and -90 Degrees are parallel with the vetical axis of the image.
    % Theta goes in a counter-clockwise fashion (similar traditional mathematics).

    % Initialize an array with theta values from -90 --> 90 degrees in increments of deltaTheta.
    % Assuming that deltaTheta is 2, then there are 90 elements in this array.
    theta = -90:deltaTheta:90;

    % Rho goes from the one corner of the image to the other.
    % Initialize an array with rho values from 0 -->  in increments of deltaRho. 
    % Assuming that deltaRho is 2, then there are 100 elements in this array.
    rho = 0:deltaRho:200;

    % These arrays contain the number of elements in each of the generated arrays.
    nTheta = length(theta);
    nRho = length(rho);

    % Initializing a Hough Array with a size of the number of elements in the theta and rho arrays.
    H = zeros(nTheta,nRho);


    % Sweeping every pixel of the image.
    for r = 1:nrows
        for c = 1:ncols

            % Since the imput is an edge map, all values that are not edges will be zero and all values greater than zero are an edge.
            % Is this pixel an edge pixel?
            if E(r,c) > 0

                % Finding every possible line that goes through that edge pixel.
                % We increment theta and start finding every possible rho value with a given theta.
                for i = 0:(nTheta-1)

                    % Finding the position of the pixel in order to convert it to our rho/theta formulation of the pixel.
                    x = c-1;
                    y = r-1;


                    thetaval = -90 + i*deltaTheta;

                    % Calculating the Rho Value with a given theta.
                    rhoval = x*cos(thetaval) + y*sind(thetaval);


                    j = floor(rhoval + 0.5);

                    % Incrementing the Hough Array for this theta and rho value combination.
                    % This combination of theta and rho goes in the hough array.
                    if j >= 0 && j < nRho
                        H(i+1,j+1) = H(i+1,j+1) + 1;
                    end
                end
            end
        end
    end
end % function

%MYHOUGHPEAKS Find Peaks in Hough Array

function peaks = myhoughpeaks(H, thresh)
    [nTheta,nRho] = size(H);
    peaks = [];
    % Add code for cases where (i,j) is along a border of the H array.
    % Finding all of the parameters that exceed the threshold on the left
    % border of the array.
    for i = 1:nTheta
        if H(i, 1) > thresh
            peaks = [peaks; [i, 1]];
        end
    end
    % Finding all of the parameters that exceed the threshold on the top
    % border of the array.
    for j = 1:nRho
        if H(1, j) > thresh
            peaks = [peaks; [1, j]];
        end
    end


    % Here is the code for the interior elements of the H array:
    for i = 2:(nTheta-1)
        for j = 2:(nRho-1)
            % This line checks to make sure that the peak that is being
            % appended is larger than the hough values near the point in the
            % array. This prevents multiple similar lines.
            if H(i,j) >= thresh && H(i,j) >= H(i, j-1) && H(i,j) >= H(i, j+1) && H(i,j) >= H(i+1, j) && H(i,j) >= H(i+1, j-1) && H(i,j) >= H(i+1, j+1) && H(i,j) >= H(i-1, j) && H(i,j) >= H(i-1, j-1) && H(i,j) >= H(i-1, j+1) 
                peaks = [peaks; [i,j]];
            end
        end
    end
end % function

% MYHOUGHLINES Determine Parameters of Lines After Hough Transform
function lines = myhoughlines(theta, rho, peaks)
    lines = [];
    for k = 1:size(peaks,1)
        % This appends each of the peaks that is above the thresholds and puts
        % it in terms of rho and theta.
        lines = [lines; [theta(peaks(k,1)),rho(peaks(k,2))]];
    end
end % function