package Iterable;
import java.util.Iterator;
public class User {
  private int id;
  private String email;
  public User( int _id,  String _email) {
    this.id = _id;
    this.email = _email;
  }
  public int getId() {
    return this.id;
  }
  public void setId(int _v) {
    this.id = _v;
  }
  public String getEmail() {
    return this.email;
  }
  public void setEmail(String _v) {
    this.email = _v;
  }
};

