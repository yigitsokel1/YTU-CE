import subprocess
import tkinter as tk
from tkinter import ttk, messagebox
import pandas as pd
import psycopg2

db = psycopg2.connect(user="postgres",
                      password="1234",
                      host="localhost",
                      port="5432",
                      database="kentselDonusum")
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
table_Box['values'] = ("Ödenmeyen Ücretlere Belirli Oranda Zam Yap", "Firmaların Çalışan Sayısını Belirli Oranda Düşür",
                       "Verilen Yaşın Üstündekileri Emekli Yap")
table_Box.place(relx=0.4, rely=0.1, relwidth=0.35, relheight=0.05)
table_Box.bind("<<ComboboxSelected>>", lambda e: screen.focus())


def choosenTable():
    if table_Box.get() == "Seçiniz...":
        messagebox.showerror("Hata", "Lütfen güncelleme seçimini yapınız!")
    elif table_Box.get() == "Ödenmeyen Ücretlere Belirli Oranda Zam Yap":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        oran_Label = tk.Label(screen, text="Oranı Giriniz", font="20", bg="#112027", fg="White")
        oran_Label.place(relx=0.2, rely=0.2, relwidth=0.2, relheight=0.05)
        oran_Entry = tk.Entry(screen, font="20")
        oran_Entry.place(relx=0.4, rely=0.2, relwidth=0.35, relheight=0.05)

        def calculate():
            tmpOran = 0
            if oran_Entry.get() == "":
                messagebox.showerror("Hata", "Lütfen oranı giriniz!")
            else:
                flag = 1
                try:
                    tmpOran = int(oran_Entry.get())
                    if tmpOran < 0 or tmpOran > 150:
                        messagebox.showerror("Hata", "Lütfen geçerli bir değer giriniz!")
                        flag = 0
                except ValueError:
                    messagebox.showerror("Hata", "Lütfen geçerli bir değer giriniz!")
                    flag = 0
                if flag:
                    butonCalculate.destroy()
                    komut_UPDATE = f"SELECT ucretHesapla({tmpOran / 100});"
                    imlec.execute(komut_UPDATE)
                    db.commit()
                    result = imlec.fetchone()[0]
                    messagebox.showerror("Successful", f"Veri Güncellendi! Toplam zam : {round(result, 2)}")
                    screen.destroy()
                    subprocess.run(["python", "mainScreen.py"])

        butonCalculate = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=calculate)
        butonCalculate.place(relx=0.75, rely=0.2, relwidth=0.05, relheight=0.05)
    elif table_Box.get() == "Firmaların Çalışan Sayısını Belirli Oranda Düşür":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        oran_Label = tk.Label(screen, text="Oranı Giriniz", font="20", bg="#112027", fg="White")
        oran_Label.place(relx=0.2, rely=0.2, relwidth=0.2, relheight=0.05)
        oran_Entry = tk.Entry(screen, font="20")
        oran_Entry.place(relx=0.4, rely=0.2, relwidth=0.35, relheight=0.05)

        def isciCikar():
            tmpOran = 0
            if oran_Entry.get() == "":
                messagebox.showerror("Hata", "Lütfen oranı giriniz!")
            else:
                flag = 1
                try:
                    tmpOran = int(oran_Entry.get())
                    if tmpOran < 0 or tmpOran > 150:
                        messagebox.showerror("Hata", "Lütfen geçerli bir değer giriniz!")
                        flag = 0
                except ValueError:
                    messagebox.showerror("Hata", "Lütfen geçerli bir değer giriniz!")
                    flag = 0
                if flag:
                    butonCikar.destroy()
                    oran_Entry.config(state="disabled")
                    komut_UPDATE = f"SELECT * FROM calisanDusur({tmpOran / 100});"
                    imlec.execute(komut_UPDATE)
                    liste = imlec.fetchall()
                    db.commit()
                    messagebox.showerror("Successful",
                                         "Veriler güncellendi! Sistemde arama sayfasından bakabilirsiniz!")
                    screen.destroy()
                    subprocess.run(["python", "mainScreen.py"])

                #    df = pd.DataFrame(liste)
                #    print(liste)
                #    df = liste
                #    print(df)
                #    table = ttk.Treeview(screen, columns=("sutun1"))
                #    table.heading("#0", text="Firma", anchor='c')
                #    table.heading("sutun1", text="Çıkarılan İşçi", anchor='c')
                #    for veri in liste:
                #        #print(veri[0], veri[1])
                #        table.insert("", "end", text=veri[0], values=(veri[1]))
                #    table.pack(expand=True)

        butonCikar = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=isciCikar)
        butonCikar.place(relx=0.75, rely=0.2, relwidth=0.05, relheight=0.05)
    elif table_Box.get() == "Verilen Yaşın Üstündekileri Emekli Yap":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        yas_Label = tk.Label(screen, text="Yaşı Giriniz", font="20", bg="#112027", fg="White")
        yas_Label.place(relx=0.2, rely=0.2, relwidth=0.2, relheight=0.05)
        yas_Entry = tk.Entry(screen, font="20")
        yas_Entry.place(relx=0.4, rely=0.2, relwidth=0.35, relheight=0.05)

        def emekliYap():
            tmpYas = 0
            if yas_Entry.get() == "":
                messagebox.showerror("Hata", "Lütfen yaşı giriniz!")
            else:
                flag = 1
                try:
                    tmpYas = int(yas_Entry.get())
                    if tmpYas < 0 or tmpYas > 150:
                        messagebox.showerror("Hata", "Lütfen geçerli bir değer giriniz!")
                        flag = 0
                except ValueError:
                    messagebox.showerror("Hata", "Lütfen geçerli bir değer giriniz!")
                    flag = 0
                if flag:
                    butonEmekli.destroy()
                    yas_Entry.config(state="disabled")
                    komut_UPDATE = f"SELECT * FROM emekliYap({tmpYas});"
                    imlec.execute(komut_UPDATE)
                    db.commit()
                    messagebox.showerror("Successful", "Veriler güncellendi! Sistemde arama sayfasından bakabilirsiniz!")
                    screen.destroy()
                    subprocess.run(["python", "mainScreen.py"])

        butonEmekli= tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=emekliYap)
        butonEmekli.place(relx=0.75, rely=0.2, relwidth=0.05, relheight=0.05)


checkTableImage = tk.PhotoImage(file="check.png")
butonCheck = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=choosenTable)
butonCheck.place(relx=0.75, rely=0.1, relwidth=0.05, relheight=0.05)


def back():
    screen.destroy()
    subprocess.run(["python", "mainScreen.py"])


backButton = tk.Button(screen, text="<", font="Times 30 bold", cursor="heart", bg="#112027", fg="White", command=back)
backButton.place(relx=0, rely=0, relwidth=0.1, relheight=0.1)

screen.mainloop()
