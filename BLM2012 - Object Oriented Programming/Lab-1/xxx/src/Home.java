
public class Home {
    private String location;
    private double price;

    public Home(String location, double price) {
        this.location = location;
        this.price = price;
    }

    public String getLocation() {
        return location;
    }

    public double getPrice() {
        return price;
    }

    public String getCategory() {
        return "Home";
    }

    @Override
    public String toString() {
        return "Home Category: " + getCategory() + ", Price: " + price + ", Location: " + location;
    }
}
