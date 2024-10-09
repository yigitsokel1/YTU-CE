public class EstateAgent {

    private String name;
    private Home [] h = new Home [50];
    int count=0;

    public String getName(){
        return this.getName();
    }

    public void setName(String name){
        this.name = name;
    }

    public void hasHome(Home home){
        h[count++] = home;
    }

    public void listHome(){
        for(int i=0; i<count; i++){
            if (h[i]!=null){
                System.out.println(h[i].getInfo());
            }
        }
    }

    public void sellHome(Home home, Customer customer){
        for(int i=0; i<count; i++){
            if (h[i]==home){
                if(customer.getHomeCounter() >= 2){
                    h[i].setPrice(h[i].discountedPrice());
                }
                customer.buyHome(h[i]);
                h[i]=null;
            }
        }
    }
}
