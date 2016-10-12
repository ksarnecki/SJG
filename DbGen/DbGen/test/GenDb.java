package mednt.lekolepki.db;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import mednt.dbconn.DBConn;
import mednt.dbconn.SDBResult;
import mednt.lekolepki.model;
public class GenDb {
  static String box(int[] ints) {
    StringBuffer buf = new StringBuffer();
    for (int i=0;i<ints.length;i++)
    buf.append(((i==0) ? "" : ",") + ints[i]);
    return buf.toString();
  }
  static String box(DBConn db, String[] strs) {
    StringBuffer buf = new StringBuffer();
    for (int i=0;i<strs.length;i++) {
    if (i!=0)
      buf.append(',');
    buf.append("'");
    buf.append(db.escape(strs[i]));
    buf.append("'");
    }
    return buf.toString();
  }
  private static String prepare(String sql, HashMap<String, String> pmap) {
    for (Map.Entry<String, String> e : pmap.entrySet())
      sql = sql.replaceAll("%\\["+e.getKey()+"]", e.getValue());
    return sql;
  }
  static public String getContent(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT now()", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("getContent - result not found");
    String _ret =_res.s(0, 0);
    return _ret;
  }
  static public AppInns getInns(DBConn _db, int[] pictureIds) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("pictureIds", "" + GenDb.box(pictureIds));
    SDBResult _res = _db.query(GenDb.prepare("SELECT i.id, i.name_pl, i.name_eng, i.name_latin, ip.picture_id FROM nw_ll_inn i LEFT JOIN ll_inn_picture ip ON ip.inn_id=i.id WHERE ip.picture_id IN (%[pictureIds]) AND (i.name_pl NOT LIKE '' OR i.name_eng NOT LIKE '' OR i.name_latin NOT LIKE '') ORDER BY i.name_pl;", _pmap));
    AppInns _ret = new AppInns();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppInn(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.s(i, 3),_res.i(i, 4)));
    return _ret;
  }
  static public AppKeywords getKeywords(DBConn _db, int[] pictureIds) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("pictureIds", "" + GenDb.box(pictureIds));
    SDBResult _res = _db.query(GenDb.prepare("SELECT kw.id, kw.name, kwp.picture_id FROM ll_keyword kw LEFT JOIN ll_keyword_picture kwp ON kwp.keyword_id=kw.id WHERE kwp.picture_id IN (%[pictureIds]) ORDER BY name;", _pmap));
    AppKeywords _ret = new AppKeywords();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppKeyword(_res.i(i, 0),_res.s(i, 1),_res.i(i, 2)));
    return _ret;
  }
  static public AppCategories getCategories(DBConn _db, int[] pictureIds) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("pictureIds", "" + GenDb.box(pictureIds));
    SDBResult _res = _db.query(GenDb.prepare("SELECT c.id, c.name, c.descr, cp.picture_id FROM ll_category c LEFT JOIN ll_category_picture cp ON cp.category_id=c.id WHERE cp.picture_id IN (%[pictureIds]) ORDER BY name;", _pmap));
    AppCategories _ret = new AppCategories();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppCategory(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.i(i, 3)));
    return _ret;
  }
  static public AppPictograms getPictograms(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT p.id, p.descr, p.created, p.modified, (p.state_id=1), pp.id, pp.val, pp.name, p.code FROM ll_picture p LEFT JOIN ll_picture_priority pp ON pp.id = p.priority_id", _pmap));
    if(_res.rows()==0)
      return new AppPictograms();
    int[] getCategoriesobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getCategoriesobj0[i]= _res.i(i, 0);
    AppCategories arr0 =getCategories(_db ,getCategoriesobj0);
    HashMap<Integer, AppCategories> hmap0 = new HashMap<Integer, AppCategories>();
    for (int i=0;i<arr0.Size();i++) {
      AppCategories s = hmap0.get(arr0.Get(i).getPictureId());
      if(s == null)
      s = new AppCategories();
      s.Insert(arr0.Get(i));
      hmap0.put(arr0.Get(i).getPictureId(), s);
    }
    int[] getKeywordsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getKeywordsobj0[i]= _res.i(i, 0);
    AppKeywords arr1 =getKeywords(_db ,getKeywordsobj0);
    HashMap<Integer, AppKeywords> hmap1 = new HashMap<Integer, AppKeywords>();
    for (int i=0;i<arr1.Size();i++) {
      AppKeywords s = hmap1.get(arr1.Get(i).getPictureId());
      if(s == null)
      s = new AppKeywords();
      s.Insert(arr1.Get(i));
      hmap1.put(arr1.Get(i).getPictureId(), s);
    }
    int[] getInnsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getInnsobj0[i]= _res.i(i, 0);
    AppInns arr2 =getInns(_db ,getInnsobj0);
    HashMap<Integer, AppInns> hmap2 = new HashMap<Integer, AppInns>();
    for (int i=0;i<arr2.Size();i++) {
      AppInns s = hmap2.get(arr2.Get(i).getPictureId());
      if(s == null)
      s = new AppInns();
      s.Insert(arr2.Get(i));
      hmap2.put(arr2.Get(i).getPictureId(), s);
    }
    AppPictograms _ret = new AppPictograms();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppPictogram(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.s(i, 3),_res.i(i, 4) == 1,new AppPriority(_res.i(i, 5),_res.i(i, 6),_res.s(i, 7)),_res.s(i, 8),hmap0.get(_res.i(i,0)) != null ? hmap0.get(_res.i(i,0)) : new AppCategories(),hmap1.get(_res.i(i,0)) != null ? hmap1.get(_res.i(i,0)) : new AppKeywords(),hmap2.get(_res.i(i,0)) != null ? hmap2.get(_res.i(i,0)) : new AppInns()));
    return _ret;
  }
  static public AppPictograms getPictograms(DBConn _db, int categoryId, String descrPattern, String innPattern, int limit, int offset, int sortTypeId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("categoryId", "" + categoryId);
    _pmap.put("descrPattern", "" + _db.escape(descrPattern));
    _pmap.put("innPattern", "" + _db.escape(innPattern));
    _pmap.put("limit", "" + limit);
    _pmap.put("offset", "" + offset);
    _pmap.put("sortTypeId", "" + sortTypeId);
    SDBResult _res = _db.query(GenDb.prepare("SELECT p.id, p.descr, p.created, p.modified, (p.state_id=1), pp.id, pp.val, pp.name, p.code FROM ll_picture p LEFT JOIN ll_picture_priority pp ON pp.id = p.priority_id LEFT JOIN ll_category_picture cp ON cp.picture_id=p.id LEFT JOIN ll_category c ON c.id=cp.category_id LEFT JOIN ll_inn_picture ip ON ip.picture_id=p.id LEFT JOIN nw_ll_inn i ON i.id=ip.inn_id WHERE CASE WHEN %[categoryId]<>0 THEN c.id=%[categoryId] ELSE 1=1 END AND CASE WHEN '%[descrPattern]' NOT LIKE '' THEN p.descr LIKE '%[descrPattern]%' OR p.descr LIKE '% %[descrPattern]%' ELSE 1=1 END AND CASE WHEN '%[innPattern]' NOT LIKE '' THEN i.name_pl LIKE '%[innPattern]%' OR i.name_pl LIKE '% %[innPattern]%' OR i.name_eng LIKE '%[innPattern]%' OR i.name_eng LIKE '% %[innPattern]%' OR i.name_latin LIKE '%[innPattern]%' OR i.name_latin LIKE '% %[innPattern]%' ELSE 1=1 END GROUP BY p.id ORDER BY CASE WHEN %[sortTypeId]=1 THEN p.descr END ASC, CASE WHEN %[sortTypeId]=2 THEN p.descr END DESC, CASE WHEN %[sortTypeId]=3 THEN p.created END ASC, CASE WHEN %[sortTypeId]=4 THEN p.created END DESC, CASE WHEN %[sortTypeId]=5 THEN p.modified END ASC, CASE WHEN %[sortTypeId]=6 THEN p.modified END DESC LIMIT %[limit] OFFSET %[offset];", _pmap));
    if(_res.rows()==0)
      return new AppPictograms();
    int[] getCategoriesobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getCategoriesobj0[i]= _res.i(i, 0);
    AppCategories arr0 =getCategories(_db ,getCategoriesobj0);
    HashMap<Integer, AppCategories> hmap0 = new HashMap<Integer, AppCategories>();
    for (int i=0;i<arr0.Size();i++) {
      AppCategories s = hmap0.get(arr0.Get(i).getPictureId());
      if(s == null)
      s = new AppCategories();
      s.Insert(arr0.Get(i));
      hmap0.put(arr0.Get(i).getPictureId(), s);
    }
    int[] getKeywordsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getKeywordsobj0[i]= _res.i(i, 0);
    AppKeywords arr1 =getKeywords(_db ,getKeywordsobj0);
    HashMap<Integer, AppKeywords> hmap1 = new HashMap<Integer, AppKeywords>();
    for (int i=0;i<arr1.Size();i++) {
      AppKeywords s = hmap1.get(arr1.Get(i).getPictureId());
      if(s == null)
      s = new AppKeywords();
      s.Insert(arr1.Get(i));
      hmap1.put(arr1.Get(i).getPictureId(), s);
    }
    int[] getInnsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getInnsobj0[i]= _res.i(i, 0);
    AppInns arr2 =getInns(_db ,getInnsobj0);
    HashMap<Integer, AppInns> hmap2 = new HashMap<Integer, AppInns>();
    for (int i=0;i<arr2.Size();i++) {
      AppInns s = hmap2.get(arr2.Get(i).getPictureId());
      if(s == null)
      s = new AppInns();
      s.Insert(arr2.Get(i));
      hmap2.put(arr2.Get(i).getPictureId(), s);
    }
    AppPictograms _ret = new AppPictograms();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppPictogram(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.s(i, 3),_res.i(i, 4) == 1,new AppPriority(_res.i(i, 5),_res.i(i, 6),_res.s(i, 7)),_res.s(i, 8),hmap0.get(_res.i(i,0)) != null ? hmap0.get(_res.i(i,0)) : new AppCategories(),hmap1.get(_res.i(i,0)) != null ? hmap1.get(_res.i(i,0)) : new AppKeywords(),hmap2.get(_res.i(i,0)) != null ? hmap2.get(_res.i(i,0)) : new AppInns()));
    return _ret;
  }
  static public AppPictograms getPictogramsByInnId(DBConn _db, int innId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("innId", "" + innId);
    SDBResult _res = _db.query(GenDb.prepare("SELECT p.id, p.descr, p.created, p.modified, (p.state_id=1), pp.id, pp.val, pp.name, p.code FROM ll_picture p LEFT JOIN ll_picture_priority pp ON pp.id = p.priority_id LEFT JOIN ll_inn_picture ip ON ip.picture_id=p.id LEFT JOIN nw_ll_inn i ON i.id=ip.inn_id WHERE i.id=%[innId] GROUP BY p.id", _pmap));
    if(_res.rows()==0)
      return new AppPictograms();
    int[] getCategoriesobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getCategoriesobj0[i]= _res.i(i, 0);
    AppCategories arr0 =getCategories(_db ,getCategoriesobj0);
    HashMap<Integer, AppCategories> hmap0 = new HashMap<Integer, AppCategories>();
    for (int i=0;i<arr0.Size();i++) {
      AppCategories s = hmap0.get(arr0.Get(i).getPictureId());
      if(s == null)
      s = new AppCategories();
      s.Insert(arr0.Get(i));
      hmap0.put(arr0.Get(i).getPictureId(), s);
    }
    int[] getKeywordsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getKeywordsobj0[i]= _res.i(i, 0);
    AppKeywords arr1 =getKeywords(_db ,getKeywordsobj0);
    HashMap<Integer, AppKeywords> hmap1 = new HashMap<Integer, AppKeywords>();
    for (int i=0;i<arr1.Size();i++) {
      AppKeywords s = hmap1.get(arr1.Get(i).getPictureId());
      if(s == null)
      s = new AppKeywords();
      s.Insert(arr1.Get(i));
      hmap1.put(arr1.Get(i).getPictureId(), s);
    }
    int[] getInnsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getInnsobj0[i]= _res.i(i, 0);
    AppInns arr2 =getInns(_db ,getInnsobj0);
    HashMap<Integer, AppInns> hmap2 = new HashMap<Integer, AppInns>();
    for (int i=0;i<arr2.Size();i++) {
      AppInns s = hmap2.get(arr2.Get(i).getPictureId());
      if(s == null)
      s = new AppInns();
      s.Insert(arr2.Get(i));
      hmap2.put(arr2.Get(i).getPictureId(), s);
    }
    AppPictograms _ret = new AppPictograms();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppPictogram(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.s(i, 3),_res.i(i, 4) == 1,new AppPriority(_res.i(i, 5),_res.i(i, 6),_res.s(i, 7)),_res.s(i, 8),hmap0.get(_res.i(i,0)) != null ? hmap0.get(_res.i(i,0)) : new AppCategories(),hmap1.get(_res.i(i,0)) != null ? hmap1.get(_res.i(i,0)) : new AppKeywords(),hmap2.get(_res.i(i,0)) != null ? hmap2.get(_res.i(i,0)) : new AppInns()));
    return _ret;
  }
  static public AppInts getPictogramsIdsByInnId(DBConn _db, int innId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("innId", "" + innId);
    SDBResult _res = _db.query(GenDb.prepare("SELECT p.id FROM ll_picture p LEFT JOIN ll_inn_picture ip ON ip.picture_id=p.id LEFT JOIN nw_ll_inn i ON i.id=ip.inn_id WHERE i.id=%[innId] GROUP BY p.id", _pmap));
    AppInts _ret = new AppInts();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(_res.i(i,0));
    return _ret;
  }
  static public AppPictograms getPictograms(DBConn _db, String pattern, String skipIds, int limit, int offset) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("pattern", "" + _db.escape(pattern));
    _pmap.put("skipIds", "" + _db.escape(skipIds));
    _pmap.put("limit", "" + limit);
    _pmap.put("offset", "" + offset);
    SDBResult _res = _db.query(GenDb.prepare("SELECT p.id, p.descr, p.created, p.modified, (p.state_id=1), pp.id, pp.val, pp.name, p.code FROM ll_picture p LEFT JOIN ll_picture_priority pp ON pp.id = p.priority_id WHERE p.id NOT IN(%[skipIds]) AND (p.descr LIKE '%[pattern]%' OR p.descr LIKE '% %[pattern]%') GROUP BY p.id ORDER BY p.descr ASC LIMIT %[limit] OFFSET %[offset];", _pmap));
    if(_res.rows()==0)
      return new AppPictograms();
    int[] getCategoriesobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getCategoriesobj0[i]= _res.i(i, 0);
    AppCategories arr0 =getCategories(_db ,getCategoriesobj0);
    HashMap<Integer, AppCategories> hmap0 = new HashMap<Integer, AppCategories>();
    for (int i=0;i<arr0.Size();i++) {
      AppCategories s = hmap0.get(arr0.Get(i).getPictureId());
      if(s == null)
      s = new AppCategories();
      s.Insert(arr0.Get(i));
      hmap0.put(arr0.Get(i).getPictureId(), s);
    }
    int[] getKeywordsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getKeywordsobj0[i]= _res.i(i, 0);
    AppKeywords arr1 =getKeywords(_db ,getKeywordsobj0);
    HashMap<Integer, AppKeywords> hmap1 = new HashMap<Integer, AppKeywords>();
    for (int i=0;i<arr1.Size();i++) {
      AppKeywords s = hmap1.get(arr1.Get(i).getPictureId());
      if(s == null)
      s = new AppKeywords();
      s.Insert(arr1.Get(i));
      hmap1.put(arr1.Get(i).getPictureId(), s);
    }
    int[] getInnsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getInnsobj0[i]= _res.i(i, 0);
    AppInns arr2 =getInns(_db ,getInnsobj0);
    HashMap<Integer, AppInns> hmap2 = new HashMap<Integer, AppInns>();
    for (int i=0;i<arr2.Size();i++) {
      AppInns s = hmap2.get(arr2.Get(i).getPictureId());
      if(s == null)
      s = new AppInns();
      s.Insert(arr2.Get(i));
      hmap2.put(arr2.Get(i).getPictureId(), s);
    }
    AppPictograms _ret = new AppPictograms();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppPictogram(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.s(i, 3),_res.i(i, 4) == 1,new AppPriority(_res.i(i, 5),_res.i(i, 6),_res.s(i, 7)),_res.s(i, 8),hmap0.get(_res.i(i,0)) != null ? hmap0.get(_res.i(i,0)) : new AppCategories(),hmap1.get(_res.i(i,0)) != null ? hmap1.get(_res.i(i,0)) : new AppKeywords(),hmap2.get(_res.i(i,0)) != null ? hmap2.get(_res.i(i,0)) : new AppInns()));
    return _ret;
  }
  static public AppCategories getCategories(DBConn _db, String pattern, String skipIds, int limit, int offset, int sortTypeId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("pattern", "" + _db.escape(pattern));
    _pmap.put("skipIds", "" + _db.escape(skipIds));
    _pmap.put("limit", "" + limit);
    _pmap.put("offset", "" + offset);
    _pmap.put("sortTypeId", "" + sortTypeId);
    SDBResult _res = _db.query(GenDb.prepare("SELECT id, name, descr, -1 FROM ll_category WHERE id NOT IN(%[skipIds]) AND (name LIKE '%[pattern]%' OR name LIKE '% %[pattern]%' OR descr LIKE '%[pattern]%' OR descr LIKE '% %[pattern]%') ORDER BY CASE WHEN %[sortTypeId]=1 THEN name END ASC, CASE WHEN %[sortTypeId]=2 THEN name END DESC, CASE WHEN %[sortTypeId]=3 THEN id END ASC, CASE WHEN %[sortTypeId]=4 THEN id END DESC LIMIT %[limit] OFFSET %[offset];", _pmap));
    AppCategories _ret = new AppCategories();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppCategory(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.i(i, 3)));
    return _ret;
  }
  static public AppKeywords getKeywords(DBConn _db, String pattern, String skipIds, int limit, int offset, int sortTypeId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("pattern", "" + _db.escape(pattern));
    _pmap.put("skipIds", "" + _db.escape(skipIds));
    _pmap.put("limit", "" + limit);
    _pmap.put("offset", "" + offset);
    _pmap.put("sortTypeId", "" + sortTypeId);
    SDBResult _res = _db.query(GenDb.prepare("SELECT id, name, -1 FROM ll_keyword WHERE id NOT IN(%[skipIds]) AND (name LIKE '%[pattern]%' OR name LIKE '% %[pattern]%') ORDER BY CASE WHEN %[sortTypeId]=1 THEN name END ASC, CASE WHEN %[sortTypeId]=2 THEN name END DESC, CASE WHEN %[sortTypeId]=3 THEN id END ASC, CASE WHEN %[sortTypeId]=4 THEN id END DESC LIMIT %[limit] OFFSET %[offset];", _pmap));
    AppKeywords _ret = new AppKeywords();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppKeyword(_res.i(i, 0),_res.s(i, 1),_res.i(i, 2)));
    return _ret;
  }
  static public AppInns getInns(DBConn _db, String pattern, String skipIds, int limit, int offset, int sortTypeId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("pattern", "" + _db.escape(pattern));
    _pmap.put("skipIds", "" + _db.escape(skipIds));
    _pmap.put("limit", "" + limit);
    _pmap.put("offset", "" + offset);
    _pmap.put("sortTypeId", "" + sortTypeId);
    SDBResult _res = _db.query(GenDb.prepare("SELECT id, name_pl, name_eng, name_latin, -1 FROM nw_ll_inn WHERE id NOT IN(%[skipIds]) AND (name_pl LIKE '%[pattern]%' OR name_eng LIKE '%[pattern]%' OR name_latin LIKE '%[pattern]%') AND (name_pl NOT LIKE '' OR name_eng NOT LIKE '' OR name_latin NOT LIKE '') ORDER BY CASE WHEN %[sortTypeId]=1 THEN COALESCE(NULLIF(name_eng, ''), NULLIF(name_pl, ''), NULLIF(name_latin, '')) END ASC, CASE WHEN %[sortTypeId]=2 THEN COALESCE(NULLIF(name_eng, ''), NULLIF(name_pl, ''), NULLIF(name_latin, '')) END DESC LIMIT %[limit] OFFSET %[offset];", _pmap));
    AppInns _ret = new AppInns();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppInn(_res.i(i, 0),_res.s(i, 1),_res.s(i, 2),_res.s(i, 3),_res.i(i, 4)));
    return _ret;
  }
  static public AppPictogram getPictogram(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    SDBResult _res = _db.query(GenDb.prepare("SELECT p.id, p.descr, p.created, p.modified, (p.state_id=1), pp.id, pp.val, pp.name, p.code FROM ll_picture p LEFT JOIN ll_picture_priority pp ON pp.id = p.priority_id WHERE p.id=%[id]", _pmap));
    int[] getCategoriesobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getCategoriesobj0[i]= _res.i(i, 0);
    AppCategories arr0 =getCategories(_db ,getCategoriesobj0);
    int[] getKeywordsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getKeywordsobj0[i]= _res.i(i, 0);
    AppKeywords arr1 =getKeywords(_db ,getKeywordsobj0);
    int[] getInnsobj0 = new int[_res.rows()];
    for (int i=0;i<_res.rows();i++)
      getInnsobj0[i]= _res.i(i, 0);
    AppInns arr2 =getInns(_db ,getInnsobj0);
    if (_res.rows()<1)
      throw new RuntimeException("getPictogram - result not found");
    AppPictogram _ret = new AppPictogram(_res.i(0, 0),_res.s(0, 1),_res.s(0, 2),_res.s(0, 3),_res.i(0, 4) == 1,new AppPriority(_res.i(0, 5),_res.i(0, 6),_res.s(0, 7)),_res.s(0, 8),arr0,arr1,arr2);
    return _ret;
  }
  static public AppCategory getCategory(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    SDBResult _res = _db.query(GenDb.prepare("SELECT id, name, descr, -1 FROM ll_category WHERE id=%[id] LIMIT 1", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("getCategory - result not found");
    AppCategory _ret = new AppCategory(_res.i(0, 0),_res.s(0, 1),_res.s(0, 2),_res.i(0, 3));
    return _ret;
  }
  static public AppInn getInn(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    SDBResult _res = _db.query(GenDb.prepare("SELECT id, name_pl, name_eng, name_latin, -1 FROM nw_ll_inn WHERE id=%[id] LIMIT 1", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("getInn - result not found");
    AppInn _ret = new AppInn(_res.i(0, 0),_res.s(0, 1),_res.s(0, 2),_res.s(0, 3),_res.i(0, 4));
    return _ret;
  }
  static public int getLastCreatedPictogramId(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT id FROM ll_picture ORDER BY created DESC LIMIT 1", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("getLastCreatedPictogramId - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int getLastCreatedCategoryId(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT id FROM ll_category ORDER BY id DESC LIMIT 1", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("getLastCreatedCategoryId - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int getLastCreatedKeywordId(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT id FROM ll_keyword ORDER BY id DESC LIMIT 1", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("getLastCreatedKeywordId - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int checkIfCategoryExists(DBConn _db, int id, String name) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _pmap.put("name", "" + _db.escape(name));
    SDBResult _res = _db.query(GenDb.prepare("SELECT COUNT(id) FROM ll_category WHERE id != %[id] AND name LIKE BINARY '%[name]' LIMIT 1", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("checkIfCategoryExists - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int checkIfKeywordExists(DBConn _db, int id, String name) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _pmap.put("name", "" + _db.escape(name));
    SDBResult _res = _db.query(GenDb.prepare("SELECT COUNT(id) FROM ll_keyword WHERE id != %[id] AND name LIKE BINARY '%[name]' LIMIT 1", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("checkIfKeywordExists - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public void addPictogram(DBConn _db, String code, String descr, int stateId, int priorityId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("code", "" + _db.escape(code));
    _pmap.put("descr", "" + _db.escape(descr));
    _pmap.put("stateId", "" + stateId);
    _pmap.put("priorityId", "" + priorityId);
    _db.execute(GenDb.prepare("INSERT INTO ll_picture(code, descr, created, modified, state_id, priority_id) VALUES ('%[code]', '%[descr]', now(), now(), %[stateId], %[priorityId]);", _pmap));
  }
  static public void addCategory(DBConn _db, String name, String descr) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("name", "" + _db.escape(name));
    _pmap.put("descr", "" + _db.escape(descr));
    _db.execute(GenDb.prepare("INSERT INTO ll_category(name, descr) VALUES('%[name]', '%[descr]');", _pmap));
  }
  static public void addKeyword(DBConn _db, String name) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("name", "" + _db.escape(name));
    _db.execute(GenDb.prepare("INSERT INTO ll_keyword(name) VALUES ('%[name]');", _pmap));
  }
  static public void updatePictogram(DBConn _db, int id, String code, String descr, int stateId, int priorityId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _pmap.put("code", "" + _db.escape(code));
    _pmap.put("descr", "" + _db.escape(descr));
    _pmap.put("stateId", "" + stateId);
    _pmap.put("priorityId", "" + priorityId);
    _db.execute(GenDb.prepare("UPDATE ll_picture SET code='%[code]', descr='%[descr]', modified=now(), state_id=%[stateId], priority_id=%[priorityId] WHERE id=%[id];", _pmap));
  }
  static public void updatePictogramStatus(DBConn _db, int id, int stateId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _pmap.put("stateId", "" + stateId);
    _db.execute(GenDb.prepare("UPDATE ll_picture SET state_id=%[stateId], modified=now() WHERE id=%[id];", _pmap));
  }
  static public void updatePictogramsModifiedTime(DBConn _db, String currPics, String leftPics) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("currPics", "" + _db.escape(currPics));
    _pmap.put("leftPics", "" + _db.escape(leftPics));
    _db.execute(GenDb.prepare("UPDATE ll_picture SET modified=now() WHERE (id IN (%[currPics]) AND id NOT IN (%[leftPics])) OR (id NOT IN (%[currPics]) AND id IN (%[leftPics]));", _pmap));
  }
  static public void updateCategory(DBConn _db, int id, String name, String descr) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _pmap.put("name", "" + _db.escape(name));
    _pmap.put("descr", "" + _db.escape(descr));
    _db.execute(GenDb.prepare("UPDATE ll_category SET name='%[name]', descr='%[descr]' WHERE id=%[id];", _pmap));
  }
  static public void updateKeyword(DBConn _db, int id, String name) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _pmap.put("name", "" + _db.escape(name));
    _db.execute(GenDb.prepare("UPDATE ll_keyword SET name='%[name]' WHERE id=%[id];", _pmap));
  }
  static public void addPictogramCategories(DBConn _db, String values) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("values", "" + _db.escape(values));
    _db.execute(GenDb.prepare("INSERT INTO ll_category_picture(picture_id, category_id) VALUES %[values]", _pmap));
  }
  static public void addPictogramInns(DBConn _db, String values) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("values", "" + _db.escape(values));
    _db.execute(GenDb.prepare("INSERT INTO ll_inn_picture(picture_id, inn_id) VALUES %[values]", _pmap));
  }
  static public void addPictogramKeywords(DBConn _db, String values) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("values", "" + _db.escape(values));
    _db.execute(GenDb.prepare("INSERT INTO ll_keyword_picture(picture_id, keyword_id) VALUES %[values]", _pmap));
  }
  static public void deletePictogramCategories(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_category_picture WHERE picture_id=%[id];", _pmap));
  }
  static public void deletePictogramInns(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_inn_picture WHERE picture_id=%[id];", _pmap));
  }
  static public void deletePictogramInnsByInnId(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_inn_picture WHERE inn_id=%[id];", _pmap));
  }
  static public void deletePictogramKeywords(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_keyword_picture WHERE picture_id=%[id];", _pmap));
  }
  static public void deletePictogram(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_picture WHERE id=%[id];", _pmap));
  }
  static public void deleteCategories(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_category WHERE id=%[id];", _pmap));
  }
  static public void deletePictureCategoriesByCategoryId(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_category_picture WHERE category_id=%[id];", _pmap));
  }
  static public void deleteKeywords(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_keyword WHERE id=%[id];", _pmap));
  }
  static public void deletePictureKeywordsByKeywordId(DBConn _db, int id) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("id", "" + id);
    _db.execute(GenDb.prepare("DELETE FROM ll_keyword_picture WHERE keyword_id=%[id];", _pmap));
  }
  static public AppPriorities getPriorities(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT id, val, name FROM ll_picture_priority ORDER BY val;", _pmap));
    AppPriorities _ret = new AppPriorities();
    for (int i=0;i<_res.rows();i++)
      _ret.Insert(new AppPriority(_res.i(i, 0),_res.i(i, 1),_res.s(i, 2)));
    return _ret;
  }
  static public int countPictogramsByStateId(DBConn _db, int stateId) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("stateId", "" + stateId);
    SDBResult _res = _db.query(GenDb.prepare("SELECT COUNT(*) FROM ll_picture WHERE state_id=%[stateId];", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("countPictogramsByStateId - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int countPictograms(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT COUNT(*) FROM ll_picture", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("countPictograms - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int countCategories(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT COUNT(*) FROM ll_category", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("countCategories - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int countKeywords(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT COUNT(*) FROM ll_keyword", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("countKeywords - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public int countInns(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT COUNT(*) FROM nw_ll_inn WHERE name_pl NOT LIKE '' OR name_eng NOT LIKE '' OR name_latin NOT LIKE ''", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("countInns - result not found");
    int _ret =_res.i(0, 0);
    return _ret;
  }
  static public String getLastUpdate(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    SDBResult _res = _db.query(GenDb.prepare("SELECT FROM_UNIXTIME(val) FROM ll_cfg WHERE key_kind LIKE 'data_version'", _pmap));
    if (_res.rows()<1)
      throw new RuntimeException("getLastUpdate - result not found");
    String _ret =_res.s(0, 0);
    return _ret;
  }
  static public void setLastUpdate(DBConn _db) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _db.execute(GenDb.prepare("UPDATE ll_cfg SET val=UNIX_TIMESTAMP(now()) WHERE key_kind LIKE 'data_version'", _pmap));
  }
  static public void setLastUpdate(DBConn _db, String value) {
    HashMap<String, String> _pmap = new HashMap<String, String>();
    _pmap.put("value", "" + _db.escape(value));
    _db.execute(GenDb.prepare("UPDATE ll_cfg SET val=%[value] WHERE key_kind LIKE 'data_version'", _pmap));
  }
};
