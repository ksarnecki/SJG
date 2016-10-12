package Iterable;
import java.util.ArrayList;
import java.util.Iterator;
public class StringArray implements Iterable<String>  {
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

