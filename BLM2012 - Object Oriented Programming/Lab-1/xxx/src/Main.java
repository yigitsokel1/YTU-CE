public class Main {

    public static void main(String[] args) {
        EstateAgent agent = new EstateAgent();

        // Add homes to the estate agent's listing
        agent.hasHome(new Apartment("Istanbul", 700, 1000));
        agent.hasHome(new Apartment("Ankara", 550, 750));
        agent.hasHome(new Villa("Ankara", 350));
        agent.hasHome(new Villa("Ankara", 400));

        System.out.println("Welcome to ABC Real Estate Agent");
        System.out.println("Here is the homes:");
        agent.listHomes();

        // Create a customer
        Customer customer = new Customer("Ali Deniz");

        // Sell homes to the customer
        agent.sellHome(new Apartment("Istanbul", 700, 1000), customer);
        agent.sellHome(new Villa("Ankara", 350), customer);
        agent.sellHome(new Villa("Ankara", 400), customer);

        System.out.println("-----------After Sales---------------------------------------");
        System.out.println("Welcome to ABC Real Estate Agent");
        System.out.println("Here is the homes:");
        agent.listHomes();

        // Customer info
        customer.getInfo();

        // List locations
        customer.listLocations();
    }
}
