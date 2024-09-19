clc;clear all;close all;

x = [];
y = [];
n = [];
m = [];
size1 = input("1.Sistemin eleman sayisini giriniz=");
for i=1:size1
    x(i) = input("Elemanlari giriniz=");
end
ref = input("Kacinci eleman 0 noktasındadir=");
for i=1:size1
    n(i) = i - ref;
end

size2 = input("2.Sistemin eleman sayisini giriniz=");
for i=1:size2
    y(i) = input("Elemanlari giriniz=");
end
ref = input("Kacinci eleman 0 noktasındadir=");
for i=1:size2
    m(i) = i - ref;
end

%% Değerleri ekrana yazdırmak
subplot(2,2,1)
stem(n,x),title('x[n]');
subplot(2,2,2)
stem(m,y),title('y[n]');
mycon = myConv(x,y);
for i=1:1:(size1+size2-1)
    label(i) = n(1)+i-1;
end
subplot(2,2,3); 
stem(label,mycon),title("My Convolution");
conhazir = conv(x,y);
subplot(2,2,4)
stem(label,conhazir),title("Internet Convolution");
fprintf('x =');
disp(x);
fprintf('y =');
disp(y);
fprintf('My convolution = ');
disp(mycon);
fprintf('Internet Convolution = ');
disp(conhazir);

pause(5);

%% 5 Saniye Ses kaydetme
recObj = audiorecorder; %% kayıt başlatma nesnesi
disp('Start speaking.'); %% ekrana mesaj
recordblocking(recObj, 5); %% kayıt işlemi
disp('End of Recording.'); %% ekrana mesaj
x1 = getaudiodata(recObj); %% kaydedilen sesi x değişkenine saklama

%% 10 Saniye Ses kaydetme
recObj = audiorecorder; %% kayıt başlatma nesnesi
disp('Start speaking.'); %% ekrana mesaj
recordblocking(recObj, 10); %% kayıt işlemi
disp('End of Recording.'); %% ekrana mesaj
x2 = getaudiodata(recObj); %% kaydedilen sesi x değişkenine saklama

h = zeros(1,1000);
h(1) = 1;h(401) = 0.4; h(801) = 0.4;

my_y1 = myConv(x1,h);
my_y2 = myConv(x2,h);
y1 = conv(x1,h);
y2 = conv(x2,h);

%% Sesleri dışa verme
sound(x1);
pause(6);
sound(x2);
pause(11);
sound(my_y1);
pause(6);
sound(my_y2);
pause(11);
sound(y1);
pause(6);
sound(y2);

%% Konvolüsyon Fonksiyonu
function con = myConv(x,y)

N = length(x);
M = length(y);

if N >= M

    for i=1:N+M-1
        con(i) = 0;
        for j=i:-1:1
            if (j <= N && i-j+1 <= M)
               con(i) = con(i) + x(j)*y(i-j+1);
            else
              con(i) = con(i) + 0;
            end
        end
    end
else 
     for i=1:N+M-1
        con(i) = 0;
        for j=i:-1:1
            if (j <= M && i-j+1 <= N)
               con(i) = con(i) + y(j)*x(i-j+1);
            else
              con(i) = con(i) + 0;
            end
        end
    end
    
end
end