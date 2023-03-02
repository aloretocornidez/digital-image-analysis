<<<<<<< HEAD
% HW 3: Hough Transform To Detect Straight Lines

E = imread('edges.png');

% Getting the number of rows in an image.
[rows, columns, numberOfColorChannels] = size(E);

rows

columns

deltaTheta = 2 
deltaRho = 2



% My hough transform implementation
[H, theta, rho] = myhough(E, deltaTheta, deltaRho);



% % Matlab hough transform implementation
% numpeaks = 3;
% [H, theta, rho] = hough(E);
% peaks = houghpeaks(H, numpeaks);
% lines = houghlines(E, theta, rho, peaks);




% imshow(-H,[]) % display the peaks as black
% imshow(H,[])   % display the peaks as white
% thresh = 2;
% peaks = myhoughpeaks(H, thresh)
% lines = myhoughlines(theta, rho, peaks)






% %MYHOUGH Hough Transform To Calculate Hough Array
function [H, theta, rho] = myhough(E, deltaTheta, deltaRho)
[nrows,ncols] = size(E);
% The theta is determined by dividing the amount of thetas in a circle
% In this case, 360 degrees / deltaTheta
theta = 3.1415926 / deltaTheta * 2:3.1415926 / deltaTheta * 2:3.1415926 / deltaTheta * 2;
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
end % function



%MYHOUGHPEAKS Find Peaks in Hough Array
% function peaks = myhoughpeaks(H, thresh)
% [nTheta,nRho] = size(H);
% peaks = [];
% % Add code for cases where (i,j) is along a border of the H array.
% % Here is the code for the interior elements of the H array:
% for i = 2:(nTheta-1)
%     for j = 2:(nRho-1)
%         if H(i,j) >= thresh && H(i,j) >= H(??) && H(i,j) >= H(??) && etc.
%             peaks = [peaks; [i,j]];
%         end
%     end
% end
% end % function



% %MYHOUGHLINES Determine Parameters of Lines After Hough Transform
% function lines = myhoughlines(theta, rho, peaks)
% lines = [];
% for k = 1:size(peaks,1)
%     lines = [lines; [theta(peaks(k,1)),rho(peaks(k,2))]];
% end
=======
% HW 3: Hough Transform To Detect Straight Lines


% Read the image, this image is an edge map.
E = imread('edges.png');



deltaTheta = 2 
deltaRho = 2



% My hough transform implementation
[H, theta, rho] = myhough(E, deltaTheta, deltaRho);



% % Matlab hough transform implementation
% numpeaks = 3;
% [H, theta, rho] = hough(E);
% peaks = houghpeaks(H, numpeaks);
% lines = houghlines(E, theta, rho, peaks);




% imshow(-H,[]) % display the peaks as black.
% imshow(H,[])   % display the peaks as white.
% thresh = 2;
% peaks = myhoughpeaks(H, thresh)
% lines = myhoughlines(theta, rho, peaks)




% MYHOUGH Hough Transform To Calculate Hough Array
function [H, theta, rho] = myhough(E, deltaTheta, deltaRho)

    % Size of the image.
    [numberOfColumns,numberOfRows] = size(E);


    % The theta is determined by dividing the amount of thetas in a circle
    % In this case, 360 degrees / deltaTheta
    theta = 1:1:1;
    rho = 2:2:2;
    nTheta = length(theta);
    nRho = length(rho);
    H = zeros(nTheta,nRho);

    % Sweeping every pixel
    for r = 1:numberOfRows
        for c = 1:numberOfColumns

            % Is this pixel an edge pixel?
            if E(r,c) > 0


                % Start testing every possible rotation.
                for i = 0:(nTheta-1)
                    

                    % x = ??;
                    % y = ??;
                    x = ??;
                    y = ??;

                    % thetaval = ?? + i*??;
                    thetaval = ?? + i*??;

                    % rhoval = x*?? + y*??;
                    rhoval = x*?? + y*??;

                    j = floor(?? + 0.5);

                    if j >= 0 && j < nRho
                        H(i+1,j+1) = H(i+1,j+1) + 1;
                    end
                end
                
            end
        end
    end
end % function



%MYHOUGHPEAKS Find Peaks in Hough Array
% function peaks = myhoughpeaks(H, thresh)
    % [nTheta,nRho] = size(H);
    % peaks = [];
    % % Add code for cases where (i,j) is along a border of the H array.
    % % Here is the code for the interior elements of the H array:
    % for i = 2:(nTheta-1)
    %     for j = 2:(nRho-1)
    %         if H(i,j) >= thresh && H(i,j) >= H(??) && H(i,j) >= H(??) && etc.
    %             peaks = [peaks; [i,j]];
    %         end
    %     end
    % end
% end % function



% %MYHOUGHLINES Determine Parameters of Lines After Hough Transform
% function lines = myhoughlines(theta, rho, peaks)
    % lines = [];
    % for k = 1:size(peaks,1)
    %     lines = [lines; [theta(peaks(k,1)),rho(peaks(k,2))]];
    % end
>>>>>>> f3628f8196f319b361d2cf205b1a091a47555cc2
% end % function