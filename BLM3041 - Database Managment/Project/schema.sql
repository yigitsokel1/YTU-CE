--İnsanlar için tablo oluşturma
CREATE TABLE insan(
	tc char(11) PRIMARY KEY,
	isim varchar(20) NOT NULL,
	soyisim varchar(20) NOT NULL,
	evID INTEGER,
	cinsiyet char(5),
	yas INTEGER CHECK (yas<=100 AND yas >= 0),
	meslek varchar(25)
);


--Evler için tablo oluşturma
CREATE TABLE ev(
	ID serial PRIMARY KEY,
	evsahibiTC char(11) REFERENCES  insan(tc) ON DELETE CASCADE,
	kisiSayisi INTEGER,
	konum varchar(20),
	bagliBelediye varchar(50)
);



--İnşaat firmalarının bulunduğu tabloyu oluşturma
CREATE TABLE firma(
	isim varchar(30) PRIMARY KEY,
	calisanSayisi INTEGER CHECK (calisanSayisi>0),
	konum varchar(20),
	subeSayisi INTEGER CHECK (subeSayisi >= 1),
	kurulmaTarihi DATE
);

--Projelerin bulunduğu tabloyu oluşturma
CREATE TABLE proje(
	ID serial PRIMARY KEY,
	evID INTEGER REFERENCES ev(ID) ON DELETE CASCADE,
	firmaIsim varchar(30) REFERENCES firma(isim) ON DELETE CASCADE,
	yikilmaTarihi DATE,
	yeniYapimTarihi DATE,
	CHECK (yeniYapimTarihi > yikilmaTarihi)
);



--Ücretlerin tutulduğu tabloyu oluşturma
CREATE TABLE ucret(
	projeID INTEGER REFERENCES proje(ID),
	ucret NUMERIC CHECK (ucret > 1000),
	odenmeDurumu varchar(20),
	odenmeTarihi DATE
)

--İnsan tablosundaki evID'lerine foreign key özelliği ekleniyor
ALTER TABLE insan
ADD CONSTRAINT insan_evid_fk FOREIGN KEY(evID) REFERENCES ev(ID);


INSERT INTO ev VALUES
	(1, '10000000000', 4, 'Beşiktaş', 'Beşiktaş Belediyesi'),
	(2, '11111111112', 3, 'Merter', 'Güngören Belediyesi'),
	(3, '12234451112', 2, 'Merter', 'Güngören Belediyesi'),
	(4, '12135484124', 3, 'Üsküdar', 'Üsküdar Belediyesi'),
	(5, '11213215442', 2, 'Sarıyer', 'Sarıyer Belediyesi'),
	(6, '52415642318', 2, 'Beşiktaş', 'Beşiktaş Belediyesi'),
	(7, '54156231542', 1, 'Beşiktaş', 'Beşiktaş Belediyesi'),
	(8, '23415642318', 2, 'Beşiktaş', 'Beşiktaş Belediyesi'),
	(9, '52316546852', 1, 'Şişli', 'Mecidiyeköy Belediyesi'),
	(10, '54112341656', 2, 'Şişli', 'Beşiktaş Belediyesi'),
	(11, '67486412232', 3, 'Şişli', 'Beşiktaş Belediyesi'),
	(12, '85465482132', 6, 'Şişli', 'Beşiktaş Belediyesi'),
	(13, '54123132482', 3, 'Sarıyer', 'Sarıyer Belediyesi'),
	(14, '94546524318', 2, 'Göztepe', 'Kadıköy Belediyesi'),
	(15, '41546524314', 3, 'Kadıköy', 'Kadıköy Belediyesi');


INSERT INTO insan VALUES
	('10000000000', 'Emin', 'Yurdakul', 1, 'Erkek', 54, 'Diş Hekimi'),
	('10000000001', 'Zeynep', 'Yurdakul', 1, 'Kadın', 52, 'Diş Hekimi'),
	('10000000002', 'Cem', 'Yurdakul', 1, 'Erkek', 13, 'Öğrenci'),
	('10000000003', 'Can', 'Yurdakul', 1, 'Erkek', 10, 'Öğrenci'),
	('11111111112', 'Ayşe', 'Çelik', 2, 'Kadın', 40, 'Devlet Memuru'),
	('11111111113', 'Ahmet', 'Çelik', 2, 'Erkek', 39, 'Devlet Memuru'),
	('11111111114', 'Sinem', 'Çelik', 2, 'Kadın', 4, NULL),
	('12234451112', 'Mehmet', 'Erdoğan', 3, 'Erkek', 25, 'Doktor'),
	('45645631238', 'Sinan', 'Baş', 3, 'Erkek', 25, 'Doktor'),
	('12135484124', 'Sevim', 'Tezcan', 4, 'Kadın', 35, 'Muhasebeci'),
	('12135484126', 'Zafer', 'Tezcan', 4, 'Erkek', 35, 'İşletmeci'),
	('12135484128', 'Yasemin', 'Tezcan', 4, 'Kadın', 14, 'Öğrenci'),
	('11213215442', 'Cemil', 'Satış', 5, 'Erkek', 75, 'Emekli'),
	('11213215443', 'Cemile', 'Satış', 5, 'Kadın', 73, 'Emekli'),
	('52415642318', 'Sevgi', 'Ekinci', 6, 'Kadın', 23, 'Serbest Meslek'),
	('52415642319', 'Serdar', 'Ekinci', 6, 'Erkek', 23, 'Esnaf'),
	('54156231542', 'Yiğit', 'Sökel', 7, 'Erkek', 22, 'Bilgisayar Mühendisi'),
	('23415642318', 'Sude', 'Can', 8, 'Kadın', 52, 'Bilgisayar Mühendisi'),
	('23415642319', 'Suat', 'Can', 8, 'Erkek', 52, 'Öğretmen'),
	('52316546852', 'Umut', 'Deşer', 9, 'Erkek', 23, 'Bilgisayar Mühendisi'),
	('54112341656', 'Melisa', 'Koç', 10, 'Kadın', 29, 'Elektrik Mühendisi'),
	('54112341654', 'Melis', 'Dinç', 10, 'Kadın', 29, 'Öğretmen'),
	('67486412232', 'Emir', 'Demir', 11, 'Erkek', 36, 'İşçi'),
	('67486412233', 'Cem', 'Demir', 11, 'Erkek', 36, 'İşçi'),
	('67486412234', 'Aykut', 'Koca', 11, 'Erkek', 36, 'İşçi'),
	('85465482132', 'Ceyda', 'Şen', 12, 'Kadın', 19, 'İşsiz'),
	('85465482133', 'Veli', 'Şen', 12, 'Erkek', 32, 'Makine Mühendisi'),
	('85465482134', 'Cemal', 'Şen', 12, 'Erkek', 40, 'Esnaf'),
	('85465482135', 'Yücel', 'Şen', 12, 'Erkek', 76, 'Emekli'),
	('85465482136', 'Fatma', 'Şen', 12, 'Kadın', 74, 'Emekli'),
	('85465482137', 'Yelda', 'Şen', 12, 'Kadın', 42, 'Hemşire'),
	('54123132482', 'Bora', 'Yılmaz', 13, 'Erkek', 47, 'İnşaat Mühendisi'),
	('54123132483', 'Beril', 'Yılmaz', 13, 'Erkek', 47, 'Öğretmen'),
	('54123132484', 'Bengü', 'Yılmaz', 13, 'Kadın', 3, NULL),
	('94546524318', 'Elgiz', 'Işık', 14, 'Kadın', 41, 'Proje Yöneticisi'),
	('94546524319', 'Ela', 'Kaşık', 14, 'Kadın', 40, 'Pazarlama Müdürü'),
	('41546524314', 'Erol', 'Tan', 15, 'Erkek', 33, 'Esnaf'),
	('41546524315', 'Yeliz', 'Tan', 15, 'Kadın', 33, 'Oyuncu'),
	('41546524316', 'Yeşim', 'Tan', 15, 'Kadın', 8, 'Öğrenci');
	
INSERT INTO firma VALUES
	('Çelik Yapım', 1000, 'Beşiktaş', 3, '01-JAN-2012'),
	('Has İnşaat', 2000, 'Beşiktaş', 6, '22-FEB-1984'),
	('Sağlam Yapım', 1500, 'Şişli', 2, '01-JUN-2006'),
	('Koç Yapım', 500, 'Şişli', 1, '16-MAY-1996'),
	('Gül İnşaat', 6000, 'Kadıköy', 10, '08-AUG-1965'),
	('Demir Yapı', 20000, 'Kadıköy', 8, '05-DEC-2000'),
	('Sevgi Yapım', 3000, 'Sarıyer', 3, '07-SEP-2006'),
	('Sarıyer İnşaat', 300, 'Sarıyer', 1, '12-NOV-2015'),
	('Rüzgar Yapı', 15000, 'Tuzla', 5, '12-OCT-2015'),
	('Kalite İnşaat', 2500, 'Tuzla', 2, '23-APR-2011');


INSERT INTO proje VALUES
	(nextval('projeID_seq'), 1, 'Çelik Yapım', NULL, NULL),
	(nextval('projeID_seq'), 2, 'Has İnşaat', '25-DEC-2022', NULL),
	(nextval('projeID_seq'), 3, 'Demir Yapı', '19-JAN-2021', '22-MAY-2021'),
	(nextval('projeID_seq'), 4, 'Gül İnşaat', NULL, NULL),
	(nextval('projeID_seq'), 5, 'Has İnşaat', '22-FEB-2022', NULL),
	(nextval('projeID_seq'), 6, 'Kalite İnşaat', '15-MAY-2020', '22-DEC-2020'),
	(nextval('projeID_seq'), 7, 'Koç Yapım', '16-APR-2021', NULL),
	(nextval('projeID_seq'), 8, 'Rüzgar Yapı', NULL, NULL),
	(nextval('projeID_seq'), 9, 'Sağlam Yapım', '12-MAR-2021', '25-OCT-2022'),
	(nextval('projeID_seq'), 10, 'Sarıyer İnşaat', '30-JUL-2022', NULL),
	(nextval('projeID_seq'), 11, 'Koç Yapım', '14-APR-2020', '15-APR-2021'),
	(nextval('projeID_seq'), 12, 'Koç Yapım', NULL, NULL),
	(nextval('projeID_seq'), 13, 'Çelik Yapım', '13-FEB-2019', '13-NOV-2019'),
	(nextval('projeID_seq'), 14, 'Rüzgar Yapı', '14-AUG-2022', NULL),
	(nextval('projeID_seq'), 15, 'Gül İnşaat', '01-JAN-2022', '01-JUL-2022');


INSERT INTO ucret VALUES 
	(1, 50000, 'Ödenmedi', NULL),
	(2, 60000, 'Ödendi', '15-DEC-2022'),
	(3, 40000, 'Ödendi', '01-DEC-2020'),
	(4, 55000, 'Ödenmedi', NULL),
	(5, 20000, 'Ödenmedi', NULL),
	(6, 35000, 'Ödendi', '05-MAR-2020'),
	(7, 22500.450, 'Ödendi', '01-MAR-2021'),
	(8, 30000, 'Ödenmedi', NULL),
	(9, 55000, 'Ödendi', '01-JAN-2021'),
	(10, 65000, 'Ödenmedi', NULL),
	(11, 22500.750, 'Ödendi', '02-FEB-2020'),
	(12, 37500.500, 'Ödenmedi', NULL),
	(13, 35000, 'Ödendi', '01-JAN-2019'),
	(14, 27500.100, 'Ödenmedi', NULL),
	(15, 75000, 'Ödenmedi', '01-AUG-2021');


