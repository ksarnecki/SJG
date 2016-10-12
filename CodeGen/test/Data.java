package Iterable;

import java.util.Iterator;
import java.util.ArrayList;
final class User {
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
final class UserArray implements Iterable<User>  {
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
final class IntArray implements Iterable<Integer>  {
  private ArrayList _table;
  public IntArray() {
    this._table = new ArrayList();
  }
  class IntArrayIterator implements Iterator<Integer> {
    int current = 0;
    public boolean hasNext() {
      return current < IntArray.this.Size();
    }
    public Integer next() {
      return IntArray.this.Get(current++);
    }
  }
  public Iterator iterator() {
    return new IntArrayIterator();
  }
  public int Size() {
    return this._table.size();
  }
  public void Insert(int _v) {
    this._table.add(new Integer(_v));
  }
  public int Get(int _ix) {
    return ((Integer) this._table.get(_ix)).intValue();
  }
  public void Delete(int _ix) {
    this._table.remove(_ix);
  }
};
final class StringArray implements Iterable<String>  {
  private ArrayList _table;
  public StringArray() {
    this._table = new ArrayList();
  }
  class ArrayIterator implements Iterator<String> {
    int current = 0;
    public boolean hasNext() {
      return current < StringArray.this.Size();
    }
    public String next() {
      return StringArray.this.Get(current++);
    }
  }
  public Iterator iterator() {
    return new ArrayIterator();
  }
  public int Size() {
    return this._table.size();
  }
  public void Insert(String _v) {
    this._table.add(_v);
  }
  public String Get(int _ix) {
    return (String) this._table.get(_ix);
  }
  public void Delete(int _ix) {
    this._table.remove(_ix);
  }
};

