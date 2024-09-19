clc;
clear all;
close all;

[tel,fs] = audioread('tel.wav');

sound(tel);
disp('Bir tusa basiniz!!');
pause;

n = 7;
d = floor(length(tel)/n); 

subplot(1,2,1);
plot(tel);title('Plot');
subplot(1,2,2);
stem(tel);title('Stem');

disp('Bir tusa basiniz!!');
pause;

for i=0:n-1
    telx = tel((i*d)+1:(i+1)*d);


y = fft(telx);

x2 = abs(y/d);
x1 = x2(1:d/2+1);
x1(2:end-1) = 2*x1(2:end-1);
fr = fs*(0:(d/2))/d;
plot(fr,x1); title(i+1,'.sinyal ');
disp('Bir tusa basiniz!!');
pause;    

end

[kayit,fs2] = audioread('kendises.wav');

sound(kayit);
disp('Bir tusa basiniz!!');
pause;

n = 11;
d = floor(length(kayit)/n);

subplot(1,2,1);
plot(kayit);title('Plot');
subplot(1,2,2);
stem(kayit);title('Stem');

disp('Bir tusa basiniz!!');
pause;

for i=0:n-1
    kayitx = kayit((i*d)+1:(i+1)*d);


kayity = fft(kayitx);

kayitx2 = abs(kayity/d);
kayitx1 = kayitx2(1:d/2+1);
kayitx1(2:end-1) = 2*kayitx1(2:end-1);
fr2 = fs2*(0:(d/2))/d;
plot(fr2,kayitx1); title(i+1,'.sinyal ');
disp('Bir tusa basiniz!!');
pause;    

end



