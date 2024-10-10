import tkinter as tk
from datetime import datetime

from tkcalendar import DateEntry
from tkinter import ttk, messagebox
import subprocess

import psycopg2

db = psycopg2.connect(user = "postgres",
                      password = "1234",
                      host = "localhost",
                      port = "5432",
                      database = "kentselDonusum")
imlec = db.cursor()



screen = tk.Tk()
screen.title("Kentsel Dönüşüm Bilgi Sistemi")
screen.geometry("1000x750+250+0")
screen.resizable(False, False)
bg = tk.PhotoImage(file="background2.png")
background_Label = tk.Label(screen, image=bg)
background_Label.place(x=0, y=0, relwidth=1, relheight=1)

tables_Label = tk.Label(screen, text="Tablo", font="20", bg="#112027", fg="White")
tables_Label.place(relx=0.2, rely=0.1, relwidth=0.2, relheight=0.05)
variableTable = tk.StringVar(screen)
variableTable.set("Seçiniz...")
table_Box = ttk.Combobox(screen, textvariable=variableTable, state="readonly")
table_Box['values'] = ("Kayıtlı Evlere Yeni İnsan Ekle", "Yeni Proje Dosyası Aç")
table_Box.place(relx=0.4, rely=0.1, relwidth=0.35, relheight=0.05)
table_Box.bind("<<ComboboxSelected>>", lambda e: screen.focus())

variableCinsiyet = tk.StringVar(screen)
variableCinsiyet.set("Seçiniz...")
variableFirma = tk.StringVar(screen)
variableFirma.set("Seçiniz...")


def choosenTable():

    if table_Box.get() == "Seçiniz...":
        messagebox.showerror("Hata", "Lütfen veri eklemek istediğiniz tabloyu seçiniz!")
    elif table_Box.get() == "Kayıtlı Evlere Yeni İnsan Ekle":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        tc_Label = tk.Label(screen, text="TC", font="20", bg="#112027", fg="White")
        tc_Label.place(relx=0.05, rely=0.2, relwidth=0.2, relheight=0.05)
        tc_Entry = tk.Entry(screen, font="20")
        tc_Entry.place(relx=0.275, rely=0.2, relwidth=0.15, relheight=0.05)
        isim_Label = tk.Label(screen, text="İsim", font="20", bg="#112027", fg="White")
        isim_Label.place(relx=0.5, rely=0.2, relwidth=0.2, relheight=0.05)
        isim_Entry = tk.Entry(screen, font="20")
        isim_Entry.place(relx=0.75, rely=0.2, relwidth=0.15, relheight=0.05)
        soyisim_Label = tk.Label(screen, text="Soy İsim", font="20", bg="#112027", fg="White")
        soyisim_Label.place(relx=0.05, rely=0.3, relwidth=0.2, relheight=0.05)
        soyisim_Entry = tk.Entry(screen, font="20")
        soyisim_Entry.place(relx=0.275, rely=0.3, relwidth=0.15, relheight=0.05)
        cinsiyet_Label = tk.Label(screen, text="Cinsiyet", font="20", bg="#112027", fg="White")
        cinsiyet_Label.place(relx=0.5, rely=0.3, relwidth=0.2, relheight=0.05)
        cinsiyet_Box = ttk.Combobox(screen, textvariable=variableCinsiyet, state="readonly", font="20", values=("Erkek", "Kadın"))
        cinsiyet_Box.place(relx=0.75, rely=0.3, relwidth=0.15, relheight=0.05)
        cinsiyet_Box.bind("<<ComboboxSelected>>", lambda e: screen.focus())
        yas_Label = tk.Label(screen, text="Yaş", font="20", bg="#112027", fg="White")
        yas_Label.place(relx=0.05, rely=0.4, relwidth=0.2, relheight=0.05)
        yas_Entry = tk.Entry(screen, font="20")
        yas_Entry.place(relx=0.275, rely=0.4, relwidth=0.15, relheight=0.05)
        meslek_Label = tk.Label(screen, text="Meslek", font="20", bg="#112027", fg="White")
        meslek_Label.place(relx=0.5, rely=0.4, relwidth=0.2, relheight=0.05)
        meslek_Entry = tk.Entry(screen, font="20")
        meslek_Entry.place(relx=0.75, rely=0.4, relwidth=0.15, relheight=0.05)
        evid_Label = tk.Label(screen, text="Ev Numarası", font="20", bg="#112027", fg="White")
        evid_Label.place(relx=0.05, rely=0.5, relwidth=0.2, relheight=0.05)
        evid_Entry = tk.Entry(screen, font="20")
        evid_Entry.place(relx=0.275, rely=0.5, relwidth=0.15, relheight=0.05)
        def insertPeople():
            flag = 1
            if tc_Entry.get() == "" or isim_Entry.get() == "" or soyisim_Entry.get() == "" or cinsiyet_Box.get() == "Seçiniz..." or yas_Entry == "" or meslek_Entry.get() == "":
                messagebox.showerror("Hata", "Lütfen bütün bilgileri doldurunuz!")
            else:
                try:
                    tmp_evid = int(evid_Entry.get())
                    tmp_age = int(yas_Entry.get())
                    tmp_tc = int(tc_Entry.get())
                    length_tc = len(tc_Entry.get())
                    if length_tc != 11:
                        messagebox.showerror("Hata", "TC numaranız 11 haneli olmalıdır!")
                        flag=0
                except ValueError:
                    messagebox.showerror("Hata", "Lütfen bilgileri kontrol ediniz!")
                    flag = 0
                if(flag):
                    try:
                        komut_INSERT = f"INSERT INTO insan VALUES('{tc_Entry.get()}', '{isim_Entry.get()}', '{soyisim_Entry.get()}', {tmp_evid}, " \
                                       f"'{cinsiyet_Box.get()}', '{tmp_age}', '{meslek_Entry.get()}');"
                        imlec.execute(komut_INSERT)
                        db.commit()
                        if imlec.rowcount == 0:
                            messagebox.showerror("Trigger Çalıştı", "Girdiğiniz Ev Numarası Yanlış!")
                        else:
                            messagebox.showerror("Successful", "Veri eklendi!")
                    except psycopg2.Error as e:
                        messagebox.showerror("Hata", "Bilgileri kontrol ediniz! (TC'niz yanlış olabilir)")
                    screen.destroy()
                    subprocess.run(["python", "mainScreen.py"])
        butonInsert = tk.Button(screen, text="Veri Ekle", font="Times 25", cursor="heart", bg="#112027", fg="White", command=insertPeople)
        butonInsert.place(relx=0.4, rely=0.6, relwidth=0.2, relheight=0.1)
    elif table_Box.get() == "Yeni Proje Dosyası Aç":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        evid_Label = tk.Label(screen, text="Ev Numarası", font="20", bg="#112027", fg="White")
        evid_Label.place(relx=0.05, rely=0.2, relwidth=0.2, relheight=0.05)
        evid_Entry = tk.Entry(screen, font="20")
        evid_Entry.place(relx=0.275, rely=0.2, relwidth=0.15, relheight=0.05)
        firma_Label = tk.Label(screen, text="Firma İsmi", font="20", bg="#112027", fg="White")
        firma_Label.place(relx=0.5, rely=0.2, relwidth=0.2, relheight=0.05)
        firma_Box = ttk.Combobox(screen, textvariable=variableFirma, state="readonly", font="20")
        komut_SELECT = f"SELECT isim FROM firma;"
        imlec.execute(komut_SELECT)
        tmpList = imlec.fetchall()
        liste = list()
        for satir in tmpList:
            liste.append(satir[0])
        firma_Box['values'] = liste
        firma_Box.place(relx=0.75, rely=0.2, relwidth=0.15, relheight=0.05)
        firma_Box.bind("<<ComboboxSelected>>", lambda e: screen.focus())
        yikim_Label = tk.Label(screen, text="Yıkım Tarihi", font="20", bg="#112027", fg="White")
        yikim_Label.place(relx=0.05, rely=0.3, relwidth=0.2, relheight=0.05)
        cal1 = DateEntry(screen,select_mode = 'day', font="20")
        cal1.place(relx=0.275, rely=0.3, relwidth=0.15, relheight=0.05)
        yapim_Label = tk.Label(screen, text="Yapım Tarihi", font="20", bg="#112027", fg="White")
        yapim_Label.place(relx=0.5, rely=0.3, relwidth=0.2, relheight=0.05)
        cal2 = DateEntry(screen, select_mode='day', font="20")
        cal2.place(relx=0.75, rely=0.3, relwidth=0.15, relheight=0.05),
        def insertProje():
            flag = 1
            komut_SELECT = f"SELECT MAX(id) FROM ev;"
            date_str = cal1.get()
            date_obj = datetime.strptime(date_str, "%m/%d/%y")
            yikilmaT = date_obj.strftime("%d-%b-%Y")
            print(yikilmaT)
            date_str = cal2.get()
            date_obj = datetime.strptime(date_str, "%m/%d/%y")
            yapimT = date_obj.strftime("%d-%b-%Y")
            print(yapimT)
            imlec.execute(komut_SELECT)
            max_id = imlec.fetchone()[0]
            if evid_Entry.get() == "" or firma_Box.get() == "Seçiniz...":
                messagebox.showerror("Hata", "Lütfen bütün bilgileri doldurunuz!")
            else:
                try:
                    tmpID = int(evid_Entry.get())
                    if tmpID > max_id:
                        messagebox.showerror("Hata", "Bu ev numarası yok!")
                        flag = 0
                    elif yikilmaT >= yapimT:
                        messagebox.showerror("Hata", "Tarihleri kontrol ediniz!")
                        flag=0
                except ValueError:
                    messagebox.showerror("Hata", "Lütfen bilgileri kontrol ediniz!")
                    flag = 0
                if(flag):
                    komut_INSERT = f"INSERT INTO proje VALUES(nextval('projeid_seq'), {evid_Entry.get()}, '{firma_Box.get()}', '{yikilmaT}', '{yapimT}');"
                    imlec.execute(komut_INSERT)
                    db.commit()
                    if imlec.rowcount == 0:
                        messagebox.showerror("Trigger Çalıştı", "Girdiğiniz Ev Numarası Yanlış!")
                    else:
                        messagebox.showerror("Successful", "Veri eklendi!")
                    screen.destroy()
                    subprocess.run(["python", "mainScreen.py"])
        butonInsert = tk.Button(screen, text="Veri Ekle", font="Times 25", cursor="heart", bg="#112027", fg="White", command=insertProje)
        butonInsert.place(relx=0.4, rely=0.6, relwidth=0.2, relheight=0.1)



checkTableImage = tk.PhotoImage(file="check.png")
butonCheck = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=choosenTable)
butonCheck.place(relx=0.7, rely=0.1, relwidth=0.05, relheight=0.05)

def back():
    screen.destroy()
    subprocess.run(["python", "mainScreen.py"])

backButton = tk.Button(screen, text="<", font="Times 30 bold", cursor="heart", bg="#112027", fg="White", command=back)
backButton.place(relx=0, rely=0, relwidth=0.1, relheight=0.1)

screen.mainloop()
