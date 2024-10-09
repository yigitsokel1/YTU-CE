
public class Villa extends Home {
    public Villa(String location, double price) {
        super(location, price);
    }

    @Override
    public String getCategory() {
        return "Villa";
    }
}
