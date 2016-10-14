public interface DBGenCommonI {
  static String boxI(int[] ints) ;
  static String boxS(DBConn db, String[] strs);
  static String prepare(String sql, HashMap<String, String> pmap);
}