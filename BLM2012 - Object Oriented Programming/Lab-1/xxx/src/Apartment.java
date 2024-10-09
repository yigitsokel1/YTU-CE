public class Apartment extends Home {
    private double monthlyDues;

    public Apartment(String location, double price, double monthlyDues) {
        super(location, price);
        this.monthlyDues = monthlyDues;
    }

    public double getMonthlyDues() {
        return monthlyDues;
    }

    @Override
    public String getCategory() {
        return "Apartment";
    }

    @Override
    public String toString() {
        return super.toString() + ", Monthly dues: " + monthlyDues;
    }
}
