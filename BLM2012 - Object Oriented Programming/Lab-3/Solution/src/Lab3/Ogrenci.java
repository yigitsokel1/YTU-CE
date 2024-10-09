package Lab3;

import java.io.Serializable;

public class Ogrenci implements Serializable{
	private static final long serialVersionUID = 1L;
	private String ogrenciAdi;
	private String ogrenciNo;
	private int vize;
	private int final_;
	private double genelNot;

	public Ogrenci(String ogrenciAdi, String ogrenciNo, int vize, int final_) {
		this.ogrenciAdi = ogrenciAdi;
		this.ogrenciNo = ogrenciNo;
		this.vize = vize;
		this.final_ = final_;
	}

	public String getOgrenciAdi() {
		return this.ogrenciAdi;
	}

	public String getOgrenciNo() {
		return this.ogrenciNo;
	}

	public int getVize() {
		return this.vize;
	}

	public int getFinal_() {
		return this.final_;
	}

	public double getGenelNot() {
		return this.genelNot;
	}

	public void genelNotHesapla() {
		double vizeCoef = 0.4;
		double finalCoef = 0.6;
        this.genelNot = (vize * vizeCoef) + (final_ * finalCoef);
    }

   
    public String toString() {
        return "Ogrenci no:" + ogrenciNo + " Ogrenci Adi: " + ogrenciAdi + " Genel not: " + this.genelNot;
    }
}
