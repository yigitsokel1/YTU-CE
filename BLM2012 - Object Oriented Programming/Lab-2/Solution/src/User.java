import java.util.HashMap;
import java.util.LinkedList;

public class User {
    private String name;

    User(String name) {
        this.name = name;
    }


    public String getName() {
        return this.name;
    }

    public String toString() {
        return "User{" +
                "name='" + name + '\'' +
                '}';
    }
}
