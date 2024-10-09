public class Apartment extends Home{

    private double dues;

    public Apartment(double price, String location, double dues) {
        super(price, location);
        this.dues = dues;
    }

    public double getDues() {
        return this.dues;
    }

    public void setDues(double dues) {
        this.dues = dues;
    }

    @Override
    public double discountedPrice() {
        return getPrice() * 0.95;
    }

    @Override
    public String getInfo() {
        return "Home Category: Villa" + ", Price: " + getPrice() + ", Location: " + getLocation()
                + ", Dues: " + dues;
    }

}
