import java.util.HashMap;

public class Customer {
    private String name;
    private String telephone;
    private String address;
    private Home [] h;
    private int homeCounter;
    private double payment;

    public Customer(String name, String telephone, String address) {
        this.name = name;
        this.telephone = telephone;
        this.address = address;
        this.h = new Home[10];
        this.homeCounter = 0;
        this.payment = 0;
    }

    public void buyHome(Home home) {
        this.h[homeCounter++] = home;
        this.payment += home.getPrice();
    }

    public void listHome(){
        for (int i = 0; i < this.homeCounter; i++)
            System.out.println(h[i].getInfo());
    }

    public void listLocations() {
        HashMap<String, Integer> locationCount = new HashMap<>();
        for (int i = 0; i < this.homeCounter; i++){
            locationCount.put(h[i].getLocation(), locationCount.getOrDefault(h[i].getLocation(), 0) + 1);
        }
        for (String city : locationCount.keySet()) {
            System.out.println("At city " + city + "---> " + locationCount.get(city) + " home(s)");
        }
    }

    public String getInfo(){
        return this.name + " has " + this.homeCounter + " home(s) with total payment: " + this.payment;
    }

    public String getName() {
        return this.name;
    }

    public String getTelephone() {
        return this.telephone;
    }

    public String getAddress() {
        return this.address;
    }

    public int getHomeCounter() {
        return this.homeCounter;
    }

    public double getPayment() {
        return this.payment;
    }

    public void setName(String newName) {
        this.name = newName;
    }

    public void setTelephone(String newTelephone) {
        this.telephone = newTelephone;
    }

    public void setAddress(String newAddress) {
        this.address = newAddress;
    }

    public void setHomeCounter(int newHomeCounter) {
        this.homeCounter = newHomeCounter;
    }

    public void setPayment(double newPayment) {
        this.payment = newPayment;
    }


}
