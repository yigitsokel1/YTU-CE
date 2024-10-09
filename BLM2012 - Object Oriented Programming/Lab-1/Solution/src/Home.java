public abstract class Home{
    private double price;
    private String location;


    public Home(double price, String location){
        this.price = price;
        this.location = location;
    }

    abstract public double discountedPrice();
    abstract public String getInfo();

    public double getPrice(){
        return this.price;
    }

    public String getLocation(){
        return this.location;
    }

    public void setPrice(double price){
        this.price = price;
    }

    public void setLocation(String location){
        this.location = location;
    }


}
