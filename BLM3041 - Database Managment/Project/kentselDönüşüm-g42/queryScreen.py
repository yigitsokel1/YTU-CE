import tkinter as tk
import subprocess
from tkinter import messagebox, ttk
from tkinter.ttk import Combobox
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
table_Box = Combobox(screen, textvariable=variableTable, state="readonly")
table_Box['values'] = ("Ev Tablosundaki Tüm Veriler", "İnsan Tablosundaki Tüm Veriler", "Firma Tablosundaki Tüm Veriler", "Ücret Tablosundaki Tüm Veriler",
                       "Proje Tablosundaki Tüm Veriler", "Evleri Konumuna Göre Göster", "Firmaların Sınır Üstündeki Ödenmemiş Ücretlerini Göster",
                       "Projesi Başlamamış veya Bitmiş Ev Sahiplerini Göster", "1'den Fazla Proje Yapan ve Çalışan Sayısı 5000 Üzeri Firmalar"
                       )
table_Box.place(relx=0.4, rely=0.1, relwidth=0.35, relheight=0.05)
table_Box.bind("<<ComboboxSelected>>", lambda e: screen.focus())

def choosenTable():
    if table_Box.get() == "Seçiniz...":
        messagebox.showerror("Hata", "Lütfen sorgu yapmak istediğiniz tabloyu seçiniz!")
    elif table_Box.get() == "Ev Tablosundaki Tüm Veriler":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_SELECT = "SELECT * FROM ev;"
        imlec.execute(komut_SELECT)
        liste = imlec.fetchall()
        table = ttk.Treeview(screen, columns=("sutun1", "sutun2", "sutun3", "sutun4"))
        table.heading("#0", text="ID", anchor='c')
        table.heading("sutun1", text="Ev Sahibi TC", anchor='c')
        table.heading("sutun2", text="Kişi Sayısı", anchor='c')
        table.heading("sutun3", text="Konum", anchor='c')
        table.heading("sutun4", text="Bağlı Olduğu Belediye", anchor='c')
        for veri in liste:
            table.insert("", "end", text=veri[0], values=(veri[1], veri[2], veri[3], veri[4]))
        table.pack(expand=True)
    elif table_Box.get() == "Firmaların Sınır Üstündeki Ödenmemiş Ücretlerini Göster":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        sinir_Label = tk.Label(screen, text="Sınır", font="20", bg="#112027", fg="White")
        sinir_Label.place(relx=0.2, rely=0.2, relwidth=0.2, relheight=0.05)
        sinir_Entry = tk.Entry(screen, font="20")
        sinir_Entry.place(relx=0.4, rely=0.2, relwidth=0.3, relheight=0.05)
        def sinirQuery():
            flag = True
            try:
                tmpSinir = int(sinir_Entry.get())
            except ValueError:
                flag=False
                messagebox.showerror("Hata", "Lütfen girdiğiniz değerleri kontrol ediniz!")
            if flag:
                butonSinir.destroy()
                sinir_Entry.config(state="disabled")
                komut_SELECT = f"SELECT firmaisim, SUM(ucret) FROM proje, ucret " \
                               f"WHERE proje.id=ucret.projeid AND odenmedurumu = 'Ödenmedi'" \
                               f"GROUP BY firmaisim HAVING SUM(ucret) >= {sinir_Entry.get()};"
                imlec.execute(komut_SELECT)
                liste = imlec.fetchall()
                table = ttk.Treeview(screen, columns=("sutun1"))
                table.heading("#0", text="Firma", anchor='c')
                table.heading("sutun1", text="Toplam Borç", anchor='c')
                for veri in liste:
                    table.insert("", "end", text=veri[0], values=(veri[1]))
                table.pack(expand=True)
        butonSinir = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=sinirQuery)
        butonSinir.place(relx=0.7, rely=0.2, relwidth=0.05, relheight=0.05)
    elif table_Box.get() == "Evleri Konumuna Göre Göster":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        konum_Label = tk.Label(screen, text="Konum", font="20", bg="#112027", fg="White")
        konum_Label.place(relx=0.2, rely=0.2, relwidth=0.2, relheight=0.05)
        konum_Entry = tk.Entry(screen, font="20")
        konum_Entry.place(relx=0.4, rely=0.2, relwidth=0.3, relheight=0.05)
        def konumQuery():
            butonKonum.destroy()
            konum_Entry.config(state="disabled")
            komut_SELECT = f"SELECT * FROM ev WHERE konum = '{konum_Entry.get()}';"
            imlec.execute(komut_SELECT)
            liste = imlec.fetchall()
            table = ttk.Treeview(screen, columns=("sutun1", "sutun2", "sutun3", "sutun4"))
            table.heading("#0", text="ID", anchor='c')
            table.heading("sutun1", text="Ev Sahibi TC", anchor='c')
            table.heading("sutun2", text="Kişi Sayısı", anchor='c')
            table.heading("sutun3", text="Konum", anchor='c')
            table.heading("sutun4", text="Bağlı Olduğu Belediye", anchor='c')
            for veri in liste:
                table.insert("", "end", text=veri[0], values=(veri[1], veri[2], veri[3], veri[4]))
            table.pack(expand=True)
        butonKonum = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=konumQuery)
        butonKonum.place(relx=0.7, rely=0.2, relwidth=0.05, relheight=0.05)
    elif table_Box.get() == "İnsan Tablosundaki Tüm Veriler":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_SELECT = "SELECT * FROM insan_tumveriler;"
        imlec.execute(komut_SELECT)
        liste = imlec.fetchall()
        table = ttk.Treeview(screen, columns=("sutun1", "sutun2", "sutun3", "sutun4", "sutun5", "sutun6"))
        table.column("sutun1", width=125, stretch=False, minwidth=100)
        table.column("sutun2", width=125, stretch=False, minwidth=250)
        table.column("sutun3", width=125, stretch=False, minwidth=100)
        table.column("sutun4", width=85, stretch=False, minwidth=100)
        table.column("sutun5", width=100, stretch=False, minwidth=100)
        table.column("sutun6", width=175, stretch=False, minwidth=100)
        table.event_generate("<<ThemeChanged>>")
        table.heading("#0", text="TC", anchor='c')
        table.heading("sutun1", text="İsim", anchor='c')
        table.heading("sutun2", text="Soyisim", anchor='c')
        table.heading("sutun3", text="Ev ID", anchor='c')
        table.heading("sutun4", text="Cinsiyet", anchor='c')
        table.heading("sutun5", text="Yaş", anchor='c')
        table.heading("sutun6", text="Meslek", anchor='c')
        for veri in liste:
            table.insert("", "end", text=veri[0], values=(veri[1], veri[2], veri[3], veri[4], veri[5], veri[6]))
        table.pack(expand=True)
    elif table_Box.get() == "Firma Tablosundaki Tüm Veriler":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_SELECT = "SELECT * FROM firma;"
        imlec.execute(komut_SELECT)
        liste = imlec.fetchall()
        table = ttk.Treeview(screen, columns=("sutun1", "sutun2", "sutun3", "sutun4"))
        table.heading("#0", text="İsim", anchor='c')
        table.heading("sutun1", text="Çalışan Sayısı", anchor='c')
        table.heading("sutun2", text="Konum", anchor='c')
        table.heading("sutun3", text="Şube Sayısı", anchor='c')
        table.heading("sutun4", text="Kurulma Tarihi", anchor='c')
        for veri in liste:
            table.insert("", "end", text=veri[0], values=(veri[1], veri[2], veri[3], veri[4]))
        table.pack(expand=True)
    elif table_Box.get() == "Proje Tablosundaki Tüm Veriler":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_SELECT = "SELECT * FROM proje;"
        imlec.execute(komut_SELECT)
        liste = imlec.fetchall()
        table = ttk.Treeview(screen, columns=("sutun1", "sutun2", "sutun3", "sutun4"))
        table.heading("#0", text="ID", anchor='c')
        table.heading("sutun1", text="Ev ID", anchor='c')
        table.heading("sutun2", text="Firma İsmi", anchor='c')
        table.heading("sutun3", text="Evin Yıkılma Tarihi", anchor='c')
        table.heading("sutun4", text="Yeni Evin Yapılma Tarihi", anchor='c')
        for veri in liste:
            table.insert("", "end", text=veri[0], values=(veri[1], veri[2], veri[3], veri[4]))
        table.pack(expand=True)
    elif table_Box.get() == "Ücret Tablosundaki Tüm Veriler":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_SELECT = "SELECT * FROM ucret;"
        imlec.execute(komut_SELECT)
        liste = imlec.fetchall()
        table = ttk.Treeview(screen, columns=("sutun1", "sutun2", "sutun3"))
        table.heading("#0", text="ID", anchor='c')
        table.heading("sutun1", text="Ücret", anchor='c')
        table.heading("sutun2", text="Ödenme Durumu", anchor='c')
        table.heading("sutun3", text="Ödenme Tarihi", anchor='c')
        for veri in liste:
            table.insert("", "end", text=veri[0], values=(veri[1], veri[2], veri[3]))
        table.pack(expand=True)
    elif table_Box.get() == "Projesi Başlamamış veya Bitmiş Ev Sahiplerini Göster":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_SELECT = "(SELECT tc, insan_tumveriler.isim, soyisim FROM insan_tumveriler " \
                       "JOIN ev ON ev.evsahibitc=insan_tumveriler.tc " \
                       "JOIN proje ON ev.id = proje.evid " \
                       "WHERE proje.yikilmatarihi IS NULL) " \
                       "UNION " \
                       "(SELECT tc, insan_tumveriler.isim, soyisim FROM insan_tumveriler " \
                       "JOIN ev ON ev.evsahibitc = insan_tumveriler.tc " \
                       "JOIN proje ON ev.id = proje.evid " \
                       "WHERE proje.yikilmatarihi IS NOT NULL AND proje.yeniyapimtarihi is NOT NULL);"
        imlec.execute(komut_SELECT)
        liste = imlec.fetchall()
        table = ttk.Treeview(screen, columns=("sutun1", "sutun2"))
        table.heading("#0", text="TC", anchor='c')
        table.heading("sutun1", text="İsim", anchor='c')
        table.heading("sutun2", text="Soyisim", anchor='c')
        for veri in liste:
            table.insert("", "end", text=veri[0], values=(veri[1], veri[2]))
        table.pack(expand=True)
    elif table_Box.get() == "1'den Fazla Proje Yapan ve Çalışan Sayısı 5000 Üzeri Firmalar":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_SELECT = "(SELECT firmaisim FROM firma, proje " \
                       "WHERE proje.firmaisim = firma.isim " \
                       "GROUP BY firmaisim " \
                       "HAVING COUNT(*) > 1) " \
                       "INTERSECT " \
                       "(SELECT isim FROM firma " \
                       " WHERE calisansayisi >= 5000);"
        imlec.execute(komut_SELECT)
        liste = imlec.fetchall()
        table = ttk.Treeview(screen)
        table.heading("#0", text="Firma", anchor='c')
        for veri in liste:
            table.insert("", "end", text=veri[0])
        table.pack(expand=True)


    def destroy():
        screen.destroy()
        subprocess.run(["python", "queryScreen.py"])
    butonDestroy = tk.Button(screen, cursor="heart", text="Yeni Sorgu", bg="#112027", fg="White", command=destroy)
    butonDestroy.place(relx=0.8, rely=0, relwidth=0.2, relheight=0.05)


checkTableImage = tk.PhotoImage(file="check.png")
butonCheck = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=choosenTable)
butonCheck.place(relx=0.75, rely=0.1, relwidth=0.05, relheight=0.05)

def back():
    screen.destroy()
    subprocess.run(["python", "mainScreen.py"])

backButton = tk.Button(screen, text="<", font="Times 30 bold", cursor="heart", bg="#112027", fg="White", command=back)
backButton.place(relx=0, rely=0, relwidth=0.1, relheight=0.1)

screen.mainloop()
