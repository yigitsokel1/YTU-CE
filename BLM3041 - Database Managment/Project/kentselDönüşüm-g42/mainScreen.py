import tkinter as tk
import subprocess



def ekleEkran():
    mainScreen.destroy()
    subprocess.run(["python", "insertScreen.py"])



def sorguEkran():
    mainScreen.destroy()
    subprocess.run(["python", "queryScreen.py"])




def guncelleEkran():
    mainScreen.destroy()
    subprocess.run(["python", "updateScreen.py"])



def silEkran():
    mainScreen.destroy()
    subprocess.run(["python", "deleteScreen.py"])


mainScreen = tk.Tk()
mainScreen.title("Kentsel Dönüşüm Bilgi Sistemi")
mainScreen.geometry("1000x750+250+0")
mainScreen.resizable(False, False)
bg = tk.PhotoImage(file="background.png")
background_Label = tk.Label(mainScreen, image=bg)
background_Label.place(x=0, y=0, relwidth=1, relheight=1)

butonSorgubg = tk.PhotoImage(file="butonSorgu.png")
butonGuncellebg = tk.PhotoImage(file="butonGüncelle.png")
butonSilbg = tk.PhotoImage(file="butonSil.png")
butonEklebg = tk.PhotoImage(file="butonEkle.png")

butonSorgu = tk.Button(mainScreen, cursor="heart", image=butonSorgubg, command=sorguEkran)
butonSorgu.place(relx=0.1, rely=0.2, relwidth=0.25, relheight=0.12)
butonEkle = tk.Button(mainScreen, cursor="heart", image=butonEklebg, command=ekleEkran)
butonEkle.place(relx=0.1, rely=0.4, relwidth=0.25, relheight=0.12)
butonGuncelle = tk.Button(mainScreen, cursor="heart", image=butonGuncellebg, command=guncelleEkran)
butonGuncelle.place(relx=0.6, rely=0.4, relwidth=0.25, relheight=0.12)
butonSil = tk.Button(mainScreen, cursor="heart", image=butonSilbg, command=silEkran)
butonSil.place(relx=0.6, rely=0.2, relwidth=0.25, relheight=0.12)



mainScreen.mainloop()
