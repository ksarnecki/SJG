package Iterable;
import java.util.ArrayList;
import java.util.Iterator;
public class IntArray implements Iterable<Integer>  {
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

