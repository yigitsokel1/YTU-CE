public class Villa extends Home{

    public Villa(double price, String location){
        super(price, location);
    }

    @Override
    public double discountedPrice() {
        return getPrice() * 0.9;
    }

    @Override
    public String getInfo() {
        return "Home Category: Villa" + ", Price: " + getPrice() + ", Location: " + getLocation();
    }
}
