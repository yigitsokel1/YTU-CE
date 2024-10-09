
import java.util.ArrayList;
import java.util.HashMap;

public class Customer {
    private String name;
    private ArrayList<Home> homes;
    private double totalPayment;

    public Customer(String name) {
        this.name = name;
        this.homes = new ArrayList<>();
        this.totalPayment = 0;
    }

    public void buyHome(Home home) {
        homes.add(home);
        totalPayment += home.getPrice();
    }

    public double discountedPrice(Home home) {
        if (homes.size() >= 2) {
            if (home instanceof Apartment) {
                return home.getPrice() * 0.95; // 5% discount for apartments
            } else if (home instanceof Villa) {
                return home.getPrice() * 0.90; // 10% discount for villas
            }
        }
        return home.getPrice();
    }

    public void addHomeWithDiscount(Home home) {
        double finalPrice = discountedPrice(home);
        homes.add(home);
        totalPayment += finalPrice;
    }

    public void listHomes() {
        for (Home home : homes) {
            System.out.println(home);
        }
    }

    public void getInfo() {
        System.out.println(name + " has " + homes.size() + " home(s) with total payment: " + totalPayment);
        listHomes();
    }

    public void listLocations() {
        HashMap<String, Integer> locationCount = new HashMap<>();
        for (Home home : homes) {
            locationCount.put(home.getLocation(), locationCount.getOrDefault(home.getLocation(), 0) + 1);
        }
        for (String city : locationCount.keySet()) {
            System.out.println("At city " + city + "---> " + locationCount.get(city) + " home(s)");
        }
    }
}
