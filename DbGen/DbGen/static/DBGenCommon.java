public class DBGenCommon implements DBGenCommonI {
  static public String box(int[] ints) {
    StringBuffer buf = new StringBuffer();
    for (int i=0;i<ints.length;i++)
    buf.append(((i==0) ? "" : ",") + ints[i]);
    return buf.toString();
  }
  static public String box(DBConn db, String[] strs) {
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
  static public String prepare(String sql, HashMap<String, String> pmap) {
    for (Map.Entry<String, String> e : pmap.entrySet())
      sql = sql.replaceAll("%\\["+e.getKey()+"]", e.getValue());
    return sql;
  }
}