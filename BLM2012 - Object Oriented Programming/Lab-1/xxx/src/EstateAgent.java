import java.util.ArrayList;

public class EstateAgent {
    private ArrayList<Home> homesForSale;

    public EstateAgent() {
        homesForSale = new ArrayList<>();
    }

    public void hasHome(Home home) {
        homesForSale.add(home);
    }

    public void sellHome(Home home, Customer customer) {
        customer.addHomeWithDiscount(home);
        homesForSale.remove(home);
    }

    public void listHomes() {
        if (homesForSale.isEmpty()) {
            System.out.println("No homes available.");
        } else {
            for (Home home : homesForSale) {
                System.out.println(home);
            }
        }
    }
}
