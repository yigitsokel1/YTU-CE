
--Sequence oluşturma
CREATE SEQUENCE evid_seq
START WITH 16
INCREMENT BY 1;

CREATE SEQUENCE projeID_seq
START WITH 1
INCREMENT BY 1;

--View oluşturma
CREATE VIEW insan_tumveriler
AS
SELECT * FROM insan


--Sorgu1
SELECT * FROM ev;

--Sorgu2
SELECT * FROM ev WHERE konum = '{konum_Entry.get()}';

--Sorgu3
SELECT * FROM insan_tumveriler;

--Sorgu4
SELECT * FROM firma;

--Sorgu5
SELECT * FROM proje;

--Sorgu6
SELECT * FROM ucret;

--Aggregate ve Having içeren sorgu
SELECT firmaisim, SUM(ucret) FROM proje, ucret 
WHERE proje.id=ucret.projeid AND odenmedurumu = 'Ödenmedi'
GROUP BY firmaisim 
HAVING SUM(ucret) >= {sinir_Entry.get()};

--Union içeren sorgu
(SELECT tc, insan_tumveriler.isim, soyisim FROM insan_tumveriler
JOIN ev ON ev.evsahibitc = insan_tumveriler.tc
JOIN proje ON ev.id = proje.evid
WHERE proje.yikilmatarihi IS NULL)

UNION

(SELECT tc, insan_tumveriler.isim, soyisim FROM insan_tumveriler
JOIN ev ON ev.evsahibitc = insan_tumveriler.tc
JOIN proje ON ev.id = proje.evid
WHERE proje.yikilmatarihi IS NOT NULL AND proje.yeniyapimtarihi is NOT NULL)


--Intersect ve Aggregate Fonksiyon içeren sorgu
(SELECT firmaisim FROM firma, proje
WHERE proje.firmaisim = firma.isim
GROUP BY firmaisim
HAVING COUNT(*) > 1)

INTERSECT

(SELECT isim FROM firma
 WHERE calisansayisi >= 5000); 

--İnsan tablosu insert trigger
CREATE FUNCTION trig_fonk_insert_people()
RETURNS TRIGGER AS $$
BEGIN
    BEGIN
    UPDATE ev
    SET kisisayisi = kisisayisi+1
    WHERE new.evid = id;
    RETURN NEW;
END;
$$ LANGUAGE 'plpgsql';


CREATE TRIGGER t_insert_people
BEFORE INSERT
ON insan
FOR EACH ROW EXECUTE PROCEDURE trig_fonk_insert_people();

--Proje tablosu insert trigger
CREATE FUNCTION trig_fonk_insert_proje()
RETURNS TRIGGER AS $$
DECLARE
    evid_table CURSOR FOR SELECT evid FROM proje;
BEGIN
    FOR satir IN evid_table LOOP
        IF (satir.evid = new.evid) THEN
            RETURN NULL;
        END IF;
    END LOOP;
    RETURN NEW;
END;
$$ LANGUAGE 'plpgsql';


CREATE TRIGGER t_insert_proje
BEFORE INSERT
ON proje
FOR EACH ROW EXECUTE PROCEDURE trig_fonk_insert_proje();

--Proje tablosu delete trigger
CREATE FUNCTION trig_fonk_delete_proje()
RETURNS TRIGGER AS $$
DECLARE
    status varchar(20);
BEGIN
    SELECT odenmedurumu INTO status FROM ucret
    WHERE ucret.projeid = old.id;
    IF status = 'Ödenmedi' THEN
        RETURN NULL;
    ELSE
        RETURN OLD;
    END IF; 
        
END;
$$ LANGUAGE 'plpgsql';


CREATE TRIGGER t_delete_proje
BEFORE delete
ON proje
FOR EACH ROW EXECUTE PROCEDURE trig_fonk_delete_proje();

--Insert1
INSERT INTO insan VALUES('{tc_Entry.get()}', '{isim_Entry.get()}', '{soyisim_Entry.get()}', {tmp_evid}, '{cinsiyet_Box.get()}', '{tmp_age}', '{meslek_Entry.get()}');

--Insert2
INSERT INTO proje VALUES(nextval('projeid_seq'), {evid_Entry.get()}, '{firma_Box.get()}', '{yikilmaT}', '{yapimT}');

--Delete1
DELETE FROM proje WHERE id = {proje_Box.get()}

--Delete2
DELETE FROM ucret WHERE odenmedurumu = 'Ödendi'

--Ücretleri belirli oranda zamlama fonksiyonu
CREATE OR REPLACE FUNCTION ucretHesapla(oran NUMERIC)
RETURNS NUMERIC AS $$
DECLARE 
    tmp NUMERIC;
    curs CURSOR FOR SELECT ucret, odenmedurumu FROM ucret;
BEGIN
    tmp = 0;
    FOR satir IN curs LOOP
        IF satir.odenmedurumu = 'Ödenmedi' THEN
            tmp = tmp + satir.ucret * oran;
        END IF;
    END LOOP;
    UPDATE ucret
    SET ucret = ucret + ucret*oran
    WHERE odenmedurumu = 'Ödenmedi';
    RETURN tmp;
END;
$$ LANGUAGE 'plpgsql';


--Type/Record oluşturma
  CREATE TYPE firmaSayi AS (isim varchar(30), sayi integer)


--Firmadaki çalışan sayısını azaltan fonksiyon
CREATE OR REPLACE FUNCTION calisandusur(oran NUMERIC)
RETURNS firmaSayi[] AS $$
DECLARE 
    fir firmaSayi[];
    curs CURSOR FOR SELECT isim, calisanSayisi FROM firma;
    i integer;
BEGIN
    i = 1;
    FOR satir IN curs LOOP
        fir[i].isim = satir.isim;
        fir[i].sayi = floor(satir.calisansayisi * oran);
        i = i+1;
    END LOOP;
    UPDATE firma
    SET calisansayisi = calisansayisi - floor(calisansayisi * oran);
    RETURN fir;
END;
$$ LANGUAGE 'plpgsql';

--Verilen yaşın üstünü emekli yapma fonksiyonu
CREATE OR REPLACE FUNCTION emekliYap(yasEmekli INTEGER)
RETURNS VOID AS $$
BEGIN
    UPDATE insan
    SET meslek = 'Emekli'
    WHERE yas >= yasEmekli;
END;
$$ LANGUAGE 'plpgsql';

--Update1
SELECT ucretHesapla({tmpOran / 100});

--Update2
SELECT * FROM calisanDusur({tmpOran / 100});


--Update3
SELECT * FROM emekliYap({tmpYas});
            