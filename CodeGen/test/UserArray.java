package Iterable;
import java.util.ArrayList;
import java.util.Iterator;
public class UserArray implements Iterable<User>  {
  private ArrayList _table;
  public UserArray() {
    this._table = new ArrayList();
  }
  class ArrayIterator implements Iterator<User> {
    int current = 0;
    public boolean hasNext() {
      return current < UserArray.this.Size();
    }
    public User next() {
      return UserArray.this.Get(current++);
    }
  }
  public Iterator iterator() {
    return new ArrayIterator();
  }
  public int Size() {
    return this._table.size();
  }
  public void Insert(User _v) {
    this._table.add(_v);
  }
  public User Get(int _ix) {
    return (User) this._table.get(_ix);
  }
  public void Delete(int _ix) {
    this._table.remove(_ix);
  }
};

