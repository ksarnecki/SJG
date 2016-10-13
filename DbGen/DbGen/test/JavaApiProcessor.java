package data;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import data.*;
import mednt.dbconn.DBConn;
import mednt.dbconn.SDBResult;
public class JavaApiProcessor {
  public static int[] convCodegenArray(IntArray array) {
    int[] ret = new int[array.Size()];
    for(int i=0;i<array.Size();i++)
      ret[i] = array.Get(i);
    return ret;
  }
  public static boolean[] convCodegenArray(BoolArray array) {
    boolean[] ret = new boolean[array.Size()];
    for(int i=0;i<array.Size();i++)
      ret[i] = array.Get(i);
    return ret;
  }
  public static String[] convCodegenArray(StringArray array) {
    String[] ret = new String[array.Size()];
    for(int i=0;i<array.Size();i++)
      ret[i] = array.Get(i);
    return ret;
  }
  public static String process(DBConn db, String request) throws Exception {
      ApiQuery query = ApiQuery.fromJSON(request);
      if(query.isSelect()) {
        SelectQuery select = query.asSelect();
        if("getContent".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          string result = GenDb.getContent(db);
          return result.toJSON();
        }
        if("getInns".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntAParam() ) {
          AppInns result = GenDb.getInns(db ,convCodegenArray(select.getParams().Get(0).asIntAParam()));
          return result.toJSON();
        }
        if("getKeywords".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntAParam() ) {
          AppKeywords result = GenDb.getKeywords(db ,convCodegenArray(select.getParams().Get(0).asIntAParam()));
          return result.toJSON();
        }
        if("getCategories".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntAParam() ) {
          AppCategories result = GenDb.getCategories(db ,convCodegenArray(select.getParams().Get(0).asIntAParam()));
          return result.toJSON();
        }
        if("getPictograms".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          AppPictograms result = GenDb.getPictograms(db);
          return result.toJSON();
        }
        if("getPictograms".equals(select.getMethodName()) && select.getParams().Size() == 6 &&  select.getParams().Get(0).isIntParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isStringParam()  &&  select.getParams().Get(3).isIntParam()  &&  select.getParams().Get(4).isIntParam()  &&  select.getParams().Get(5).isIntParam() ) {
          AppPictograms result = GenDb.getPictograms(db ,select.getParams().Get(0).asIntParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asStringParam(), select.getParams().Get(3).asIntParam(), select.getParams().Get(4).asIntParam(), select.getParams().Get(5).asIntParam());
          return result.toJSON();
        }
        if("getPictogramsByInnId".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          AppPictograms result = GenDb.getPictogramsByInnId(db ,select.getParams().Get(0).asIntParam());
          return result.toJSON();
        }
        if("getPictogramsIdsByInnId".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          AppInts result = GenDb.getPictogramsIdsByInnId(db ,select.getParams().Get(0).asIntParam());
          return result.toJSON();
        }
        if("getPictograms".equals(select.getMethodName()) && select.getParams().Size() == 4 &&  select.getParams().Get(0).isStringParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isIntParam()  &&  select.getParams().Get(3).isIntParam() ) {
          AppPictograms result = GenDb.getPictograms(db ,select.getParams().Get(0).asStringParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asIntParam(), select.getParams().Get(3).asIntParam());
          return result.toJSON();
        }
        if("getCategories".equals(select.getMethodName()) && select.getParams().Size() == 5 &&  select.getParams().Get(0).isStringParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isIntParam()  &&  select.getParams().Get(3).isIntParam()  &&  select.getParams().Get(4).isIntParam() ) {
          AppCategories result = GenDb.getCategories(db ,select.getParams().Get(0).asStringParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asIntParam(), select.getParams().Get(3).asIntParam(), select.getParams().Get(4).asIntParam());
          return result.toJSON();
        }
        if("getKeywords".equals(select.getMethodName()) && select.getParams().Size() == 5 &&  select.getParams().Get(0).isStringParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isIntParam()  &&  select.getParams().Get(3).isIntParam()  &&  select.getParams().Get(4).isIntParam() ) {
          AppKeywords result = GenDb.getKeywords(db ,select.getParams().Get(0).asStringParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asIntParam(), select.getParams().Get(3).asIntParam(), select.getParams().Get(4).asIntParam());
          return result.toJSON();
        }
        if("getInns".equals(select.getMethodName()) && select.getParams().Size() == 5 &&  select.getParams().Get(0).isStringParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isIntParam()  &&  select.getParams().Get(3).isIntParam()  &&  select.getParams().Get(4).isIntParam() ) {
          AppInns result = GenDb.getInns(db ,select.getParams().Get(0).asStringParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asIntParam(), select.getParams().Get(3).asIntParam(), select.getParams().Get(4).asIntParam());
          return result.toJSON();
        }
        if("getPictogram".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          AppPictogram result = GenDb.getPictogram(db ,select.getParams().Get(0).asIntParam());
          return result.toJSON();
        }
        if("getCategory".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          AppCategory result = GenDb.getCategory(db ,select.getParams().Get(0).asIntParam());
          return result.toJSON();
        }
        if("getInn".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          AppInn result = GenDb.getInn(db ,select.getParams().Get(0).asIntParam());
          return result.toJSON();
        }
        if("getLastCreatedPictogramId".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          int result = GenDb.getLastCreatedPictogramId(db);
          return result.toJSON();
        }
        if("getLastCreatedCategoryId".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          int result = GenDb.getLastCreatedCategoryId(db);
          return result.toJSON();
        }
        if("getLastCreatedKeywordId".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          int result = GenDb.getLastCreatedKeywordId(db);
          return result.toJSON();
        }
        if("checkIfCategoryExists".equals(select.getMethodName()) && select.getParams().Size() == 2 &&  select.getParams().Get(0).isIntParam()  &&  select.getParams().Get(1).isStringParam() ) {
          int result = GenDb.checkIfCategoryExists(db ,select.getParams().Get(0).asIntParam(), select.getParams().Get(1).asStringParam());
          return result.toJSON();
        }
        if("checkIfKeywordExists".equals(select.getMethodName()) && select.getParams().Size() == 2 &&  select.getParams().Get(0).isIntParam()  &&  select.getParams().Get(1).isStringParam() ) {
          int result = GenDb.checkIfKeywordExists(db ,select.getParams().Get(0).asIntParam(), select.getParams().Get(1).asStringParam());
          return result.toJSON();
        }
        if("addPictogram".equals(select.getMethodName()) && select.getParams().Size() == 4 &&  select.getParams().Get(0).isStringParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isIntParam()  &&  select.getParams().Get(3).isIntParam() ) {
          GenDb.addPictogram(db ,select.getParams().Get(0).asStringParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asIntParam(), select.getParams().Get(3).asIntParam());
          return "";
        }
        if("addCategory".equals(select.getMethodName()) && select.getParams().Size() == 2 &&  select.getParams().Get(0).isStringParam()  &&  select.getParams().Get(1).isStringParam() ) {
          GenDb.addCategory(db ,select.getParams().Get(0).asStringParam(), select.getParams().Get(1).asStringParam());
          return "";
        }
        if("addKeyword".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isStringParam() ) {
          GenDb.addKeyword(db ,select.getParams().Get(0).asStringParam());
          return "";
        }
        if("updatePictogram".equals(select.getMethodName()) && select.getParams().Size() == 5 &&  select.getParams().Get(0).isIntParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isStringParam()  &&  select.getParams().Get(3).isIntParam()  &&  select.getParams().Get(4).isIntParam() ) {
          GenDb.updatePictogram(db ,select.getParams().Get(0).asIntParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asStringParam(), select.getParams().Get(3).asIntParam(), select.getParams().Get(4).asIntParam());
          return "";
        }
        if("updatePictogramStatus".equals(select.getMethodName()) && select.getParams().Size() == 2 &&  select.getParams().Get(0).isIntParam()  &&  select.getParams().Get(1).isIntParam() ) {
          GenDb.updatePictogramStatus(db ,select.getParams().Get(0).asIntParam(), select.getParams().Get(1).asIntParam());
          return "";
        }
        if("updatePictogramsModifiedTime".equals(select.getMethodName()) && select.getParams().Size() == 2 &&  select.getParams().Get(0).isStringParam()  &&  select.getParams().Get(1).isStringParam() ) {
          GenDb.updatePictogramsModifiedTime(db ,select.getParams().Get(0).asStringParam(), select.getParams().Get(1).asStringParam());
          return "";
        }
        if("updateCategory".equals(select.getMethodName()) && select.getParams().Size() == 3 &&  select.getParams().Get(0).isIntParam()  &&  select.getParams().Get(1).isStringParam()  &&  select.getParams().Get(2).isStringParam() ) {
          GenDb.updateCategory(db ,select.getParams().Get(0).asIntParam(), select.getParams().Get(1).asStringParam(), select.getParams().Get(2).asStringParam());
          return "";
        }
        if("updateKeyword".equals(select.getMethodName()) && select.getParams().Size() == 2 &&  select.getParams().Get(0).isIntParam()  &&  select.getParams().Get(1).isStringParam() ) {
          GenDb.updateKeyword(db ,select.getParams().Get(0).asIntParam(), select.getParams().Get(1).asStringParam());
          return "";
        }
        if("addPictogramCategories".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isStringParam() ) {
          GenDb.addPictogramCategories(db ,select.getParams().Get(0).asStringParam());
          return "";
        }
        if("addPictogramInns".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isStringParam() ) {
          GenDb.addPictogramInns(db ,select.getParams().Get(0).asStringParam());
          return "";
        }
        if("addPictogramKeywords".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isStringParam() ) {
          GenDb.addPictogramKeywords(db ,select.getParams().Get(0).asStringParam());
          return "";
        }
        if("deletePictogramCategories".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deletePictogramCategories(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deletePictogramInns".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deletePictogramInns(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deletePictogramInnsByInnId".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deletePictogramInnsByInnId(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deletePictogramKeywords".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deletePictogramKeywords(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deletePictogram".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deletePictogram(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deleteCategories".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deleteCategories(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deletePictureCategoriesByCategoryId".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deletePictureCategoriesByCategoryId(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deleteKeywords".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deleteKeywords(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("deletePictureKeywordsByKeywordId".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          GenDb.deletePictureKeywordsByKeywordId(db ,select.getParams().Get(0).asIntParam());
          return "";
        }
        if("getPriorities".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          AppPriorities result = GenDb.getPriorities(db);
          return result.toJSON();
        }
        if("countPictogramsByStateId".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isIntParam() ) {
          int result = GenDb.countPictogramsByStateId(db ,select.getParams().Get(0).asIntParam());
          return result.toJSON();
        }
        if("countPictograms".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          int result = GenDb.countPictograms(db);
          return result.toJSON();
        }
        if("countCategories".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          int result = GenDb.countCategories(db);
          return result.toJSON();
        }
        if("countKeywords".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          int result = GenDb.countKeywords(db);
          return result.toJSON();
        }
        if("countInns".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          int result = GenDb.countInns(db);
          return result.toJSON();
        }
        if("getLastUpdate".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          string result = GenDb.getLastUpdate(db);
          return result.toJSON();
        }
        if("setLastUpdate".equals(select.getMethodName()) && select.getParams().Size() == 0) {
          GenDb.setLastUpdate(db);
          return "";
        }
        if("setLastUpdate".equals(select.getMethodName()) && select.getParams().Size() == 1 &&  select.getParams().Get(0).isStringParam() ) {
          GenDb.setLastUpdate(db ,select.getParams().Get(0).asStringParam());
          return "";
        }
      }
    throw new Exception("bad request");
  }
};
