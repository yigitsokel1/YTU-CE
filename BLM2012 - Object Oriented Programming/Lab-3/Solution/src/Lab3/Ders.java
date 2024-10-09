package Lab3;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.LinkedList;

public class Ders {

	private String dersAdi;
	private LinkedList<Ogrenci> ogrenciler;
	private int subeASayisi;
	private int subeBSayisi;
	private int ogrenciSayisi;
	
	public Ders(String dersAdi) {
		this.dersAdi = dersAdi;
        ogrenciler = new LinkedList<>();
	}
	
	public String getDersAdi() {
		return this.dersAdi;
	}
	
	public void setDersAdi(String dersAdi) {
		this.dersAdi = dersAdi;
	}
	
	public LinkedList<Ogrenci> getOgrenciler() {
		return this.ogrenciler;
	}
	
	public void dosyaOku(String dosyaAdi) throws IOException {
		try {
            ObjectInputStream input = new ObjectInputStream(new FileInputStream(dosyaAdi));
            ogrenciler = (LinkedList<Ogrenci>) input.readObject();
            input.close();
        } catch (ClassNotFoundException e1) {
            e1.printStackTrace();
        } catch (IOException e2) {

            e2.printStackTrace();
        }
        this.ogrenciSayisi = ogrenciler.size();
	}

	
	public void gruplayaAyir() {
		subeASayisi = ogrenciSayisi / 2;
        subeBSayisi = ogrenciSayisi - subeASayisi;
	}
	
	public void ekranaYazdir() {
		for (Ogrenci o : ogrenciler) {
            System.out.println(o.toString());
        }
	}
	
	public void hesapla() {
        Thread t1 = new Thread(new Hesapla(0, subeASayisi));
        t1.start();
        Thread t2 = new Thread(new Hesapla(subeASayisi, ogrenciler.size()));
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
	
	
	public class Hesapla implements Runnable {
		private int i;
        private int j;

        public Hesapla(int i, int j) {
            this.i = i;
            this.j = j;
        }

        public void run() {
            for (int k = i; k < j; k++) {
                (ogrenciler.get(k)).genelNotHesapla();
            }
        }
	}
	
}
