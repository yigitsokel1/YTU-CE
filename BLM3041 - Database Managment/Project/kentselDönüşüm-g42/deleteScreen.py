import tkinter as tk
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
table_Box['values'] = ("Yenisi Yapılmış Evlerin Projesini Sil", "Ödenmiş Ücretleri Ücret Tablosundan Sil")
table_Box.place(relx=0.4, rely=0.1, relwidth=0.35, relheight=0.05)
table_Box.bind("<<ComboboxSelected>>", lambda e: screen.focus())

variableProje = tk.StringVar(screen)
variableProje.set("Seçiniz...")

def choosenTable():
    if table_Box.get() == "Seçiniz...":
        messagebox.showerror("Hata", "Lütfen veri silmek istediğiniz seçeneği seçiniz!")
    elif table_Box.get() == "Yenisi Yapılmış Evlerin Projesini Sil":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        proje_Label = tk.Label(screen, text="Projeler", font="20", bg="#112027", fg="White")
        proje_Label.place(relx=0.2, rely=0.2, relwidth=0.2, relheight=0.05)
        proje_Box = ttk.Combobox(screen, textvariable=variableProje, state="readonly", font="20")
        proje_Box.place(relx=0.4, rely=0.2, relwidth=0.35, relheight=0.05)
        komut_SELECT = f"SELECT id FROM proje WHERE yeniyapimtarihi IS NOT NULL;"
        imlec.execute(komut_SELECT)
        tmpList = imlec.fetchall()
        liste = list()
        for satir in tmpList:
            liste.append(satir[0])
        proje_Box['values'] = liste
        proje_Box.bind("<<ComboboxSelected>>", lambda e: screen.focus())

        def chooseProject():
            if proje_Box.get() == "Seçiniz...":
                messagebox.showerror("Hata", "Lütfen projeyi seçiniz!")
            else:
                komut_DELETE = f"DELETE FROM proje WHERE id = {proje_Box.get()}"
                imlec.execute(komut_DELETE)
                db.commit()
                if imlec.rowcount == 1:
                    messagebox.showerror("Successful", "Veri Silindi!")
                else:
                    messagebox.showerror("Trigger Çalıştı", "Ücretini ödemediği için veri silinmedi!")
                screen.destroy()
                subprocess.run(["python", "mainScreen.py"])
        butonProject = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=chooseProject)
        butonProject.place(relx=0.75, rely=0.2, relwidth=0.05, relheight=0.05)
    elif table_Box.get() == "Ödenmiş Ücretleri Ücret Tablosundan Sil":
        butonCheck.destroy()
        table_Box.config(state="disabled")
        komut_DELETE = f"DELETE FROM ucret WHERE odenmedurumu = 'Ödendi'"
        imlec.execute(komut_DELETE)
        db.commit()
        messagebox.showerror("Successful", "Veriler silindi!")

checkTableImage = tk.PhotoImage(file="check.png")
butonCheck = tk.Button(screen, cursor="heart", bg="#112027", image=checkTableImage, command=choosenTable)
butonCheck.place(relx=0.75, rely=0.1, relwidth=0.05, relheight=0.05)

def back():
    screen.destroy()
    subprocess.run(["python", "mainScreen.py"])

backButton = tk.Button(screen, text="<", font="Times 30 bold", cursor="heart", bg="#112027", fg="White", command=back)
backButton.place(relx=0, rely=0, relwidth=0.1, relheight=0.1)

screen.mainloop()
