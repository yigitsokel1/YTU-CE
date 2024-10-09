package Lab3;

import java.io.IOException;

public class Main {

	public static void main(String[] args) throws IOException {
		Ders ders = new Ders("OOP");
		ders.dosyaOku("ogrenci.ser");
        ders.gruplayaAyir();
        ders.hesapla();
        ders.ekranaYazdir();
	}

}
